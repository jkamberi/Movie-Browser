#include "browser.h"
#include "gui.h"
#include "graphics.h"
#include "config.h"
#include <iostream>

void Browser::update()
{
	for (auto m : movieWindows)
		m->update();

	graphics::MouseState ms;
	graphics::getMouseState(ms);

	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasX(ms.cur_pos_y);

	// Selecting a Movie and on-click events
	// When we select a movie the description of the movie is shown in the botton of the screen
	for (auto m : movieWindows) 
	{
		if (m->contains(mx, my)) {
			m->setHovered(true);
			selectedw = m;
		}
		else {
			m->setHovered(false);
		}
	}

	if (ms.button_left_pressed && state == STATE_PREVIEW) // if we click again the description is closed
	{
		mwindow->selected(false);
		selectedw = nullptr;
		mwindow = nullptr;
		state = STATE_ILDE;
		statetxt = "IDLE";
	} 
	else if (ms.button_left_pressed && selectedw && selectedw->contains(mx, my)) // the first time we select a movie
	{
		mwindow = selectedw;
		mwindow->selected(true);
		state = STATE_PREVIEW;
		statetxt = "PREVIEW";
		for (auto m : movieWindows)
		{
			if (m != mwindow)
				m->selected(false);
		}
	} 

	// Hovering Buttons and on-click events
	// In this button we expand the searching menu
	if (search_button->contains(mx, my)) {
		search_button->setHovered(true);
		selected_b = search_button;
	}
	else {
		search_button->setHovered(false);
	}

	if (ms.button_left_pressed && state == STATE_SEARCHING) 
	{
		state = STATE_ILDE;
		statetxt = "IDLE";
	}
	else if (ms.button_left_pressed && selected_b && selected_b->contains(mx, my))
	{
		state = STATE_SEARCHING;
		statetxt = "SEARCHING";
	}

}

void Browser::init()
{
	// Movie Descriptions
	std::string lostHighway_desc = "Anonymous videotapes presage a musician's murder conviction, and a gangster's girlfriend leads a mechanic astray.";
	std::string theHunt_desc = "A teacher lives a lonely life, all the while struggling over his son's custody. His life slowly gets better as he finds";
	std::string theHunt_desc2 = "love and receives good news from his son, but his new luck is about to be brutally shattered by an innocent little lie.";

	// Some generic buttons
	// 
	//for (int i = 0; i < 7; i++)
	//	button_menu[i] = new Button(80, 35, 75, (CANVAS_HE/2 - 175) + 50*i, "Button " + std::to_string(i+1));

	search_button = new IconButton("arrow_forward.png");

	// Movies initialization
	movies[0] = new Movie("The Hunt (Jagten)", "Thomas Vinterberg", "Mads Mikkelsen, Thomas Bo Larsen, Annika Wedderkopp", "Drama", "", "2012", theHunt_desc, theHunt_desc2, "hunt.png");
	for (int i = 1; i < 13; i++)
		movies[i] = new Movie();

	// Movie Window Initialization
	for (int i = 0; i < 6; i++) {
		movieWindows[i] = new MovieWindow(P_WIDTH, P_HEIGHT, INIT_POS_X + 50 + (i) * (P_WIDTH + 20), INIT_POS_Y, *movies[i]);
		movieWindows[i+6] = new MovieWindow(P_WIDTH, P_HEIGHT, INIT_POS_X + 50 + (i)* (P_WIDTH + 20), INIT_POS_Y + P_HEIGHT + 50, *movies[i+6]);
	}
	 

}

