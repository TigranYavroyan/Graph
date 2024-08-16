#ifndef GR_ADJ_LIST_HPP
#define GR_ADJ_LIST_HPP

#include <iostream>
#include <vector>
#include <utility>

template <bool directed>
class Graph_al {
public:
	using vec_2d = std::vector<std::vector<int>>;
	using list = std::vector<std::vector<std::pair<int, int>>>;
	using vec_vis = std::vector<bool>;
public:
	Graph_al (int n, vec_2d& edges);
	Graph_al (const list& adj_list);
	Graph_al (const Graph_al& other);
	Graph_al (Graph_al&& other);

private:

};

#include "gr_adj_list_header.hpp"

#endif // GR_ADJ_LIST_HPP