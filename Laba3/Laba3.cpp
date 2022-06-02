#include <iostream>
#include "LiSt.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	Adjacency test;

	test.input("input.txt");

	fstream file("input.txt");

	if (!file.is_open())
		return 0;

	string out;

	while (getline(file, out)) {
		cout << out << endl;
	}

	cout << endl;

	cout << test.Dijkstra("Владивосток", "Санкт-Петербург") << endl;
	cout << test.Dijkstra("Владивосток", "Хабаровск") << endl;
	cout << test.Dijkstra("Владивосток", "Москва") << endl;

	cout << endl;

	cout << test.Dijkstra("Москва", "Санкт-Петербург") << endl;
	cout << test.Dijkstra("Москва", "Хабаровск") << endl;
	cout << test.Dijkstra("Москва", "Владивосток") << endl;

	cout << endl;

	cout << test.Dijkstra("Санкт-Петербург", "Москва") << endl;
	cout << test.Dijkstra("Санкт-Петербург", "Хабаровск") << endl;
	cout << test.Dijkstra("Санкт-Петербург", "Владивосток") << endl;

	cout << endl;

	cout << test.Dijkstra("Хабаровск", "Санкт-Петербург") << endl;
	cout << test.Dijkstra("Хабаровск", "Москва") << endl;
	cout << test.Dijkstra("Хабаровск", "Владивосток") << endl;
	return 0;
}
