#ifndef EXTRA_CASES_HPP
#define EXTRA_CASES_HPP

template <bool directed>
std::vector<typename Graph_adj_list<directed>::val_type> Graph_adj_list<directed>::curr_levels_vertexes (val_type u, int level) const {
	if (u >= al.size() || level < 0)
		throw std::out_of_range("Out of range");

	if (level == 0) return {u};

	std::vector<val_type> res{};
	vec_vis visits(al.size(), false);
	std::queue<val_type> q;
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

			for (val_type v : al[u]) {
				if (!visits[v]) {
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
int Graph_adj_list<directed>::components_number () const {
	int size = al.size();
	int components = 0;

	vec_vis visits(size, false);
	for (val_type u = 0; u < size; ++u) {
		if (!visits[u]) {
			_dfs_helper(u, visits);
			++components;
		}
	}

	return components;
}

#endif // EXTRA_CASES_HPP