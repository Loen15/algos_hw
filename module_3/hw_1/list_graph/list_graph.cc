#include "list_graph.h"

#include <cassert>

ListGraph::ListGraph(int size) : lists_(size) {}

ListGraph::ListGraph(IGraph const& graph) 
                    : lists_(graph.VerticesCount()) {
    for (int from = 0; from < lists_.size(); from++) {
        lists_[from] = graph.GetNextVertices(from);
    }
}

void ListGraph::AddEdge (int from, int to) {
    assert(0 <= from && from < lists_.size());
    assert(0 <= to && to < lists_.size());
    lists_[from].push_back(to);
}

int ListGraph::VerticesCount() const {
    return lists_.size();
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    assert(0 <= vertex && vertex < lists_.size());
    return lists_[vertex];
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    assert(0 <= vertex && vertex < lists_.size());
    std::vector<int> prev_vertices;
    for (int from = 0; from < lists_.size(); from++) {
        for (int to : lists_[from]) {
            if (to == vertex)
                prev_vertices.push_back(from);
        }
    }
    return prev_vertices;
}