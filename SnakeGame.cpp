#include "GameMap.h"
#include "InputManager.h"
#include "Snake.h"
#include <ncurses.h>

#define TICKSPEED 2 // tick per second

unsigned int tick; // 시간 경과 기록 (앞서 설정한 tick 단위)
int score; // 점수
bool isOver{false}; // 게임 오버 여부 check

void Snake::Dead() { isOver = true; }

int SnakeGame() {
    // Start()
    tick = 0;

    GameMap map;
    InputManager key_input;
    Snake snake{{STARTPOS, STARTPOS}, SNAKE_DEFAULT};

    map.map[STARTPOS][STARTPOS] = HEAD;
    for (int i = 1; i < SNAKE_DEFAULT; i++) {
        map.map[STARTPOS][STARTPOS + i] = BODY;
    }

    char key;

    // Update()
    while (1) {
        tick++;
        key = key_input.keyDown(); // 방향키 입력 처리

        snake.moveSnake(map.map, key); // snake 이동 처리

        map.printMap();

        mvprintw(0, 0, "%u", tick);
        mvprintw(0, 5, "input: %c", key);
        delch();
        refresh();

        if (tick > 200 || isOver) break;
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
    curs_set(0);

    // Update()
    while (1) {
        int x = SnakeGame();
        if (x == -1) break;
    }
    endwin();
}