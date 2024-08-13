#ifndef IS_CYCLED_HPP
#define IS_CYCLED_HPP

template <bool directed>
bool Graph_adj_list<directed>::is_cycled () const {
    int size = al.size();
	vec_vis visits(size, false);
    vec_vis in_stack (size, false);
    for (val_type u = 0; u < size; ++u) {
	    if (_is_cycled (u, visits, in_stack, -1))
            return true;
    }

    return false;
}

template <bool directed>
bool Graph_adj_list<directed>::_is_cycled (val_type u, vec_vis& visits, vec_vis& in_stack, val_type parent) const {
	visits[u] = true;
    in_stack[u] = true;
	for (val_type v : al[u]) {
		if (v != parent) {
			if (in_stack[v] == true) return true;
			if (_is_cycled(v, visits, in_stack, u)) return true;
		}
	}
    in_stack[u] = false;

	return false;
}

#endif // IS_CYCLED_HPP