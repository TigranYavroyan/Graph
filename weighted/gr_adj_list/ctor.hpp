#ifndef CTOR_HPP
#define CTOR_HPP

template <bool directed>
Graph_al<directed>::Graph_al (int n, const vec_2d& edges) : al(n + 1) {
	for (int i = 0; i < edges.size(); ++i) {
		add_edge(edges[i][0], edges[i][1], edges[i][2]);
	}
}

template <bool directed>
Graph_al<directed>::Graph_al (const list& adj_list) : al{adj_list} {}

template <bool directed>
Graph_al<directed>::Graph_al (const Graph_al& other) : al{other.al} {}

template <bool directed>
Graph_al<directed>::Graph_al (Graph_al&& other) : al{other.al} {
	other.al.clear();
}

#endif // CTOR_HPP