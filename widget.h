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