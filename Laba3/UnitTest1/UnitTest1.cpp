#include "pch.h"
#include "../List.h"

TEST(Adjacency, input) {
	Adjacency test;

	test.input("input.txt");

	List* iter = test.all_elements;

	ASSERT_STREQ(iter->node->name.c_str(), "Санкт-Петербург");

	iter = iter->next;

	ASSERT_STREQ(iter->node->name.c_str(), "Москва");

	iter = iter->next;

	ASSERT_STREQ(iter->node->name.c_str(), "Хабаровск");

	iter = iter->next;

	ASSERT_STREQ(iter->node->name.c_str(), "Владивосток");
}

TEST(Adjacency, Dijkstra) {
	Adjacency test;

	test.input("input.txt");

	ASSERT_STREQ(test.Dijkstra("Москва", "Хабаровск").c_str(), "Москва Санкт-Петербург Хабаровск");
	ASSERT_STREQ(test.Dijkstra("Москва", "Санкт-Петербург").c_str(), "Москва Санкт-Петербург");
	ASSERT_STREQ(test.Dijkstra("Москва", "Владивосток").c_str(), "Москва Санкт-Петербург Владивосток");
}
