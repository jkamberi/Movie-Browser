#include "graphics.h"


void update(float ms)
{

}


void draw()
{

}


int main()
{
    graphics::createWindow(1200, 600, "Movie Browser");

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(1000, 500);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    graphics::Brush br;
    br.fill_color[0] = 0.5f;
    br.fill_color[1] = 0.7f;
    br.fill_color[2] = 0.9f;
    graphics::setWindowBackground(br);

    graphics::setFont("assets\\orange juice 2.0.ttf");

    graphics::startMessageLoop();

    return 0;
}