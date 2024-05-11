#ifndef GAMEMAP
#define GAMEMAP

#include <ncurses.h>
#include <vector>

#define MAPSIZE 21

class GameMap{
    public:
        GameMap(int startpos, int snakeSize);
        GameMap();
        void printMap();
    public:
        std::vector<std::vector<int>> map;
    
    private:
        // 색상 팔레트 번호
        // 빈 공간(흰색): 1 빈 공간(격자): 2 벽: 3 모서리: 4 스네이크: body 5, head 6 아이템: + 7, - 8 게이트: 9
        enum palatteID { space = 1, spaceg = 2, wall = 3, Iwall = 4, body = 5, head = 6, growth = 7, poison = 8, gate = 9 }; 
        enum colorID { green = 1, lightgreen = 2, gray = 3, darkgray = 4, lightblue = 5, blue = 6, red = 7, purple = 8};
};

#endif /* GAMEMAP */