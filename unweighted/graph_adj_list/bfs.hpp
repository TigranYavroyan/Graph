#ifndef BFS_HPP
#define BFS_HPP

template <bool directed>
template <typename func>
void Graph_adj_list<directed>::bfs (func f, val_type u) {
    if (u >= al.size())
        throw std::out_of_range("Out of range");

    vec_vis visits(al.size(), false);
    std::queue<val_type> q;
    val_type val;

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

            for (val_type v : al[val]) {
                if (!visits[v]) {
                    q.push(v);
                    visits[v] = true;
                }
            }
        }
        std::cout << '\n';
    }
}

#endif // BFS_HPP