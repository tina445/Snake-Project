#include "GameMap.h"
#include "InputManager.h"
#include "Snake.h"
#include "ItemManager.h"
#include "GateManager.h"
#include <ncurses.h>

#define TICKSPEED 4 // tick per second
#define MAXSTAGE 5 // 최대 스테이지 수

using namespace std;

int tick; // 시간 경과 기록 (앞서 설정한 tick 단위)
int stage{1}; // 현재 스테이지
bool isOver{false}; // 게임 오버 여부 check
bool isClear{false}; // 스테이지 클리어 여부 check
WINDOW *scoreboard, *missionboard;
InputManager key_input;

// 함수 정의부
WINDOW* initBoard(int y, int x); // 메인 맵과 겹치지 않도록 좌표 y, x에 스코어보드를 관리할 window 객체 생성
int snakeGame(); // 스네이크 게임 함수
void nextStage(int tick); // 스테이지 클리어시 다음 스테이지 진행 대기
vector<pair<int, bool>> createMission(); // 스테이지 목표 생성
bool compareMission(vector<pair<int, bool>> &mission, vector<int> score); // 목표 달성 여부 판별
void printScoreboard(int curlen, int maxlen, int growcount, int poisoncount, int gate, int tick); // 스코어보드 출력
void printMissionboard(vector<pair<int, bool>> &mission);

int main(int agrc, char *argv[]) {
    // Strat()
    initscr();
    noecho();
    nodelay(stdscr, true);
    keypad(stdscr, true);
    start_color();
    curs_set(0);

    int gamestate;
    
    // Update()
    while (1) {
        gamestate = snakeGame();
        if (gamestate == -1) break; // 게임 실패
        else if (gamestate == 1) { // 모든 스테이지를 클리어
            printw("Congratulations!! You cleared All stages!!");
            refresh();
            napms(5000);
            break;
        }
    }

    endwin();
}

int snakeGame() {
    // Start()
    clear();
    itemManager::instance().delitemArr(); // 아이템 리스트 비우기
    GateManager::Instance().initialization(); // 게이트 로직 초기화 
    tick = 0;
    
    GameMap map{stage};
    Snake snake{{map.ySize() / 2, map.xSize() / 2}, SNAKE_DEFAULT}; // 스네이크 객체
    vector<pair<int, bool>> missions{createMission()}; // 미션들을 관리하는 벡터
    
    scoreboard = initBoard(2, (map.xSize() + 1) * 4);
    missionboard = initBoard(11, (map.xSize() + 1) * 4);
    mvprintw(0, (map.xSize() / 2) * 4, "Stage %d", stage); // 현재 스테이지 표시
    
    int maxsize{SNAKE_DEFAULT}; // 한 스테이지에서 도달한 스네이크의 최대 길이
    char key;

    // Update()
    while (1) {
        tick++;
        itemManager::instance().spawnItem(map.map, tick); // 아이템 생성 로직에 따라 아이템 생성 시도
        itemManager::instance().destroyItem(map.map, tick); // 아이템 수명에 따라 아이템 삭제 시도
        GateManager::Instance().SpawnGate(map.map, tick, snake.getSize() - 1); // 게이트 생성 로직에 따라 게이트 생성 시도
        key = key_input.keyDown(); // 방향키 입력 처리

        snake.moveSnake(map.map, key); // snake 이동 처리
        if (snake.getSize() < 3) snake.Dead(); // snake 길이가 3보다 작으면 게임 오버
        maxsize = (snake.getSize() > maxsize ? snake.getSize() : maxsize); // 스네이크의 max length 판별

        map.printMap();
        printScoreboard(snake.getSize(), maxsize, snake.getitemCount(1), snake.getitemCount(), snake.getgateCount(), tick); // 메인 맵 옆에 스코어보드 출력
        printMissionboard(missions); // 메인 맵 옆에 미션 보드 출력

        refresh();
        wrefresh(scoreboard);
        wrefresh(missionboard);
        wclear(scoreboard);
        wclear(missionboard);

        if (isOver) {
            delwin(scoreboard);
            delwin(missionboard);
            return -1; // 게임 실패
        }
        else if (compareMission(missions, {maxsize, snake.getitemCount(1), snake.getitemCount(), snake.getgateCount(), tick})) { // 모든 목표를 달성했는지 확인
            if (stage >= MAXSTAGE) return 1; // 모든 스테이지를 성공
            
            stage++;

            nextStage(tick);

            delwin(scoreboard);
            delwin(missionboard);
            return 0; // 스테이지 성공
        }

        napms(1000 / TICKSPEED);
    }
}

