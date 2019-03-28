#include "game.h"
#include "pingpong.h"

void PingPongFactory(struct Game *curGame)
{
    curGame->MaxToPlay = 7;
    curGame->ToWin = 4;
    curGame->Score2Win = 11;       //总分11分
    curGame->FeverPitchScore = 10; //当10平后
    curGame->Lead4Win = 2;         //需领先2分方可获胜

    //方法初始化
    curGame->GameStart = GameStart;

    GameInit(curGame);
}

void GameStart(struct Game *cGame)
{
    //TODO:判断场地方向
    //TODO:判断发球次序
}
