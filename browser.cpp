#include "browser.h"
#include "graphics.h"
#include "config.h"
#include <iostream>
#include <locale>

void Browser::update()
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);

	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasX(ms.cur_pos_y);

	// Movie Windows

	// Selecting a Movie and on-click events
	// When we select a movie the description of the movie is shown in the botton of the screen
	for (auto m : movieWindows) 
	{
		if (m->contains(mx, my)) {
			m->setHovered(true);
			selectedw = m;
		}
		else {
			m->setHovered(false);
		}
	}

	if (ms.button_left_pressed && state == STATE_PREVIEW) // if we click again the description is closed
	{
		mwindow->selected(false);
		selectedw = nullptr;
		mwindow = nullptr;
		state = STATE_ILDE;
	} 
	else if (ms.button_left_pressed && selectedw && selectedw->contains(mx, my) && (state == STATE_ILDE || state == STATE_FILTERED_by_GENRE || state == STATE_FILTERED_by_YEAR || state == STATE_FILTERED_by_TXT)) // the first time we select a movie
	{
		mwindow = selectedw;
		mwindow->selected(true);
		state = STATE_PREVIEW;
		for (auto m : movieWindows)
		{
			if (m != mwindow)
				m->selected(false);
		}
	} 

	// Buttons

	// Hovering Buttons and on-click events
	// In this button we expand the searching menu
	if (search_button->contains(mx, my)) {
		search_button->setHovered(true);
		selected_b1 = search_button;
	}
	else {
		search_button->setHovered(false);
	}

	if (ms.button_left_pressed && state == STATE_SEARCHING && selected_b1->contains(mx, my)) 
	{
		state = STATE_ILDE;
	}
	else if (ms.button_left_pressed && selected_b1 && selected_b1->contains(mx, my))
	{
		state = STATE_SEARCHING;
		txtf->emptyText();
	}

	for (auto gb : genreButtons)
	{
		if (gb->contains(mx, my))
			gb->setHovered(true);
		else
			gb->setHovered(false);
	}

	for (auto gb : genreButtons)
	{
		if (ms.button_left_pressed && state == STATE_SEARCHING && gb->contains(mx, my)) {
			gb->setClicked(true);
			genre = gb->getLabel();
			state = STATE_FILTERED_by_GENRE;
		}
	}

	if (yearButton->contains(mx, my))
		yearButton->setHovered(true);
	else
		yearButton->setHovered(false);

	if (ms.button_left_pressed && yearButton->isClicked() && yearButton->contains(mx, my))
	{
		yearButton->setClicked(false);
		state = STATE_SEARCHING;
	}
	if (ms.button_left_pressed && state == STATE_SEARCHING && yearButton->contains(mx, my))
	{
		yearButton->setClicked(true);
		state = STATE_YEARS;
	}

	for (auto yb : yearButtons) {

		if (yb->contains(mx, my))
			yb->setHovered(true);
		else
			yb->setHovered(false);

		if (ms.button_left_pressed && state == STATE_YEARS && yb->contains(mx, my)) {
			yb->setClicked(true);
			year = yb->getLabel();
			state = STATE_FILTERED_by_YEAR;
		}
	}

	if (txtButton->contains(mx, my))
		txtButton->setHovered(true);
	else
		txtButton->setHovered(false);

	if (ms.button_left_pressed && state == STATE_SEARCHING && txtButton->contains(mx, my))
	{
		txtButton->setClicked(true);
		state = STATE_FILTERED_by_TXT;
	}

	if (clearFilters->contains(mx, my))
		clearFilters->setHovered(true);
	else
		clearFilters->setHovered(false);

	if (ms.button_left_pressed && clearFilters->contains(mx, my))
	{
		state = STATE_ILDE;
		for (auto gb : genreButtons)
			gb->setClicked(false);
		for (auto yb : yearButtons)
			yb->setClicked(false);
		yearButton->setClicked(false);
		txtButton->setClicked(false);
	}

	// TextField
	if (txtf->isSelected())
		txtf->update();

	if (txtf->contains(mx, my))
		txtf->setHovered(true);
	else
		txtf->setHovered(false);

	if (ms.button_left_pressed && state == STATE_SEARCHING && txtf->contains(mx, my)) 
	{
		txtf->selected(true);
	}
	else if (ms.button_left_pressed && state == STATE_SEARCHING && txtf->isSelected())
		txtf->selected(false);

}

