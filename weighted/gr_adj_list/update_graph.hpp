#ifndef UPDATE_GRAPH_HPP
#define UPDATE_GRAPH_HPP

template <bool directed>
void Graph_al<directed>::add_edge (int u, int v, int weight) {
	if (_not_same_vals(u, v))
		al[u].push_back({v, weight});

	if (!directed && _not_same_vals(u, v))
		al[v].push_back({u, weight});
}

template <bool directed>
void Graph_al<directed>::add_vertex () {
	al.push_back(std::vector<std::pair<int, int>>());
}
#endif // UPDATE_GRAPH_HPP