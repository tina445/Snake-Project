#include <ncurses.h>
#include <vector>
#include "GameMap.h"

using namespace std;

#define MAPSIZE 21 // game map의 사이즈 (n * n)

// 빈 공간 0 벽 1 모서리 2 스네이크 body 3 head 4 아이템 + 5 - 6 게이트 입구 7 출구 8
GameMap::GameMap() {
    vector<int> tmp; // map에 넣을 임시 1차원 벡터 (empty vector)

    for (int i = 0; i < MAPSIZE; i++) {
        map.push_back(tmp);
        for (int j = 0; j < MAPSIZE; j++) {
            if (i == 0 || j == 0 || i == MAPSIZE-1 || j == MAPSIZE-1) {
                if (i == j || (i == 0 && j == MAPSIZE-1 ) || (i == MAPSIZE-1 && j == 0)) 
                    map[i].push_back(2); // 모서리 (대체 불가능한 벽)
                else 
                    map[i].push_back(1); // 일반 벽 object
            }
                else 
                    map[i].push_back(0); // 빈 공간
        }
    }
    start_color();

    // 색상 정의
    init_color(green, 700, 1000, 700);
    init_color(lightgreen, 850, 1000, 850); // 빈 공간의 격자무늬
    init_color(gray, 400, 400, 400); // 벽에 사용
    init_color(darkgray, 200, 200, 200); // 모서리에 사용
    init_color(lightblue, 90, 700, 1000); // snake body에 사용
    init_color(blue, 90, 320, 1000); // snake head에 사용

    // 색상 팔레트 지정
    init_pair(space, COLOR_BLACK, green);
    init_pair(spaceg, COLOR_BLACK, lightgreen);
    init_pair(wall, COLOR_BLACK, gray);
    init_pair(Iwall, COLOR_BLACK, darkgray);
    init_pair(body, COLOR_BLACK, lightblue);
    init_pair(head, COLOR_BLACK, blue);
}

void GameMap::printMap() { // map 출력
    move(1, 0);
    for (int y = 0; y < MAPSIZE; y++) {
        for (int x = 0; x < MAPSIZE; x++) {
            if (map[y][x] == 0) mvaddch(y+1, x * 4, '\t' | COLOR_PAIR(((y + x) % 2) + 1)); 
            else mvaddch(y+1, x * 4, '\t' | COLOR_PAIR(map[y][x] + 2)); 
        }
        printw("\b\b\b\b\n");
    }
}

