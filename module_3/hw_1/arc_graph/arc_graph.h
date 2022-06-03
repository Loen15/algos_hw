#ifndef ARC_GRAPH_H
#define ARC_GRAPH_H

#include "i_graph.h"

class ArcGraph : public IGraph {
public:
    explicit ArcGraph (int size);
    explicit ArcGraph (IGraph const& graph);

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;
private:
    std::vector<std::vector<int>> lists_; 
};

#endif ARC_GRAPH_H