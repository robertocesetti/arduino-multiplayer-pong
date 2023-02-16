#include <U8glib.h>

class RenderEngine
{
private:
    U8GLIB_SSD1306_128X64 display;
    const int width;
    const int height;

    void clearDisplay();

public:
    RenderEngine();
    ~RenderEngine();
    
    int getWidth() { return width; }
    int getHeight() { return height; }
    void render();
};