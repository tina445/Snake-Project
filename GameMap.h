#ifndef GAMEMAP
#define GAMEMAP

#include <ncurses.h>
#include <vector>
#include <string>

class GameMap{
    public:
        GameMap(int stage);
        GameMap();
        void printMap();
        int ySize();
        int xSize();
    private:
        void createMap(int stage);
        const char* selectMap(int stage);

    public:
        std::vector<std::vector<int>> map;
    private:
        // 색상 팔레트 번호
        // 빈 공간(흰색): 1 빈 공간(격자): 2 벽: 3 모서리: 4 스네이크: body 5, head 6 아이템: + 7, - 8 게이트: 9
        enum palatteID { space = 1, spaceg = 2, wall = 3, Iwall = 4, body = 5, head = 6, growth = 7, poison = 8, gate = 9 }; 
        enum colorID { green = 20, lightgreen = 21, gray = 22, darkgray = 23, lightblue = 24, blue = 25, red = 26, purple = 27};

        std::vector<std::vector<std::string>> mapList {{"stage/world1.map"},
                                        {"stage/world2-1.map", "stage/world2-2.map", "stage/world2-3.map", "stage/world2-4.map", "stage/world2-5.map"},
                                        {"stage/world3-1.map", "stage/world3-2.map", "stage/world3-3.map", "stage/world3-4.map", "stage/world3-5.map"},
                                        {"stage/world4-1.map", "stage/world4-2.map", "stage/world4-3.map", "stage/world4-4.map", "stage/world4-5.map"},
                                        {"stage/world5-1.map", "stage/world5-2.map"}};
};

#endif /* GAMEMAP */