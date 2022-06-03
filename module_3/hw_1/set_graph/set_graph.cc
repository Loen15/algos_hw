#include "set_graph.h"

SetGraph::SetGraph(int size) : lists_(size) {}

SetGraph::SetGraph(IGraph const& graph) 
                    : lists_(graph.VerticesCount()) {

}

void SetGraph::AddEdge (int from, int to) {

}

int SetGraph::VerticesCount() const {

}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {

}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {

}