#ifndef GRAPH_ADJ_MATRIX_HPP
#define GRAPH_ADJ_MATRIX_HPP

#include <vector>
#include <iostream>
#include <iomanip>
#include <queue>
#include <stack>
#include <algorithm>

template <bool directed = false>
class Graph_adj_matrix {
public:
	// in Graph_adj_list is using val_type = int;
    using matrix = std::vector<std::vector<int>>;
    using vec_vis = std::vector<bool>;
public:
    Graph_adj_matrix (int n, const matrix& edges);
    Graph_adj_matrix (int n, int (*edges)[2], int size);
	Graph_adj_matrix (const matrix& am);
	Graph_adj_matrix (const Graph_adj_matrix<directed>& other);
	Graph_adj_matrix (Graph_adj_matrix<directed>&& other);

    ~Graph_adj_matrix () = default;
public:
    void add_edge (int u, int v);
    void add_vertex ();

    template <typename func>
    void dfs (func f, int u = 0);

    template <typename func>
    void bfs (func f, int u = 0);

	void transpose ();
	Graph_adj_matrix<directed> clone_transpose() const;

	std::vector<int> curr_levels_vertexes (int u, int level) const;
	matrix find_all_paths (int u, int v) const;
    std::vector<int> shortest_path (int u, int v) const;
	bool is_cycled () const;
    std::vector<int> top_sort () const;
	int components_number () const; // can be stored in variable and counted once at ctoring
	matrix find_sccs_kosarajou () const;

    void print () const;
private:
    matrix am; // adj_matrix

	void _find_all_paths (int u, int v, matrix& res, std::vector<int>& sub_res, vec_vis& visits) const;

	void _dfs_helper (int u, vec_vis& visits) const;

    template <typename func>
    void _dfs (int u, vec_vis& visits, func f);
	bool _is_cycled (int u, vec_vis& visits, vec_vis& in_stack, int parent) const;

	void _fill_in_order(int u, vec_vis& visited, std::stack<int>& st) const;
	void _find_scc(int u, vec_vis& visited, std::vector<int>& component) const;
};

#include "graph_adj_matrix_header.hpp"

#endif // GRAPH_ADJ_MATRIX_HPP