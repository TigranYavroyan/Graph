#include "graph_adj_list.hpp"

template <bool directed>
Graph_adj_list<directed>::Graph_adj_list (int n, const list& edges) : al(n + 1) {
    for (int i = 0; i < edges.size(); ++i) {
        add_edge(edges[i][0], edges[i][1]);
    }
}
template <bool directed>
Graph_adj_list<directed>::Graph_adj_list (int n, int (*edges)[2], int size) : al(n + 1) {
    for (int i = 0; i < size; ++i) {
        add_edge(edges[i][0], edges[i][1]);
    }
}

template <bool directed>
void Graph_adj_list<directed>::add_edge (int u, int v) {
    if (u >= al.size() || v >= al.size())
        throw std::out_of_range("Out of range");

    if (_not_same_vals(u, v))
        al[u].push_back(v);

    if (!directed && _not_same_vals(v, u))
        al[v].push_back(u); // if undirected
}

template <bool directed>
void Graph_adj_list<directed>::add_vertex () {
    al.resize(al.size() + 1);
}

template <bool directed>
template <typename func>
void Graph_adj_list<directed>::dfs (func f, int u) {
    if (u >= al.size())
        throw std::out_of_range("Out of range");

    vec_vis visits(al.size(), false);
    _dfs(u, visits, f);
}

template <bool directed>
template <typename func>
void Graph_adj_list<directed>::_dfs (int u, vec_vis& visits, func f) {
    f(u);
    visits[u] = true;
    for (auto& v : al[u]) {
        if (!visits[v]) _dfs(v, visits, f);
    }
}

template <bool directed>
template <typename func>
void Graph_adj_list<directed>::bfs (func f, int u) {
    if (u >= al.size())
        throw std::out_of_range("Out of range");

    vec_vis visits(al.size(), false);
    std::queue<int> q;
    int val;

    q.push(u);

    // while (!q.empty()) {
    //     val = q.front(); q.pop();

    //     f(val);
    //     visits[val] = true;

    //     for (int v : al[val]) {
    //         if (!visits[v]) {
    //             q.push(v);
    //             visits[v] = true;
    //         }
    //     }
    // }

    while (!q.empty()) {
        int size = q.size();
        while (size--) {
            val = q.front(); q.pop();

            f(val);
            visits[val] = true;

            for (int v : al[val]) {
                if (!visits[v]) {
                    q.push(v);
                    visits[v] = true;
                }
            }
        }
        std::cout << '\n';
    }

}

template <bool directed>
typename Graph_adj_list<directed>::list Graph_adj_list<directed>::find_all_paths (int u, int v) const {
	if (u == v)
		return list();

	vec_vis visits(al.size(), false);
	list res{};
	std::vector<int> sub_res{};

	_find_all_paths(u, v, res, sub_res, visits);
	return res;
}

template <bool directed>
void Graph_adj_list<directed>::_find_all_paths (int u, int v, list& res, std::vector<int>& sub_res, vec_vis& visits) const {

	sub_res.push_back(u);

	if (u == v) {
		res.push_back(sub_res);
		sub_res.pop_back();
		return;
	}

	visits[u] = true;
	for (int val : al[u]) {
		if (!visits[val]) {
			_find_all_paths (val, v, res, sub_res, visits);
			visits[val] = false;
		}
	}

	sub_res.pop_back();
}

template <bool directed>
std::vector<int> Graph_adj_list<directed>::shortest_path (int u, int v) const {
    int al_size = al.size();

    vec_vis visits(al_size, false);
    std::queue<int> q;
    std::vector<int> parents(al_size, -1);
    std::vector<int> res;

    q.push(u);
    while (!q.empty()) {
        u = q.front(); q.pop();
        visits[u] = true;

        if (u == v) {
            while (u != -1) {
                res.push_back(u);
                u = parents[u];
            }
            std::reverse(res.begin(), res.end());
            return res;
        }

        for (int v : al[u]) {
            if (!visits[v]) {
                if (parents[v] == -1) parents[v] = u;
                q.push(v);
            }
        }
    }

    throw std::invalid_argument("There is no path\n");
}

template <bool directed>
std::vector<int> Graph_adj_list<directed>::curr_levels_vertexes (int u, int level) const {
	if (u >= al.size() || level < 0)
		throw std::out_of_range("Out of range");

	if (level == 0) return {u};

	std::vector<int> res{};
	vec_vis visits(al.size(), false);
	std::queue<int> q;
	int size;

	q.push(u);

	while (!q.empty()) {

		if (!level) {
			while (!q.empty()) {
				res.push_back(q.front());
				q.pop();
			}

			return res;
		}

		size = q.size();
		while (size--) {
			u = q.front(); q.pop();

			for (int v : al[u]) {
				if (!visits[v]) {
					q.push(v);
					visits[v] = true;
				}
			}

		}
		--level;
	}

	throw std::out_of_range("out of range");
}

template <bool directed>
bool Graph_adj_list<directed>::is_cycled () const {
    int size = al.size();
	vec_vis visits(size, false);
    vec_vis in_stack (size, false);
    for (int u = 0; u < size; ++u) {
	    if (_is_cycled (u, visits, in_stack, -1))
            return true;
    }

    return false;
}

template <bool directed>
bool Graph_adj_list<directed>::_is_cycled (int u, vec_vis& visits, vec_vis& in_stack, int parent) const {
	visits[u] = true;
    in_stack[u] = true;
	for (int v : al[u]) {
		if (v != parent) {
			if (in_stack[v] == true) return true;
			if (_is_cycled(v, visits, in_stack, u)) return true;
		}
	}
    in_stack[u] = false;

	return false;
}

template <bool directed>
std::vector<int> Graph_adj_list<directed>::top_sort () const { // Kahn's algorithm
    int size = al.size();
    int u;
    std::vector<int> res;
    std::vector<int> in_degree(size, 0); // how many nodes coming in indexes node
    std::queue<int> q;

    for (u = 0; u < size; ++u) {
        for (int v : al[u]) {
            ++in_degree[v];
        }
    }

    for (u = 0; u < size; ++u) {
        if (in_degree[u] == 0) q.push(u);
    }

    while (!q.empty()) {
        u = q.front(); q.pop();
        res.push_back(u);

        for (int v : al[u]) {
            --in_degree[v];
            if (in_degree[v] == 0) q.push(v);
        }
    }

    if (res.size() != size) return {}; // cycle in graph

    return res;
}

template <bool directed>
int Graph_adj_list<directed>::components_number () const {
	int size = al.size();
	int components = 0;

	vec_vis visits(size, false);
	for (int u = 0; u < size; ++u) {
		if (!visits[u]) {
			_dfs_helper(u, visits);
			++components;
		}
	}
	
	return components;
}

template <bool directed>
void Graph_adj_list<directed>::_dfs_helper (int u, vec_vis& visits) const {
	visits[u] = true;
	for (int v : al[u]) {
		if (!visits[v]) _dfs_helper(v, visits);
	}
}

template <bool directed>
void Graph_adj_list<directed>::print () const {
    int size = al.size();
    int row_size;

    for (int i = 0; i < size; ++i) {
        row_size = al[i].size();
        std::cout << i << " -> ";
        for (int j = 0; j < row_size; ++j) {
            std::cout << al[i][j];
            if ((j + 1) != row_size) std::cout << ", ";
        }
        std::cout << '\n';
    }
}

template <bool directed>
bool Graph_adj_list<directed>::_not_same_vals (int i, int val) const {
    for (int u : al[i]) {
        if (u == val)
            return false;
    }
    return true;
}
