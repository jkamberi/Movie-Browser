#pragma once
#include "widget.h"

class IconButton : public Button
{
	std::string icon = "";
public:
	void draw() override;

	void set_pos(float x, float y) { Widget::set_pos(x, y); }
	void setHovered(bool h) { Widget::setHovered(h); }
	bool contains(float x, float y) { return Button::contains(x, y); }

	void setIcon(std::string i) { icon = i; }

	IconButton(std::string ic) { width = 48; height = 48; pos_x = 50; pos_y = WINDOW_HE / 2; icon = ic; }
};
