#ifndef DFS_HPP
#define DFS_HPP

template <bool directed>
template <typename func>
void Graph_al<directed>::dfs (func f) {
	int size = al.size();
	vec_vis visits(size, false);

	for (int u = 0; u < size; ++u) {
		if (!visits[u])
			_dfs(u, visits, f);
	}
}

template <bool directed>
template <typename func>
void Graph_al<directed>::_dfs (int u, vec_vis& visits, func f) {
	visits[u] = true;
	f(u);

	for (const auto& pair : al[u]) {
		if (!visits[pair.first])
			_dfs(pair.first, visits, f);
	}
}

template <bool directed>
void Graph_al<directed>::_dfs_helper (int u, vec_vis& visits) {
	visits[u] = true;

	for (const auto& pair : al[u]) {
		if (!visits[pair.first])
			_dfs_helper(pair.first, visits);
	}
}

#endif // DFS_HPP