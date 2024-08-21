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
template <bool directed>
std::vector<int> Graph_al<directed>::sssp_djikstra (int src, int dst) const {
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, pair_cmp> q;

	int size = al.size();
	std::vector<double> dist(size, std::numeric_limits<double>::infinity());
	std::vector<int> paths(size, -1);

	dist[src] = 0;
	q.push({src, 0});

	while (!q.empty()) {
		auto [u, cost] = q.top(); q.pop();
		// if I found more efficient way to achieve u, I don't need to track more expensive way
		if (dist[u] < cost) continue; // optimization

		for (auto [v, c] : al[u]) {
			if (dist[v] > dist[u] + c) {
				dist[v] = dist[u] + c;
				q.push({v, dist[v]});
				paths[v] = u;
			}
		}
	}

	return _get_path(src, dst, paths);
}

#endif // SSSP_DJIKSTRA