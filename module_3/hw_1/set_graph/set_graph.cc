#include "set_graph.h"

#include <cassert>

SetGraph::SetGraph(int size) : sets_(size) {}

SetGraph::SetGraph(IGraph const& graph) 
                    : sets_(graph.VerticesCount()) {
    for (int from = 0; from < graph.VerticesCount(); from++) {
        for (auto to : graph.GetNextVertices(from)) {
            sets_[from].insert(to);
        }
    }
}

void SetGraph::AddEdge (int from, int to) {
    assert(0 <= from && from < sets_.size());
    assert(0 <= to && to < sets_.size());
    sets_[from].insert(to);
}

int SetGraph::VerticesCount() const {
    return sets_.size();
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    assert(0 <= vertex && vertex < sets_.size());
    std::vector<int> next_vertices;
    for (auto to : sets_[vertex]) {
        next_vertices.push_back(to);
    }
    return next_vertices;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    assert(0 <= vertex && vertex < sets_.size());
    std::vector<int> prev_vertices;
    for (int from = 0; from < sets_.size(); from++) {
        if (sets_[from].find(vertex) != sets_[from].end()) {
            prev_vertices.push_back(from);
        }
    }
    return prev_vertices;    
}