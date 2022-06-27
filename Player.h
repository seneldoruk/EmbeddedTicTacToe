#ifndef PLAYER_H
#define PLAYER_H

#include <utility>
#include "GameField.h"
using namespace std;


class Player
{
public:
    char myval;
    char opponentval;
    // class rather than array
    virtual void getNextMove(){};
};

class HumanPlayer : public Player
{

public:
    GameField *gameField;
    char value;
    HumanPlayer(char val, GameField *field)
    {
        value = val;
        gameField = field;
    }

    virtual void getNextMove();
};

class MachinePlayer : public Player
{
public:
    GameField *gameField;
    MachinePlayer(char val, GameField *field)
    {
        gameField = field;
        myval = val;
        if (myval == 'O')
        {
            opponentval = 'X';
        }
        else
        {
            opponentval = 'O';
        }
    }

    virtual void getNextMove();
};
#endif
