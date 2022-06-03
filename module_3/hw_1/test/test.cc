#include"test.h"

#include <iostream>
#include <queue>

void run() {
    ArcGraph arc_graph(7);
    arc_graph.AddEdge(0, 1);
    arc_graph.AddEdge(0, 5);
    arc_graph.AddEdge(1, 2);
    arc_graph.AddEdge(1, 3);
    arc_graph.AddEdge(1, 5);
    arc_graph.AddEdge(1, 6);
    arc_graph.AddEdge(3, 2);
    arc_graph.AddEdge(3, 4);
    arc_graph.AddEdge(3, 6);
    arc_graph.AddEdge(5, 4);
    arc_graph.AddEdge(5, 6);
    arc_graph.AddEdge(6, 4);

    std::cout << "ArcGraph:" << std::endl;
    BFS(arc_graph);
    DFS(arc_graph);

    ListGraph list_graph(arc_graph);
    std::cout << "ListGraph:" << std::endl;
    BFS(list_graph);
    DFS(list_graph);

    MatrixGraph matrix_graph(list_graph);
    std::cout << "MatrixGraph:" << std::endl;
    BFS(matrix_graph);
    DFS(matrix_graph);

    SetGraph set_graph(matrix_graph);
    std::cout << "MatrixGraph:" << std::endl;
    BFS(set_graph);
    DFS(set_graph);

}

void BFS(IGraph const& graph) {
    std::cout << "BFS: ";
    if (graph.VerticesCount() == 0) {
        std::cout << "Graph empty" << std::endl;
        return;
    }
    std::vector<bool> visited(graph.VerticesCount(), 0);
    std::queue<int> q;
    q.push(0);
    while (!q.empty()) {
        std::cout << q.front() << " ";
        for (auto vertex : graph.GetNextVertices(q.front())) {
            if (!visited[vertex]) {
                q.push(vertex);
                visited[vertex] = true;
            }
        }
        q.pop();
    }
    std::cout << std::endl;
}

void DFS(IGraph const& graph) {
    std::cout << "DFS: ";
    if (graph.VerticesCount() == 0) {
        std::cout << "Graph empty" << std::endl;
        return;
    }
    if (graph.VerticesCount() > 1000) {
        std::cout << "Count of vertices more of 1000, pls use BFS" << std::endl;
        return;
    }
    std::vector<bool> visited(graph.VerticesCount(), 0);
    
    for (int i = 0; i < graph.VerticesCount(); i++) {
        if (!visited[i]) {
            SupportiveDFS(graph, i, visited);
        }
    }
    std::cout << std::endl;
}

void SupportiveDFS(IGraph const& graph, int vertex, std::vector<bool> &visited) {
    visited[vertex] = true;
    std::cout << vertex << " ";
    
    for (int next_vertex : graph.GetNextVertices(vertex)) {
        if (!visited[next_vertex]) {
            SupportiveDFS(graph, next_vertex, visited);
        }
    }
}
