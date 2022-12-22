#include "gui.h"
#include "config.h"

void Widget::draw()
{
	graphics::Brush br;

	SETCOLOR(br.fill_color, 0, 0.3f, 0.3f);
	SETCOLOR(br.outline_color, 0.0f, 0.1f, 0.1f);
	br.outline_opacity = 1.f; 
	
	graphics::drawRect(pos_x, pos_y, width, height, br);
}

Widget::~Widget()
{
}


void Button::button_pressed()
{
}

void Button::draw()
{
	graphics::Brush br;

	SETCOLOR(br.fill_color, 0.2f, 0.2f, 0.2f);
	SETCOLOR(br.outline_color, 0.5f, 0.5f, 0.5f);
	br.outline_opacity = 1.f;

	graphics::drawRect(pos_x, pos_y, width, height, br);

	graphics::Brush text;
	text.outline_opacity = 0;
	SETCOLOR(text.fill_color, 1, 1, 1);

	graphics::setFont("FiraSans-Regular.ttf");
	graphics::drawText(pos_x - width/3, pos_y + height/4, 17.f, label, text);
}

Button::~Button()
{
}


void MovieWindow::pressed()
{
}

void MovieWindow::draw()
{
	graphics::Brush br;

	br.texture = ASSET_PATH + std::string(movie.getPoster());
	SETCOLOR(br.outline_color, 0.3f, 0.3f, 0.3f);
	br.outline_opacity = 1.f;

	graphics::drawRect(pos_x, pos_y, width, height, br);
}

MovieWindow::~MovieWindow()
{
}
