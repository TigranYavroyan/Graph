#ifndef GR_ADJ_LIST_HPP
#define GR_ADJ_LIST_HPP

#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <stack>
#include <algorithm>
#include <limits>

template <bool directed>
class Graph_al {
public:
	using vec_2d = std::vector<std::vector<int>>;
	using list = std::vector<std::vector<std::pair<int, int>>>;
	using vec_vis = std::vector<bool>;
public:
	Graph_al (int n, const vec_2d& edges);
	Graph_al (const list& adj_list);
	Graph_al (const Graph_al& other);
	Graph_al (Graph_al&& other);

	~Graph_al () = default;
public:
	void add_edge (int u, int v, int weight);
	void add_vertex ();

	template <typename func>
	void dfs (func f, int u = 0);

	template <typename func>
	void bfs (func f, int u = 0);

	void transpose ();

	std::vector<int> top_sort () const;
	vec_2d find_sccs_kosarajou () const;
	vec_2d find_sccs_tarjan () const;
	Graph_al<directed> clone_transpose () const;
	std::vector<double> sssp_top_sort (int src = 0) const;
	void print () const;

private:
	list al;

	bool _not_same_vals (int u, int v) const;

	template <typename func>
	void _dfs (int u, vec_vis& visits, func f);

	void _dfs_helper (int u, vec_vis& visits);

	void _fill_in_order (int u, vec_vis& visits, std::stack<int>& st) const;
	void _find_scc (int u, vec_vis& visits, std::vector<int>& component) const;
	void _find_scc_tarjan (int u, vec_vis& in_stack, std::vector<int>& ids, std::vector<int>& low_link, std::stack<int>& st, vec_2d& res) const;
	void _dfs_sssp (int u, std::vector<double>& dist) const;
};

#include "gr_adj_list_header.hpp"

#endif // GR_ADJ_LIST_HPP