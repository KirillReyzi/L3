#include "List.h"

bool Adjacency::input(string path) {
	ifstream file;
	file.open(path);
	if (!file.is_open()) {
		cout << "FILE ERORR" << endl;
		return false;
	}

	string a;
	string b;
	int cost_a_b = 0;
	int cost_b_a = 0;
	string buff;

	int pos = 0;
	int check = 0;
	string curent;

	while (getline(file, curent)) {
		for (int i = 0; i < curent.size(); i++) {
			if (curent[i] == ';') {
				if (check == 0) {
					a = curent.substr(pos, i);
					pos = i + 1;
					check++;
				}
				else if (check == 1) {
					b = curent.substr(pos, i - pos);
					pos = i + 1;
					check++;
				}
				else if (check == 2) {
					buff = curent.substr(pos, i - pos);
					if (buff != "N/A") {
						cost_a_b = stoi(buff);
					}
					pos = i + 1;
					check = 0;
				}
			}
		}
		buff = curent.substr(pos, curent.size() - pos);
		if (buff != "N/A") {
			cost_b_a = stoi(buff);
		}
		pos = 0;

		add_way(a, b, cost_a_b);
		add_way(b, a, cost_b_a);

		cost_a_b = 0;
		cost_b_a = 0;
	}

	return true;
}

List* Adjacency::add_elem(string name) {
	Node* a = new Node();
	a->name = name;
	List* lst = new List();
	lst->node = a;

	if (all_elements == nullptr) {
		all_elements = lst;
		return lst;
	}

	List* iter = all_elements;
	while (iter->next) {
		iter = iter->next;
	}
	iter->next = lst;
	return lst;
}

void Adjacency::add_way(string _a, string _b, int cost) {
	if (cost == 0)
		return;

	Node* node_a;
	Node* node_b;

	List* a;
	List* b;


	a = search_elem(_a);
	if (!a) {
		node_a = add_elem(_a)->node;
	}
	else {
		node_a = a->node;
	}

	b = search_elem(_b);
	if (!b) {
		node_b = add_elem(_b)->node;
	}
	else {
		node_b = b->node;
	}

	List* lst = new List();
	lst->node = node_b;
	lst->cost = cost;

	if (node_a->destination == nullptr) {
		node_a->destination = lst;
		return;
	}

	List* buff = node_a->destination;
	while (buff->next)
	{
		buff = buff->next;
	}

	buff->next = lst;
}

List* Adjacency::search_elem(string a) {
	List* buff = all_elements;
	while (buff)
	{
		if (buff->node->name == a) {
			return buff;
		}
		buff = buff->next;
	}
	return nullptr;
}

void Adjacency::reset() {
	List* iter = all_elements;

	while (iter) {
		iter->cost = 99999999;
		iter->node->visited = false;
		iter = iter->next;
	}
}

string Adjacency::Dijkstra(string _a, string _b) {
	if (!search_elem(_a))
		return "Wrong way";
	if (!search_elem(_b))
		return "Wrong way";

	reset();
	string way;
	search_elem(_a)->cost = 0;
	string cur = Dijkstra(_a, _b, 0);

	while (cur != _a) {
		way = cur + " " + way;
		reset();
		search_elem(_a)->cost = 0;
		cur = Dijkstra(_a, cur, 0);
	}
	return _a + " " + way + _b;
}

string Adjacency::Dijkstra(string _a, string _b, int cost)
{
	List* a = search_elem(_a);
	a->node->visited = true;

	List* adjacency = a->node->destination;

	bool change = false;

	int curent_cost;
	while (adjacency)
	{
		List* cur = search_elem(adjacency->node->name);
		curent_cost = adjacency->cost + cost;
		if (curent_cost < cur->cost) {
			cur->cost = curent_cost;
			if (cur->node->name == _b) {
				change = true;
			}
		}
		adjacency = adjacency->next;
	}

	sort_list();

	List* next = all_elements;

	string name = "";

	while (next) {
		if (!next->node->visited)
			name = Dijkstra(next->node->name, _b, next->cost);
		next = next->next;
	}

	if (name != "")
		return name;
	if (change)
		return  search_elem(_a)->node->name;
	return "";
}

void Adjacency::sort_list() {
	List* iter = all_elements;
	while (iter->next)
	{
		List* a = all_elements;
		List* b = all_elements->next;
		while (b)
		{
			if (a->cost > b->cost) {
				Node* buff_node = b->node;
				int buff_cost = b->cost;

				b->node = a->node;
				b->cost = a->cost;

				a->node = buff_node;
				a->cost = buff_cost;
			}
			a = a->next;
			b = b->next;
		}
		iter = iter->next;
	}
}