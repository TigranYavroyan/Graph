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

	Graph gr(edges_max(edges_2), edges_2);
	gr.add_edge(5, 0, 12);
	gr.print();
	endl();

	auto res = gr.find_sccs_kosarajou();

	for (auto& row : res) {
		print_path(row);
		endl();
	}
	endl();

}