#include "graphics.h"
#include "browser.h"
#include "config.h"

void update(float ms)
{
    Browser* app = (Browser*)graphics::getUserData();
    app->update();
}


void draw()
{
    Browser* app = (Browser*)graphics::getUserData();
    app->draw();
}


int main()
{
    Browser app;
    app.init();

    graphics::createWindow(WINDOW_WI, WINDOW_HE, "Movie Browser");

    graphics::setUserData(&app);
    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(WINDOW_WI, WINDOW_HE);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    graphics::startMessageLoop();

    return 0;
}