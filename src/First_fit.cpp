#include <iostream>
#include <list>

#include "First_fit.hpp"

First_fit::First_fit(int v)
{
    this->v = v;
    adj = new std::list<int>[v];
}

First_fit::~First_fit() { delete[] adj; }

void First_fit::add_edge(const int v1, const int v2) const
{
    adj[v1].push_back(v2);
    adj[v2].push_back(v1);
}

void First_fit::greedy_coloring() const
{
    int result[v];

    result[0] = 0; // Assigning first color to first vertex 

    for (int u = 1; u < v; u++) // Initialise the rest vertices with -1 as color (-1 indicates the vertex hasn't been colored yet)
        result[u] = -1;

    bool available[v]; // Array storing the available colors. True means the color cr is available to use, false, one of the vertex's neighbor has that color
    for (int cr = 0; cr < v; cr++)
        available[cr] = true; // Initialise all colors to be available 

    for (int u = 1; u < v; u++) // Assign colors to remaining V-1 vertices
    {
        for (auto& i : adj[u]) // Traverse all adjacent vertices and flag their colors as unavailable
	        if (result[i] != -1)
                available[result[i]] = false;

        int cr;
        for (cr = 0; cr < v; cr++) // Find the first available color from the array
            if (available[cr])
                break;

        result[u] = cr; // Assign the found color

        for (auto& i : adj[u]) // Reset the colors to true for the next iteration
	        if (result[i] != -1)
                available[result[i]] = true;
    }

    for (auto u = 0; u < v; u++) // Print the result
	    std::cout << "Vertex " << u+1 << " --->  Color "
             << result[u]+1 << std::endl;
}