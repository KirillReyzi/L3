#pragma once
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Node;

class List {
public:
	List() : node(nullptr), cost(99999999), next(nullptr) {};
	Node* node;
	int cost;

	List* next;
};

class Node {
public:
	Node() : name(""), visited(0), destination(nullptr) {};
	string name;
	bool visited;

	List* destination;
};


class Adjacency
{
public:
	Adjacency() : all_elements(nullptr) {};
	bool input(string path);

	string Dijkstra(string _a, string _b);
	List* all_elements;

private:
	string Dijkstra(string _a, string _b, int cost);
	List* search_elem(string a);
	List* add_elem(string name);
	void add_way(string a, string b, int cost);
	void sort_list();
	void reset();
};