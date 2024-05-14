// Snake.cpp

#include "Snake.h"
#include "ItemManager.h"
#include "objectid.h"

using namespace std;

Snake::Snake(pair<int, int> headPos, int sizeDefault)
{
	Snake::head = headPos; // snake head init

	for (int i = 1; i < sizeDefault; i++) { // snake body init
		Snake::body.push_back({ headPos.first, headPos.second + i});
	}
}

Snake::Snake() {}

void Snake::moveSnake(vector<vector<int>> &map, char input)
{
	state = NONE; //뱀 성장, 축소, 유지 상태 판단
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
	map[head.first][head.second] = OBJECTID::head; // 변경된 head 좌표를 map에 매핑
	map[body.front().first][body.front().second] = OBJECTID::body; // snake head가 있던 위치에 body 배치

	switch (state)
	{
	case NONE:
		map[body.back().first][body.back().second] = 0; // snake tail(body deque의 back index)좌표를 빈 공간으로 대체
		body.pop_back();
		break;
	case GROW: // 진행방향으로 snake tail(body deque의 back index)를 유지
		break;
	case GROWLESS:
		map[body.back().first][body.back().second] = 0; 
		body.pop_back(); // 첫번째 실행은 이동 처리
		map[body.back().first][body.back().second] = 0; 
		body.pop_back(); // 두번째 실행은 snake tail 삭제
		break;
	}
}

void Snake::Collidable(std::vector<std::vector<int>> &map)
{
	if (map[head.first][head.second] == wall || map[head.first][head.second] == Iwall || map[head.first][head.second] == OBJECTID::body) // 벽 또는 자신의 몸통에 충돌하면 게임 오버
		Dead();
	else if (map[head.first][head.second] == growth) //성장 아이템 충돌
	{
		itemManager::instance().destroyItem(map, {head.first, head.second});
		growCount++; // 성장 아이템 획득 횟수 기록
		state = GROW;
	}
	else if (map[head.first][head.second] == poison) //독성 아이템 충돌
	{
		poisonCount++; // 독성 아이템 획득 횟수 기록
		itemManager::instance().destroyItem(map, {head.first, head.second});
		state = GROWLESS;
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

int Snake::getSize() { // 스네이크 길이 반환
	return body.size() + 1;
}

int Snake::getitemCount(int s) { // s = 0일 경우(default) poison 카운트 return, 1일 경우 growth 카운트 return
	if (s) return growCount;

	return poisonCount;
}