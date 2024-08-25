#ifndef BFS_HPP
#define BFS_HPP

template <bool directed>
template <typename func>
void Graph_al<directed>::bfs (func f, int u) {
	if (_out_of_ranges(u))
		throw std::out_of_range("There is no vertexes (src or dst)");

    std::queue<int> q;
    vec_vis visits(al.size(), false);

    q.push(u);
    visits[u] = true;
    while (!q.empty()) {
        u = q.front(); q.pop();

        f(u);

        for (const auto& pair : al[u]) {
            if (!visits[pair.first]) {
                q.push(pair.first);
                visits[pair.first] = true;
            }
        }
        
    }
}

#endif // BFS_HPP