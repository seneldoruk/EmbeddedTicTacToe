#include "lib.h"
#include "Player.h"

extern cDevControlPointer pointer;
extern cDevDisplayGraphic disp;

void HumanPlayer::getNextMove()
{
    cDevControlPointer::cData event = pointer.get();
    disp.refresh();
    int lastpos = event.posX;
    while (1)
    {
        event = pointer.get();
        if ((lastpos != event.posX) && gameField->setElementPixel(event.posX, event.posY, value))
        {
            return;
        }
    }
};

void MachinePlayer::getNextMove()
{
    // wait(0.5);
    cSystem::delayMilliSec(700);
    pair<int, int> availablePositions[9];
    int filled = 0;
    // getting available positions
    for (int i = 2; i > -1; i--)
    {
        for (int j = 2; j > -1; j--)
        {
            if (gameField->arr[i][j].value == 0)
            {
                availablePositions[filled] = make_pair(i, j);
                filled = filled + 1;
            }
        }
    }
    int first;
    int second;
    bool testmove;
    // find if game can be won this turn
    for (int i = 0; i < filled; i++)
    {
        first = availablePositions[i].first;
        second = availablePositions[i].second;
        testmove = gameField->testMove(first, second, myval);
        if (testmove)
        {
            gameField->setElementIndex(first, second, myval);
            return;
        }
    }
    // find if opponent can win the game this turn
    for (int i = 0; i < filled; i++)
    {
        first = availablePositions[i].first;
        second = availablePositions[i].second;
        testmove = gameField->testMove(first, second, opponentval);
        if (testmove)
        {
            gameField->setElementIndex(first, second, myval);
            return;
        }
    }
    // find if any corner is available
    pair<int, int> corners[4] = {make_pair(0, 0), make_pair(0, 2), make_pair(2, 0), make_pair(2, 2)};
    for (int i = 0; i < filled; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (availablePositions[i] == corners[j])
            {
                first = availablePositions[i].first;
                second = availablePositions[i].second;
                gameField->setElementIndex(first, second, myval);
                return;
            }
        }
    }
    // all else failed, return first available position
    first = availablePositions[0].first;
    second = availablePositions[0].second;
    gameField->setElementIndex(first, second, myval);
    return;
};
