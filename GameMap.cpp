#include <ncurses.h>
#include <vector>
#include "GameMap.h"
#include "objectid.h"

using namespace std;

#define MAPSIZE 21 // game map의 사이즈 (n * n)

GameMap::GameMap(int startpos, int snakeSize) {
    vector<int> tmp; // map에 넣을 임시 1차원 벡터 (empty vector)

    for (int i = 0; i < MAPSIZE; i++) {
        map.push_back(tmp);
        for (int j = 0; j < MAPSIZE; j++) {
            if (i == 0 || j == 0 || i == MAPSIZE-1 || j == MAPSIZE-1) {
                if (i == j || (i == 0 && j == MAPSIZE-1 ) || (i == MAPSIZE-1 && j == 0)) 
                    map[i].push_back(OBJECTID::Iwall); // 모서리 (대체 불가능한 벽)
                else 
                    map[i].push_back(OBJECTID::wall); // 일반 벽 object
            }
                else 
                    map[i].push_back(OBJECTID::wall); // 빈 공간
        }
    }

    map[startpos][startpos] = OBJECTID::head; // snake head;
    for (int i = 1; i < snakeSize; i++) {
        map[startpos][startpos + i] = OBJECTID::body; //snake body
    }

    // 색상 정의
    init_color(green, 700, 1000, 700);
    init_color(lightgreen, 850, 1000, 850); // 빈 공간의 격자무늬
    init_color(gray, 400, 400, 400); // 벽에 사용
    init_color(darkgray, 200, 200, 200); // 모서리에 사용
    init_color(lightblue, 90, 700, 1000); // snake body에 사용
    init_color(blue, 90, 320, 1000); // snake head에 사용
    init_color(red, 1000, 240, 240);
    init_color(purple, 400, 200, 800);

    // 색상 팔레트 지정
    init_pair(space, COLOR_BLACK, green);
    init_pair(spaceg, COLOR_BLACK, lightgreen);
    init_pair(wall, COLOR_BLACK, gray);
    init_pair(Iwall, COLOR_BLACK, darkgray);
    init_pair(body, COLOR_BLACK, lightblue);
    init_pair(head, COLOR_BLACK, blue);
    init_pair(growth, COLOR_BLACK, red);
    init_pair(poison, COLOR_BLACK, purple);
}

GameMap::GameMap() {}

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

