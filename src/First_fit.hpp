#pragma once

#include <iostream>
#include <list>

class First_fit
{
private:
	int v;
	std::list<int>* adj;

public:
	explicit First_fit(int v);
	~First_fit();
	void add_edge(int v1, int v2) const;
	void greedy_coloring() const;
	std::list<int>* get_list()const { return adj; }
};