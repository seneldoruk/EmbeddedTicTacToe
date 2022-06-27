#ifndef DRAWTOOL_H
#define DRAWTOOL_H
class DrawTool
{
public:
    int xStart;
    int yStart;
    int w;

    DrawTool(int x, int y, int width)
    {
        xStart = x;
        yStart = y;
        w = width;
        drawTable();
    }

    DrawTool(){};

    void drawTable();

    void drawX(int a, int b);

    void drawO(int a, int b);

    void drawWinner(int from_i, int from_j, int to_i, int to_j, char c);
};
#endif
