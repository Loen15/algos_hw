#ifndef LIST_GRAPH_H
#define LIST_GRAPH_H

#include "i_graph.h"

class ListGraph : public IGraph {
public:
    explicit ListGraph (int size);
    explicit ListGraph (IGraph const& graph);

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;
private:
    std::vector<std::vector<int>> lists_; 
};

#endif LIST_GRAPH_H