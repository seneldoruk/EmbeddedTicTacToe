#include "DrawTool.h"
#ifndef GAMEFIELD_H
#define GAMEFIELD_H
class Square
{
public:
    int xStart;
    int yStart;
    int width;
    int xEnd;
    int yEnd;
    char value;
    Square(){};

    Square(int x, int y, int w)
    {
        value = 0;
        xStart = x;
        yStart = y;
        width = w;
        xEnd = xStart + width;
        yEnd = yStart + width;
    };
    bool setElement(char c)
    {
        if (value == 0)
        {
            value = c;
            return true;
        }
        return false;
    }
    bool checkAvailable(int x, int y)
    {
        return x > xStart && x < xEnd && y > yStart && y < yEnd && value == 0;
    }
};

class GameField
{
public:
    static const int widthElement = 3;
    int xStart;
    int yStart;
    int width;
    int xEnd;
    int yEnd;
    Square arr[widthElement][widthElement];
    int center;
    bool isEnded;
    DrawTool drawTool;
    GameField(){};
    GameField(int xStart, int yStart, int width) : drawTool(xStart, yStart, width)
    {
        isEnded = false;
        xStart = xStart;
        yStart = yStart;
        width = width;
        int elementXStart;
        int elementYStart;
        for (int i = 0; i < widthElement; i++)
        {
            for (int j = 0; j < widthElement; j++)
            {
                elementXStart = xStart + (j * width);
                elementYStart = yStart + (i * width);
                arr[i][j] = Square(elementXStart, elementYStart, width);
            }
        }
        center = (widthElement / 2);
    };
    bool checkIsEnded(int i, int j, char val)
    {
        bool horizontal = checkHorizontal(i, val);
        bool vertical = checkVertical(j, val);
        bool diagonalTop = checkDiagonalTopLeft(val);
        bool diagonalBottom = checkDiagonalBottomLeft(val);
        bool noFreeSquare = checkFreeSquares();
        if (horizontal || vertical || diagonalTop || diagonalBottom || noFreeSquare)
        {
            isEnded = true;
            if(vertical){
                drawTool.drawWinner(0, j, widthElement-1, j, val);
            }
            else if(horizontal){
                drawTool.drawWinner(i,0,i,widthElement-1, val);
            }
            else if(diagonalTop){
                drawTool.drawWinner(0,0,widthElement-1, widthElement-1, val);
            }
            else if (diagonalBottom){
                drawTool.drawWinner(widthElement-1,0,0,widthElement-1, val);
            }
            else if(noFreeSquare){
                drawTool.drawWinner(0, 0, 0, 0, 0);
            }
            return true;
        }
        return false;
    };
    bool testMove(int i, int j, char val)
    {
        arr[i][j].value = val;
        bool horizontal = checkHorizontal(i, val);
        bool vertical = checkVertical(j, val);
        bool diagonalTop = checkDiagonalTopLeft(val);
        bool diagonalBottom = checkDiagonalBottomLeft(val);
        if (horizontal || vertical || diagonalTop || diagonalBottom)
        {
            arr[i][j].value = 0;
            return true;
        }
        arr[i][j].value = 0;
        return false;
    };
    bool checkHorizontal(int i, char val)
    {
        for (int j = 0; j < widthElement; j++)
        {
            if (val != arr[i][j].value)
            {
                return false;
            }
        }
        return true;
    };
    bool checkVertical(int j, char val)
    {
        for (int i = 0; i < widthElement; i++)
        {
            if (val != arr[i][j].value)
            {
                return false;
            }
        }
        return true;
    };
    bool checkDiagonalTopLeft(char val)
    {
        // left to right 0,0 -> width, width
        // right to left 0,width -> width, 0
        for (int i = 0; i < widthElement; i++)
        {
            if (arr[0 + i][0 + i].value != val)
            {
                return false;
            }
        }
        return true;
    };
    bool checkDiagonalBottomLeft(char val)
    {
        for (int i = 0; i < widthElement; i++)
        {
            if (arr[widthElement - 1 - i][0 + i].value != val)
            {
                return false;
            }
        }
        return true;
    };
    bool checkFreeSquares(){
        for (int i = 0; i < widthElement; i++)
        {
            for (int j = 0; j < widthElement; j++)
            {
                if(arr[i][j].value != 'X' && arr[i][j].value != 'O'){
                    return false;
                }
            }
            
        }
        return true;
        
    }
    bool setElementIndex(int i, int j, char c)
    {
        if (arr[i][j].setElement(c))
        {
            switch (c)
            {
            case 'X':
                drawTool.drawX(i, j);
                break;
            case 'O':
                drawTool.drawO(i, j);
                break;
            }
            checkIsEnded(i, j, c);
            return true;
        }
        return false;
    };
    bool setElementPixel(int x, int y, char c)
    {
        for (int i = 0; i < widthElement; i++)
        {
            for (int j = 0; j < widthElement; j++)
            {
                if (arr[i][j].checkAvailable(x, y))
                {
                    if (arr[i][j].setElement(c))
                    {
                        switch (c)
                        {
                        case 'X':
                            drawTool.drawX(i, j);
                            break;
                        case 'O':
                            drawTool.drawO(i, j);
                            break;
                        }
                        checkIsEnded(i, j, c);
                        return true;
                    }
                    return false;
                }
            }
        }
        return false;
    };
};
#endif
