#pragma once
#include "gui.h"
#include "movie.h"

class Browser 
{
public:
	enum brower_state { STATE_ILDE, STATE_PREVIEW, STATE_SEARCHING };
protected:
	Widget* widget;
	Button* search_button;

	MovieWindow* mwindow = nullptr;
	MovieWindow* selectedw = nullptr;

	Button* button_menu[7];
	Movie* movies[6];
	MovieWindow* movieWindows[6];

	brower_state state = STATE_ILDE;
	std::string statetxt = "STATE_IDLE";
public:
	void update();
	void draw();
	void init();

	~Browser();
};