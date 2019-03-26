#ifndef __GAME_H_
#define __GAME_H_

struct GameStatus
{
    //当场双方成绩
    unsigned int Player1Score;
    unsigned int Player2Score;

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
    //每次连续发球次数
    unsigned int ServerTime;
    //

    struct GameStatus gameStatus;

    /*
    //当场是否已分出胜负
    bool (*IsFinish)();
    //是否比赛已结束——已达到胜利标准
    bool (*IsEndAll)();

    //当场获胜者
    unsigned int (*CurVictory)();
    //最终赢家
    unsigned int (*TheWinner)();

    //是否需要交换赛场
    bool (*IsNeedChangeSide)();
*/
    //得分
    void (*Player1GetScore)(struct GameStatus *gs, unsigned int score);
    void (*Player2GetScore)(struct GameStatus *gs, unsigned int score);
};

unsigned int CountNum(unsigned int score);
void GameInit(struct Game *gg);
#endif