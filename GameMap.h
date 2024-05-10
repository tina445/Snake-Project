#ifndef GAMEMAP
#define GAMEMAP

#include <ncurses.h>
#include <vector>

class GameMap{
    public:
        GameMap();
        void printMap();
    public:
        std::vector<std::vector<int>> map;
};

#endif /* GAMEMAP */