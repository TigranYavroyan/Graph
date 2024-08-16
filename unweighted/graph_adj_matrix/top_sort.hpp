#ifndef TOP_SORT_HPP
#define TOP_SORT_HPP

template <bool directed>
std::vector<int> Graph_adj_matrix<directed>::top_sort () const { // Kahn's algorithm
    int size = am.size();
    int u;
    std::vector<int> res;
    std::vector<int> in_degree(size, 0);
    std::queue<int> q;

    for (u = 0; u < size; ++u) {
        for (int v = 0; v < size; ++v) {
            if (am[u][v] == 1) ++in_degree[v];
        }
    }

    for (u = 0; u < size; ++u) {
        if (in_degree[u] == 0) q.push(u);
    }

    while (!q.empty()) {
        u = q.front(); q.pop();
        res.push_back(u);

        for (int v = 0; v < size; ++v) {
            if (am[u][v] == 1) {
                --in_degree[v];
                if (in_degree[v] == 0) q.push(v);
            }
        }
    }

    if (res.size() != size) return {};

    return res;
}

#endif // TOP_SORT_HPP