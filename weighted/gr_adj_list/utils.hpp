#ifndef UTILS_HPP
#define UTILS_HPP

template <bool directed>
void Graph_al<directed>::print () const {
	int al_size = al.size();
	int row_size;

	for (int i = 0; i < al_size; ++i) {
		std::cout << i << " -> ";
		row_size = al[i].size();
		for (int j = 0; j < row_size; ++j) {
			std::cout << "{" << al[i][j].first << ", " << al[i][j].second << "}";
			if (j != (row_size - 1))
				std::cout << ", ";
		}
		std::cout << '\n';
	}
}

template <bool directed>
bool Graph_al<directed>::_not_same_vals (int u, int v) const {
	for (const auto& pair : al[u]) {
		if (pair.first == v) return false;
	}
	return true;
}

template <bool directed>
template <typename T>
void Graph_al<directed>::print_vec (const std::vector<T>& vec) const {
	for (auto val : vec) {
		std::cout << val << ' ';
	}
	std::cout << '\n';
}

template <bool directed>
std::vector<int> Graph_al<directed>::_get_path (int u, int v, const std::vector<int>& paths) const {
	std::vector<int> path;
	while (v != u) {
		if (paths[v] == -1)
			return {};
		path.push_back(v);
		v = paths[v];
	}
	path.push_back(u);
	reverse(path.begin(), path.end());

	return path;
}


#endif // UTILS_HPP