#pragma once
#include <string>

class Movie {
	std::string name, director, stars, genre, year, description, description2, poster;
public:
	std::string getName()         { return name; }
	std::string getDirector()     { return director; }
	std::string getCast()         { return stars; }
	std::string getGenre()        { return genre; }
	std::string getYear()         { return year; }
	std::string getDescription()  { return description; }
	std::string getDescription2() { return description2; }
	std::string getPoster()       { return poster; }

	Movie() { name = "Movie Name"; director = "-"; stars = "-"; genre = "-"; year = "-"; description = "-"; description2 = "-"; poster = "jp.png"; }

	Movie (std::string n, std::string d, std::string s, std::string g, std::string y, std::string desc, std::string desc2, std::string p) :
		name(n), director(d), stars(s), genre(g), year(y), description(desc), description2(desc2), poster(p) {}

	~Movie() {}
};