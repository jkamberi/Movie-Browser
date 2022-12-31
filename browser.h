#pragma once
#include "gui.h"
#include "movie.h"
#include <list>

class Browser 
{
public:
	enum brower_state { STATE_ILDE, STATE_PREVIEW, STATE_SEARCHING };
protected:
	IconButton* search_button;
	Button* selected_b1;

	Movie* movies[15];
	std::list<MovieWindow*> movieWindows;

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