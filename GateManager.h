#include <vector>
#define MAXSPAWNTIME 100
#define MINSPAWNTIME 10 
class GateManager
{
    public:
        static GateManager& Instance();


        void SpawnGate(std::vector<std::vector<int>> &map, int tick);
        std::pair<int, int> BlinkPos(std::pair<int, int> curGate, std::vector<std::vector<int>> &map, int dir); // 게이트 충돌시 다른 게이트의 주변 빈공간 반환
        std::pair<int, int> getGatePos() { return gate;}
        std::pair<int, int> getGate_PairPos() { return gate_pair;}
        void setWallPos(std::pair<int, int> pos) {wallPos.push_back(pos);}
        int getBlinkDir() { return blinkDir; }
    private:
        GateManager();
        
        std::vector<std::pair<int, int>> wallPos; // 벽 좌표들
        static GateManager* _instance;
        std::pair<int, int> gate; // 게이트 좌표
        std::pair<int, int> gate_pair; // 게이트 좌표
        std::vector<std::pair<int, int>> direation{{-1, 0}, {0, 1}, {0, -1},{1, 0}}; // 방향좌표 기본 -> 시계 -> 반시계 -> 반대
        int blinkDir = 0; // 게이트 통과 후 뱀 방향
        int lastSpawnTime = 0;
        int coolTime = 0;
};