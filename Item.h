#include <vector>
#define DURATION 18 // 아이템 유지 시간(tick)

class item
{
    public:
        item(std::vector<std::vector<int>> &map, int &tick);
        ~item();

        void settingItem();
        int getDuration() { return duration; }
        std::pair<int, int> getPosition() {return pos; }
    private:
        int spawnTime = 0; // 아이템이 생성된 시점
        std::vector<std::vector<int>> &map;
        bool isGrowth; // 아이템 종류 결정
        int duration = DURATION; // 아이템 유지 시간
        std::pair<int, int> pos; // 아이템이 위치하는 좌표
};