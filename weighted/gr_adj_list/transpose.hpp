#ifndef TRANSPOSE
#define TRANSPOSE

template <bool directed>
void Graph_al<directed>::transpose () {
    if (!directed) {
        throw std::invalid_argument("Can't transpose the undirected graph");
    }

    int size = al.size();

    list new_al(size, std::vector<pair_i>());

    for (int i = 0; i < size; ++i) {
        for (const auto& pair : al[i]) {
            new_al[pair.first].push_back({i, pair.second});
        }
    }

    al = new_al;
}

template <bool directed>
Graph_al<directed> Graph_al<directed>::clone_transpose () const {
    if (!directed) {
        throw std::invalid_argument("Can't transpose the undirected graph");
    }

    int size = al.size();

    list new_al(size, std::vector<pair_i>());

    for (int i = 0; i < size; ++i) {
        for (const auto& pair : al[i]) {
            new_al[pair.first].push_back({i, pair.second});
        }
    }

    return Graph_al<directed>(new_al);
}

#endif // TRANSPOSE