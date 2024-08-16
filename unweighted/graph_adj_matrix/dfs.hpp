#ifndef DFS_HPP
#define DFS_HPP

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
void Graph_adj_matrix<directed>::_dfs_helper (int u, vec_vis& visits) const {
	visits[u] = true;
	for (int v = 0; v < am.size(); ++v) {
		if (!visits[v] && am[u][v] == 1) _dfs_helper(v, visits);
	}
}

#endif // DFS_HPP