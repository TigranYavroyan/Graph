#ifndef TRANSPOSE_HPP
#define TRANSPOSE_HPP

template <bool directed>
Graph_adj_list<directed> Graph_adj_list<directed>::clone_transpose () const {
	if (!directed) {
		throw std::invalid_argument("can't transpose the undirected graph");
	}

	int size = al.size();
	list new_al(size, std::vector<val_type>(0, 0));

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < al[i].size(); ++j) {
			new_al[al[i][j]].push_back(i);
		}
	}

	return Graph_adj_list(new_al);
}

template <bool directed>
void Graph_adj_list<directed>::transpose () {
	if (!directed) {
		throw std::invalid_argument("can't transpose the undirected graph");
	}

	int size = al.size();
	list new_al(size, std::vector<val_type>(0, 0));

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < al[i].size(); ++j) {
			new_al[al[i][j]].push_back(i);
		}
	}

	al = new_al;
}

#endif // TRANSPOSE_HPP