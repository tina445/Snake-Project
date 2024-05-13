#include <ncurses.h>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "GameMap.h"
#include "objectid.h"

using namespace std;

#define MAPSIZE 21 // game map의 사이즈 (n * n)

GameMap::GameMap(int stage) {
    createMap(stage); // 스테이지에 해당하는 맵 생성

    // 색상 정의
    init_color(green, 700, 1000, 700);
    init_color(lightgreen, 850, 1000, 850); // 빈 공간의 격자무늬
    init_color(gray, 400, 400, 400); // 벽에 사용
    init_color(darkgray, 200, 200, 200); // 모서리에 사용
    init_color(lightblue, 90, 700, 1000); // snake body에 사용
    init_color(blue, 90, 320, 1000); // snake head에 사용
    init_color(red, 1000, 240, 240); // growth 아이템에 사용
    init_color(purple, 400, 200, 800); // poison 아이템에 사용

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

GameMap::GameMap() {
    createMap(1); // 스테이지에 해당하는 맵 생성(기본값: 1)

    // 색상 정의
    init_color(green, 700, 1000, 700);
    init_color(lightgreen, 850, 1000, 850); // 빈 공간의 격자무늬
    init_color(gray, 400, 400, 400); // 벽에 사용
    init_color(darkgray, 200, 200, 200); // 모서리에 사용
    init_color(lightblue, 90, 700, 1000); // snake body에 사용
    init_color(blue, 90, 320, 1000); // snake head에 사용
    init_color(red, 1000, 240, 240); // growth 아이템에 사용
    init_color(purple, 400, 200, 800); // poison 아이템에 사용

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

void GameMap::createMap(int stage) {
    ifstream readfile;
    readfile.open(selectMap(stage)); // 맵에 대한 정보가 담긴 파일 열기 (ex: stage/world1.map)

    vector<int> tmp; // map에 넣을 임시 1차원 벡터 (empty vector)
    string line; // 한 행에 대한 정보를 담을 임시 문자열

    if (readfile.is_open()) {
        for (int i = 0; !readfile.eof(); i++) {
            map.push_back(tmp);
            getline(readfile, line);
        
            for (char obj : line) {
                map[i].push_back(obj % '0'); // 맵에 해당하는 오브젝트 저장
            }
        }   
    }

    readfile.close();
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

int GameMap::ySize() { // 맵의 세로 길이 반환
    return map.size();
}

int GameMap::xSize() { // 맵의 가로 길이 반환
    return map[0].size();
}

const char* GameMap::selectMap(int stage) { // 스테이지에 해당하는 맵들중 하나를 고름
    srand(time(NULL));
    int i{rand() % static_cast<int>(mapList[stage - 1].size())}; // 맵 번호 인덱스를 랜덤으로 설정

    return mapList[stage - 1][i].c_str(); // string을 fstream.open()에 사용 가능한 형식인 const char*로 변환
}