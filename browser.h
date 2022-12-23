#pragma once
#include "gui.h"
#include "movie.h"

class Browser 
{
private:
	Widget* widget;
	Button* button;
	MovieWindow* mwindow = nullptr;

	Button* button_menu[7];
	MovieWindow* movieWindows[6];

public:
	void update();
	void draw();
	void init();
	~Browser();
};