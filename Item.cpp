#include "Item.h"
#include <stdlib.h>
#include <time.h>

#define MAPSIZE 21

item::item(std::vector<std::vector<int>> &map, int tick) : map(map), spawnTime(tick)
{
    settingItem();
}

item::~item()
{
    map[pos.first][pos.second] = 0;
}

void item::settingItem()
{
    srand(time(NULL));
    isGrowth = rand()%2;
    while (1)
    {
        int x = (rand() % MAPSIZE-1) + 1;
        int y = (rand() % MAPSIZE-1) + 1;
        if (map[x][y] != 0)
            continue;

        if (isGrowth)
            map[x][y] = 5;
        else
            map[x][y] = 6;

        pos = {x,y};
        duration = DURATION + spawnTime;
        break;
    }
}


