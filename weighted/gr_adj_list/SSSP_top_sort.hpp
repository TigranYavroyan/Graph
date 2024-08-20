#ifndef SSSP_TOP_SORT
#define SSSP_TOP_SORT

template <bool directed>
std::vector<double> Graph_al<directed>::sssp_top_sort (int src) const {// now it is without top sort , just dfs with greedy logics
	int size = al.size();

	std::vector<double> dist(size, std::numeric_limits<double>::infinity());
	dist[src] = 0;
	_dfs_sssp(src, dist);

	return dist;
}

template <bool directed>
void Graph_al<directed>::_dfs_sssp (int u, std::vector<double>& dist) const {
	for (const auto& pair : al[u]) {
		if (dist[pair.first] > dist[u] + pair.second)
			dist[pair.first] = dist[u] + pair.second;
		_dfs_sssp(pair.first, dist);
	}
}

#endif // SSSP_TOP_SORT