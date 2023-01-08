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
	virtual void draw()=0;
	virtual void set_pos(float x, float y) { pos_x = x; pos_y = y; }
	virtual void setHovered(bool h) { hovered = h; }
};


class Button : public Widget 
{
private:
	std::string label;
	bool clicked = false;
public:
	virtual void draw();
	virtual bool contains(float x, float y) { return (distance(x, y, pos_x, pos_y+height/2) < height/2); }

	void set_pos(float x, float y) { Widget::set_pos(x, y); }
	void setHovered(bool h) { Widget::setHovered(h); }

	void setClicked(bool cl) { clicked = cl; }
	bool isClicked() { return clicked; }

	std::string getLabel() { return label; }

	Button() { width = 80; height = 35; pos_x = WINDOW_WI / 2; pos_y = WINDOW_HE / 2; label = "Button"; }
	Button(float w, float h, float posx, float posy, std::string l) : label(l) { width = w; height = h; pos_x = posx; pos_y = posy; }

	~Button();
};

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

	~IconButton();
};


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

	~MovieWindow();
};


class TextField : public Widget
{
	bool sel = false;
	std::string textl;
public:
	void draw() override;
	void update();
	void setHovered(bool h) { Widget::setHovered(h); }

	void selected(bool s) { sel = s; }
	bool isSelected() { return sel; }
	bool contains(float x, float y) { return distance(x, y, pos_x, pos_y) < width / 4 + 5; }

	std::string getText() { return textl; }

	TextField(float w, float h, float posx, float posy, std::string txt) : textl(txt) { width = w; height = h; pos_x = posx; pos_y = posy; }

	~TextField();
};