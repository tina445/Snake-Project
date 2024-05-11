#include <vector>
#define DURATION 7

class item
{
    public:
        item(std::vector<std::vector<int>> &map, int tick);
        ~item();

        void settingItem();
        int getDuration() { return duration; }
    private:
        int spawnTime = 0;
        std::vector<std::vector<int>> &map;
        bool isGrowth; 
        int duration = DURATION;
        std::pair<int, int> pos;
};