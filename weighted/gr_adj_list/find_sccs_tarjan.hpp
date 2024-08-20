#ifndef FIND_SCCS_TARJAN
#define FIND_SCCS_TARJAN

template <bool directed>
typename Graph_al<directed>::vec_2d Graph_al<directed>::find_sccs_tarjan () const {
    int size = al.size();
	std::vector<int> ids(size, -1);
	std::vector<int> low_link(size, -1);
	std::stack<int> st;
	vec_vis in_stack(size, false);
	vec_2d res;

	for (int u = 0; u < size; ++u) {
		if (ids[u] == -1)
			_find_scc_tarjan(u, in_stack, ids, low_link, st, res);
	}

	return res;
}

template <bool directed>
void Graph_al<directed>::_find_scc_tarjan (int u, vec_vis& in_stack, std::vector<int>& ids, std::vector<int>& low_link, std::stack<int>& st, vec_2d& res) const {
	static int id = 0;
	in_stack[u] = true;
	st.push(u);
	ids[u] = low_link[u] = id++;

	for (const auto& pair : al[u]) {
		if (ids[pair.first] == -1) _find_scc_tarjan (pair.first, in_stack, ids, low_link, st, res);
		if (in_stack[pair.first] == true) low_link[u] = std::min(low_link[u], low_link[pair.first]);
	}

	if (ids[u] == low_link[u]) {
		std::vector<int> sub_res;

		for (int top = st.top() ; ; top = st.top()) {
			sub_res.push_back(top);
			st.pop();
			in_stack[top] = false;
			if (top == u) {
				res.push_back(std::move(sub_res));
				break;
			}
		}
	}
}

#endif // FIND_SCCS_TARJAN