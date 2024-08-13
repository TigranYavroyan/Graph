#ifndef BFS_HPP
#define BFS_HPP

template <bool directed>
template <typename func>
void Graph_adj_matrix<directed>::bfs (func f, int u) {
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

#endif // BFS_HPP