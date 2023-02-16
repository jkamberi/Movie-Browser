#pragma once
#include "widget.h"

class MovieWindow : public Widget
{
private:
	Movie movie;
	bool sel = false;
public:
	void draw() override;
	void setHovered(bool h) { Widget::setHovered(h); }

	Movie getMovie() { return movie; }
	void selected(bool s) { sel = s; }
	bool contains(float x, float y) { return distance(x, y, pos_x, pos_y) < width / 2 + 5; }

	MovieWindow(float w, float h, float posx, float posy, Movie m) : movie(m) { width = w; height = h; pos_x = posx; pos_y = posy; }
};