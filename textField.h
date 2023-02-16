#pragma once
#include "widget.h"

class TextField : public Widget
{
	bool sel = false;
	std::string entered_text;
public:
	void draw() override;
	void update();
	void setHovered(bool h) { Widget::setHovered(h); }

	void selected(bool s) { sel = s; }
	bool isSelected() { return sel; }
	bool contains(float x, float y) { return distance(x, y, pos_x, pos_y) < width / 4 + 5; }

	std::string getText() { return entered_text; }
	void emptyText() { entered_text = ""; }

	TextField(float w, float h, float posx, float posy, std::string txt) : entered_text(txt) { width = w; height = h; pos_x = posx; pos_y = posy; }
};