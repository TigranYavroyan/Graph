#ifndef UPDATE_GRAPH_HPP
#define UPDATE_GRAPH_HPP

template <bool directed>
void Graph_adj_matrix<directed>::add_edge (int u, int v) {
    if (u >= am.size() || v >= am.size())
        throw std::out_of_range("Out of range");

    am[u][v] = 1;
    if (!directed)
        am[v][u] = 1;
}

template <bool directed>
void Graph_adj_matrix<directed>::add_vertex () {
    int dest_size = am.size() + 1;

    for (std::vector<int>& row : am) {
        row.resize(dest_size, 0);
    }

    am.resize(dest_size, std::vector<int>(dest_size, 0));
}

#endif // UPDATE_GRAPH_HPP