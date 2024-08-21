#ifndef SSSP_TOP_SORT
#define SSSP_TOP_SORT

template <bool directed>
std::vector<int> Graph_al<directed>::sssp_top_sort (int src, int dst) const { // can work only with DAG
	int size = al.size();

	std::vector<double> dist(size, std::numeric_limits<double>::infinity());
	std::vector<int> res = top_sort();
	std::vector<int> paths(size, -1);

	reverse(res.begin(), res.end());
	std::stack<int, std::vector<int>> st(res);

	dist[st.top()] = 0;
	_dfs_sssp(dist, st, paths);

	return _get_path(src, dst, paths);
}

template <bool directed>
void Graph_al<directed>::_dfs_sssp (std::vector<double>& dist, std::stack<int, std::vector<int>>& st, std::vector<int>& paths) const {
	while (!st.empty()) {
		int top = st.top(); st.pop();

		for (auto [v, c] : al[top]) {
			if (dist[v] > dist[top] + c) { // relaxation
				dist[v] = dist[top] + c;
				paths[v] = top;
			}
		}
	}
}

template <bool directed>
std::vector<int> Graph_al<directed>::_get_path (int u, int v, const std::vector<int>& paths) const {
	std::vector<int> path;
	while (v != u) {
		path.push_back(v);
		v = paths[v];
	}
	path.push_back(u);
	reverse(path.begin(), path.end());

	return path;
}

#endif // SSSP_TOP_SORT