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

void Widget::update()
{
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

	float hov = 1.0f * hovered;

	
	br.texture = ASSET_PATH + std::string(ic);

	SETCOLOR(br.outline_color, 0.2f-(hov * 0.2f), 0.2f-(hov * 0.2f), 0.2f-(hov * 0.2f));
	br.outline_opacity = 0.8f;
	br.outline_width = 2.5f;
	
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


void MovieWindow::draw()
{
	graphics::Brush br;

	float hov = 1.0f * hovered;

	br.texture = ASSET_PATH + std::string(movie.getPoster());
	SETCOLOR(br.outline_color, (hov * 0.2f)+(sel * 0.2f)+0.3f, (hov * 0.2f)+(sel * 0.2f)+0.3f, (hov * 0.2f)+(sel * 0.2f)+0.3f);
	br.outline_opacity = 1.f;
	br.outline_width = 1 + 0.8f * sel;

	graphics::drawRect(pos_x, pos_y, width, height, br);
}

MovieWindow::~MovieWindow()
{
}
