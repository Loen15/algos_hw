#ifndef SET_GRAPH_H
#define SET_GRAPH_H

#include "../i_graph/i_graph.h"

#include <unordered_set>

class SetGraph : public IGraph {
public:
    explicit SetGraph (int size);
    explicit SetGraph (IGraph const& graph);

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;
private:
    std::vector<std::unordered_set<int>> sets_;
};

#endif // SET_GRAPH_H