#ifndef OBJECTID
#define OBJECTID

// 빈 공간 0 벽 1 모서리 2 스네이크 body 3 head 4 아이템 + 5 - 6 게이트 입구 7 출구 8
enum obj { space = 0, wall = 1, Iwall = 2, body = 3, head = 4, growth = 5, poison = 6, gate = 7, gate_pair = 8};

#endif /* OBJECTID */