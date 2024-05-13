// Snake.h
#ifndef SNAKE
#define SNAKE

#include <deque>
#include <vector>

#define SNAKE_DEFAULT 3 // snake의 기본 사이즈

class Snake {
    public:
        Snake(std::pair<int, int> headPos, int sizeDefault);
        Snake();

        void moveSnake(std::vector<std::vector<int>> &map, char input);
        void turnSnake(char key_input);
        void snakeLocate(std::vector<std::vector<int>> &map);
        void Collidable(std::vector<std::vector<int>> &map);
        int getSize();
        void Dead();

    public:
        enum DIR // 진행방향
        {
            UP, RIGHT, DOWN, LEFT
        };
        
        DIR dir = LEFT; //��Ӹ� �ڵ� �̵� ����
    private:
        int growCount{}, poisonCount{}, gateCount{};
        std::deque<std::pair<int, int>> body;
        std::pair<int, int> head;

        enum STATE // 스네이크 상태 (다른 오브젝트와의 상호작용)
        {
            NONE, GROW, GROWLESS, BLINKING // NONE: 상호작용하지 않은 상태 GROW: growth 아이템 획득 상태 GROWLESS: poison 아이템 획득 상태 blinking 게이트로 이동 중인 상태
        };
        STATE state = NONE;
        
    };
#endif /* SNAKE */