//*******************************************************************
#include "lib.h"
#include "Module/RTOS.h"
#include "Player.h"
#include "GameField.h"
#include "DrawTool.h"
//*******************************************************************
#if defined _MCU_TYPE_STM32L1XX
#include "configSTM32L1xx.h"
#elif defined _MCU_TYPE_STM32F7XX
#include "configSTM32F7xx.h"
#elif defined _MCU_TYPE_LPC1758
#include "configLPC1758.h"
#elif defined _MCU_TYPE_VIRTUAL
#include "configVirtual.h"
#else
#error "Device type not defined"
#endif

//*******************************************************************
bool getUserInput(char c)
{
    disp.clear();
    cDevControlPointer::cData event = pointer.get();
    disp.drawText(290, 150, 0, "Spieler fuer %1c", c);

    disp.drawFrame(50, 250, 200, 100, 1, cHwDisplayGraphic::Yellow);
    disp.drawText(90, 283, 0, "Machine");

    disp.drawFrame(550, 250, 200, 100, 1, cHwDisplayGraphic::Yellow);
    disp.drawText(600, 283, 0, "Mensch");
    int lastx = pointer.get().posX;
    while (1)
    {
        disp.refresh();
        event = pointer.get();
        if (event.posX != lastx)
        {
            if (event.posX > 50 && event.posX < 250 && event.posY > 250 && event.posY < 350)
            {
                disp.drawRectangle(50, 250, 200, 100, cHwDisplayGraphic::Yellow);
                disp.refresh();
                cSystem::delayMilliSec(1000);
                disp.clear();
                return true;
            }
            else if (event.posX > 550 && event.posX < 750 && event.posY > 250 && event.posY < 350)
            {
                disp.drawRectangle(550, 250, 200, 100, cHwDisplayGraphic::Yellow);
                disp.refresh();
                cSystem::delayMilliSec(1000);
                disp.clear();

                return false;
            }
        }
    }
}

void startGame()
{
    int xStart = 190;
    int yStart = 15;
    int width = 150;
    bool isMachineX = getUserInput('X');
    bool isMachineO = getUserInput('O');
    disp.clear();
    GameField field(xStart, yStart, width);
    Player *playerX;
    Player *playerO;
    if (isMachineX)
    {
        playerX = new MachinePlayer('X', &field);
    }
    else
    {
        playerX = new HumanPlayer('X', &field);
    }
    if (isMachineO)
    {
        playerO = new MachinePlayer('O', &field);
    }
    else
    {
        playerO = new HumanPlayer('O', &field);
    }

    disp.refresh();
    cDevControlPointer::cData event = pointer.get();

    while (1)
    {
        playerX->getNextMove();
        event = pointer.get();
        if (field.isEnded)
        {
            break;
        }
        disp.refresh();
        playerO->getNextMove();
        event = pointer.get();
        if (field.isEnded)
        {
            break;
        }
        disp.refresh();
    }
    int lastx = event.posX;
    int lasty = event.posY;
    bool isNotClicked =
        lastx == pointer.get().posX || event.posX <= 0 || event.posX > 1000 || lasty == pointer.get().posY ||
        event.posY <= 0 || event.posX > 500;
    while (isNotClicked)
    {
        event = pointer.get();
        isNotClicked =
            lastx == pointer.get().posX || event.posX <= 0 || event.posX > 1000 || lasty == pointer.get().posY ||
            event.posY <= 0 || event.posX > 500;
    }
}

/*************************************************************************/
int main(void)
{

#ifdef USE_GRAPHIC_DISPLAY
    disp.setBackColor(cHwDisplayGraphic::Navy);
    disp.clear();
#endif

    while (1)
    {
#ifdef USE_GRAPHIC_DISPLAY
        cDevControlPointer::cData event = pointer.get();
        startGame();
        disp.refresh();

#endif
    }
}

// EOF
