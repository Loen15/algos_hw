#include "matrix_graph.h"

#include <cassert>

MatrixGraph::MatrixGraph(int size)
                    : matrix_(size, std::vector<bool>(size, 0)) {}

MatrixGraph::MatrixGraph(IGraph const& graph) 
                    : matrix_(graph.VerticesCount(), std::vector<bool>(graph.VerticesCount(), 0)) {
    for (int from = 0; from < graph.VerticesCount(); from++) {
        for (auto to : graph.GetNextVertices(from)) {
            matrix_[from][to] = true;
        }
    }
}

void MatrixGraph::AddEdge (int from, int to) {
    assert(0 <= from && from < matrix_.size());
    assert(0 <= to && to < matrix_.size());
    matrix_[from][to] = true;
}

int MatrixGraph::VerticesCount() const {
    return matrix_.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    assert(0 <= vertex && vertex < matrix_.size());
    std::vector<int> next_vertices;
    for (int to = 0; to < matrix_.size(); to++) {
        if (matrix_[vertex][to])
            next_vertices.push_back(to);
    }
    return next_vertices;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    assert(0 <= vertex && vertex < matrix_.size());
    std::vector<int> prev_vertices;
    for (int from = 0; from < matrix_.size(); from++) {
        if (matrix_[from][vertex])
            prev_vertices.push_back(from);
    }
    return prev_vertices;
}