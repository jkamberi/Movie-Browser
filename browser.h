#pragma once
#include "widget.h"
#include "button.h"
#include "iconButton.h"
#include "movieWindow.h"
#include "textField.h"
#include "movie.h"
#include <list>

class Browser 
{
public:
	enum brower_state { STATE_ILDE, STATE_PREVIEW, STATE_SEARCHING, STATE_YEARS, STATE_FILTERED_by_GENRE, STATE_FILTERED_by_YEAR, STATE_FILTERED_by_TXT };
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