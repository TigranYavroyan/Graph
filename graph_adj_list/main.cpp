#include <graph_adj_list.hpp>
#include <helpers.h>

using graph = Graph_adj_list<true>;
using std::vector;
using namespace graph_utils;

int main () {
    vector<vector<int>> edges_1 {
        {0, 1},
        {0, 2},
        {1, 3},
        {2, 3},
        {3, 4},
    };

    vector<vector<int>> edges_2 {
        {0, 1},
        {0, 2},
        {1, 3},
        {2, 4},
        {2, 5},
        {3, 7},
        {7, 6},
    };


    vector<vector<int>> cycled_edges_1 {
        {0, 1},
        {0, 2},
        {1, 3},
        {2, 4},
        {2, 5},
        {3, 7},
        {6, 1},
        {7, 6},
    };

    vector<vector<int>> cycled_edges_2 {
        {0, 1},
        {0, 2},
        {1, 2},
        {1, 3},
        {2, 5},
        {2, 7},
        {3, 4},
        {3, 7},
        {4, 6},
        {5, 3},
        {6, 7},
        {7, 0},
    };

	vector<vector<int>> multi_components = {
		{0, 1},
		{1, 2},
		{3, 4},
		{4, 5},
		{6, 7},
		{8, 9},
	};

    graph gr(edges_max(cycled_edges_2), cycled_edges_2);
    gr.print();
    std::cout << '\n';
	gr.transpose();
	gr.print();
	std::cout << '\n';

	// vector<vector<int>> all_paths = gr.find_all_paths(0, edges_max(edges_2));

	// for (vector<int>& row : all_paths) {
	// 	print_path(row);
	// 	std::cout << '\n';
	// }

	// std::cout << std::boolalpha << gr.is_cycled() << std::endl;
    // auto res = gr.top_sort();

    // if (res.empty()) std::cout << "top sort nema" << std::endl;
    // else {
    //     for (auto val : res) {
    //         std::cout << val << ' ';
    //     }
    // }
}