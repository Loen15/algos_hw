#ifndef MATRIX_GRAPH_H
#define MATRIX_GRAPH_H

#include "i_graph.h"

class MatrixGraph : public IGraph {
public:
    explicit MatrixGraph (int size);
    explicit MatrixGraph (IGraph const& graph);

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;
private:
    std::vector<std::vector<int>> lists_; 
};

#endif MATRIX_GRAPH_H