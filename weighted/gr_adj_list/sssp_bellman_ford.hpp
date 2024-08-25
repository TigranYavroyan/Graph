#ifndef SSSP_BELLMAN_FORD_HPP
#define SSSP_BELLMAN_FORD_HPP

// returns true and path , if it exist
// return false and affected vertexes, if there is no path
template <bool directed>
std::pair<std::vector<int>, bool> Graph_al<directed>::sssp_bellman_ford (int src, int dst) const {
	if (_out_of_ranges(src) || _out_of_ranges(dst))
		throw std::out_of_range("There is no vertexes (src or dst)");

    int size = al.size();
    std::vector<int> paths(size, -1);
    std::vector<int> affected_vertexes;
    std::vector<double> dist(size, std::numeric_limits<double>::infinity());
    std::vector<int> res;

    dist[src] = 0;

    for (int i = 0; i < size - 1; ++i) {
        for (int u = 0; u < size; ++u) {
            for (auto [v, c] : al[u]) {
                _relaxation(dist, u, v, c, paths);
            }
        }
    }

    for (int i = 0; i < size - 1; ++i) {
        for (int u = 0; u < size; ++u) {
            for (auto [v, c] : al[u]) {
                if (_relaxation(dist, u, v, c, paths)) {
                    dist[v] = -std::numeric_limits<double>::infinity();
                }
            }
        }
    }

    for (int i = 0; i < size; ++i) {
        if (dist[i] == -std::numeric_limits<double>::infinity())
            affected_vertexes.push_back(i);
    }

    res = _get_path(src, dst, paths);

    if (!res.empty()) return {res, true};
    else return {affected_vertexes, false};

}

#endif // SSSP_BELLMAN_FORD_HPP