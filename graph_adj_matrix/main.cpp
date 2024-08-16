#include <graph_adj_matrix.hpp>
#include <helpers.h>

using std::vector;
using graph = Graph_adj_matrix<true>;
using namespace graph_utils;

int main () {
    // vector<vector<int>> edges_1 = {
    //     {0, 3},
    //     {1, 2},
    //     {1, 4},
    //     {2, 4},
    //     {3, 2},
    //     {3, 0},
    //     {3, 5},
    //     {4, 5},
    //     {5, 4}
    // };

    // vector<vector<int>> edges_2 = {
    //     {0, 1},
    //     {0, 2},
    //     {1, 3},
    //     {1, 2},
    //     {2, 5},
    //     {2, 7},
    //     {3, 4},
    //     {3, 7},
    //     {4, 6},
    //     {5, 3},
    //     {6, 7},
    //     {7, 0},
    // };

    // vector<vector<int>> edges_3 = {
    //     {0, 1},
    //     {0, 2},
    //     {1, 2},
    //     {1, 3},
    //     {2, 1},
    //     {2, 4},
    //     {3, 1},
    //     {3, 4},
    //     {4, 2},
    //     {4, 3},
    // };

	// vector<vector<int>> edges_4 = {
    //     {0, 1},
    //     {0, 3},
    //     {1, 4},
    //     {2, 3},
    //     {2, 5},
    //     {3, 4},
    //     {4, 5},
    //     {5, 4},
    // };

	// vector<vector<int>> cycled_edges_1 = {
    //     {0, 1},
    //     {0, 2},
    //     {1, 3},
    //     {2, 4},
    //     {2, 5},
    //     {3, 7},
	// 	{6, 1},
	// 	{7, 6},
    // };

    // int matrix[][2] = {
    //     {0, 3},
    //     {1, 2},
    //     {1, 4},
    //     {2, 4},
    //     {3, 2},
    //     {3, 0},
    //     {3, 5},
    //     {4, 5},
    //     {5, 4}
    // };

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

	vector<vector<int>> for_scc_1 = {
		{0, 1},
		{1, 2},
		{1, 4},
		{1, 6},
		{2, 3},
		{3, 2},
		{3, 4},
		{3, 5},
		{4, 5},
		{5, 4},
		{6, 0},
		{6, 2},
	};

	vector<vector<int>> for_scc_2 = {
		{0, 1},
		{1, 2},
	};

	vector<vector<int>> for_scc_3 = {
		{0, 1},
		{1, 2},
		{2, 3},
		{3, 0},
		{3, 4},
		{4, 5},
		{5, 4},
		{5, 6},
		{6, 7},
		{7, 8},
		{8, 9},
		{9, 10},
		{10, 6},
	};

	vector<vector<int>> for_scc_4 = {
		{0, 1},
		{1, 2},
		{2, 0},
		{2, 3},
	};

	// just transposing and passing dfs is not working for this case
	vector<vector<int>> for_scc_5 = { // so we are using Kosarajou's argorithm
		{0, 1},
		{1, 2},
		{1, 3},
		{2, 0},
		{3, 4},
		{4, 5},
		{5, 3},
		{6, 5},
		{6, 7},
		{7, 6},
	};

	// Tarjan's example
	vector<vector<int>> for_scc_6 = {
		{0, 1},
		{1, 2},
		{1, 4},
		{1, 6},
		{2, 3},
		{3, 2},
		{3, 5},
		{4, 5},
		{4, 7},
		{5, 4},
		{6, 0},
		{6, 2},
	};

    graph gr(edges_max(for_scc_6), for_scc_6);
    gr.print();
	endl();
	auto res = gr.find_sccs_kosarajou();
	for (auto row : res) {
		print_path(row);
		endl();
	}
	auto res2 = gr.find_sccs_tarjan();
	endl();
	for (auto row : res2) {
		print_path(row);
		endl();
	}
	// gr.print();
    // gr.bfs([](const int val){std::cout << val << ' ';});

    // print_path(gr.shortest_path(0, 5));
	// Graph_adj_matrix::matrix res = gr.find_all_paths(0, 2);

	// for (const std::vector<int>& row : res) {
	// 	print_path(row);
	// 	std::cout << '\n';
	// }

	// std::vector<int> level = gr.curr_levels_vertexes(0, 2);
	// for (int val : level) {
	// 	std::cout << val << ' ';
	// }
	// std::cout << '\n';

	// std::cout << std::boolalpha << gr.is_cycled() << std::endl;
    // auto res = gr.top_sort();

    // if (res.empty()) std::cout << "top sort nema" << std::endl;
    // else {
    //     for (auto val : res) {
    //         std::cout << val << ' ';
    //     }
    //     std::cout << '\n';
    // }
}