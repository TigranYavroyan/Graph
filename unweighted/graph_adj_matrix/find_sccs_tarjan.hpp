#ifndef FIND_SCCS_TARJAN_HPP
#define FIND_SCCS_TARJAN_HPP

template <bool directed>
typename Graph_adj_matrix<directed>::matrix Graph_adj_matrix<directed>::find_sccs_tarjan () const {
	int size = am.size();

	vec_vis in_stack(size, false);
	std::vector<int> ids(size, -1);
	std::vector<int> low_link(size, -1);
	std::vector<int> sub_res;
	std::stack<int> st;
	matrix res;

	for (int u = 0; u < size; ++u) {
		if (ids[u] == -1)
			_find_sccs_tarjan(u, in_stack, st, ids, low_link, res, sub_res);
	}

	return res;
}

template <bool directed>
void Graph_adj_matrix<directed>::_find_sccs_tarjan (int u, vec_vis& in_stack, std::stack<int>& st, std::vector<int>& ids, std::vector<int>& low_link, matrix& res, std::vector<int>& sub_res) const {
	static int id = 0;

	in_stack[u] = true;
	st.push(u);
	ids[u] = low_link[u] = id++;

	for (int v = 0; v < am.size(); ++v) {
		if (am[u][v] == 1) {
			if (ids[v] == -1) _find_sccs_tarjan(v, in_stack, st, ids, low_link, res, sub_res);
			if (in_stack[v] == true) low_link[u] = std::min(low_link[u], low_link[v]);
		}
	}

	if (ids[u] == low_link[u]) {
		for (int top = st.top() ; ; top = st.top()) {

			sub_res.push_back(top);
			st.pop();
			in_stack[top] = false;
			if (u == top) {
				break;
			}
		}

		res.push_back(std::move(sub_res));
	}
}

#endif // FIND_SCCS_TARJAN_HPP