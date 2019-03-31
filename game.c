#include <MATH.H>
#include "game.h"

//统计出数值里有多少个1
unsigned int CountNum(unsigned int score)
{
    unsigned int count = 0;
    while (score)
    {
        score = score & --score;
        count++;
    }
    return count;
}

//得出传入玩家的对手
unsigned int _AnotherPlayer(unsigned int CurPlayer)
{
    return CurPlayer == PLAYER01 ? PLAYER02 : PLAYER01;
}

//处理每次得分之后的公共逻辑
void OneScoreUp(struct GameStatus *gs, unsigned int score, unsigned int *playerScore)
{
    (*playerScore) += score;
    ++gs->BallSrvCount;

    if (gs->BallSrvCount >= gs->curGameP->ServerTime)
    {
        gs->BallSrvCount = 0;
        gs->HasBallSrv = _AnotherPlayer(gs->HasBallSrv);
    }
}

void Player1GetScore(struct GameStatus *gs, unsigned int score)
{
    OneScoreUp(gs, score, &(gs->Player1Score));
}
void Player2GetScore(struct GameStatus *gs, unsigned int score)
{
    OneScoreUp(gs, score, &(gs->Player2Score));
}

void GameInit(struct Game *gg)
{
    gg->gameStatus.curGameP = gg;

    gg->Player1GetScore = Player1GetScore;
    gg->Player2GetScore = Player2GetScore;

    //gg->IsWin = IsWin;
}

bool GetIsWin(struct Game *curGame, unsigned int *winner)
{
    if (curGame->gameStatus.Player1Score >= curGame->Score2Win && curGame->gameStatus.Player2Score < curGame->FeverPitchScore)
    {
        *winner = PLAYER01;
        return true;
    }
    else if (curGame->gameStatus.Player2Score >= curGame->Score2Win && curGame->gameStatus.Player1Score < curGame->FeverPitchScore)
    {
        *winner = PLAYER02;
        return true;
    }
    else if (curGame->gameStatus.Player1Score > curGame->FeverPitchScore && curGame->gameStatus.Player2Score > curGame->FeverPitchScore && abs(curGame->gameStatus.Player1Score - curGame->gameStatus.Player2Score) >= curGame->Lead4Win)
    {
        if (curGame->gameStatus.Player1Score > curGame->gameStatus.Player2Score)
            *winner = PLAYER01;
        else
            *winner = PLAYER02;
        return true;
    }

    return false;
}