#include "game.h"
#include "pingpong.h"

//初始化乒乓球规则
void PingPongFactory(struct Game *gameP)
{
    gameP->MaxToPlay = 7;
    gameP->ToWin = 4;
    gameP->Score2Win = 11;       //总分11分
    gameP->FeverPitchScore = 10; //当10平后
    gameP->Lead4Win = 2;         //需领先2分方可获胜

    gameP->ServerTime = 2; //每两分换一次发球

    //方法初始化
    gameP->GameStart = GameStart;
    gameP->NextGame = NextGame;
    gameP->IsWin = GetIsWin;

    GameInit(gameP);
}

//从0:0 开始比赛
void GameStart(struct Game *gameP)
{
    //判断场地方向

    //判断发球次序
    gameP->gameStatus.HasBallSrv = PLAYER02; //TODO:第一次发球顺序得随机生成
    gameP->gameStatus.BallSrvCount = 0;
    
    gameP->gameStatus.PlayCount = 0;
}

void NextGame(struct Game *gameP)
{
    //TODO: 计算回合胜利情况

    //得分清零
    gameP->gameStatus.Player1Score = 0;
    gameP->gameStatus.Player2Score = 0;
}
