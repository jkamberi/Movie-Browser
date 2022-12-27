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
	void update();

	virtual void draw()=0;
	virtual void set_pos(float x, float y) { pos_x = x; pos_y = y; }
	virtual void setHovered(bool h) { hovered = h; }

	~Widget();
};


class Button : public Widget 
{
private:
	std::string label;
public:
	virtual void draw();
	virtual bool contains(float x, float y) { return (distance(x, y, pos_x, pos_y) < height / 2); }

	void set_pos(float x, float y) { Widget::set_pos(x, y); }
	void setHovered(bool h) { Widget::setHovered(h); }

	Button() { width = 80; height = 35; pos_x = CANVAS_WI / 2; pos_y = CANVAS_HE / 2; label = "Button"; }
	Button(float w, float h, float posx, float posy, const std::string& l) : label(l) { width = w; height = h; pos_x = posx; pos_y = posy; }

	~Button();
};

class IconButton : public Button
{
	std::string icon = "";
public:
	void draw();

	void set_pos(float x, float y) { Widget::set_pos(x, y); }
	void setIcon(std::string i) { icon = i; }
	void setHovered(bool h) { Widget::setHovered(h); }

	bool contains(float x, float y) { return Button::contains(x, y); }

	IconButton(std::string ic) { width = 48; height = 48; pos_x = 50; pos_y = CANVAS_HE / 2; icon = ic; }

	~IconButton();
};


class MovieWindow : public Widget
{
private:
	Movie movie;
	bool sel = false;
public:
	void draw();
	void setHovered(bool h) { Widget::setHovered(h); }

	Movie getMovie() { return movie; }
	void selected(bool s) { sel = s; }
	bool contains(float x, float y) { return (distance(x, y, pos_x, pos_y) < P_WIDTH/2+5); }

	MovieWindow(float w, float h, float posx, float posy, Movie m) : movie(m) { width = w; height = h; pos_x = posx; pos_y = posy; }

	~MovieWindow();
};