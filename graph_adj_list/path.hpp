#ifndef PATH_HPP
#define PATH_HPP

template <bool directed>
typename Graph_adj_list<directed>::list Graph_adj_list<directed>::find_all_paths (val_type u, val_type v) const {
	if (u == v)
		return list();

	vec_vis visits(al.size(), false);
	list res{};
	std::vector<val_type> sub_res{};

	_find_all_paths(u, v, res, sub_res, visits);
	return res;
}

template <bool directed>
void Graph_adj_list<directed>::_find_all_paths (val_type u, val_type v, list& res, std::vector<val_type>& sub_res, vec_vis& visits) const {

	sub_res.push_back(u);

	if (u == v) {
		res.push_back(sub_res);
		sub_res.pop_back();
		return;
	}

	visits[u] = true;
	for (val_type val : al[u]) {
		if (!visits[val]) {
			_find_all_paths (val, v, res, sub_res, visits);
			visits[val] = false;
		}
	}

	sub_res.pop_back();
}

template <bool directed>
std::vector<typename Graph_adj_list<directed>::val_type> Graph_adj_list<directed>::shortest_path (val_type u, val_type v) const {
    int al_size = al.size();

    vec_vis visits(al_size, false);
    std::queue<val_type> q;
    std::vector<val_type> parents(al_size, -1);
    std::vector<val_type> res;

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

        for (val_type v : al[u]) {
            if (!visits[v]) {
                if (parents[v] == -1) parents[v] = u;
                q.push(v);
            }
        }
    }

    throw std::invalid_argument("There is no path\n");
}

#endif // PATH_HPP