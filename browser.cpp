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
	//widget = new Widget();
	//widget->set_w(65.f);

	//button = new Button();

	//Button* b = new Button();

	// some generic buttons
	for (int i = 0; i < 7; i++)
		button_menu[i] = new Button(80, 35, 75, (WINDOW_HE/2 - 175) + 50*i, "Button " + std::to_string(i+1));

	// movies initialization
	lostHighway = new Movie("Lost Highway", "David Lynch", "Bill Pullman, Patricia Arquette, John Roselius", "Mystery, Thriller", "1997", "lh2.png");
	mwindow = new MovieWindow(WINDOW_HE/4, WINDOW_WI/5, WINDOW_WI/2 - 480, WINDOW_HE/2 - 240, *lostHighway);
}

void Browser::draw()
{
	graphics::Brush br;

	// background
	//br.texture = ASSET_PATH + std::string("ba.jpg");
	SETCOLOR(br.fill_color, 0.1f, 0.f, 0.f);
	SETCOLOR(br.fill_secondary_color, 0, 0, 0);
	br.outline_opacity = 0;
	br.gradient = true;
	br.gradient_dir_u = 4.f;
	br.gradient_dir_v = 0.f;
	
	graphics::drawRect(WINDOW_WI/2, WINDOW_HE/2, WINDOW_WI, WINDOW_HE, br);

	// test

	//widget->draw();
	//button->draw();
	mwindow->draw();

	for (auto button : button_menu)
		button->draw();
}

Browser::~Browser()
{
}
