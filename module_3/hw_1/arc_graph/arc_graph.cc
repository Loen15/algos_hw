#include "arc_graph.h"

ArcGraph::ArcGraph(int size) : lists_(size) {}

ArcGraph::ArcGraph(IGraph const& graph) 
                    : lists_(graph.VerticesCount()) {

}

void ArcGraph::AddEdge (int from, int to) {

}

int ArcGraph::VerticesCount() const {

}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {

}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {

}