#include "graph_adj_matrix.hpp"


template <bool directed>
Graph_adj_matrix<directed>::Graph_adj_matrix (int n, const matrix& edges) : am(n + 1, std::vector<int>(n + 1, 0)) {
    for (auto& edge : edges) {
        add_edge(edge[0], edge[1]);
    }
}

template <bool directed>
Graph_adj_matrix<directed>::Graph_adj_matrix(int n, int (*matrix)[2], int size) : am(n + 1, std::vector<int>(n + 1, 0)) {
    for (int i = 0; i < size; ++i) {
        add_edge(matrix[i][0], matrix[i][1]);
    }
}

template <bool directed>
void Graph_adj_matrix<directed>::add_edge (int u, int v) {
    if (u >= am.size() || v >= am.size())
        throw std::out_of_range("Out of range");

    am[u][v] = 1;
    if (!directed)
        am[v][u] = 1;
}

template <bool directed>
void Graph_adj_matrix<directed>::add_vertex () {
    int dest_size = am.size() + 1;

    for (std::vector<int>& row : am) {
        row.resize(dest_size, 0);
    }

    am.resize(dest_size, std::vector<int>(dest_size, 0));
}

template <bool directed>
template <typename func>
void Graph_adj_matrix<directed>::dfs (func f, int u) {
    if (u >= am.size())
        throw std::out_of_range("Out of range");

    vec_vis visits(am.size(), false);
    _dfs(u, visits, f);
}

template <bool directed>
template <typename func>
void Graph_adj_matrix<directed>::_dfs (int u, vec_vis& visits, func f) {
    f(u);
    visits[u] = true;

    for (int v = 0; v < am.size(); ++v) {
        if (!visits[v] && am[u][v] == 1)
            _dfs(v, visits, f);
    }

}

template <bool directed>
template <typename func>
void Graph_adj_matrix<directed>::bfs (func f, int u) {
    std::queue<int> q;
    int am_size = am.size();
    vec_vis visits(am_size, false);

    q.push(u);

    while (!q.empty()) {
        u = q.front(); q.pop();

        f(u);
        visits[u] = true;

        for (int v = 0; v < am_size; ++v) {
            if (!visits[v] && am[u][v] == 1) {
                q.push(v);
                visits[v] = true;
            }
        }
    }

    // while (!q.empty()) {
    //     int size = q.size();
    //     while (size--) {
    //         u = q.front(); q.pop();

    //         f(u);
    //         visits[u] = true;

    //         for (int v = 0; v < am_size; ++v) {
    //             if (!visits[v] && am[u][v] == 1) {
    //                 q.push(v);
    //                 visits[v] = true;
    //             }
    //         }
    //     }
    //     std::cout << '\n';
    // }
}

template <bool directed>
void Graph_adj_matrix<directed>::transpose () {
	if (!directed) {
		std::cout << "Can't transpose the undirected graph\n";
		return;
	}

	int size = am.size();

	for (int i = 0; i < size; ++i) {
		for (int j = i + 1; j < size; ++j) {
			std::swap(am[i][j], am[j][i]);
		}
	}
}

template <bool directed>
typename Graph_adj_matrix<directed>::matrix Graph_adj_matrix<directed>::find_all_paths (int u, int v) const {
	if (u == v)
		return matrix();

	vec_vis visits(am.size(), false);
	matrix res{};
	std::vector<int> sub_res{};

	_find_all_paths(u, v, res, sub_res, visits);
	return res;
}

template <bool directed>
void Graph_adj_matrix<directed>::_find_all_paths (int u, int v, matrix& res, std::vector<int>& sub_res, vec_vis& visits) const {
	sub_res.push_back(u);

	if (u == v) {
		res.push_back(sub_res);
		sub_res.pop_back();
		return;
	}

	visits[u] = true;
	for (int i = 0; i < am.size(); ++i) {
		if (!visits[i] && am[u][i] == 1) {
			_find_all_paths(i, v, res, sub_res, visits);
			visits[i] = false;
		}
	}

	sub_res.pop_back();
}

