#pragma once
#include <string>

// Here are stored all the movie properties and information
class Movie 
{
	std::string name, director, stars, genre1, genre2, year, description, description2, poster;
public:
	std::string getName()         { return name; }
	std::string getDirector()     { return director; }
	std::string getCast()         { return stars; }
	std::string getGenre1()		  { return genre1; }
	std::string getGenre2()       { return genre2; }
	std::string getYear()         { return year; }
	std::string getDescription()  { return description; }
	std::string getDescription2() { return description2; }
	std::string getPoster()       { return poster; }

	Movie() { name = "Movie Name"; director = "-"; stars = "-"; genre1 = "-"; genre2 = "-"; year = "-"; description = "-"; description2 = "-"; poster = "jp.png"; }

	Movie (std::string n, std::string d, std::string s, std::string g1, std::string g2, std::string y, std::string desc, std::string desc2, std::string p) :
		name(n), director(d), stars(s), genre1(g1), genre2(g2), year(y), description(desc), description2(desc2), poster(p) {}

	~Movie() {}
};