void Browser::init()
{
	// Movie Descriptions
	std::string lostHighway_desc = "Anonymous videotapes presage a musician's murder conviction, and a gangster's girlfriend leads a mechanic astray.";
	std::string theHunt_desc = "A teacher lives a lonely life, all the while struggling over his son's custody. His life slowly gets better as he finds";
	std::string theHunt_desc2 = "love and receives good news from his son, but his new luck is about to be brutally shattered by an innocent little lie.";
	std::string topGun_desc = "After thirty years, Maverick is still pushing the envelope as a top naval aviator, but must confront ghosts of his past";
	std::string topGun_desc2 = "when he leads TOP GUN's elite graduates on a mission that demands the ultimate sacrifice from those chosen to fly it.";
	std::string shutterIsland_desc = "In 1954, a U.S. Marshal investigates the disappearance of a murderer who escaped from a hospital for the criminally insane.";
	std::string theDarkKnight_desc = "When the menace known as the Joker wreaks havoc and chaos on the people of Gotham, Batman must accept one";
	std::string theDarkKnight_desc2 = "of the greatest psychological and physical tests of his ability to fight injustice.";
	std::string parasite_desc = "Greed and class discrimination threaten the newly formed symbiotic relationship between the wealthy Park family and the destitute Kim clan.";
	std::string theuglytruth_desc = "An uptight television producer takes control of a morning show segment on modern relationships hosted by a misogynistic man.";
	std::string knivesout_desc = "A detective investigates the death of the patriarch of an eccentric, combative family.";
	std::string desc_300 = "King Leonidas of Sparta and a force of 300 men fight the Persians at Thermopylae in 480 B.C.";
	std::string thewolfofwallstreet_desc = "Based on the true story of Jordan Belfort, from his rise to a wealthy stock-broker living the high life to his fall involving crime, corruption";
	std::string thewolfofwallstreet_desc2 = "and the federal government.";
	std::string interstellar_desc = "A team of explorers travel through a wormhole in space in an attempt to ensure humanity's survival.";
	std::string matrix_desc = "When a beautiful stranger leads computer hacker Neo to a forbidding underworld, he discovers";
	std::string matrix_desc2 = "the shocking truth--the life he knows is the elaborate deception of an evil cyber-intelligence.";

	// Buttons Initialization
	search_button = new IconButton("arrow_forward.png");

	genreButtons[0] = new Button(70, 30, 70, 100, "Drama");
	genreButtons[1] = new Button(70, 30, 70, 150, "Action");
	genreButtons[2] = new Button(110, 30, 90, 200, "Adventure");
	genreButtons[3] = new Button(70, 30, 150, 100, "Thriller");
	genreButtons[4] = new Button(70, 30, 150, 150, "Mystery");
	genreButtons[5] = new Button(70, 30, 230, 100, "Crime");
	genreButtons[6] = new Button(70, 30, 230, 150, "Comedy");
	genreButtons[7] = new Button(70, 30, 190, 200, "Sci-Fi");
	genreButtons[8] = new Button(85, 30, 280, 200, "Romance");

	yearButton = new Button(77, 30, 140, 280, "Select...");

	yearButtons[0] = new Button(70, 30, 140, 310, "1997");
	yearButtons[1] = new Button(70, 30, 140, 340, "1999");
	yearButtons[2] = new Button(70, 30, 140, 370, "2006");
	yearButtons[3] = new Button(70, 30, 140, 400, "2008");
	yearButtons[4] = new Button(70, 30, 140, 430, "2009");
	yearButtons[5] = new Button(70, 30, 140, 460, "2010");
	yearButtons[6] = new Button(70, 30, 140, 490, "2012");
	yearButtons[7] = new Button(70, 30, 140, 520, "2013");
	yearButtons[8] = new Button(70, 30, 140, 550, "2014");
	yearButtons[9] = new Button(70, 30, 140, 580, "2019");
	yearButtons[10] = new Button(70, 30, 140, 610, "2022");

	txtButton = new Button(67, 30, 320, WINDOW_HE / 2 + 150, "Search");

	clearFilters = new Button(145, 30, WINDOW_WI - 130, 50, "CLEAR FILTERS");

	// Movies Initialization
	movies[0] = new Movie("The Hunt (Jagten)", "Thomas Vinterberg", "Mads Mikkelsen, Thomas Bo Larsen, Annika Wedderkopp", "Drama", "", "2012", theHunt_desc, theHunt_desc2, "hunt.png");
	movies[1] = new Movie("Top Gun: Maverick", "Joseph Kosinski", "Tom Cruise, Jennifer Connelly, Miles Teller", "Action", "Drama", "2022", topGun_desc, topGun_desc2, "topgun.png");
	movies[2] = new Movie("Shutter Island", "Martin Scorsese", "Leonardo DiCaprio, Emily Mortimer, Mark Ruffalo", "Mystery", "Thriller", "2010", shutterIsland_desc, "", "shutter_island.png");
	movies[3] = new Movie("The Dark Knight", "Christopher Nolan", "Christian Bale, Heath Ledger, Aaron Eckhart", "Action", "Crime", "2008", theDarkKnight_desc, theDarkKnight_desc2, "thedarkknight.png");
	movies[4] = new Movie("Parasite", "Bong Joon Ho", "Song Kang-ho, Lee Sun-kyun, Cho Yeo-jeong", "Drama", "Thriller", "2019", parasite_desc, "", "parasite.png");
	movies[5] = new Movie("The Ugly Truth", "Robert Luketic", "Katherine Heigl, Gerard Butler, Bree Turner", "Comedy", "Romance", "2009", theuglytruth_desc, "", "theuglytruth.png");
	movies[6] = new Movie("Knives Out", "Rian Johnson", "Daniel Craig, Chris Evans, Ana de Armas", "Comedy", "Crime", "2019", knivesout_desc, "", "knivesout.png");
	movies[7] = new Movie("300", "Zack Snyder", "Gerard Butler, Lena Headey, David Wenham", "Action", "Drama", "2006", desc_300, "", "300.png");
	movies[8] = new Movie("The Wolf of Wall Street", "Martin Scorsese", "Leonardo DiCaprio, Johan Hill, Margot Robbie", "Biography", "Comedy", "2013", thewolfofwallstreet_desc, thewolfofwallstreet_desc2, "thewolfofwallstreet.png");
	movies[9] = new Movie("Lost Highway", "David Lynch", "Bill Pullman, Patricia Arquette, John Roselius", "Mystery", "Thriller", "1997", lostHighway_desc, "", "losthighway.png");
	movies[10] = new Movie("Interstellar", "Christopher Nolan", "Matthew McConaughey, Anne Hathaway, Jessica Chastain", "Adventure", "Sci-Fi", "2014", interstellar_desc, "", "interstellar.png");
	movies[11] = new Movie("The Matrix", "Wachowski Brothers", "Keanu Reeves, Lawrence Fishburne, Carrie-Anne Moss", "Action", "Sci-Fi", "1999", matrix_desc, matrix_desc2, "matrix.png");

	// Movie Window Initialization
	for (int i = 0; i < 12; i++) {
		if (i<6)
			movieWindows.push_front(new MovieWindow(P_WIDTH, P_HEIGHT, INIT_POS_X + 50 + (i) * (P_WIDTH + 20), INIT_POS_Y, *movies[i]));
		else if (i>=6)
			movieWindows.push_front(new MovieWindow(P_WIDTH, P_HEIGHT, INIT_POS_X + 50 + (i-6) * (P_WIDTH + 20), INIT_POS_Y + P_HEIGHT + 50, *movies[i]));
	}

	// Text Field Initialization
	txtf = new TextField(200, 30, 160, WINDOW_HE / 2 + 150, "");
}

