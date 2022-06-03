#include "arc_graph.h"

#include <cassert>

ArcGraph::ArcGraph(int size) : count_(size) {}

ArcGraph::ArcGraph(IGraph const& graph) 
                    : count_(graph.VerticesCount()) {
    for (int from = 0; from < count_; from++) {
        for (auto to : graph.GetNextVertices(from)) {
            list_.emplace_back(from, to);
        }
    }
}

void ArcGraph::AddEdge (int from, int to) {
    assert(0 <= from && from < count_);
    assert(0 <= to && to < count_);
    list_.emplace_back(from, to);
}

int ArcGraph::VerticesCount() const {
    return count_;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    assert(0 <= vertex && vertex < count_);
    std::vector<int> next_vertices;
    for (auto pair : list_) {
        if (pair.first == vertex)
            next_vertices.push_back(pair.second);
    }
    return next_vertices;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    assert(0 <= vertex && vertex < count_);
    std::vector<int> prev_vertices;
    for (auto pair : list_) {
        if (pair.second == vertex)
            prev_vertices.push_back(pair.first);
    }
    return prev_vertices;
}