#ifndef GR_ADJ_LIST_HPP
#define GR_ADJ_LIST_HPP

#include <iostream>
#include <vector>
#include <utility>

template <bool directed>
class Graph_al {
public:
	using vec_2d = std::vector<std::vector<int>>;
	using list = std::vector<std::vector<std::pair<int, int>>>;
	using vec_vis = std::vector<bool>;
public:
	Graph_al (int n, vec_2d& edges);
	Graph_al (const list& adj_list);
	Graph_al (const Graph_al& other);
	Graph_al (Graph_al&& other);

	~Graph_al () = default;
public:
	void add_edge (int u, int v, int weight);
	void add_vertex ();

	template <typename func>
	void dfs (func f);

	template <typename func>
	void bfs (func f);

	void print () const;
private:
	list al;

	bool _not_same_vals (int u, int v) const;

	template <typename func>
	void _dfs (int u, vec_vis& visits, func f);

	void _dfs_helper (int u, vec_vis& visits);
};

#include "gr_adj_list_header.hpp"

#endif // GR_ADJ_LIST_HPP