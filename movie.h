#pragma once
#include <string>

class Movie {
	std::string name, director, cast, genre, year, description, poster;
public:
	std::string getName()        { return name; }
	std::string getDirector()    { return director; }
	std::string getCast()        { return cast; }
	std::string getGenre()       { return genre; }
	std::string getYear()        { return year; }
	std::string getDescription() { return description; }
	std::string getPoster()      { return poster; }

	Movie() { name = "-"; director = "-"; cast = "-"; genre = "-"; year = "-"; description = "-"; poster = "hunt.png"; }

	Movie (std::string n, std::string d, std::string c, std::string g, std::string y, std::string desc, std::string p) :
		name(n), director(d), cast(c), genre(g), year(y), description(desc), poster(p) {}

	~Movie() {}
};