#ifndef TOP_SORT_HPP
#define TOP_SORT_HPP

template <bool directed>
std::vector<int> Graph_al<directed>::top_sort () const {
    int size = al.size();
    std::queue<int> q;
    std::vector<int> in_degree(size, 0);
    std::vector<int> res;
    int u;

    for (int i = 0; i < size; ++i) {
        for (const auto& pair : al[i]) {
            ++in_degree[pair.first];
        }
    }

    for (int i = 0; i < size; ++i) {
        if (in_degree[i] == 0) q.push(i);
    }

    while (!q.empty()) {
        u = q.front(); q.pop();
        res.push_back(u);

        for (const auto& pair : al[u]) {
            --in_degree[pair.first];
            if (in_degree[pair.first] == 0)
                q.push(pair.first);
        }
    }

    if (res.size() != size)
        return {};

    return res;
}

#endif // TOP_SORT_HPP