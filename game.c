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

void Player1GetScore(struct GameStatus *gs, unsigned int score)
{
    gs->Player1Score += score;
}
void Player2GetScore(struct GameStatus *gs, unsigned int score)
{
    gs->Player2Score += score;
}

void GameInit(struct Game *gg)
{
    gg->gameStatus.Player1Score = 0;
    gg->gameStatus.Player2Score = 0;

    gg->Player1GetScore = Player1GetScore;
    gg->Player2GetScore = Player2GetScore;

    gg->IsWin = IsWin;
}

bool IsWin(struct Game *curGame, unsigned int *winner)
{
    if (curGame->gameStatus.Player1Score >= curGame->Score2Win && curGame->gameStatus.Player1Score - curGame->gameStatus.Player2Score < curGame->FeverPitchScore)
    {
        *winner = PLAYER01;
        return true;
    }
    else if (curGame->gameStatus.Player2Score >= curGame->Score2Win && curGame->gameStatus.Player2Score - curGame->gameStatus.Player1Score < curGame->FeverPitchScore)
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