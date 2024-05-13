#include "GameMap.h"
#include "InputManager.h"
#include "Snake.h"
#include "ItemManager.h"
#include <ncurses.h>

#define TICKSPEED 3 // tick per second
#define MAXSTAGE 5 // 최대 스테이지 수

using namespace std;

unsigned int tick; // 시간 경과 기록 (앞서 설정한 tick 단위)
int stage{1}; // 현재 스테이지
bool isOver{false}; // 게임 오버 여부 check
bool isClear{false}; // 스테이지 클리어 여부 check
WINDOW *scoreboard, *missionboard;

int snakeGame();

WINDOW* initBoard(int y, int x); // 메인 맵과 겹치지 않도록 좌표 y, x에 스코어보드를 관리할 window 객체 생성

void printScoreboard(int curlen, int maxlen, int growcount, int poisoncount, int tick); // 스코어보드 출력
void printMissionboard();

int main(int agrc, char *argv[]) {
    // Strat()
    initscr();
    noecho();
    nodelay(stdscr, true);
    keypad(stdscr, true);
    start_color();
    curs_set(0);
    
    // Update()
    while (1) {
        int x = snakeGame();
        if (x == -1) break;
    }

    endwin();
}

int snakeGame() {
    // Start()
    tick = 0;
    InputManager key_input;
    GameMap map{stage};
    Snake snake{{map.ySize() / 2, map.xSize() / 2}, SNAKE_DEFAULT}; // 스네이크 객체
    vector<pair<int, bool>> missions(5); // 미션들을 관리하는 벡터
    
    scoreboard = initBoard(2, (map.xSize() + 1) * 4);
    missionboard = initBoard(11, (map.xSize() + 1) * 4);
    wbkgd(scoreboard, COLOR_PAIR(1));
    wbkgd(missionboard, COLOR_PAIR(1));
    mvprintw(0, (map.xSize() / 2) * 4, "Stage %d", stage);
    
    int maxsize{3}; // 한 스테이지에서 도달한 스네이크의 최대 길이
    char key;

    // Update()
    while (1) {
        tick++;
        itemManager::instance().spawnItem(map.map, tick); // 아이템 생성 로직에 따라 아이템 생성 시도
        itemManager::instance().destroyItem(map.map, tick); // 아이템 수명에 따라 아이템 삭제 시도
        key = key_input.keyDown(); // 방향키 입력 처리

        snake.moveSnake(map.map, key); // snake 이동 처리
        if (snake.getSize() < 3) snake.Dead(); // snake 길이가 3보다 작으면 게임 오버
        maxsize = (snake.getSize() > maxsize ? snake.getSize() : maxsize); // 스네이크의 max length 판별

        map.printMap();
        printScoreboard(snake.getSize(), maxsize, snake.getitemCount(1), snake.getitemCount(), tick); // 메인 맵 옆에 스코어보드 출력
        printMissionboard(); // 메인 맵 옆에 미션 보드 출력

        refresh();
        wrefresh(scoreboard);
        wrefresh(missionboard);
        werase(scoreboard);
        werase(missionboard);

        if (isOver) {
            delwin(scoreboard);
            delwin(missionboard);
            break;
        }
        napms(1000 / TICKSPEED);
    }
    
    return -1;
}

WINDOW* initBoard(int y, int x) {
    WINDOW* win{newwin(8, 25, y , x)};
    return win;
}

void printScoreboard(int curlen, int maxlen, int growcount, int poisoncount, int tick) { 
    box(scoreboard, 0, 0);
    mvwprintw(scoreboard, 0, 7, "Score board");

    mvwprintw(scoreboard, 1, 1, "length: %2d / %2d", curlen, maxlen); // B: current length / max length
    mvwprintw(scoreboard, 2, 1, "growth item: %d", growcount); // +: 획득한 growth items
    mvwprintw(scoreboard, 3, 1, "poison item: %d", poisoncount); // -: 획득한 poison items
    mvwprintw(scoreboard, 4, 1, "gate: 0"); // G: gate 사용 횟수
    mvwprintw(scoreboard, 5, 1, "time: %2d : %02d", (tick / TICKSPEED) / 60, (tick / TICKSPEED) % 60); // 게임 플레이 타임(스테이지별)
}

void printMissionboard() {
    box(missionboard, 0, 0);
    mvwprintw(missionboard, 0, 6, "Mission board");

}

void Snake::Dead() { isOver = true; } // 게임 오버 처리