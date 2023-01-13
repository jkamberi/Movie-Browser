#pragma once
#include "gui.h"
#include "movie.h"
#include <list>

class Browser 
{
public:
	enum brower_state { STATE_ILDE, STATE_PREVIEW, STATE_SEARCHING, STATE_FILTERED, STATE_TYPING, STATE_YEARS };
protected:
	IconButton* search_button;
	Button* selected_b1;
	Button* genreButtons[9];
	Button* yearButton;
	Button* yearButtons[11];
	Button* txtButton;
	Button* clearFilters;

	Movie* movies[12];
	std::list<MovieWindow*> movieWindows;

	MovieWindow* mwindow = nullptr;
	MovieWindow* selectedw = nullptr;

	TextField* txtf;

	brower_state state = STATE_ILDE;
	std::string statetxt = "IDLE";
	std::string genre;
	std::string year;
	float text_size = 17.0f;
public:
	void update();
	void draw();
	void init();

	~Browser();
};