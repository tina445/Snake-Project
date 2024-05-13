#include "GameMap.h"
#include "InputManager.h"
#include "Snake.h"
#include "ItemManager.h"
#include <ncurses.h>

#define TICKSPEED 2 // tick per second

unsigned int tick; // 시간 경과 기록 (앞서 설정한 tick 단위)
int stage; // 현재 스테이지
bool isOver{false}; // 게임 오버 여부 check
WINDOW *scoreboard;

int snakeGame();

WINDOW* initScoreboard(int x, int y);

void printScoreboard(int curlen, int maxlen, int growcount, int poisoncount, int tick);

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
    GameMap map;
    Snake snake{{map.ySize() / 2, map.xSize() / 2}, SNAKE_DEFAULT};

    scoreboard = initScoreboard(2, (map.xSize() + 1) * 4);

    wbkgd(scoreboard, COLOR_PAIR(1));
    
    char key;

    // Update()
    while (1) {
        tick++;
        itemManager::instance().spawnItem(map.map, tick); // 아이템 생성 로직에 따라 아이템 생성 시도
        itemManager::instance().destroyItem(map.map, tick); // 아이템 수명에 따라 아이템 삭제 시도
        key = key_input.keyDown(); // 방향키 입력 처리

        snake.moveSnake(map.map, key); // snake 이동 처리
        if (snake.getSize() < 3) snake.Dead(); // snake 길이가 3보다 작으면 게임 오버

        map.printMap();
        printScoreboard(snake.getSize(), 3, snake.getitemCount(1), snake.getitemCount(), tick);
        
        refresh();
        wrefresh(scoreboard);
        touchwin(stdscr);
        werase(scoreboard);

        if (isOver) {
            delwin(scoreboard);
            break;
        }
        napms(1000 / TICKSPEED);
    }
    
    return -1;
}

WINDOW* initScoreboard(int y, int x) {
    WINDOW* win{newwin(8, 25, y , x)};
    return win;
}

void printScoreboard(int curlen, int maxlen, int growcount, int poisoncount, int tick) {
    box(scoreboard, 0, 0);
    mvwprintw(scoreboard, 0, 7, "Score board");

    mvwprintw(scoreboard, 1, 1, "length: %d / %d", curlen, maxlen);
    mvwprintw(scoreboard, 2, 1, "growth item: %d", growcount);
    mvwprintw(scoreboard, 3, 1, "poison item: %d", poisoncount);
    mvwprintw(scoreboard, 4, 1, "gate: 0");
    mvwprintw(scoreboard, 5, 1, "time: %2d : %02d", (tick / TICKSPEED) / 60, (tick / TICKSPEED) % 60);
}

void Snake::Dead() { isOver = true; } // 게임 오버 처리