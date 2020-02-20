#pragma once

#include <vector>

struct book {
	int id;
	int score;
};

struct library {
	int id;
	int numOfBooks;
	int signUpDays;
	int numOfBooksPerDay;
	std::vector <int> books;
};

struct Libraries {
	int numOfBooks;
	int numOfLib;
	int numOfDays;
	std::vector <struct book> books;
	std::vector <struct library> libs;
};

int hashcode(int argc, char **argv);
