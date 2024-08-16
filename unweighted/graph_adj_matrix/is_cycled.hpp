#ifndef IS_CYCLED_HPP
#define IS_CYCLED_HPP

template <bool directed>
bool Graph_adj_matrix<directed>::is_cycled () const {
    int size = am.size();
	vec_vis visits(size, false);
	vec_vis in_stack(size, false);

    for (int u = 0; u < size; ++u) {
        if (_is_cycled(u, visits, in_stack, -1))
            return true;
    }

    return false;
}

template <bool directed>
bool Graph_adj_matrix<directed>::_is_cycled (int u, vec_vis& visits, vec_vis& in_stack, int parent) const {
	visits[u] = true;
    in_stack[u] = true;
	for (int i = 0; i < am.size(); ++i) {
		if (am[u][i] == 1 && i != parent) {
			if (in_stack[i] == true) return true;
			if (_is_cycled(i, visits, in_stack, u)) return true;
		}
	}
    in_stack[u] = false;

	return false;
}

#endif // IS_CYCLED_HPP