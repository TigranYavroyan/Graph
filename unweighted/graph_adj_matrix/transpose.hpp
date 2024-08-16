#ifndef TRANSPOSE_HPP
#define TRANSPOSE_HPP

template <bool directed>
void Graph_adj_matrix<directed>::transpose () {
	if (!directed) {
		std::cout << "Can't transpose the undirected graph\n";
		return;
	}

	int size = am.size();

	for (int i = 0; i < size; ++i) {
		for (int j = i + 1; j < size; ++j) {
			std::swap(am[i][j], am[j][i]);
		}
	}
}

template <bool directed>
Graph_adj_matrix<directed> Graph_adj_matrix<directed>::clone_transpose () const {
	if (!directed) {
		throw std::invalid_argument("Can't transpose the undirected graph");
	}

	int size = am.size();
	matrix new_am = am;

	for (int i = 0; i < size; ++i) {
		for (int j = i + 1; j < size; ++j) {
			std::swap(new_am[i][j], new_am[j][i]);
		}
	}

	return Graph_adj_matrix(new_am);
}

#endif // TRANSPOSE_HPP