#include "GateManager.h"
#include <stdlib.h>
#include <time.h>

void GateManager::SpawnGate(std::vector<std::vector<int>> &map, int tick)
{
    if (lastSpawnTime + coolTime >= tick || wallPos.size() == 0)
        return;
    srand(time(NULL));
    lastSpawnTime = tick; // 리스폰 시간 초기화
    coolTime =  (rand() % MAXSPAWNTIME) + MINSPAWNTIME; // 다음 스폰 시간 설정

    if (gate != gate_pair)
        map[gate.first][gate.second] = 1; map[gate_pair.first][gate_pair.second] = 1; // 게이트가 이미 존재 시 기존 게이트 삭제

    while (1) //게이트 좌표 설정
    {
        gate = wallPos[rand() % wallPos.size()];
        gate_pair = wallPos[rand() % wallPos.size()];
        if (gate == gate_pair)
            continue;
        break;
    }
    map[gate.first][gate.second] = 7;
    map[gate_pair.first][gate_pair.second] = 8;
    
}

std::pair<int, int> GateManager::BlinkPos(std::pair<int, int> curGate, std::vector<std::vector<int>> &map, int dir)
{
    std::pair<int, int> otherGate = (gate == curGate) ? gate_pair : gate; // 출구 게이트 찾기
    std::pair<int, int> res;

    if  (map[otherGate.first + direation[dir].first][otherGate.second + direation[dir].second] == 0) // 뱀 집입 방향 공간 확인
        return res = {otherGate.first + direation[dir].first, otherGate.second + direation[dir].second};
    
    if (map[otherGate.first + direation[(dir + 1) % 4].first][otherGate.second + direation[(dir + 1) % 4].second] == 0) // 시계방향 회전 후 공간 확인
        return res = {otherGate.first + direation[(dir + 1) % 4].first, otherGate.second + direation[(dir + 1) % 4].second};

    if (map[otherGate.first + direation[((dir - 1) + 4 )% 4].first][otherGate.second + direation[((dir - 1) + 4 )% 4].second] == 0) // 반시계 방향 회전 후 공간 확인
        return res = {otherGate.first + direation[((dir - 1) + 4 )% 4].first, otherGate.second + direation[((dir - 1) + 4 )% 4].second};

    if (map[otherGate.first + direation[(dir + 2) % 4].first][otherGate.second + direation[(dir + 2) % 4].second] == 0) // 짐입 반대 방향 회전 후 공간 확인
        return res = {otherGate.first + direation[(dir + 2) % 4].first, otherGate.second + direation[(dir + 2) % 4].second};
    
    return curGate;
}

GateManager& GateManager::Instance()
{
    if(_instance == nullptr)
        _instance = new GateManager();

    return *_instance;
}

GateManager::GateManager() {}
GateManager* GateManager::_instance;