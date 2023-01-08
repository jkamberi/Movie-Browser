#include "gui.h"
#include "config.h"

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

Button::~Button()
{
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

IconButton::~IconButton()
{
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

MovieWindow::~MovieWindow()
{
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
		graphics::drawRect(pos_x - pos_x/2 - 3, pos_y, 1.5f, 20, br);
	}

	graphics::Brush text;
	text.outline_opacity = 1;
	SETCOLOR(text.fill_color, 0.9f, 0.9f, 0.9f);

	graphics::setFont(ASSET_PATH + std::string("FiraSans-Regular.ttf"));
	graphics::drawText(pos_x - pos_x/2, pos_y + 8, 17.f, textl, text);

}

void TextField::update()
{
	static float delay = 0.f;
	static int prev = 0;
	delay += graphics::getDeltaTime();

	for (int i = graphics::SCANCODE_A; i <= graphics::SCANCODE_0; i++)
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
		}
	}
}

TextField::~TextField()
{
}
