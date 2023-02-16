//#include <U8glib.h>

typedef struct Display {
    //U8GLIB_SSD1306_128X64 device;
    void * device;
    int width;
    int height;
} Display;

typedef struct RenderEngine {
    //U8GLIB_SSD1306_128X64 device;
    Display * display;
} RenderEngine;


void initializeRender(RenderEngine *renderEngine);

void render(void);