void Browser::draw()
{
	graphics::Brush br;

	// Draw background
	SETCOLOR(br.fill_color, 0.2f, 0.2f, 0.2f);
	SETCOLOR(br.fill_secondary_color, 0.01f, 0.01f, 0.01f);
	br.outline_opacity = 0;
	br.gradient = true;
	br.gradient_dir_u = 6.f;
	br.gradient_dir_v = 0.f;

	graphics::drawRect(WINDOW_WI / 2, WINDOW_HE / 2, WINDOW_WI, WINDOW_HE, br);


	// Draw Movie Windows with the movies
	for (auto mw : movieWindows)
	{
		if (state == STATE_ILDE)
			mw->draw();
		else if (state == STATE_FILTERED_by_GENRE && (mw->getMovie().getGenre1() == genre || mw->getMovie().getGenre2() == genre))
			mw->draw();
		else if (state == STATE_FILTERED_by_YEAR && mw->getMovie().getYear() == year)
			mw->draw();
		else if (state == STATE_FILTERED_by_TXT) {
			std::string movie_name = mw->getMovie().getName();
			std::string movie_dir = mw->getMovie().getDirector();
			std::string movie_stars = mw->getMovie().getCast();
			std::locale loc;
			for (auto& a : movie_name) {
				a = std::tolower(a, loc);
			}
			for (auto& b : movie_dir) {
				b = std::tolower(b, loc);
			}			
			for (auto& c : movie_stars) {
				c = std::tolower(c, loc);
			}
			if (movie_name.find(txtf->getText()) != std::string::npos || movie_dir.find(txtf->getText()) != std::string::npos || movie_stars.find(txtf->getText()) != std::string::npos)
				mw->draw();
		}
	}


	if (state == STATE_PREVIEW)
	{
		// Previewing the description/summary of the movie. Here we show the poster, the title, the genre, the director and stars and the year
		// Draw background
		graphics::Brush br;

		SETCOLOR(br.fill_color, 0.05f, 0.05f, 0.05f);
		SETCOLOR(br.outline_color, 0.2f, 0.2f, 0.2f);
		SETCOLOR(br.fill_secondary_color, 0.2f, 0.f, 0.f);
		br.outline_opacity = 0.5f;
		br.outline_width = 3.f;
		br.gradient = true;
		br.gradient_dir_u = .4f;
		br.gradient_dir_v = 0.f;

		graphics::drawRect(WINDOW_WI / 2 + 90, WINDOW_HE / 2 + 230, WINDOW_WI - 200, WINDOW_HE / 2 - 50, br);

		// Draw the movie poster
		graphics::Brush d;

		d.texture = ASSET_PATH + std::string(mwindow->getMovie().getPoster());
		SETCOLOR(d.outline_color, 0.3f, 0.3f, 0.3f);
		d.outline_opacity = 1.f;

		graphics::drawRect(WINDOW_WI / 2 - 470, WINDOW_HE / 2 + 230, P_WIDTH, P_HEIGHT, d);

		// Drawing Genre Box 
		graphics::Brush ge;

		SETCOLOR(ge.fill_color, 0.2f, 0.2f, 0.2f);
		SETCOLOR(ge.outline_color, 0.3f, 0.3f, 0.3f);
		ge.outline_opacity = 1.f;
		ge.outline_width = 1.f;

		graphics::drawRect(WINDOW_WI / 2 - 125, WINDOW_HE / 2 + 93, 80, 30, ge);

		graphics::Brush text;
		text.outline_opacity = 1;
		SETCOLOR(text.fill_color, 1, 1, 1);
		// SETCOLOR(text.outline_color, 1, 1, 1);

		// Draw genre
		graphics::setFont(ASSET_PATH + std::string("RobotoSlab-Regular.ttf"));

		if (mwindow->getMovie().getGenre1().length() >= 7 || mwindow->getMovie().getGenre1() == "Comedy")
			text_size = 14.5f;
		else
			text_size = 17.f;
		if (mwindow->getMovie().getGenre1() == "Adventure" || mwindow->getMovie().getGenre1() == "Biography")
			text_size = 12.f;

		graphics::drawText(WINDOW_WI / 2 - 150, WINDOW_HE / 2 + 99, text_size, mwindow->getMovie().getGenre1(), text);
		if (mwindow->getMovie().getGenre2() != "")
		{
			if (mwindow->getMovie().getGenre2().length() >= 7 || mwindow->getMovie().getGenre2() == "Comedy")
				text_size = 14.f;
			else
				text_size = 17.f;
			graphics::drawRect(WINDOW_WI / 2 - 30, WINDOW_HE / 2 + 93, 75, 30, ge);
			graphics::drawText(WINDOW_WI / 2 - 55, WINDOW_HE / 2 + 99, text_size, mwindow->getMovie().getGenre2(), text);
		}

		// Draw the movie Title
		if (mwindow->getMovie().getName().length() > 16)
			text_size = 17.5f;
		else
			text_size = 20.f;
		graphics::drawText(WINDOW_WI / 2 - 350, WINDOW_HE / 2 + 100, text_size, mwindow->getMovie().getName(), text);

		// Draw Year
		graphics::setFont(ASSET_PATH + std::string("KeepCalm-Medium.ttf"));
		graphics::drawText(WINDOW_WI / 2 - 350, WINDOW_HE / 2 + 130, 17.f, mwindow->getMovie().getYear(), text);

		// Draw Description
		SETCOLOR(text.fill_color, 0.7, 0.7, 0.7);
		graphics::setFont(ASSET_PATH + std::string("RobotoSlab-Bold.ttf"));
		graphics::drawText(WINDOW_WI / 2 - 350, WINDOW_HE / 2 + 200, 15.f, mwindow->getMovie().getDescription(), text);
		graphics::drawText(WINDOW_WI / 2 - 350, WINDOW_HE / 2 + 220, 15.f, mwindow->getMovie().getDescription2(), text);

		// Draw Director
		SETCOLOR(text.fill_color, 1, 1, 1);
		graphics::setFont(ASSET_PATH + std::string("RobotoSlab-Regular.ttf"));
		graphics::drawText(WINDOW_WI / 2 - 350, WINDOW_HE / 2 + 335, 18.f, "Directing :    " + mwindow->getMovie().getDirector(), text);

		// Draw Stars
		graphics::drawText(WINDOW_WI / 2 - 350, WINDOW_HE / 2 + 370, 18.f, "Starring :    " + mwindow->getMovie().getCast(), text);
	}

	if (state == STATE_SEARCHING || state == STATE_YEARS)
	{
		// Changing the button position
		search_button->set_pos(WINDOW_WI/3 - 40, WINDOW_HE / 2);
		search_button->setIcon("arrow_back.png");

		// Drawing the search menu
		graphics::Brush br;

		SETCOLOR(br.fill_color, 0.1f, 0.f, 0.f);
		SETCOLOR(br.fill_secondary_color, 0.02f, 0.02f, 0.02f);
		SETCOLOR(br.outline_color, 0.1f, 0.1f, 0.1f);
		br.outline_opacity = 3;
		br.gradient = true;
		br.gradient_dir_u = 1.f;
		br.gradient_dir_v = 0.f;

		graphics::drawRect(WINDOW_WI/8 + 60, WINDOW_HE / 2, WINDOW_WI/3, WINDOW_HE, br);

		// Searching By Genre
		graphics::Brush text;
		text.outline_opacity = 0;
		SETCOLOR(text.fill_color, 0.7f, 0.7f, 0.7f);

		graphics::setFont(ASSET_PATH + std::string("KeepCalm-Medium.ttf"));
		graphics::drawText(20, 60, 17.f, "Genre:", text);
		graphics::drawText(20, 280, 17.f, "Year:", text);
		graphics::drawText(40, WINDOW_HE/2 + 100, 17.f, "Filter by   Movie  Name ,   Director   or   Actors:", text);

		for (auto gb : genreButtons)
			gb->draw();

		yearButton->draw();

		txtf->draw();
		txtButton->draw();
	}
	else
	{
		search_button->set_pos(50, WINDOW_HE / 2);
		search_button->setIcon("arrow_forward.png");
	}

	if (state == STATE_YEARS)
		for (auto yb : yearButtons)
			yb->draw();

	search_button->draw();
	clearFilters->draw();
}

Browser::~Browser()
{
	for (auto gb : genreButtons)
		delete gb;

	for (auto m : movies)
		delete m;

	for (auto mw : movieWindows)
		delete mw;

	movieWindows.clear();
}
