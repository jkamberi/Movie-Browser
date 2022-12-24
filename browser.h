#pragma once
#include "gui.h"
#include "movie.h"

class Browser 
{
public:
	enum brower_state { STATE_ILDE, STATE_PREVIEW, STATE_SEARCHING };
protected:
	Widget* widget;
	Button* button;

	Description* desc = nullptr;

	MovieWindow* mwindow = nullptr;
	MovieWindow* selectedw = nullptr;

	Button* button_menu[7];
	MovieWindow* movieWindows[6];

	brower_state state = STATE_ILDE;
	std::string statetxt = "STATE_IDLE";
public:
	void update();
	void draw();
	void init();

	~Browser();
};