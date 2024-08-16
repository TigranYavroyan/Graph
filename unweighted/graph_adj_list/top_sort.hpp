#ifndef TOP_SORT_HPP
#define TOP_SORT_HPP

template <bool directed>
std::vector<typename Graph_adj_list<directed>::val_type> Graph_adj_list<directed>::top_sort () const { // Kahn's algorithm
    int size = al.size();
    val_type u;
    std::vector<val_type> res;
    std::vector<val_type> in_degree(size, 0); // how many nodes coming in indexes node
    std::queue<val_type> q;

    for (u = 0; u < size; ++u) {
        for (val_type v : al[u]) {
            ++in_degree[v];
        }
    }

    for (u = 0; u < size; ++u) {
        if (in_degree[u] == 0) q.push(u);
    }

    while (!q.empty()) {
        u = q.front(); q.pop();
        res.push_back(u);

        for (val_type v : al[u]) {
            --in_degree[v];
            if (in_degree[v] == 0) q.push(v);
        }
    }

    if (res.size() != size) return {}; // cycle in graph

    return res;
}

#endif // TOP_SORT_HPP