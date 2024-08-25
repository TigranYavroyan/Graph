#ifndef SSSP_TOP_SORT
#define SSSP_TOP_SORT


// this method can't track cycles , bcz of top_sort's logic
template <bool directed>
std::vector<int> Graph_al<directed>::sssp_top_sort (int src, int dst) const { // can work only with DAG
	if (_out_of_ranges(src) || _out_of_ranges(dst))
		throw std::out_of_range("There is no vertexes (src or dst)");

	int size = al.size();

	std::vector<double> dist(size, std::numeric_limits<double>::infinity());
	std::vector<int> res = top_sort();
	if (res.empty()) return res;

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
			_relaxation(dist, top, v, c, paths);
		}
	}
}

#endif // SSSP_TOP_SORT