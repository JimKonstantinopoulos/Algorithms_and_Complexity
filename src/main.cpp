#include "Graph.hpp"

#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <sstream>


Graph* read_data(const std::string& fn, const int exams)
{
	std::vector<std::set<int>> exam_students(exams + 1);

    Graph* graph = new Graph(exams, fn);

	std::fstream fs(fn);

    if (!fs.is_open())
    {
	    std::cerr << "Could not open file: " << fn << std::endl;
        exit(-1);
    }

    int student_id = 0;
	std::string line;

    while (getline(fs, line))
    {
        if (line.empty())
            continue;
        student_id++;
        std::istringstream iss(line);
        int exam_id;
        while (iss >> exam_id) 
        {
            exam_students[exam_id].insert(student_id);
            std::cout << "Student " << student_id << " is enrolled in exam " << exam_id << std::endl;
        }
    }
    fs.close();

	std::cout << "#################################" << std::endl;

    for (int i = 1; i <= exams; i++)
    {
	    std::cout << "Exam " << i << " Enrolled students: ";
        for (int student : exam_students[i])
	        std::cout << student << " ";
	    std::cout << std::endl;        
    }
	std::cout << std::endl;

    graph->initialize_adj_matrix(exam_students);
    
    graph->conflict_density();
    
    graph->deg_min_med_max();

    graph->deg_mean();

    graph->c_v();

	std::cout << graph->to_string() << std::endl;

    return graph;
}

void select_algorithm(const int choice, Graph *graph)
{
    switch(choice)
    {
    case 1:
        graph->return_first_fit()->greedy_coloring();
        break;

    case 2:
	    {
			Dsatur* dsatur = new Dsatur(graph->return_map());
			dsatur->color_graph();
			dsatur->show_graph();
			break;
	    }

    case 3:
        {
			RLF* rlf = new RLF(graph->return_map());
            rlf->color_graph();
            rlf->show_graph();
			break;
		}
        
    default:
        exit(-1);
    }
}

void select_menu_option(const int option)
{
	std::string datasets[14] =
    {
        "../datasets/car-f-92.stu",
        "../datasets/car-s-91.stu",
        "../datasets/ear-f-83.stu",
        "../datasets/hec-s-92.stu",
        "../datasets/kfu-s-93.stu",
        "../datasets/lse-f-91.stu",
        "../datasets/pur-s-93.stu",
        "../datasets/rye-s-93.stu",
        "../datasets/sta-f-83.stu",
        "../datasets/toy_e5_s6.stu",
        "../datasets/tre-s-92.stu",
        "../datasets/uta-s-92.stu", 
        "../datasets/ute-s-92.stu", 
        "../datasets/yor-f-83.stu", 
    };

    int exams[14] = {543, 682, 190, 81, 461, 381, 2419, 486, 139, 5, 261, 622, 184, 181};

    Graph g;

    switch (option)
    {
    case 1:
        g.print_statistic_array();
        break;

    case 2:
    {
        const int size = sizeof(datasets) / sizeof(datasets[0]);
        std::cout << "Please select one of the following files:" << std::endl;
        for (int i = 0; i < size; i++)
	        std::cout << i+1 << "->" << datasets[i] << std::endl;
        int choice = 0;
        std::cin >> choice;
        Graph* graph = read_data(datasets[choice - 1], exams[choice - 1]);
        std::cout << "Apply graph coloring with: " << std::endl;
        std::cout << "1) First fit: " << std::endl;
        std::cout << "2) Dsatur: " << std::endl;
        std::cout << "3) RLF: " << std::endl;
        std::cout << "Or Press any key to exit" << std::endl;
        std::cin >> choice;
        select_algorithm(choice, graph);
        break;
    }

    default:
        exit(-1);
    }
}

void execute_menu()
{
    int option;

    std::cout << "1) Print Statistics Array" << std::endl;
    std::cout << "2) Read Data from file" << std::endl;
    std::cout << "Or Press any key to exit" << std::endl;
    std::cin >> option;

    select_menu_option(option);
}

int main()
{
    execute_menu();

    return 0;
}