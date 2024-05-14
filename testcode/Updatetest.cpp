#include <ncurses.h>
#include <unistd.h>

#define TICKSPEED 2 // tick per second

char Input() { // 입력 처리 함수
    int inp = getch();
    char ch;

    if (inp != -1) { // 입력이 있을 경우
        move(4, 0);
        deleteln();
        
        switch (inp) { // 방향키 처리
        case KEY_UP:
            ch = 'U';
            printw("arrow key: KEY_UP");
            break;
        case KEY_DOWN:
            ch = 'D';
            printw("arrow key: KEY_DOWN");
            break;
        case KEY_LEFT:
            ch = 'L';
            printw ("arrow key: KEY_LEFT");
            break;
        case KEY_RIGHT:
            ch = 'R';
            printw("arrow key: KEY_RIGHT");
            break;
        default:
            ch = static_cast<char>(inp);
            break;
        }
    }
    else { // 입력이 없을 경우
        ch = ' ';
    }

    return ch;
}

int main(int argc, char *argv[]) {
    unsigned int tick{};

    initscr();
    noecho(); // getch()에서 자동으로 입력값을 출력하지 않게 함
    keypad(stdscr, true); // 방향키 등 특수 키 입력 활성화
    nodelay(stdscr, true); // non-blocking 활성화(getch()가 프로그램 실행을 멈추지 않게 함)
    curs_set(0); // 화면에 커서가 보이지 않게 함

    printw("press any key\npress ~ to quit");

    while (1) {
        tick++;

        mvprintw(2, 0, "tick: %u", tick); // mvprintw(y, x, ch): y, x로 커서 이동 후 출력
        char ch = Input();
        mvprintw(3, 0 ,"input: %c", ch);

        if (ch == '~') break;

        refresh();
        delch();
        napms(1000 / TICKSPEED);
    }
    endwin();
}