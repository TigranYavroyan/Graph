#ifndef GRAPH_ADJ_LIST_HPP
#define GRAPH_ADJ_LIST_HPP

#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>

template <bool directed = false>
class Graph_adj_list {
public:
	using val_type = int;
    using list = std::vector<std::vector<val_type>>;
    using vec_vis = std::vector<bool>;
public:
    Graph_adj_list (int n, const list& edges);
	Graph_adj_list (const list& al);
    Graph_adj_list (int n, val_type (*edges)[2], int size);
	Graph_adj_list (const Graph_adj_list<directed>& other);
	Graph_adj_list (Graph_adj_list<directed>&& other);

    ~Graph_adj_list () = default;
public:
    void add_edge (val_type u, val_type v);
    void add_vertex ();

	Graph_adj_list<directed> clone_transpose () const;
	void transpose ();

    template <typename func>
    void dfs (func f, val_type u = 0);

    template <typename func>
    void bfs (func f, val_type u = 0);

	list find_all_paths (val_type u, val_type v) const;
	std::vector<val_type> curr_levels_vertexes (val_type u, int level) const;
    std::vector<val_type> shortest_path (val_type u, val_type v) const; // unweighted graph
	bool is_cycled () const;
    std::vector<val_type> top_sort () const;
	int components_number () const; // can be stored in variable and counted once at ctoring
	list find_sccs() const;

    void print () const;

private:
    list al;

    bool _not_same_vals (int i, val_type val) const;

    template <typename func>
    void _dfs (val_type u, vec_vis& visits, func f);

	void _dfs_helper (val_type u, vec_vis& visits) const;

	void _find_all_paths (val_type u, val_type v, list& res, std::vector<val_type>& sub_res, vec_vis& visits) const;
	bool _is_cycled (val_type u, vec_vis& visits, vec_vis& in_stack, val_type parent) const;

	void print_vec(const std::vector<val_type>& vec) const;

	void _fill_in_order(int u, vec_vis& visited, std::stack<val_type>& st) const;
	void _find_scc(int u, vec_vis& visited, std::vector<val_type>& component) const;

};

#include "graph_adj_list_header.hpp"

#endif // GRAPH_ADJ_LIST_HPP