#include "gui.h"
#include "config.h"
#include <iostream>

void Button::draw()
{
	float hov = 1.0f * hovered;

	graphics::Brush br;

	SETCOLOR(br.fill_color, 0.05f+hov/2, 0.05f+hov/2, 0.05f+hov/2);
	br.outline_opacity = 1.f;
	br.outline_width = 1.f;
	
	graphics::drawRect(pos_x, pos_y, width, height, br);

	if (clicked) {
		SETCOLOR(br.fill_color, 0.5f, 0, 0);
		graphics::drawRect(pos_x, pos_y + 11, 15, 3, br);
	}

	graphics::Brush text;
	text.outline_opacity = 0;
	SETCOLOR(text.fill_color, 0.9f, 0.9f, 0.9f);

	graphics::setFont(ASSET_PATH + std::string("KeepCalm-Medium.ttf"));
	graphics::drawText(pos_x - width/3, pos_y + height/4, 13.f, label, text);
}


void IconButton::draw()
{
	float hov = 1.0f * hovered;

	graphics::Brush br;

	br.texture = ASSET_PATH + std::string(icon);

	SETCOLOR(br.outline_color, 0.2f - (hov * 0.2f), 0.2f - (hov * 0.2f), 0.2f - (hov * 0.2f));
	br.outline_opacity = 0.8f;
	br.outline_width = 2.5f;

	graphics::drawRect(pos_x, pos_y, width, height, br);
}


void MovieWindow::draw()
{
	float hov = 1.0f * hovered;

	graphics::Brush br;

	br.texture = ASSET_PATH + std::string(movie.getPoster());
	SETCOLOR(br.outline_color, (hov * 0.2f)+(sel * 0.2f)+0.3f, (hov * 0.2f)+(sel * 0.2f)+0.3f, (hov * 0.2f)+(sel * 0.2f)+0.3f);
	br.outline_opacity = 1.f;
	br.outline_width = 1 + 0.8f * sel;

	graphics::drawRect(pos_x, pos_y, width, height, br);
}


void TextField::draw()
{
	float hov = 1.f * hovered;
	float g = 0.3f * sinf(graphics::getGlobalTime() / 100);

	graphics::Brush br;

	SETCOLOR(br.fill_color, 0.3f, 0.3f, 0.3f);
	SETCOLOR(br.outline_color, (hov * 0.5f) + 0.2f, (hov * 0.5f) + 0.2f, (hov * 0.5f) + 0.2f);
	br.outline_opacity = 1;

	graphics::drawRect(pos_x, pos_y, width, height, br);
	
	if (sel) {
		SETCOLOR(br.fill_color, 0.f + g, 0.f + g, 0.f + g);
		br.outline_opacity = 0;
		graphics::drawRect(pos_x - pos_x/2 - 15, pos_y, 1.5f, 20, br);
	}

	graphics::Brush text;
	text.outline_opacity = 1;
	SETCOLOR(text.fill_color, 0.9f, 0.9f, 0.9f);

	graphics::setFont(ASSET_PATH + std::string("FiraSans-Regular.ttf"));
	graphics::drawText(pos_x - pos_x/2 - 15, pos_y + 8, 17.f, entered_text, text);

}

// mapping scancodes
char scancode_to_char(int scancode) {
	switch (scancode) {
		case graphics::SCANCODE_A: return 'a';
		case graphics::SCANCODE_B: return 'b';
		case graphics::SCANCODE_C: return 'c'; 
		case graphics::SCANCODE_D: return 'd';
		case graphics::SCANCODE_E: return 'e';
		case graphics::SCANCODE_F: return 'f';
		case graphics::SCANCODE_G: return 'g';
		case graphics::SCANCODE_H: return 'h';
		case graphics::SCANCODE_I: return 'i';
		case graphics::SCANCODE_J: return 'j';
		case graphics::SCANCODE_K: return 'k';
		case graphics::SCANCODE_L: return 'l';
		case graphics::SCANCODE_M: return 'm';
		case graphics::SCANCODE_N: return 'n';
		case graphics::SCANCODE_O: return 'o';
		case graphics::SCANCODE_P: return 'p';
		case graphics::SCANCODE_Q: return 'q';
		case graphics::SCANCODE_R: return 'r';
		case graphics::SCANCODE_S: return 's';
		case graphics::SCANCODE_T: return 't';
		case graphics::SCANCODE_U: return 'u';
		case graphics::SCANCODE_V: return 'v';
		case graphics::SCANCODE_W: return 'w';
		case graphics::SCANCODE_X: return 'x';
		case graphics::SCANCODE_Y: return 'y';
		case graphics::SCANCODE_Z: return 'z';

		case graphics::SCANCODE_1: return '1';
		case graphics::SCANCODE_2: return '2';
		case graphics::SCANCODE_3: return '3';
		case graphics::SCANCODE_4: return '4';
		case graphics::SCANCODE_5: return '5';
		case graphics::SCANCODE_6: return '6';
		case graphics::SCANCODE_7: return '7';
		case graphics::SCANCODE_8: return '8';
		case graphics::SCANCODE_9: return '9';
		case graphics::SCANCODE_0: return '0';

		case graphics::SCANCODE_BACKSPACE: return '\b';
		case graphics::SCANCODE_SPACE: return ' ';
		//case graphics::SCANCODE_RETURN: return '\n';

		default: return 0;
	}
};

void TextField::update()
{
	static float delay = 0.f;
	static int prev = 0;
	delay += graphics::getDeltaTime();

	for (int i = graphics::SCANCODE_A; i <= graphics::SCANCODE_SPACE; i++)
	{
		if (graphics::getKeyState((graphics::scancode_t)i))
		{
			if (prev == i && delay < 200.0f)
				continue;
			else
			{
				prev = i;
				delay = 0.f;
			}
			char key_char = scancode_to_char(i);

			if (key_char == '\b') {
				entered_text = entered_text.substr(0, entered_text.length() - 1);
			}
			else {
				entered_text += key_char;
			}
		}
	}
}