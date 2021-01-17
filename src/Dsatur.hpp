#pragma once

#include <map>
#include <vector>

class Dsatur
{
private:
	std::map<int, std::vector<int>> graph;
	std::map<int, int> graph_colors;

public:
	Dsatur(const std::map<int, std::vector<int>>& graph);
	void color_graph();
	void show_graph();
};