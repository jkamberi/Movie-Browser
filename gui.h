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
public:	
	void set_w(float w) { width = w; }
	void set_h(float h) { height = h; }
	void set_pos(float x, float y) { pos_x = x; pos_y = y; }
	virtual void draw();

	Widget(float w = 35.f, float h = 35.f, float posx = WINDOW_WI/2, float posy = WINDOW_HE/2) : width(w), height(h), pos_x(posx), pos_y(posy) {}

	~Widget();
};

class Button : public Widget 
{
private:
	std::string label;
public:
	void set_label(const std::string& l) { label = l; }
	void set_pos(float x, float y) { Widget::set_pos(x, y); }
	void button_pressed();
	void draw();
	Button() { width = 80; height = 35; pos_x = WINDOW_WI / 2; pos_y = WINDOW_HE / 2; label = "Button"; }

	Button(float w, float h, float posx, float posy, const std::string& l) : label(l) { width = w; height = h; pos_x = posx; pos_y = posy; }

	~Button();
};

class MovieWindow : public Widget 
{
private:
	Movie movie;
public:
	void pressed();
	void draw();

	MovieWindow(float w, float h, float posx, float posy, Movie m) : movie(m) { width = w; height = h; pos_x = posx; pos_y = posy; }

	~MovieWindow();
};