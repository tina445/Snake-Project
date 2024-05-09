#include <ncurses.h>
#include <unistd.h>
#include <iostream>
#include <charconv>

#define TICKSPEED 2 // tick per second

int main(int argc, char *argv[]) {
    initscr();

    int tick{}, sec, min;
    char s[100];

    while (1) {
        tick++;
        sec = (tick / 2) % 60;
        min = sec / 60;
        //std::to_chars(s, s + 100, time);
        printw("%d : %d", min, sec);
        refresh();
        deleteln();
        move(0, 0);
        usleep(1000000 / TICKSPEED);
        
    }

    endwin();
    
    return 0;
}