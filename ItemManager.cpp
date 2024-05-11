#include "ItemManager.h"
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

void itemManager::spawnItem(std::vector<std::vector<int>> &map, int tick) // 아이템 생성
{
    if (itemArr.size() >= MAXITEM || lastSpawnTick + coolTime >= tick) // 아이템이 최대 개수(3개)에 도달하거나 생성 주기에 도달하지 않으면 아이템을 생성하지 않음
        return;
    
    lastSpawnTick = tick; // 마지막에 아이템이 생성된 시간 기록

    srand(time(NULL));
    coolTime = (rand()%MAXSPAWNDELAY) + MINSPAWNDELAY; // 새로운 아이템이 등장할 간격 랜덤 지정

    item* tem = new item(map, tick); // 새로운 아이템 생성 (동적 할당)
    itemArr.push_back(tem); // 리스트에 생성된 아이템 정보 저장
}

void itemManager::destroyItem(std::vector<std::vector<int>> &map, int curTime) // 아이템 삭제 (자연 삭제)
{
    for (std::list<item*>::iterator iter = itemArr.begin(); iter != itemArr.end(); ++iter) { // 아이템의 최대 수명 틱보다 현재 틱이 커지면 삭제
        if ((*iter)->getDuration() <= curTime) {
            map[(*iter)->getPosition().first][(*iter)->getPosition().second] = 0; // map 매핑 -> 아이템이 사라졌기 때문에 0

            delete *iter; // 메모리 할당 해제
            itemArr.erase(iter); // 소멸한 아이템의 정보를 아이템 리스트에서 삭제
            break;
        }
    }
}

void itemManager::destroyItem(std::vector<std::vector<int>> &map, std::pair<int, int> pos) // 아이템 삭제 (스네이크와의 상호작용)
{
    for (std::list<item*>::iterator iter = itemArr.begin(); iter != itemArr.end(); ++iter) {
        if ((*iter)->getPosition() == pos) {
            map[(*iter)->getPosition().first][(*iter)->getPosition().second] = 0; // map 매핑 -> 아이템이 사라졌기 때문에 0

            delete *iter; // 메모리 할당 해제
            itemArr.erase(iter); // 소멸한 아이템의 정보를 아이템 리스트에서 삭제
            break;
        }
    }
}

// private method 정의부
itemManager& itemManager::instance() { // static instance init
    if (_instance == nullptr)
        _instance = new itemManager();

    return *_instance;
}

itemManager::itemManager() {}
itemManager* itemManager:: _instance;