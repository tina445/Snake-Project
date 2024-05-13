#include "InputManager.h"
#include <ncurses.h>

char InputManager::keyDown() {
    int input = getch();
    char ch;

    switch (input)
    {
    case KEY_UP:
            ch = 'U';
        break;
    case KEY_DOWN:
        ch = 'D';
        break;
    case KEY_LEFT:
        ch = 'L';
        break;
    case KEY_RIGHT:
        ch = 'R';
        break;
    case KEY_ENTER:
        ch = 'N';
        break;
    default:
        ch = ' ';
        break;
    }

    return ch;
}