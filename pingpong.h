#include "bool.h"
#include "game.h"
#ifndef __PINGPONG_H_
#define __PINGPONG_H_

//用乒乓球规则初始化赛场
void PingPongFactory(struct Game *curGame);

void GameStart(struct Game *curGame);
//bool IsFinish(struct Game *curGame, unsigned int *winner);
#endif