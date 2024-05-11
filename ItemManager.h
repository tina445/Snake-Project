class item;
class itemManager
{
    public:
        static itemManager& instance()
        {
            if (_instance == nullptr)
                _instance = new itemManager();

            return *_instance;
        }

        void spawnItem(std::vector<std::vector<int>> &map, int tick);
        void destroyItem(int curTime);
        int getItemNum() { return itemNum; }

    private:
        itemManager();
        static itemManager* _instance;
        int itemNum = 0;
        item* itemArr[3];
        int lastSpawnTick = 0;
        int coolTime = 3;
};