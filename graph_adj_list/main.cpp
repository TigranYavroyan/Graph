#include <graph_adj_list.hpp>
#include <helpers.h>

using graph = Graph_adj_list;
using std::vector;
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

	vector<vector<int>> cycled_edges_1 = {
        {0, 1},
        {0, 2},
        {1, 3},
        {2, 4},
        {2, 5},
        {3, 7},
		{6, 1},
		{7, 6},
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

    graph gr(edges_max(cycled_edges_1), cycled_edges_1);
    gr.print();
    std::cout << '\n';
    // gr.bfs([](const int val){std::cout << val << ' ';});
    // vector<int> res = gr.shortest_path(4,0);

    // for (int i = 0; i < res.size(); ++i) {
    //     std::cout << res[i];
    //     if ((i + 1) != res.size()) std::cout << " -> ";
    // }

	// Graph_adj_list::list res = gr.find_all_paths(1,3);

	// for (const auto& row : res) {
	// 	print_path(row);
	// 	std::cout << '\n';
	// }
	// std::vector<int> level = gr.curr_levels_vertexes(0, 2);
	// for (int val : level) {
	// 	std::cout << val << ' ';
	// }
	// std::cout << '\n';
	std::cout << std::boolalpha << gr.is_cycled() << std::endl;
}