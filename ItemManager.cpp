#include "ItemManager.h"
#include "Item.cpp"
#include <stdlib.h>
#include <time.h>

#define MAXITEM 3
#define MAXSPAWNDELAY 7
#define MINSPAWNDELAY 2
void itemManager::spawnItem(std::vector<std::vector<int>> &map, int tick)
{
    if (lastSpawnTick + coolTime >= tick)
        return;
    
    if (itemNum >= MAXITEM)
        return;
    
    lastSpawnTick = tick;
    srand(time(NULL));
    coolTime = (rand()%MAXSPAWNDELAY) + MINSPAWNDELAY;
    item* tem = new item(map, tick);
    itemArr[itemNum] = tem;
    itemNum++;
}

void itemManager::destroyItem(int curTime)
{
    for (int i = 0; i < MAXITEM; i++)
        if (itemArr[i]->getDuration() >= curTime)
            delete itemArr[i];

}
