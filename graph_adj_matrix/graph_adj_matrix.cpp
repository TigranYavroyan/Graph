#include "graph_adj_matrix.hpp"

Graph_adj_matrix::Graph_adj_matrix (int n, const matrix& edges) : am(n + 1, std::vector<int>(n + 1, 0)) {
    for (auto& edge : edges) {
        add_edge(edge[0], edge[1]);
    }
}

Graph_adj_matrix::Graph_adj_matrix(int n, int (*matrix)[2], int size) : am(n + 1, std::vector<int>(n + 1, 0)) {
    for (int i = 0; i < size; ++i) {
        add_edge(matrix[i][0], matrix[i][1]);
    }
}

void Graph_adj_matrix::add_edge (int u, int v) {
    if (u >= am.size() || v >= am.size())
        throw std::out_of_range("Out of range");
    
    am[u][v] = 1;
    am[v][u] = 1; // if undirected
}

void Graph_adj_matrix::add_vertex () {
    int dest_size = am.size() + 1;

    for (std::vector<int>& row : am) {
        row.resize(dest_size, 0);
    }

    am.resize(dest_size, std::vector<int>(dest_size, 0));
}

template <typename func>
void Graph_adj_matrix::dfs (func f, int u) {
    if (u >= am.size())
        throw std::out_of_range("Out of range");
    
    vec_vis visits(am.size(), false);
    _dfs(u, visits, f);
}

template <typename func>
void Graph_adj_matrix::_dfs (int u, vec_vis& visits, func f) {
    f(u);
    visits[u] = true;

    for (int v = 0; v < am.size(); ++v) {
        if (!visits[v] && am[u][v] == 1)
            _dfs(v, visits, f);
    }

}

template <typename func>
void Graph_adj_matrix::bfs (func f, int u) {
    std::queue<int> q;
    int am_size = am.size();
    vec_vis visits(am_size, false);

    q.push(u);

    while (!q.empty()) {
        u = q.front(); q.pop();

        f(u);
        visits[u] = true;

        for (int v = 0; v < am_size; ++v) {
            if (!visits[v] && am[u][v] == 1) {
                q.push(v);
                visits[v] = true;
            }
        }
    }

    // while (!q.empty()) {
    //     int size = q.size();
    //     while (size--) {
    //         u = q.front(); q.pop();

    //         f(u);
    //         visits[u] = true;

    //         for (int v = 0; v < am_size; ++v) {
    //             if (!visits[v] && am[u][v] == 1) {
    //                 q.push(v);
    //                 visits[v] = true;
    //             }
    //         }
    //     }
    //     std::cout << '\n';
    // }
}

std::vector<int> Graph_adj_matrix::shortest_path (int u, int v) const {
    int am_size = am.size();

    std::queue<int> q;
    vec_vis visits(am_size, false);
    std::vector<int> parents(am_size, -1);
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

        for (int v = 0; v < am_size; ++v) {
            if (!visits[v] && am[u][v] == 1) {
                if (parents[v] == -1) parents[v] = u;
                q.push(v);
            }
        }
    }

    throw std::invalid_argument("There is no path\n");
}

void Graph_adj_matrix::print () const {
    int size = am.size();

    int maxRowIndexDigits = 2/*std::to_string(m_row - 1).length()*/;
    int maxColIndexDigits = std::to_string(size - 1).length();

    std::cout << "      ";
    for (int j = 0; j < size; ++j) {
        std::cout << std::setw(maxColIndexDigits + 1) << j;
    }
    std::cout << '\n' << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << std::setw(maxRowIndexDigits + 2) << i << " |";
        for (int j = 0; j < size; ++j) {
            std::cout << std::setw(maxColIndexDigits + 1) << am[i][j];
        }
        std::cout.put('\n');
    }
    std::cout << std::endl;
}
