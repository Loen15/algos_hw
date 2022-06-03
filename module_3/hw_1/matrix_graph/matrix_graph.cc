#include "matrix_graph.h"

MatrixGraph::MatrixGraph(int size) : lists_(size) {}

MatrixGraph::MatrixGraph(IGraph const& graph) 
                    : lists_(graph.VerticesCount()) {

}

void MatrixGraph::AddEdge (int from, int to) {

}

int MatrixGraph::VerticesCount() const {

}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {

}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {

}