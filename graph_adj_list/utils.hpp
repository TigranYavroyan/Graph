#ifndef UTILS_HPP
#define UTILS_HPP

template <bool directed>
void Graph_adj_list<directed>::print () const {
    int size = al.size();
    int row_size;

    for (int i = 0; i < size; ++i) {
        row_size = al[i].size();
        std::cout << i << " -> ";
        for (int j = 0; j < row_size; ++j) {
            std::cout << al[i][j];
            if ((j + 1) != row_size) std::cout << ", ";
        }
        std::cout << '\n';
    }
}

template <bool directed>
bool Graph_adj_list<directed>::_not_same_vals (int i, val_type val) const {
    for (int u : al[i]) {
        if (u == val)
            return false;
    }
    return true;
}

template <bool directed>
void Graph_adj_list<directed>::print_vec (const std::vector<val_type>& vec) const {
	for (const auto& val : vec) {
		std::cout << val << ' ';
	}
	std::cout << '\n';
}

#endif // UTILS_HPP