void Browser::draw()
{
	graphics::Brush br;

	// background
	SETCOLOR(br.fill_color, 0.2f, 0.2f, 0.2f);
	SETCOLOR(br.fill_secondary_color, 0.01f, 0.01f, 0.01f);
	br.outline_opacity = 0;
	br.gradient = true;
	br.gradient_dir_u = 6.f;
	br.gradient_dir_v = 0.f;
	
	graphics::drawRect(CANVAS_WI/2, CANVAS_HE/2, CANVAS_WI, CANVAS_HE, br);

	// test
	graphics::Brush text;
	text.outline_opacity = 0;
	SETCOLOR(text.fill_color, 1, 1, 1);

	graphics::setFont("KeepCalm-Medium.ttf");
	graphics::drawText(10, 30, 17.f, "Current State: " + statetxt , text);

	for (auto mw : movieWindows) 
		mw->draw();


	if (state == STATE_PREVIEW) 
	{
		// Previewing the description of the movie. Here we show the poster, the title, the genre, the director and stars and the year
		// Draw background
		graphics::Brush br;

		SETCOLOR(br.fill_color, 0.05f, 0.05f, 0.05f);
		SETCOLOR(br.outline_color, 0.2f, 0.2f, 0.2f);
		SETCOLOR(br.fill_secondary_color, 0.2f, 0.f, 0.f);
		br.outline_opacity = 0.5f;
		br.outline_width = 3.f;
		br.gradient = true;
		br.gradient_dir_u = .4f;
		br.gradient_dir_v = 0.f;

		graphics::drawRect(CANVAS_WI / 2 + 90, CANVAS_HE / 2 + 230, CANVAS_WI - 200, CANVAS_HE / 2 - 50, br);

		// Draw the movie poster
		graphics::Brush d;

		d.texture = ASSET_PATH + std::string(mwindow->getMovie().getPoster());
		SETCOLOR(d.outline_color, 0.3f, 0.3f, 0.3f);
		d.outline_opacity = 1.f;

		graphics::drawRect(CANVAS_WI / 2 - 470, CANVAS_HE / 2 + 230, P_WIDTH, P_HEIGHT, d);

		
		graphics::Brush ge;

		SETCOLOR(ge.fill_color, 0.2f, 0.2f, 0.2f);
		SETCOLOR(ge.outline_color, 0.3f, 0.3f, 0.3f);
		ge.outline_opacity = 1.f;
		ge.outline_width = 1.f;

		graphics::drawRect(CANVAS_WI / 2 - 125, CANVAS_HE / 2 + 93, 70, 30,ge);

		graphics::Brush text;
		text.outline_opacity = 1;
		SETCOLOR(text.fill_color, 1, 1, 1);
		//SETCOLOR(text.outline_color, 1, 1, 1);

		// Draw genre
		graphics::setFont("RobotoSlab-Regular.ttf");
		graphics::drawText(CANVAS_WI / 2 - 150, CANVAS_HE / 2 + 99, 17.f, mwindow->getMovie().getGenre1(), text);
		if (mwindow->getMovie().getGenre2() != "")
		{
			graphics::drawRect(CANVAS_WI / 2 - 50, CANVAS_HE / 2 + 93, 70, 30, ge);
			graphics::drawText(CANVAS_WI / 2 - 75, CANVAS_HE / 2 + 99, 17.f, mwindow->getMovie().getGenre2(), text);
		}

		// Draw the movie Title
		graphics::drawText(CANVAS_WI / 2 - 350, CANVAS_HE / 2 + 100, 20.f, mwindow->getMovie().getName(), text);

		// Draw Year
		graphics::setFont("KeepCalm-Medium.ttf");
		graphics::drawText(CANVAS_WI / 2 - 350, CANVAS_HE / 2 + 130, 17.f, mwindow->getMovie().getYear(), text);

		// Draw Description
		SETCOLOR(text.fill_color, 0.7, 0.7, 0.7);
		graphics::setFont("RobotoSlab-Bold.ttf");
		graphics::drawText(CANVAS_WI / 2 - 350, CANVAS_HE / 2 + 200, 15.f, mwindow->getMovie().getDescription(), text);
		graphics::drawText(CANVAS_WI / 2 - 350, CANVAS_HE / 2 + 220, 15.f, mwindow->getMovie().getDescription2(), text);

		// Draw Director
		SETCOLOR(text.fill_color, 1, 1, 1);
		graphics::setFont("RobotoSlab-Regular.ttf");
		graphics::drawText(CANVAS_WI / 2 - 350, CANVAS_HE / 2 + 335, 18.f, "Directing :    " + mwindow->getMovie().getDirector(), text);

		// Draw Stars
		graphics::drawText(CANVAS_WI / 2 - 350, CANVAS_HE / 2 + 370, 18.f, "Starring :    " + mwindow->getMovie().getCast(), text);
	}

	if (state == STATE_SEARCHING)
	{
		// Changing the button position
		search_button->set_pos(CANVAS_WI/3 - 40, CANVAS_HE / 2);
		search_button->setIcon("arrow_back.png");

		// Drawing the search menu
		graphics::Brush br;

		SETCOLOR(br.fill_color, 0.1f, 0.f, 0.f);
		SETCOLOR(br.fill_secondary_color, 0.02f, 0.02f, 0.02f);
		SETCOLOR(br.outline_color, 0.1f, 0.1f, 0.1f);
		br.outline_opacity = 3;
		br.gradient = true;
		br.gradient_dir_u = 1.f;
		br.gradient_dir_v = 0.f;

		graphics::drawRect(CANVAS_WI/8 + 60, CANVAS_HE / 2, CANVAS_WI/3, CANVAS_HE, br);
	}
	else
	{
		search_button->set_pos(50, CANVAS_HE / 2);
		search_button->setIcon("arrow_forward.png");
	}

	search_button->draw();
}

Browser::~Browser()
{
	
}
