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
}