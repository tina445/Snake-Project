// Snake.h
#ifndef SNAKE
#define SNAKE

#pragma once
#include "GameMap.h"
#include <deque>
#include <vector>

#define STARTPOS 10 // 시작시 snake head가 위치할 좌표
#define SNAKE_DEFAULT 3 // snake의 기본 사이즈

#define BODY 3 // snake body id
#define HEAD 4 // snake head id

class Snake {
    public:
        Snake(std::pair<int, int> headPos, int sizeDefault);
        Snake();

        void moveSnake(std::vector<std::vector<int>> &map, char input);
        void turnSnake(char key_input);
        void snakeLocate(std::vector<std::vector<int>> &map);
        void Collidable(std::vector<std::vector<int>> &map);
        void Dead();

    public:
        enum DIR
        {
            UP, RIGHT, DOWN, LEFT
        };
        std::deque<std::pair<int, int>> body;
        std::pair<int, int> head;
        DIR dir = LEFT; //��Ӹ� �ڵ� �̵� ����
        int snakeLength;
    private:
        enum STATE
        {
            NONE, GROW, GROWLESS
        };
        STATE state = NONE;
    };
#endif /* SNAKE */