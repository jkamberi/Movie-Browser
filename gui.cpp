#include "gui.h"
#include "config.h"

void Widget::draw()
{
	graphics::Brush br;

	SETCOLOR(br.fill_color, 0, 0.3f, 0.3f);
	SETCOLOR(br.outline_color, 0.0f, 0.1f, 0.1f)
	br.outline_opacity = 1.f; 
	
	graphics::drawRect(pos_x, pos_y, width, height, br);
}

void Widget::update()
{
}

Widget::~Widget()
{
}

void Button::draw()
{
	graphics::Brush br;

	SETCOLOR(br.fill_color, 0, 0.3f, 0.3f);
	SETCOLOR(br.outline_color, 0.0f, 0.1f, 0.1f)
	br.outline_opacity = 1.f;

	graphics::drawRect(pos_x, pos_y, width, height, br);

	graphics::Brush text;
	text.outline_opacity = 0;
	SETCOLOR(text.fill_color, 1, 1, 1);

	graphics::setFont("JosefinSans-Regular.ttf");
	graphics::drawText(pos_x, pos_y, 25.f, label, text);
}