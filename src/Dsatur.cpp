#include "Dsatur.hpp"

#include <iostream>
#include <climits>

Dsatur::Dsatur(const std::map<int, std::vector<int>>& graph)
{
    this->graph = graph;
    for (const auto& i : graph)
        graph_colors[i.first] = -1;
}

void Dsatur::color_graph() // Coloring graph 
{
    if (graph.empty())
    {
        graph_colors = std::map<int, int>();
    }

    std::vector<int> saturation_colors; // Vector for each vertex's neighbor's color
    std::vector<int> todo; // Vector for vertices that hasn't yet been colored
	
    int max_degree = -1;
    int degree = -1;

    for (auto& i : graph) // Find the vertex with the highest degree (most neighbors), and save it's particulars
    {
        if (static_cast<int>(i.second.size()) > degree)
        {
            degree = static_cast<int>(i.second.size());
            max_degree = static_cast<int>(i.first);
        }
    }

    if (max_degree == -1)
    {
        std::cerr << "Error: Could not find a max degree node in the graph (reason unknown)" << std::endl;
        graph_colors = std::map<int, int>();
    }

    graph_colors[max_degree] = 0; // Apply to that vertex the first color

    std::map<int, int> saturation_level; // Vector for the number of colored neighbors of each vertex

    for (auto& i : graph) // Initialize saturation_level of each vertex to 0
        saturation_level[i.first] = 0;

    for (auto& i : graph[max_degree]) // Increase saturation_level by 1, for each vertex adjacent to max-degree vertex
        saturation_level[i] += 1;

    saturation_level[max_degree] = INT_MIN; // Upgrade saturation_level of max_degree vertex with the smallest integer so that it will never be increased and used later

    for (const auto& i : graph) // Insert uncolored vertices into todo vector
    {
        if (i.first != max_degree)
        {
            todo.push_back(i.first);
        }
    }

    while (!todo.empty())
    {
        int saturation = -1;
        int saturation_vertex = -1;

        for (auto& i : saturation_level) // Find the vertex with the highest saturation_level and take it's particulars
        {
            if (i.second > saturation)
            {
                saturation = i.second;
                saturation_vertex = i.first;
                saturation_colors.clear();

                for (auto& j : this->graph[i.first])
                {
                    saturation_colors.push_back(this->graph_colors[j]); // Add into saturation_colors, the color of each neighbor vertex
                }
            }
        }

        if (saturation_vertex == -1)
        {
            std::cerr << "Error: Could not find a max saturated node in the graph (reason unknown)" << std::endl;
            graph_colors = std::map<int, int>();
        }

        for (auto i = todo.begin(); i != todo.end(); ++i) // Delete the vertex that's about to get colored from todo vector
        {
            if (*i == saturation_vertex)
            {
                todo.erase(i);
                if (i == todo.end())
                    break;
            }
        }

        int lower_color = 0;
        int done = 0;

        while (!done)
        {
            done = 1;

            for (auto& i : saturation_colors) // Browse each color in saturation_colors vector and add the +1 biggest color from the biggest color in the vector
            {
                if (i == lower_color)
                {
                    lower_color += 1;
                    done = 0;
                }
            }
        }
        
        graph_colors[saturation_vertex] = lower_color; // Color the vertex with the color found above

        for (auto& i : graph[saturation_vertex]) // Increase saturation_level by 1 to vertices adjacent to vertex that just got colored
            if (saturation_level[i] != INT_MIN)
                saturation_level[i] += 1;
    	 
        saturation_level[saturation_vertex] = INT_MIN; // Colored vertex will never be used again
	}
}

void Dsatur::show_graph() // Print the result
{
    for (auto& i : graph_colors)
        std::cout << "Vertex: " << i.first + 1 << " color ---> " << i.second + 1 << std:: endl;
}
