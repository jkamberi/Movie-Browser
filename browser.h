#pragma once
#include "gui.h"
#include "movie.h"

class Browser 
{
public:
	enum brower_state { STATE_ILDE, STATE_PREVIEW, STATE_SEARCHING };
protected:
	IconButton* search_button;
	Button* selected_b;

	Movie* movies[12];
	MovieWindow* movieWindows[12];

	MovieWindow* mwindow = nullptr;
	MovieWindow* selectedw = nullptr;

	brower_state state = STATE_ILDE;
	std::string statetxt = "IDLE";
public:
	void update();
	void draw();
	void init();

	~Browser();
};