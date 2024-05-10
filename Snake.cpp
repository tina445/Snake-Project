// Snake.cpp

#include <iostream>
#include "Snake.h"
using namespace std;

Snake::Snake(pair<int, int> headPos)
{
	Snake::head = headPos;
	Snake::tail.push_back({ headPos.first - 1, headPos.second });
	Snake::tail.push_back({ headPos.first - 2, headPos.second });
}

void Snake::SnakeLogic()
{
	//pair<int, int> prev = tail[0];
	//tail[0].first = head.first;
	//tail[0].second = head.second;

	tail[tail.size()-1].first = head.first;
	tail[tail.size()-1].second = head.second;

	switch (dir)
	{
	case UP:
		head.second--;
		break;
	case RIGHT:
		head.first--;
		break;
	case DOWN:
		head.second++;
		break;
	case LEFT:
		head.first++;
		break;
	}

	//pair<int, int> tmpPrev;
	//for (auto iter = tail.begin() + 1; iter != tail.end(); iter++)
	//{
	//	tmpPrev = (*iter);
	//	(*iter) = prev;
	//	prev = tmpPrev;
	//}
}

void Snake::turnSnake()
{
	if () //왼쪽 방향키 입력
		dir = static_cast<DIR>((dir - 1 + 4) % 4);
	else if () // 오른쪽 방향키 입력
		dir = static_cast<DIR>((dir + 1) % 4);


}
