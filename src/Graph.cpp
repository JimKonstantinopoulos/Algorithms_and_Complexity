#include "Graph.hpp"

#include <algorithm>
#include <cmath>
#include <string>

Graph::Graph() = default;

Graph::Graph(const int v, const std::string& problem_name) 
{
    V = v;
    problemName = problem_name;
    adjMatrix = new int[V * V];
    first_fit = new First_fit(V);
}

Graph::~Graph()
{
    delete[] adjMatrix;
    delete first_fit;
}

void Graph::initialize_adj_matrix(std::vector<std::set<int>> exam_students)
{
    std::cout << "Adjacency Matrix" << std::endl;
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (i == j)
            {
                add_edge(i, j, 0);
                continue;
            }
            const int c = common_elements(exam_students[i + 1], exam_students[j + 1]);
            if (c > 0)
            {
                std::cout << i + 1 << " " << j + 1 << " " << c << std::endl;
            	if(j > i)
					first_fit->add_edge(i, j);    

                g_map[i].push_back(j);
            }
            add_edge(i, j, c);
        }
    }
}

void Graph::add_edge(const int i, const int j, const int c) const
{
    adjMatrix[i * V + j] = c;
}

int Graph::common_elements(std::set<int>& s1, std::set<int>& s2)
{
    int c = 0;
    for (int x : s1) 
    {
        for (int y : s2)
        {
            if (x == y)
            {
                c++;
                break;
            }
        }
    }
    return c;
}

void Graph::conflict_density()
{
    int c = 0;
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (adjMatrix[i * V + j] > 0) 
            {
                c++;
            }
            
        }
    }
    this -> confDen = static_cast<double>(c) / static_cast<double>(V * V);
}

void Graph::deg_min_med_max()
{
	this -> max = 0;
    this -> min = (1LL << 31) - 1; //max του integer

    for (int i = 0; i < V; i++)
    {
        int c = 0;
        for (int j = 0; j < V; j++) 
        {
            if (adjMatrix[i * V + j] > 0)
            {
                c++;
            }
        }
        this -> sequence_degree.push_back(c);
        if (c > max)
            this -> max = c;

        if (c < min)
            this -> min = c;
    }

	std::sort(sequence_degree.begin(), sequence_degree.end());
    int index_med;
    if (sequence_degree.size() % 2 == 0)
    {
        index_med = sequence_degree.size() / 2;
    } 
    else 
    {
        index_med = (sequence_degree.size() + 1) / 2;
    }

    this -> med = sequence_degree[index_med];
}

void Graph::deg_mean()
{
    int sum = 0;
    for (int i : sequence_degree)
    {
        sum += sequence_degree[i];
    }
    this -> mean = static_cast<double>(sum) / static_cast<double>(sequence_degree.size());
}

void Graph::c_v() 
{
    double sum = 0.0;
    double a, b;
    for (int i : sequence_degree)
    {
        a = static_cast<double>(i) - mean;
        b = pow(a, 2.0);
        sum += b;
    }
    const double s_2 = sum / static_cast<double>(sequence_degree.size());
    const double s = sqrt(s_2);
    this -> CV = (s / mean) * 100;
}

void Graph::print_statistic_array()  const
{
    for (const auto& i : statisticArray) 
    {
        std::cout << i << std::endl;
    }
}

int Graph::get_vertices() const {return V;}

int* Graph::get_adj_matrix() const {return adjMatrix;}

First_fit* Graph::return_first_fit() const
{
    return first_fit;
}

std::map<int, std::vector<int>> Graph::return_map() const
{
    return g_map;
}


std::string Graph::to_string() const
{
    return "Name: " + this -> problemName.substr(12, 8) + " |V|: " + std::to_string(V) + " Conflict Density: "+ std::to_string(confDen) +
                                        " Min: " + std::to_string(min) + " Med: " + std::to_string(med) + " Max: " + std::to_string(max) +
                                        " Mean: " + std::to_string(mean) + " CV(%): " + std::to_string(CV) + "%";
}