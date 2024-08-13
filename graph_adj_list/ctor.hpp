#ifndef CTOR_HPP
#define CTOR_HPP

template <bool directed>
Graph_adj_list<directed>::Graph_adj_list (int n, const list& edges) : al(n + 1) {
    for (int i = 0; i < edges.size(); ++i) {
        add_edge(edges[i][0], edges[i][1]);
    }
}
template <bool directed>
Graph_adj_list<directed>::Graph_adj_list (int n, val_type (*edges)[2], int size) : al(n + 1) {
    for (int i = 0; i < size; ++i) {
        add_edge(edges[i][0], edges[i][1]);
    }
}

template <bool directed>
Graph_adj_list<directed>::Graph_adj_list (const list& _al) : al{_al} {}

template <bool directed>
Graph_adj_list<directed>::Graph_adj_list (const Graph_adj_list<directed>& other) : al{other.al} {}

template <bool directed>
Graph_adj_list<directed>::Graph_adj_list (Graph_adj_list<directed>&& other) : al{other.al} {
	other.al.clear();
}

#endif // CTOR_HPP