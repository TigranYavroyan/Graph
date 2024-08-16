#ifndef FIND_SCCS_HPP
#define FIND_SCCS_HPP

template <bool directed>
typename Graph_adj_matrix<directed>::matrix Graph_adj_matrix<directed>::find_sccs_kosarajou () const {
	int size = am.size();
	std::stack<int> st;
	vec_vis visits(size, false);

	for (int u = 0; u < size; ++u) {
		if (!visits[u])
			_fill_in_order(u, visits, st);
	}

	fill(visits.begin(), visits.end(), false);

	Graph_adj_matrix<directed> other = this->clone_transpose();
	matrix sccs;
	std::vector<int> component;

	while (!st.empty()) {
		int u = st.top();
		st.pop();

		if (!visits[u]) {
			other._find_scc(u, visits, component);
			sccs.push_back(std::move(component));
		}
	}

	return sccs;
}

template <bool directed>
void Graph_adj_matrix<directed>::_fill_in_order (int u, vec_vis& visits, std::stack<int>& st) const {
	visits[u] = true;

	for (int v = 0; v < am.size(); ++v) {
		if (!visits[v] && am[u][v] == 1)
			_fill_in_order(v, visits, st);
	}

	st.push(u);
}

template <bool directed>
void Graph_adj_matrix<directed>::_find_scc (int u, vec_vis& visits, std::vector<int>& component) const {
	visits[u] = true;
	component.push_back(u);

	for (int v = 0; v < am.size(); ++v) {
		if (!visits[v] && am[u][v] == 1)
			_find_scc (v, visits, component);
	}
}

#endif // FIND_SCCS_HPP