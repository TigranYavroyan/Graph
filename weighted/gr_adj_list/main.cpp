#include <gr_adj_list.hpp>
#include <helpers.h>

using std::vector;
using namespace graph_utils;
using Graph = Graph_al<true>;

int main () {
	vector<vector<int>> edges_1 = {
		{0, 1, 4},
		{0, 1, 4},
		{0, 2, 5},
		{1, 2, 5},
		{1, 3, 10},
		{2, 3, 4},
	};

	vector<vector<int>> edges_2 = {
		{0, 1, 5},
		{1, 3, 4},
		{1, 2, 3},
		{1, 4, 2},
		{3, 4, 7},
		{3, 5, 6},
	};

	// Tarjan's example
	vector<vector<int>> for_scc_6 = {
		{0, 1, 10},
		{1, 2, 10},
		{1, 4, 10},
		{1, 6, 10},
		{2, 3, 10},
		{3, 2, 10},
		{3, 5, 10},
		{4, 5, 10},
		{4, 7, 10},
		{5, 4, 10},
		{6, 0, 10},
		{6, 2, 10},
	};

	vector<vector<int>> for_sssp = {
		{0, 1, 3},
		{0, 2, 6},
		{1, 2, 2},
		{1, 3, 4},
		{1, 4, 11},
		{2, 3, 8},
		{2, 6, 11},
		{3, 4, 4},
		{3, 5, 5},
		{3, 6, 2},
		{4, 7, 9},
		{5, 7, 1},
		{6, 7, 2},
	};

	vector<vector<int>> test_sssp = {
		{0, 1, 1},
		{0, 3, 5},
		{1, 2, 1},
		{2, 4, 1},
		{4, 3, 3},
	};

	Graph gr(edges_max(for_sssp), for_sssp);
	gr.print();
	endl();

	auto res = gr.sssp_top_sort();

	for (auto val : res) {
		std::cout << val << ' ';
	}
	endl();

}