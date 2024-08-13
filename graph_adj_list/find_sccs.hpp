#ifndef FIND_SCCS_HPP
#define FIND_SCCS_HPP

template <bool directed>
void Graph_adj_list<directed>::_fill_in_order(int u, vec_vis& visits, std::stack<typename Graph_adj_list<directed>::val_type>& st) const {
	visits[u] = true;

	for (auto v : al[u]) {
		if (!visits[v])
			_fill_in_order(v, visits, st);
	}

	st.push(u);
}

template <bool directed>
void Graph_adj_list<directed>::_find_scc(int u, vec_vis& visits, std::vector<typename Graph_adj_list<directed>::val_type>& component) const {
	visits[u] = true;
	component.push_back(u);

	for (auto v : al[u]) {
		if (!visits[v])
			_find_scc(v, visits, component);
	}
}

template <bool directed>
typename Graph_adj_list<directed>::list Graph_adj_list<directed>::find_sccs() const {
	std::stack<val_type> st;
	int size = al.size();

	vec_vis visits(size, false);

	for (int i = 0; i < size; i++)
		if (!visits[i])
			_fill_in_order(i, visits, st);

	Graph_adj_list<directed> gr = clone_transpose();

	fill(visits.begin(), visits.end(), false);

	list sccs;
	std::vector<val_type> component;

	while (!st.empty()) {
		int v = st.top();
		st.pop();


		if (!visits[v]) {
			gr._find_scc(v, visits, component);
			sccs.push_back(std::move(component));
		}
	}

	return sccs;
}

#endif // FIND_SCCS_HPP