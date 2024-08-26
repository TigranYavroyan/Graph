#ifndef MST_PRIM_HPP
#define MST_PRIM_HPP

namespace {
    struct for_mst_pq {
        bool operator() (const std::pair<int, std::pair<int, int>>& a, std::pair<int, std::pair<int, int>>& b) {
            return a.second.second > b.second.second;
        }
    };
}

// designed for finding Minimum spanning Tree in undirected graph
template <bool directed>
typename Graph_al<directed>::vec_2d Graph_al<directed>::mst_prim (int src) const { // maybe can write better
    if (directed) return {};

    if (_out_of_ranges(src))
        throw std::out_of_range("The src is out of range");

    int size = al.size();
    vec_vis visits(size, false);
    std::priority_queue<std::pair<int, pair_i>, std::vector<std::pair<int, pair_i>>, for_mst_pq> q;
    vec_2d res(size, std::vector<int>(0, 0));
    int MST = 0;

    q.push({-1, {src, 0}});
    while (!q.empty()) {
        auto [p, pair] = q.top(); q.pop();
        auto [u, w] = pair;

        if (visits[u] == true) continue;

        visits[u] = true;
        MST += w;

        if (p != -1)
            res[p].push_back(u);

        for (auto [v, c] : al[u]) {
            if (!visits[v]) {
                q.push({u, {v, c}});
            }
        }
    }

    std::cout << "MST: " << MST << std::endl;

    return res;
}

#endif // MST_PRIM_HPP