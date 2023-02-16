#include "render-engine.h"
#include <U8glib.h>

RenderEngine::RenderEngine() : display(U8G_I2C_OPT_NONE | U8G_I2C_OPT_FAST), width(display.getWidth()), height(display.getHeight())
{
    this->clearDisplay();
}

RenderEngine::~RenderEngine()
{
}

void RenderEngine::render()
{
    char strBuf[16]; // used for string formatting

    display.firstPage();
    do
    {
        // Display the "You Lose" screen
        display.setFont(u8g_font_gdb20r); // switch to bigger font
        strcpy(strBuf, "TRY");
        display.drawStr((width - display.getStrPixelWidth(strBuf)) / 2, height / 2, strBuf);
        strcpy(strBuf, "AGAIN!");
        display.drawStr((width - display.getStrPixelWidth(strBuf)) / 2, height, strBuf);
        display.setFont(u8g_font_profont10r); // switch back to our normal font
    } while (display.nextPage());
}

void RenderEngine::clearDisplay()
{
    // Clear the screen
    display.firstPage();
    do
    {
    } while (display.nextPage());
}