#ifndef GR_ADJ_LIST_HPP
#define GR_ADJ_LIST_HPP

#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <stack>
#include <algorithm>
#include <limits>
#include <list>

template <bool directed>
class Graph_al {
public:
	using vec_2d = std::vector<std::vector<int>>;
	using pair_i = std::pair<int, int>;
	using list = std::vector<std::vector<pair_i>>;
	using vec_vis = std::vector<bool>;
public:
	Graph_al (int n, const vec_2d& edges);
	Graph_al (const list& adj_list);
	Graph_al (const Graph_al& other);
	Graph_al (Graph_al&& other);

	~Graph_al () = default;
public:
	void add_edge (int u, int v, int weight); // ~0(1)
	void add_vertex (); // ~0(1)

	template <typename func>
	void dfs (func f, int u = 0); // O(V + E)

	template <typename func>
	void bfs (func f, int u = 0); // O(V + E)

	void transpose ();  // O(V + E)

	std::vector<int> top_sort () const;  // O(V + E)
	vec_2d find_sccs_kosarajou () const; // O(V + E) + O(V + E) + O(V + E)+ O(V)
	vec_2d find_sccs_tarjan () const; // O(V + E)
	Graph_al<directed> clone_transpose () const; // O(V + E)
	std::vector<int> sssp_top_sort (int src, int dst) const; // O(V + E) + O(V + E)
	std::vector<int> sssp_djikstra (int src, int dst) const; // O((V + E) * log V)
	std::pair<std::vector<int>, bool> sssp_bellman_ford (int src, int dst) const; // O(V * (V + E)) + O(V * (V + E))
	vec_2d mst_prim (int src = 0) const; 
	void print () const;

private:
	list al;

	struct pair_cmp {
		bool operator() (const pair_i& a, const pair_i& b) { return a.second > b.second; }
	};

	bool _not_same_vals (int u, int v) const;

	template <typename T>
	void print_vec(const std::vector<T>& vec) const;

	template <typename func>
	void _dfs (int u, vec_vis& visits, func f);

	void _dfs_helper (int u, vec_vis& visits);

	void _fill_in_order (int u, vec_vis& visits, std::stack<int>& st) const;
	void _find_scc (int u, vec_vis& visits, std::vector<int>& component) const;
	void _find_scc_tarjan (int u, vec_vis& in_stack, std::vector<int>& ids, std::vector<int>& low_link, std::stack<int>& st, vec_2d& res) const;
	void _dfs_sssp (std::vector<double>& dist, std::stack<int, std::vector<int>>& st, std::vector<int>& paths) const;
	bool _relaxation (std::vector<double>& dist, int u, int v, int cost, std::vector<int>& path) const;
	std::vector<int> _get_path (int u, int v, const std::vector<int>& paths) const;
	bool _out_of_ranges  (int u) const;
};

#include "gr_adj_list_header.hpp"

#endif // GR_ADJ_LIST_HPP