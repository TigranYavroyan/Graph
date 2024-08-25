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

	vector<vector<int>> gpt = {
		{0, 1, 1},
		{1, 2, 1},
		{1, 3, 3},
		{2, 3, 1},
		{3, 4, 1},
	};

	vector<vector<int>> kormen = { // cycled
		{0, 1, 10},
		{0, 2, 5},
		{1, 2, 2},
		{1, 3, 1},
		{2, 1, 3},
		{2, 3, 9},
		{2, 4, 2},
		{3, 4, 4},
		{4, 0, 7},
		{4, 3, 6},
	};

	vector<vector<int>> neg_cyc = {
		{0, 1, 1},
		{1, 2, 1},
		{2, 3, 1},
		{3, 4, 1},
		{4, 5, 1},
		{5, 2, -5},
		{4, 6, 1},
	};

	vector<vector<int>> test = {
		{0, 1, 1},
		{1, 2, 1},
		{2, 3, 1},
		{3, 4, 1},
		{4, 2, -100},
		{4, 5, 1},
	};

	vector<vector<int>> check = test;
	int dst = edges_max(check);
	int src = 0;

	Graph gr(edges_max(check), check);
	gr.print();
	endl();

	print_path(gr.sssp_top_sort(src, dst));
	endl();
	print_path(gr.sssp_djikstra(src, dst));
	endl();
	auto [res, flag] = gr.sssp_bellman_ford(src, dst);

	if (flag) {
		print_path(res);
	}
	else {
		std::cout << "There is no path\n";
		print_path(res);
	}
	endl();
}