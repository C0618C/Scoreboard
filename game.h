#include "bool.h"

#ifndef __GAME_H_
#define __GAME_H_

#define PLAYER01 0
#define PLAYER02 1

unsigned int CountNum(unsigned int score);
void GameInit(struct Game *gg);
bool IsWin(struct Game *curGame, unsigned int *winner);

struct GameStatus
{
    //当场双方成绩
    int Player1Score;
    int Player2Score;

    //已赢场次
    //用8位来表示8场比赛 低位为第一场1010 1101表示 1、3、4、6、8赢得了胜利
    //当已经过去的比赛双方为0时则是平局
    unsigned long Player1Win;
    unsigned long Player2Win;

    //已比盘数
    unsigned int PlayCount;

    //当前发球权
    unsigned int HasBallSrv;
    //已连续发球次数
    unsigned int BallSrvCount;
};

struct Game
{
    //总场次
    unsigned int MaxToPlay;
    //获胜所需场次
    unsigned int ToWin;
    //总分数
    unsigned int Score2Win;
    //白热化阶段开始分数
    unsigned int FeverPitchScore;
    //白热化阶段领先分数
    unsigned int Lead4Win;

    //每次连续发球次数
    unsigned int ServerTime;
    //

    struct GameStatus gameStatus;

    //当场是否已分出胜负
    //bool (*IsWin)(struct Game *curGame, unsigned int *winner);
    //是否比赛已结束——已达到胜利标准
    bool (*IsEndAll)(struct Game *curGame, unsigned int *winner);

    //当场获胜者
    //unsigned int (*CurVictory)(struct Game *curGame);
    //最终赢家
    unsigned int (*TheWinner)(struct Game *curGame);

    //是否需要交换赛场
    bool (*IsNeedChangeSide)(struct Game *curGame);

    //得分
    void (*Player1GetScore)(struct GameStatus *gs, unsigned int score);
    void (*Player2GetScore)(struct GameStatus *gs, unsigned int score);

    //开始游戏 —— 处理发球顺序，场地位置等
    void (*GameStart)(struct Game *gs);
};

#endif