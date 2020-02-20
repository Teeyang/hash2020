
#include "Header.h"
#include <iostream>
#include<algorithm>
#include <fstream>
#include <vector>

using namespace std;

struct Libraries getLibraries(char *filename)
{
	struct Libraries LibrariesWithInfomation = { 0 };
	int numOfBooks = 0, numOfLibs = 0, numOfDays = 0;
	vector <book> books;
	vector <library> libs;
	struct book b = { 0 };
	struct library l = { 0 };
	int bookId = 0;

	ifstream input_file;
	input_file.open(filename);
	input_file >> numOfBooks;
	input_file >> numOfLibs;
	input_file >> numOfDays;
	for (int i = 0; i < numOfBooks; i++) {
		b = { 0 };
		input_file >> b.score;
		b.id = i;
		books.push_back(b);
	}
	for (int i = 0; i < numOfLibs; i++) {
		l = { 0 };
		input_file >> l.numOfBooks;
		input_file >> l.signUpDays;
		input_file >> l.numOfBooksPerDay;
		for (int y = 0; y < l.numOfBooks; y++) {
			input_file >> bookId;
			l.books.push_back(bookId);
		}
		l.id = i;
		libs.push_back(l);
	}
	input_file.close();

	sort(books.begin(), books.end(), [](const struct book& a, const struct book& b) {
		return a.score < b.score;
	});
	LibrariesWithInfomation.numOfBooks = numOfBooks;
	LibrariesWithInfomation.numOfLib = numOfLibs;
	LibrariesWithInfomation.numOfDays = numOfDays;
	LibrariesWithInfomation.books = books;
	LibrariesWithInfomation.libs = libs;

	return LibrariesWithInfomation;
}

void proccessAndUpdateSolution(struct Libraries d, char *outfile)
{
	vector <int> scanned;
	int max_book = 0;

	sort(d.libs.begin(), d.libs.end(), [](const struct library& a, const struct library& b) {
		return a.signUpDays < b.signUpDays || (a.signUpDays <= b.signUpDays && a.numOfBooksPerDay > b.numOfBooksPerDay);
	});
	ofstream output_file;
	output_file.open(outfile);
	output_file << d.numOfLib << endl;
	for (int i = 0; i < d.numOfLib; i++) 
	{
		output_file << d.libs[i].id << " " << d.libs[i].numOfBooks << endl;
		for (int y = 0; y < d.libs[i].numOfBooks; y++) {
			output_file << d.libs[i].books[y] << " ";
		}
		output_file << endl;
	}
	output_file.close();
}

int main(int argc, char *argv[])
{
	struct Libraries d = getLibraries(argv[1]);
	proccessAndUpdateSolution(d, argv[2]);
	return (0);
}