#pragma once
#include "gui.h"
#include "movie.h"

class Browser 
{
private:
	Widget* widget;
	Button* button;
	Movie* lostHighway;
	MovieWindow* mwindow;

	Button* button_menu[7];
public:
	void update();
	void draw();
	void init();
	~Browser();
};