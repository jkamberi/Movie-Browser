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

	// Select a Movie
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

	if (ms.button_left_pressed && state == STATE_PREVIEW)
	{
		selectedw = nullptr;
		mwindow = nullptr;
		state = STATE_ILDE;
		statetxt = "STATE_IDLE";
	} 
	else if (ms.button_left_pressed && selectedw)
	{
		mwindow = selectedw;
		mwindow->selected(true);
		state = STATE_PREVIEW;
		statetxt = "STATE_PREVIEW";
		for (auto m : movieWindows)
		{
			if (m != mwindow)
				m->selected(false);
		}
	} 

	// Hovering Buttons
	search_button->setHovered( search_button->contains(mx, my) );
}

void Browser::init()
{
	// Movie Descriptions
	std::string lostHighway_desc = "Anonymous videotapes presage a musician's murder conviction, and a gangster's girlfriend leads a mechanic astray.";
	std::string theHunt_desc = "A teacher lives a lonely life, all the while struggling over his son's custody. His life slowly gets better as he finds love and receives good news from his son, but his new luck is about to be brutally shattered by an innocent little lie.";

	// Some generic buttons
	// 
	//for (int i = 0; i < 7; i++)
	//	button_menu[i] = new Button(80, 35, 75, (CANVAS_HE/2 - 175) + 50*i, "Button " + std::to_string(i+1));

	search_button = new Button("arrow_forward.png");

	// Movies initialization
	movies[0] = new Movie("The Hunt (Jagten)", "Thomas Vinterberg", "Mads Mikkelsen, Thomas Bo Larsen, Annika Wedderkopp", "Drama", "2012", theHunt_desc, "hunt.png");
	for (int i = 1; i < 6; i++)
		movies[i] = new Movie();

	// Movie Window Initialization
	for (int i = 0; i < 6; i++) {
		movieWindows[i] = new MovieWindow(P_WIDTH, P_HEIGHT, INIT_POS_X + (i)* (P_WIDTH + 20), INIT_POS_Y, *movies[i]);
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

	graphics::setFont("FiraSans-Regular.ttf");
	graphics::drawText(10, 30, 17.f, "Current State: " + statetxt , text);



	
	search_button->draw();

	for (auto mw : movieWindows) 
		mw->draw();


	if (state == STATE_PREVIEW) {
		// Previewing the description of the movie. Here we show the poster, the title, the genre, the director and stars and the year
		// Draw background
		graphics::Brush br;

		SETCOLOR(br.fill_color, 0.07f, 0.07f, 0.07f);
		SETCOLOR(br.outline_color, 0.2f, 0.2f, 0.2f);
		br.outline_opacity = 0.5f;
		br.outline_width = 3.f;

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
		graphics::drawText(CANVAS_WI / 2 - 150, CANVAS_HE / 2 + 99, 17.f, mwindow->getMovie().getGenre(), text);

		// Draw the movie Title
		graphics::setFont("RobotoSlab-Bold.ttf");
		graphics::drawText(CANVAS_WI / 2 - 350, CANVAS_HE / 2 + 100, 20.f, mwindow->getMovie().getName(), text);

		// Draw Year
		graphics::setFont("KeepCalm-Medium.ttf");
		graphics::drawText(CANVAS_WI / 2 - 350, CANVAS_HE / 2 + 130, 17.f, mwindow->getMovie().getYear(), text);

		// Draw Description
		graphics::setFont("RobotoSlab-Bold.ttf");
		graphics::drawText(CANVAS_WI / 2 - 350, CANVAS_HE / 2 + 170, 15.f, mwindow->getMovie().getDescription(), text);

		// Draw Director
		graphics::drawText(CANVAS_WI / 2 - 350, CANVAS_HE / 2 + 335, 18.f, "Directing :    " + mwindow->getMovie().getDirector(), text);

		// Draw Stars
		graphics::drawText(CANVAS_WI / 2 - 350, CANVAS_HE / 2 + 370, 18.f, "Starring :    " + mwindow->getMovie().getCast(), text);
	}
}

Browser::~Browser()
{
	for (auto b : button_menu) delete b;
}
