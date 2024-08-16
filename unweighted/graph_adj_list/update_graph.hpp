#ifndef UPDATE_GRAPH_HPP
#define UPDATE_GRAPH_HPP

template <bool directed>
void Graph_adj_list<directed>::add_vertex () {
    al.resize(al.size() + 1);
}

template <bool directed>
void Graph_adj_list<directed>::add_edge (val_type u, val_type v) {
    if (u >= al.size() || v >= al.size())
        throw std::out_of_range("Out of range");

    if (_not_same_vals(u, v))
        al[u].push_back(v);

    if (!directed && _not_same_vals(v, u))
        al[v].push_back(u); // if undirected
}

#endif // UPDATE_GRAPH_HPP