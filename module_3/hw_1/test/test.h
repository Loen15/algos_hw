#ifndef TEST_H
#define TEST_H

#include "../arc_graph/arc_graph.h"
#include "../list_graph/list_graph.h"
#include "../matrix_graph/matrix_graph.h"
#include "../set_graph/set_graph.h"

void run();

void BFS(IGraph const& graph);

void DFS(IGraph const& graph);

void SupportiveDFS(IGraph const& graph, int vertex, std::vector<bool> &visited);

#endif // TEST_H