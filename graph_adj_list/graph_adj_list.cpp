#include "graph_adj_list.hpp"

Graph_adj_list::Graph_adj_list (int n, const list& edges) : al(n + 1) {
    for (int i = 0; i < edges.size(); ++i) {
        add_edge(edges[i][0], edges[i][1]);
    }
}
Graph_adj_list::Graph_adj_list (int n, int (*edges)[2], int size) : al(n + 1) {
    for (int i = 0; i < size; ++i) {
        add_edge(edges[i][0], edges[i][1]);
    }
}

void Graph_adj_list::print () const {
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

void Graph_adj_list::add_edge (int u, int v) {
    if (u >= al.size() || v >= al.size())
        throw std::out_of_range("Out of range");

    if (_not_same_vals(u, v))
        al[u].push_back(v);

    if (_not_same_vals(v, u))
        al[v].push_back(u); // if undirected
}

void Graph_adj_list::add_vertex () {
    al.resize(al.size() + 1);
}

template <typename func>
void Graph_adj_list::dfs (func f, int u) {
    if (u >= al.size())
        throw std::out_of_range("Out of range");

    vec_vis visits(al.size(), false);
    _dfs(u, visits, f);
}

template <typename func>
void Graph_adj_list::_dfs (int u, vec_vis& visits, func f) {
    f(u);
    visits[u] = true;
    for (auto& v : al[u]) {
        if (!visits[v]) _dfs(v, visits, f);
    }
}

template <typename func>
void Graph_adj_list::bfs (func f, int u) {
    if (u >= al.size())
        throw std::out_of_range("Out of range");

    vec_vis visits(al.size(), false);
    std::queue<int> q;
    int val;

    q.push(u);

    // while (!q.empty()) {
    //     val = q.front(); q.pop();

    //     f(val);
    //     visits[val] = true;

    //     for (int v : al[val]) {
    //         if (!visits[v]) {
    //             q.push(v);
    //             visits[v] = true;
    //         }
    //     }
    // }

    while (!q.empty()) {
        int size = q.size();
        while (size--) {
            val = q.front(); q.pop();

            f(val);
            visits[val] = true;
                
            for (int v : al[val]) {
                if (!visits[v]) {
                    q.push(v);
                    visits[v] = true;
                }
            }
        }
        std::cout << '\n';
    }

}

std::vector<int> Graph_adj_list::shortest_path (int u, int v) const {
    int al_size = al.size();

    vec_vis visits(al_size, false);
    std::queue<int> q;
    std::vector<int> parents(al_size, -1);
    std::vector<int> res;

    q.push(u);
    while (!q.empty()) {
        u = q.front(); q.pop();
        visits[u] = true;

        if (u == v) {
            while (u != -1) {
                res.push_back(u);
                u = parents[u];
            }
            std::reverse(res.begin(), res.end());
            return res;
        }

        for (int v : al[u]) {
            if (!visits[v]) {
                if (parents[v] == -1) parents[v] = u;
                q.push(v);
            }
        }
    }

    throw std::invalid_argument("There is no path\n");
}

bool Graph_adj_list::_not_same_vals (int i, int val) const {
    for (int u : al[i]) {
        if (u == val)
            return false;
    }
    return true;
}