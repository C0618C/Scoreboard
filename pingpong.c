#include "game.h"
#include "pingpong.h"

void PingPongFactory(struct Game *gameP)
{
    gameP->MaxToPlay = 7;
    gameP->ToWin = 4;
    gameP->Score2Win = 11;       //总分11分
    gameP->FeverPitchScore = 10; //当10平后
    gameP->Lead4Win = 2;         //需领先2分方可获胜

    //方法初始化
    gameP->GameStart = GameStart;

    GameInit(gameP);
}

void GameStart(struct Game *gameP)
{
    //TODO:判断场地方向
    //TODO:判断发球次序
}