template <bool directed>
std::vector<int> Graph_adj_matrix<directed>::shortest_path (int u, int v) const {
    int am_size = am.size();

    std::queue<int> q;
    vec_vis visits(am_size, false);
    std::vector<int> parents(am_size, -1);
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

        for (int v = 0; v < am_size; ++v) {
            if (!visits[v] && am[u][v] == 1) {
                if (parents[v] == -1) parents[v] = u;
                q.push(v);
            }
        }
    }

    throw std::invalid_argument("There is no path\n");
}

template <bool directed>
std::vector<int> Graph_adj_matrix<directed>::curr_levels_vertexes (int u, int level) const {
	if (u >= am.size() || level < 0)
		throw std::out_of_range("Out of range");

	if (level == 0) return {u};

	std::vector<int> res{};
	vec_vis visits(am.size(), false);
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

			for (int v = 0; v < am.size(); ++v) {
				if (!visits[v] && am[u][v] == 1) {
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
bool Graph_adj_matrix<directed>::is_cycled () const {
    int size = am.size();
	vec_vis visits(size, false);
	vec_vis in_stack(size, false);

    for (int u = 0; u < size; ++u) {
        if (_is_cycled(u, visits, in_stack, -1))
            return true;
    }

    return false;
}

template <bool directed>
bool Graph_adj_matrix<directed>::_is_cycled (int u, vec_vis& visits, vec_vis& in_stack, int parent) const {
	visits[u] = true;
    in_stack[u] = true;
	for (int i = 0; i < am.size(); ++i) {
		if (am[u][i] == 1 && i != parent) {
			if (in_stack[i] == true) return true;
			if (_is_cycled(i, visits, in_stack, u)) return true;
		}
	}
    in_stack[u] = false;

	return false;
}

template <bool directed>
std::vector<int> Graph_adj_matrix<directed>::top_sort () const { // Kahn's algorithm
    int size = am.size();
    int u;
    std::vector<int> res;
    std::vector<int> in_degree(size, 0);
    std::queue<int> q;

    for (u = 0; u < size; ++u) {
        for (int v = 0; v < size; ++v) {
            if (am[u][v] == 1) ++in_degree[v];
        }
    }

    for (u = 0; u < size; ++u) {
        if (in_degree[u] == 0) q.push(u);
    }

    while (!q.empty()) {
        u = q.front(); q.pop();
        res.push_back(u);

        for (int v = 0; v < size; ++v) {
            if (am[u][v] == 1) {
                --in_degree[v];
                if (in_degree[v] == 0) q.push(v);
            }
        }
    }

    if (res.size() != size) return {};

    return res;
}

template <bool directed>
int Graph_adj_matrix<directed>::components_number () const {
	int size = am.size();
	vec_vis visits(size, false);
	int components = 0;

	for (int u = 0; u < size; ++u) {
		if (!visits[u]) {
			_dfs_helper(u, visits);
			++components;
		}
	}

	return components;
}

template <bool directed>
void Graph_adj_matrix<directed>::_dfs_helper (int u, vec_vis& visits) const {
	visits[u] = true;
	for (int v = 0; v < am.size(); ++v) {
		if (!visits[v] && am[u][v] == 1) _dfs_helper(v, visits);
	}
}

template <bool directed>
void Graph_adj_matrix<directed>::print () const {
    int size = am.size();

    int maxRowIndexDigits = 2/*std::to_string(m_row - 1).length()*/;
    int maxColIndexDigits = std::to_string(size - 1).length();

    std::cout << "      ";
    for (int j = 0; j < size; ++j) {
        std::cout << std::setw(maxColIndexDigits + 1) << j;
    }
    std::cout << '\n' << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << std::setw(maxRowIndexDigits + 2) << i << " |";
        for (int j = 0; j < size; ++j) {
            std::cout << std::setw(maxColIndexDigits + 1) << am[i][j];
        }
        std::cout.put('\n');
    }
    std::cout << std::endl;
}
