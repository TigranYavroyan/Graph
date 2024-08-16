#ifndef DFS_HPP
#define DFS_HPP

template <bool directed>
template <typename func>
void Graph_adj_list<directed>::dfs (func f, val_type u) {
    if (u >= al.size())
        throw std::out_of_range("Out of range");

    vec_vis visits(al.size(), false);
    _dfs(u, visits, f);
}

template <bool directed>
template <typename func>
void Graph_adj_list<directed>::_dfs (val_type u, vec_vis& visits, func f) {
    f(u);
    visits[u] = true;
    for (auto& v : al[u]) {
        if (!visits[v]) _dfs(v, visits, f);
    }
}

template <bool directed>
void Graph_adj_list<directed>::_dfs_helper (val_type u, vec_vis& visits) const {
	visits[u] = true;
	for (val_type v : al[u]) {
		if (!visits[v]) _dfs_helper(v, visits);
	}
}

#endif // DFS_HPP