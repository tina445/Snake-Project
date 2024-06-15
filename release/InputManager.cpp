#include "InputManager.h"
#include <ncurses.h>

char InputManager::keyDown() {
    int input = getch();
    char ch;

    switch (input)
    {
    case KEY_UP:
    case 'w':
    case 'W':
            ch = 'U';
        break;
    case KEY_DOWN:
    case 's':
    case 'S':
        ch = 'D';
        break;
    case KEY_LEFT:
    case 'a':
    case 'A':
        ch = 'L';
        break;
    case KEY_RIGHT:
    case 'd':
    case 'D':
        ch = 'R';
        break;
    case '\n':
        ch = 'N';
        break;
    default:
        ch = ' ';
        break;
    }

    return ch;
}