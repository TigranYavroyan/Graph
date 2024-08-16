#ifndef EXTRA_CASES_HPP
#define EXTRA_CASES_HPP

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

#endif // EXTRA_CASES_HPP