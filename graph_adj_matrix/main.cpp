#include <graph_adj_matrix.hpp>
#include <helpers.h>

using std::vector;
using graph = Graph_adj_matrix;
using namespace graph_utils;

int main () {
    vector<vector<int>> edges_1 = {
        {0, 3},
        {1, 2},
        {1, 4},
        {2, 4},
        {3, 2},
        {3, 0},
        {3, 5},
        {4, 5},
        {5, 4}
    };

    vector<vector<int>> edges_2 = {
        {0, 1},
        {0, 2},
        {1, 3},
        {1, 2},
        {2, 5},
        {2, 7},
        {3, 4},
        {3, 7},
        {4, 6},
        {5, 3},
        {6, 7},
        {7, 0},
    };

    vector<vector<int>> edges_3 = {
        {0, 1},
        {0, 2},
        {1, 2},
        {1, 3},
        {2, 1},
        {2, 4},
        {3, 1},
        {3, 4},
        {4, 2},
        {4, 3},
    };

	vector<vector<int>> edges_4 = {
        {0, 1},
        {0, 3},
        {1, 4},
        {2, 3},
        {2, 5},
        {3, 4},
        {4, 5},
        {5, 4},
    };

    int matrix[][2] = {
        {0, 3},
        {1, 2},
        {1, 4},
        {2, 4},
        {3, 2},
        {3, 0},
        {3, 5},
        {4, 5},
        {5, 4}
    };

    int size_matr = sizeof(matrix) / sizeof(matrix[0]);

    graph gr(edges_max(edges_4), edges_4);
    gr.print();
    // gr.bfs([](const int val){std::cout << val << ' ';});

    // print_path(gr.shortest_path(0, 5));
	// Graph_adj_matrix::matrix res = gr.find_all_paths(0, 2);

	// for (const std::vector<int>& row : res) {
	// 	print_path(row);
	// 	std::cout << '\n';
	// }

	std::vector<int> level = gr.curr_levels_vertexes(0, 0);
	for (int val : level) {
		std::cout << val << ' ';
	}
	std::cout << '\n';


}