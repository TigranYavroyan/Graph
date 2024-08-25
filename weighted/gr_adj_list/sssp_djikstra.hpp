#ifndef SSSP_DJIKSTRA
#define SSSP_DJIKSTRA

namespace {
	struct pair_cmp {
		bool operator() (const std::pair<int, int>& a, const std::pair<int, int>& b) {
			return a.second > b.second;
		}
	};
}

// djikstra can't track negative cycles
// so can't work with negative weights
template <bool directed>
std::vector<int> Graph_al<directed>::sssp_djikstra (int src, int dst) const {
	if (_out_of_ranges(src) || _out_of_ranges(dst))
		throw std::out_of_range("There is no vertexes (src or dst)");

	int size = al.size();

	for (int u = 0; u < size; ++u) { // check for negative weights
		for (auto [v, c] : al[u]) {
			if (c < 0) return {};
		}
	}

	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, pair_cmp> q;
	std::vector<double> dist(size, std::numeric_limits<double>::infinity());
	std::vector<int> paths(size, -1);

	dist[src] = 0;
	q.push({src, 0});

	while (!q.empty()) {
		auto [u, cost] = q.top(); q.pop();
		
		// if I found more efficient way to achieve u, I don't need to track more expensive way
		if (dist[u] < cost) continue; // optimization

		for (auto [v, c] : al[u]) {
			if (_relaxation(dist, u, v, c, paths))
				q.push({v, dist[v]});
		}
	}

	print_vec(paths);
	return _get_path(src, dst, paths);
}

#endif // SSSP_DJIKSTRA