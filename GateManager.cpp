#include "GateManager.h"
#include "objectid.h"
#include <stdlib.h>
#include <time.h>

void GateManager::SpawnGate(std::vector<std::vector<int>> &map, int tick, int snakeBodyNum)
{
    if (!isSpawnGate(snakeBodyNum, tick))
        return;
    srand(time(NULL));
    lastSpawnTime = tick; // 리스폰 시간 초기화
    coolTime =  (rand() % MAXSPAWNTIME) + MINSPAWNTIME; // 다음 스폰 시간 설정

    if (gate != gate_pair)
        map[gate.first][gate.second] = 1, map[gate_pair.first][gate_pair.second] = 1; // 게이트가 이미 존재 시 기존 게이트 삭제

    while (1) //게이트 좌표 설정
    {
        gate = wallPos[rand() % wallPos.size()]; // 미리 저장해둔 벽 좌표들 중 한개 선택
        gate_pair = wallPos[rand() % wallPos.size()];
        if (gate == gate_pair) // gate와 gate_pair가 겹치지 않도록 함
            continue;
        break;
    }
    map[gate.first][gate.second] = 7; // 게이트 좌표 map 매핑
    map[gate_pair.first][gate_pair.second] = 8;
    
}

bool GateManager::isSpawnGate(int snakeBodyNum, int tick) 
{
    if (lastSpawnTime + coolTime >= tick || wallPos.size() == 0)
        return false;
    else if (isPassingThrought) // 게이트 통과중인지 판단
    {
        if (initialTick == 0) // 처음 게이트에 충돌 or 다시 게이트에 충돌시 initialTick 재기록
        {
            initialTick = tick;
            return false;
        }
        else if (snakeBodyNum < tick-initialTick) // tick-initialTick < snakeBodyNum 즉 뱀 몸통 길이보다 많은 Tick이 흘렀다면 뱀이 전부 통과함
        {
            isPassingThrought = false;
            return true;
        }
        else
            return false;
    }
    else
        return true;
}

std::pair<int, int> GateManager::BlinkPos(std::pair<int, int> curGate, std::vector<std::vector<int>> &map, int dir)
{
    isPassingThrought = true; // 뱀이 게이트 통과중
    resetInitialTick(); // 뱀의 게이트 탈출여부 관리 변수 초기화
    
    std::pair<int, int> otherGate = (gate == curGate) ? gate_pair : gate; // 출구 게이트 찾기
    std::pair<int, int> res;
    int tmpDir = dir; // 뱀의 게이트 충돌전 기본 방향

    for (int i : rotate) { // 우선순위: 진행 방향(0), 시계(1), 반시계(3), 반대(2)
        blinkDir = (tmpDir + i) % 4; // 우선순위에 따라 회전
        if (checkBlink(otherGate, blinkDir, map))
        {
            return {otherGate.first + direation[blinkDir].first, otherGate.second + direation[blinkDir].second};
        }
    }

    return curGate;
}

bool GateManager::checkBlink(std::pair<int, int> GatePos, int dir, std::vector<std::vector<int>> &map)
{
    GatePos.first += direation[dir].first, GatePos.second += direation[dir].second;

    if ((0 < GatePos.first && GatePos.first < map.size()) && (0 < GatePos.second && GatePos.second < map[0].size())) { // 게이트 통과 후 진행방향이 맵 밖인지 검사
        if (map[GatePos.first][GatePos.second] == space || // 게이트 통과 후 진행방향이 빈공간인지 검사
            map[GatePos.first][GatePos.second] == growth || // 게이트 통과 후 진행방향이 growth 아이템인지 검사
            map[GatePos.first][GatePos.second] == poison ) { // 게이트 통과 후 진행방향이 poison 아이템인지 검사 -> 스네이크가 통과 가능한 유형 
                return true;
            }
    }
    return false;
}

void GateManager::initialization() // GateManager 초기화 
{
    wallPos.clear();
    blinkDir = 0;
    coolTime = 40;
    lastSpawnTime = 0;
    initialTick = 0;
    isPassingThrought = false;
    gate = gate_pair = {0, 0};
}

void GateManager::resetInitialTick() {initialTick = 0;}

// private 정의부
GateManager& GateManager::Instance()
{
    if(_instance == nullptr)
        _instance = new GateManager();

    return *_instance;
}

GateManager::GateManager() {}
GateManager* GateManager::_instance;