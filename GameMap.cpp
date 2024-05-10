#ifndef GAMEMAP
#define GAMEMAP

#include <vector>
#include <ncurses.h>

using namespace std;

#define MAPSIZE 21

// 빈 공간 0 벽 1 모서리 2 스네이크 tail 3 head 4 아이템 + 5 - 6 게이트 입구 7 출구 8
namespace gamemap {
    class GameMap {
        public:
            GameMap() {
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
            }

            void printMap() { // map 출력
                move(1,0);
                for (int y = 0; y < MAPSIZE; y++) {
                    
                    for (int x = 0; x < MAPSIZE; x++) {
                        mvprintw(y+1, x, "%d", map[y][x]); 
                    }
                    printw("\n");
                }
            }
    
        public:
            vector<vector<int>> map;
    };
}


#endif /* GAMEMAP */