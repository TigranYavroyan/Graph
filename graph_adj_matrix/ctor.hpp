#ifndef CTOR_HPP
#define CTOR_HPP

template <bool directed>
Graph_adj_matrix<directed>::Graph_adj_matrix (int n, const matrix& edges) : am(n + 1, std::vector<int>(n + 1, 0)) {
    for (auto& edge : edges) {
        add_edge(edge[0], edge[1]);
    }
}

template <bool directed>
Graph_adj_matrix<directed>::Graph_adj_matrix(int n, int (*matrix)[2], int size) : am(n + 1, std::vector<int>(n + 1, 0)) {
    for (int i = 0; i < size; ++i) {
        add_edge(matrix[i][0], matrix[i][1]);
    }
}

template <bool directed>
Graph_adj_matrix<directed>::Graph_adj_matrix (const matrix& _am) : am{_am} {}

template <bool directed>
Graph_adj_matrix<directed>::Graph_adj_matrix (const Graph_adj_matrix<directed>& other) : am{other.am} {}

template <bool directed>
Graph_adj_matrix<directed>::Graph_adj_matrix (Graph_adj_matrix<directed>&& other) : am{other.am} {
	other.am.clear();
}

#endif // CTOR_HPP