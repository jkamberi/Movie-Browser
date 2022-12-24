#include "browser.h"
#include "gui.h"
#include "graphics.h"
#include "config.h"

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
		else
			m->setHovered(false);
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
	button->setHovered( button->contains(mx, my) );
}

void Browser::init()
{
	// Movie Descriptions
	std::string losth_desc = "Anonymous videotapes presage a musician's murder conviction, and a gangster's girlfriend leads a mechanic astray.";

	// Some generic buttons
	//for (int i = 0; i < 7; i++)
	//	button_menu[i] = new Button(80, 35, 75, (CANVAS_HE/2 - 175) + 50*i, "Button " + std::to_string(i+1));
	button = new Button("arrow_forward.png");

	// Movies initialization
	
	// Movie Window Initialization
	for (int i = 0; i < 6; i++) {
		Movie* m = new Movie();
		movieWindows[i] = new MovieWindow(P_WIDTH, P_HEIGHT, INIT_POS_X + (i)* (P_WIDTH + 20), INIT_POS_Y, *m);
	}
	 
	// Movie Preview
	if (state == STATE_PREVIEW)
	{
		desc = new Description(selectedw->getMovie());
	}
}

void Browser::draw()
{
	graphics::Brush br;

	// background
	SETCOLOR(br.fill_color, 0.3f, 0.3f, 0.3f);
	SETCOLOR(br.fill_secondary_color, 0.01f, 0.01f, 0.01f);
	br.outline_opacity = 0;
	br.gradient = true;
	br.gradient_dir_u = 5.f;
	br.gradient_dir_v = 0.f;
	
	graphics::drawRect(CANVAS_WI/2, CANVAS_HE/2, CANVAS_WI, CANVAS_HE, br);

	// test
	graphics::Brush text;
	text.outline_opacity = 0;
	SETCOLOR(text.fill_color, 1, 1, 1);

	graphics::setFont("FiraSans-Regular.ttf");
	graphics::drawText(10, 30, 17.f, "Current State: " + statetxt , text);



	
	button->draw();

	for (auto mw : movieWindows)
		mw->draw();
	
	if (state == STATE_PREVIEW)
		desc->draw();
}

Browser::~Browser()
{
	for (auto b : button_menu) delete b;
}
