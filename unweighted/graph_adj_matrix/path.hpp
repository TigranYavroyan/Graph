#ifndef PATH_HPP
#define PATH_HPP

template <bool directed>
typename Graph_adj_matrix<directed>::matrix Graph_adj_matrix<directed>::find_all_paths (int u, int v) const {
	if (u == v)
		return matrix();

	vec_vis visits(am.size(), false);
	matrix res{};
	std::vector<int> sub_res{};

	_find_all_paths(u, v, res, sub_res, visits);
	return res;
}

template <bool directed>
void Graph_adj_matrix<directed>::_find_all_paths (int u, int v, matrix& res, std::vector<int>& sub_res, vec_vis& visits) const {
	sub_res.push_back(u);

	if (u == v) {
		res.push_back(sub_res);
		sub_res.pop_back();
		return;
	}

	visits[u] = true;
	for (int i = 0; i < am.size(); ++i) {
		if (!visits[i] && am[u][i] == 1) {
			_find_all_paths(i, v, res, sub_res, visits);
			visits[i] = false;
		}
	}

	sub_res.pop_back();
}

template <bool directed>
std::vector<int> Graph_adj_matrix<directed>::shortest_path (int u, int v) const {
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

#endif // PATH_HPP