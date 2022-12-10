#include "browser.h"
#include "gui.h"
#include "graphics.h"
#include "config.h"

void Browser::update()
{
}

void Browser::init()
{
	// widget initialization
	widget = new Widget();
	widget->set_w(65.f);

	button = new Button(90.f, 40.f, 200.f, 200.f, "button");
}

void Browser::draw()
{
	graphics::Brush br;

	// background
	//br.texture = ASSET_PATH + std::string("800252.png");
	SETCOLOR(br.fill_color, 0.1f, 0.f, 0.f);
	SETCOLOR(br.fill_secondary_color, 0, 0, 0);
	br.outline_opacity = 0;
	br.gradient = true;
	br.gradient_dir_u = 4.f;
	br.gradient_dir_v = 0.f;
	
	graphics::drawRect(WINDOW_WI/2, WINDOW_HE/2, WINDOW_WI, WINDOW_HE, br);

	widget->draw();
	button->draw();
}

Browser::~Browser()
{
}
