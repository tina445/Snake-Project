#include "GameMap.h"
#include "InputManager.h"
#include "Snake.h"
#include "ItemManager.h"
#include <ncurses.h>

#define TICKSPEED 2 // tick per second

unsigned int tick; // 시간 경과 기록 (앞서 설정한 tick 단위)
int score; // 점수
bool isOver{false}; // 게임 오버 여부 check

void Snake::Dead() { isOver = true; } // 게임 오버 처리

int SnakeGame() {
    // Start()
    tick = 0;
    InputManager key_input;
    GameMap map;
    Snake snake{{map.ySize() / 2, map.xSize() / 2}, SNAKE_DEFAULT};

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
        mvprintw(0, 0, "%u", tick);
        mvprintw(0, 5, "input: %c", key);
        delch();
        refresh();

        if (tick > 1000 || isOver) break;
        napms(1000 / TICKSPEED);
    }
    
    return -1;
}

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
        int x = SnakeGame();
        if (x == -1) break;
    }
    mvprintw(0, MAPSIZE, "gameover");
    endwin();
}