#include "Item.h"
#include <stdlib.h>
#include <time.h>

item::item(std::vector<std::vector<int>> &map, int tick) : map(map), spawnTime(tick)
{
    settingItem();
}

item::~item() {}

void item::settingItem()
{
    srand(time(NULL));
    isGrowth = rand() % 2;
    while (1)
    {   
        // 아이템의 좌표 지정
        int x = (rand() % map[0].size()-1) + 1;
        int y = (rand() % map.size()-1) + 1;

        if (map[y][x] != 0)
            continue;

        // 맵 매핑
        if (isGrowth)
            map[y][x] = 5;
        else
            map[y][x] = 6;

        pos = {y, x};
        duration = spawnTime + DURATION;
        break;
    }
}


