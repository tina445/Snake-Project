#include "GameMap.cpp"
#include "InputManager.cpp"
#include <ncurses.h>

#define TICKSPEED 2 // tick per second
unsigned int tick{};

using namespace gamemap;
using namespace inputmanager;

int main(int agrc, char *argv[]) {
    // init window
    initscr();
    noecho();
    nodelay(stdscr, true);
    keypad(stdscr, true);
    curs_set(0);

    // Awake()
    GameMap map;
    InputManager key_input;

    // Start()
    char key;

    // Update()
    while (1) {
        tick++;
        map.printMap();
        mvprintw(0, 0, "%u", tick);

        key = key_input.keyDown();
        mvprintw(0, 5, "input: %c", key);
        delch();
        refresh();

        if (tick > 200) break;
        napms(1000 / TICKSPEED);
    }
    endwin();
}