WINDOW* initBoard(int y, int x) {
    WINDOW* win{newwin(9, 33, y , x)};
    return win;
}

void printScoreboard(int curlen, int maxlen, int growcount, int poisoncount, int gate, int tick) { 
    box(scoreboard, 0, 0);
    mvwprintw(scoreboard, 0, 10, "Score board");

    mvwprintw(scoreboard, 2, 6, "length: %2d / %2d", curlen, maxlen); // B: current length / max length
    mvwprintw(scoreboard, 3, 6, "growth item: %d", growcount); // +: 획득한 growth items
    mvwprintw(scoreboard, 4, 6, "poison item: %d", poisoncount); // -: 획득한 poison items
    mvwprintw(scoreboard, 5, 6, "gate: %d", gate); // G: gate 사용 횟수
    mvwprintw(scoreboard, 6, 6, "time: %2d : %02d", (tick / TICKSPEED) / 60, (tick / TICKSPEED) % 60); // 게임 플레이 타임(스테이지별)
}

void printMissionboard(vector<pair<int, bool>> &mission) { // 미션 내용을 메인 맵 옆에 출력
    box(missionboard, 0, 0);
    mvwprintw(missionboard, 0, 9, "Mission board");
    
    mvwprintw(missionboard, 2, 6, "length: %d", mission[0].first); // B: current length / max length
    mvwprintw(missionboard, 3, 6, "growth item: %d", mission[1].first); // +: 획득한 growth items
    mvwprintw(missionboard, 4, 6, "poison item: %d", mission[2].first); // -: 획득한 poison items
    mvwprintw(missionboard, 5, 6, "gate: %d", mission[3].first); // G: gate 사용 횟수
    mvwprintw(missionboard, 6, 6, "time: %d", mission[4].first / TICKSPEED); // 게임 플레이 타임

    for (int i = 0; i < mission.size(); i++) {
        mvwprintw(missionboard, i + 2, 22, "( %c )", mission[i].second ? 'v' : ' '); // 목표 달성 여부 출력 (달성했을 경우 체크 표시)
    }
}

void nextStage(int tick) { // 다음 스테이지 진출 확인
    int y, x;

    printw("Stage clear!\n");
    for (int t = tick + (TICKSPEED * 5); t > tick; t--) { // 다음 스테이지 실행까지 5초 기다리기
        
        printw("move next stage in %d seconds...\n", ((t - tick) / TICKSPEED) % 60);
        printw("press ENTER to continue");
        getyx(stdscr, y, x);
        if (key_input.keyDown() == 'N') return; // 엔터키를 누르면 즉시 다음 스테이지 실행
        refresh();

        move(y, 0);
        deleteln();
        move(y - 1,0);
        deleteln();

        napms(1000 / TICKSPEED);
    }
}

vector<pair<int, bool>> createMission() { // 각 스테이지별로 미션 생성
    vector<pair<int, bool>> vec;
    srand(time(NULL));

    vec.push_back({7 + stage + (rand() % 3), false}); // 최대 몸 길이(B) 목표 8~11, 9~12, 10~13, 11~14, 12~15
    vec.push_back({5 + (stage - 1) + (rand() % 3), false}); // growth item(+) 목표 5~8, 6~9 7~10, 8~11, 9~12
    vec.push_back({2 + stage + (rand() % 2), false}); // poison item(-) 목표 3~5, 4~6, 5~7, 6~8, 7~9
    vec.push_back({1 + (stage / 2) + (rand() % 2), false}); // gate 통과(G) 목표 1~3, 2~4, 2~4, 3~5, 3~5 
    vec.push_back({((50 + (stage * 10)) * TICKSPEED), false}); // 플레이 시간(sec) 목표 60, 70, 80, 90, 100

    return vec;
}

bool compareMission(vector<pair<int, bool>> &mission, vector<int> score) { // 미션 성공 여부 판별
    int count{};
    for (int i = 0; i < mission.size(); i++) {
        if (score[i] >= mission[i].first) mission[i].second = true;

        if (mission[i].second) count++;
    }

    if (count == mission.size()) return true;
    
    return false;
}

void Snake::Dead() { isOver = true; } // 게임 오버 처리