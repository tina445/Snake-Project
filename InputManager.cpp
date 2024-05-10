#ifndef INPUTMANAGER
#define INPUTMANAGER

#include <ncurses.h>

namespace inputmanager {
    class InputManager {
        public:
            char keyDown() {
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
                default:
                    ch = ' ';
                    break;
                }

                return ch;
            }
    };
}


#endif /* INPUTMANAGER */