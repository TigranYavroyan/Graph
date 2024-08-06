#ifndef GRAPH_ADJ_LIST_HPP
#define GRAPH_ADJ_LIST_HPP

#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>

class Graph_adj_list {
public:
    using list = std::vector<std::vector<int>>;
    using vec_vis = std::vector<bool>;
public:
    Graph_adj_list (int n, const list& edges);
    Graph_adj_list (int n, int (*edges)[2], int size);

    ~Graph_adj_list () = default;
public:
    void add_edge (int u, int v);
    void add_vertex ();

    template <typename func>
    void dfs (func f, int u = 0);

    template <typename func>
    void bfs (func f, int u = 0);

	list find_all_paths (int u, int v) const;
	std::vector<int> curr_levels_vertexes (int u, int level);
    std::vector<int> shortest_path (int u, int v) const; // unweighted graph

    void print () const;
private:
    list al;

    bool _not_same_vals (int i, int val) const;

    template <typename func>
    void _dfs (int u, vec_vis& visits, func f);

	void _find_all_paths (int u, int v, list& res, std::vector<int>& sub_res, vec_vis& visits) const;
};

#include "graph_adj_list.cpp"

#endif // GRAPH_ADJ_LIST_HPP