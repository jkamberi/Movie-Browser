#pragma once
#include "gui.h"

class Browser 
{
private:
	Widget* widget;
	Button* button;
public:
	void update();
	void draw();
	void init();
	~Browser();
};