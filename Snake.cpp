// Snake.cpp

#include <iostream>
#include "Snake.h"
using namespace std;

Snake::Snake(pair<int, int> headPos, int sizeDefault)
{
	Snake::head = headPos; // snake head init

	for (int i = 1; i < sizeDefault; i++) { // snake body init
		Snake::body.push_back({ headPos.first, headPos.second + i});
	}

	snakeLength = SNAKE_DEFAULT; // 스네이크의 길이
}

Snake::Snake() {}

void Snake::moveSnake(vector<vector<int>> &map, char input)
{
	turnSnake(input); // 방향키 입력을 받아 snake의 진행 방향 변경

	body.push_front(head); // snake head가 있던 위치에 body 삽입

	switch (dir) // 진행 방향에 따라 snake의 head 좌표 이동
	{
	case UP:
		head.first--;
		break;
	case RIGHT:
		head.second++;
		break;
	case DOWN:
		head.first++;
		break;
	case LEFT:
		head.second--;
		break;
	}

	Collidable(map); // 충돌 판단
	// snake 좌표 -> map 매핑

	map[head.first][head.second] = HEAD; // 변경된 head 좌표를 map에 매핑
	map[body.front().first][body.front().second] = BODY; // snake head가 있던 위치에 body 배치
	map[body.back().first][body.back().second] = 0; // snake tail(body deque의 back index)좌표를 빈 공간으로 대체

	body.pop_back();
}

void Snake::Collidable(std::vector<std::vector<int>> &map)
{
	if (map[head.first][head.second] == 1 || map[head.first][head.second] == 2)
	{
		Dead();
	}
		
}

void Snake::turnSnake(char key_input)
{
	DIR prev = dir;

	if (key_input == 'L') { //왼쪽 방향키 입력
		dir = LEFT;
	}
	else if (key_input == 'R') { // 오른쪽 방향키 입력
		dir = RIGHT;
	}
	else if (key_input == 'U') { // 위쪽 방향키 입력
		dir = UP;
	}
	else if (key_input == 'D') { // 아래쪽 방향키 입력
		dir = DOWN;
	}
	else return;

	if ((dir + 2) % 4 == prev ) Dead(); // 진행 방향과 반대 방향을 입력하면 게임 오버
}