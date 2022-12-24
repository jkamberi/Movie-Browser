#pragma once
#include "config.h"
#include "movie.h"

class Widget 
{
protected:
	float width;
	float height;
	float pos_x;
	float pos_y;
	bool hovered = false;
public:	
	void draw();
	void update();

	void set_w(float w) { width = w; }
	void set_h(float h) { height = h; }
	void set_pos(float x, float y) { pos_x = x; pos_y = y; }

	virtual void setHovered(bool h) { hovered = h; }
	bool contains(float x, float y) { return (distance(x, y, pos_x, pos_y) < P_WIDTH/2); }

	Widget(float w = 35.f, float h = 35.f, float posx = CANVAS_WI/2, float posy = CANVAS_HE/2) : width(w), height(h), pos_x(posx), pos_y(posy) {}

	~Widget();
};


class Button : public Widget 
{
private:
	std::string label;
	std::string ic = "";
public:
	void draw();
	void set_label(const std::string& l) { label = l; }
	void set_pos(float x, float y) { Widget::set_pos(x, y); }

	void button_pressed();
	void setHovered(bool h) { Widget::setHovered(h); }
	bool contains(float x, float y) { return (distance(x, y, pos_x, pos_y) < height/2); }

	Button() { width = 80; height = 35; pos_x = CANVAS_WI / 2; pos_y = CANVAS_HE / 2; label = "Button"; }
	
	Button(std::string icon) { width = 40; height = 40; pos_x = 50; pos_y = CANVAS_HE / 2; ic = icon; }

	Button(float w, float h, float posx, float posy, const std::string& l) : label(l) { width = w; height = h; pos_x = posx; pos_y = posy; }

	~Button();
};


class MovieWindow : public Widget
{
protected:
	Movie movie;
	bool sel = false;
public:
	void draw();

	Movie getMovie() { return movie; }
	void selected(bool s) { sel = s; }
	void setHovered(bool h) { Widget::setHovered(h); }
	bool contains(float x, float y) { return (distance(x, y, pos_x, pos_y) < P_WIDTH/2); }

	MovieWindow(float w, float h, float posx, float posy, Movie m) : movie(m) { width = w; height = h; pos_x = posx; pos_y = posy; }

	~MovieWindow();
};


class Description : public Widget
{
	Movie movie;
	bool active = false;
public:
	void draw();
	void setActive(bool a) { active = a; }

	Description(Movie m) : movie(m) {}

	~Description() {}
};