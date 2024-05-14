#include <vector>
#define MAXSPAWNTIME 30
#define MINSPAWNTIME 20

class GateManager
{
    public:
        static GateManager& Instance();

        void SpawnGate(std::vector<std::vector<int>> &map, int tick, int snakeBodyNum);
        std::pair<int, int> BlinkPos(std::pair<int, int> curGate, std::vector<std::vector<int>> &map, int dir); // 게이트 충돌시 다른 게이트의 주변 빈공간 반환
        std::pair<int, int> getGatePos() { return gate; } // 게이트의 좌표 반환
        std::pair<int, int> getGate_PairPos() { return gate_pair; } // 게이트(pair)의 좌표 반환
        void setWallPos(std::pair<int, int> pos) {wallPos.push_back(pos);}
        int getBlinkDir() { return blinkDir; }
        void initialization(); // 게이트 매니저 초기화
        bool isSpawnGate(int snakeBodyNum, int tick); // 게이트 (재)스폰 가능 여부 판단
    private:
        GateManager();
        void resetInitialTick(); // 게이트 재충돌시 시간 측정 변수 초기화 

        std::vector<std::pair<int, int>> wallPos; // 게이트 스폰 좌표 판단을 위해 미리 저장할 벽 좌표 벡터
        static GateManager* _instance;
        std::pair<int, int> gate; // 게이트 좌표
        std::pair<int, int> gate_pair; // 게이트 좌표
        std::vector<std::pair<int, int>> direation{{-1, 0}, {0, 1}, {0, -1},{1, 0}}; // 방향좌표 기본 -> 시계 -> 반시계 -> 반대
        int blinkDir = 0; // 게이트 통과 후 뱀 방향
        int lastSpawnTime = 0;
        int coolTime = 0;
        bool isPassingThrought = false;
        int initialTick = 0; // 뱀이 전부 통과했는지 판단하기 위한 시간 측정 변수
};