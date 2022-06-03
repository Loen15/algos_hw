#include "list_graph.h"

ListGraph::ListGraph(int size) : lists_(size) {}

ListGraph::ListGraph(IGraph const& graph) 
                    : lists_(graph.VerticesCount()) {

}

void ListGraph::AddEdge (int from, int to) {

}

int ListGraph::VerticesCount() const {

}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {

}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {

}