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
    int otherGateY = otherGate.first; // 출구 게이트 Y
    int otherGateX = otherGate.second;// 출구 게이트 X
    int saveDir = dir;
    while (1)
    {
        if ((0 < otherGateY + direation[saveDir].first && otherGateY + direation[saveDir].first < map.size()) && (0 < otherGateX + direation[saveDir].second && otherGateX + direation[saveDir].second < map[0].size()) 
        && map[otherGateY + direation[saveDir].first][otherGateX + direation[saveDir].second] == 0)
        {
            
            blinkDir = saveDir;
            if (blinkDir == 2 || blinkDir == 3)
                blinkDir = (blinkDir == 2) ? 3 : 2;
            return {otherGateY + direation[saveDir].first, otherGateX + direation[saveDir].second};
        }
        
        saveDir = (saveDir + 1) % 4;
        if (saveDir == dir)
            break;
    }
    
    
    
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