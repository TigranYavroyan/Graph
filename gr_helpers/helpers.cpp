#include "helpers.h"

void graph_utils::print_path (const std::vector<int>& path) {
    for (int i = 0; i < path.size(); ++i) {
        std::cout << path[i];
        if ((i + 1) != path.size()) std::cout << " -> ";
    }
}

int graph_utils::edges_max (const std::vector<std::vector<int>>& edges) {
    std::optional<int> max;
    for (int i = 0; i < edges.size(); ++i) {
        for (int val : edges[i]) {
            if (!max.has_value() || max.value() < val)
                max = val;
        }
    }
    return max.value();
}