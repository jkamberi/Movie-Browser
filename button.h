#pragma once
#include "widget.h"

class Button : public Widget
{
private:
	std::string label;
	bool clicked = false;
public:
	virtual void draw();
	virtual bool contains(float x, float y) { return (distance(x, y, pos_x, pos_y) < height / 1.5); }

	void set_pos(float x, float y) { Widget::set_pos(x, y); }
	void setHovered(bool h) { Widget::setHovered(h); }

	void setClicked(bool cl) { clicked = cl; }
	bool isClicked() { return clicked; }

	std::string getLabel() { return label; }

	Button() { width = 80; height = 35; pos_x = WINDOW_WI / 2; pos_y = WINDOW_HE / 2; label = "Button"; }
	Button(float w, float h, float posx, float posy, std::string l) : label(l) { width = w; height = h; pos_x = posx; pos_y = posy; }
};