#define MAXITEM 3
#define MAXSPAWNDELAY 7
#define MINSPAWNDELAY 2

#include <vector>
#include <list>
#include "Item.h"

class itemManager
{
    public:
        static itemManager& instance();

        void spawnItem(std::vector<std::vector<int>> &map, int tick);
        void destroyItem(std::vector<std::vector<int>> &map, int curTime);
        void destroyItem(std::vector<std::vector<int>> &map, std::pair<int, int> pos);

    private:
        itemManager();
        static itemManager* _instance;
        int itemNum = 0; // 현재 생성된 아이템의 갯수
        std::list<item*> itemArr; // 아이템 정보를 저장할 리스트
        int lastSpawnTick = 0; 
        int coolTime = 3; // 아이템 생성 주기 (초기값)
};