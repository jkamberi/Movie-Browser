#pragma once
#include "graphics.h"

#define ASSET_PATH "assets\\"
#define WINDOW_WI 1600
#define WINDOW_HE 850
#define CANVAS_WI 1600
#define CANVAS_HE 850
#define P_WIDTH 200
#define P_HEIGHT 300
#define INIT_POS_X  CANVAS_WI/2-480
#define INIT_POS_Y  CANVAS_HE/2-150

#define SETCOLOR(c, r, g, b) { c[0]=r; c[1]=g; c[2]=b; }


inline float distance(float x1, float y1, float x2, float y2) 
{
	float dx = x1 - x2;
	float dy = y1 - y2;
	return sqrtf(dx * dx + dy * dy);
}