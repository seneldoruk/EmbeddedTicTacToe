#include "DrawTool.h"
#include "lib.h"

extern cDevControlPointer pointer;
extern cDevDisplayGraphic disp;

void DrawTool::drawTable()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            disp.drawFrame(xStart + (i * w), yStart + (j * w), w, w, 5, cHwDisplayGraphic::Red);
        }
    }
}

void DrawTool::drawX(int a, int b)
{
    int x1 = xStart + (w * b) + 5;
    int x2 = (xStart + (w * b)) + w - 10;
    int y1 = yStart + (w * a) + 5;
    int y2 = (yStart + (w * a)) + w - 5;
    disp.drawLine(x1, y2, x2, y1, 5, cHwDisplayGraphic::Green);
    disp.drawLine(x1, y1, x2, y2, 5, cHwDisplayGraphic::Green);
    disp.refresh();
}

void DrawTool::drawO(int a, int b)
{

    int x = xStart + (w * b) + w / 2;
    int y = yStart + (w * a) + w / 2;
    disp.drawCircle(x, y, (w / 2) - 5, cHwDisplayGraphic::Yellow);
    disp.drawCircle(x, y, (w / 2) - 10, cHwDisplayGraphic::Navy);
    disp.refresh();
}

void DrawTool::drawWinner(int from_i, int from_j, int to_i, int to_j, char c)
{
    int x1 = (from_j * w) + xStart + (w / 2);
    int x2 = (to_j * w) + xStart + (w / 2);
    int y1 = (from_i * w) + yStart + (w / 2);
    int y2 = (to_i * w) + yStart + (w / 2);
    disp.drawLine(x1, y1, x2, y2, 10, cHwDisplayGraphic::White);
    // disp.drawRectangle(130, 100, 550, 200, cHwDisplayGraphic::Black);
    // so line can be seen better
    disp.drawRectangle(240, 133, 300, 40, cHwDisplayGraphic::Black);
    if (c == 0)
    {
        disp.drawText(280, 140, 0, "Unentschieden");
    }
    else
    {
        disp.drawText(280, 135, 0, "%0c hat gewonnen", c);
    }
    disp.drawRectangle(130, 258, 550, 40, cHwDisplayGraphic::Black);
    disp.drawText(150, 233 + 30, 0, "<<Klicken um wieder zu spielen>>", c);
    disp.refresh();
}
