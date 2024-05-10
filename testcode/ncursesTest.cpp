#include <ncurses.h>

int main(int argc, char *argv[]) {
    initscr();

    box(stdscr, 0, 0);
    refresh();
    printw("hello world!", 10, 10);
    refresh();
    
    getch();
    endwin();
    
    return 0;
}