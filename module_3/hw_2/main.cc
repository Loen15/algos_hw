// Задача 2. Количество различных путей (3 балла)  
// Обязательная задача  
// Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами. Найдите   количество различных кратчайших путей между заданными вершинами.  
// Требования: сложность O(V+E).   
// Формат ввода.  
// v: кол-во вершин (макс. 50000),  
// n: кол-во ребер (макс. 200000),  
// n пар реберных вершин,  
// пара вершин u, w для запроса.  
// Формат вывода.  
// Количество кратчайших путей от u к w. 

#include <iostream>
#include <vector>
#include <cassert>
#include <queue>

struct IGraph {
    virtual ~IGraph() {}
        
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<int> GetVertices(int vertex) const = 0;
};

class ListGraph : public IGraph {
public:
    explicit ListGraph(int size) : lists_(size) {}

    void AddEdge(int from, int to) override {
        assert(0 <= from && from < lists_.size());
        assert(0 <= to && to < lists_.size());
        lists_[from].push_back(to);
        lists_[to].push_back(from);
    }
    int VerticesCount() const override { return lists_.size(); }

    std::vector<int> GetVertices(int vertex) const override {
        assert(0 <= vertex && vertex < lists_.size());
        return lists_[vertex];
    }
private:
    std::vector<std::vector<int>> lists_; 
};

void run();

int CountOfWays(IGraph const& graph, int u, int w);

int main() {
    run();
    return 0;
}

void run() {
    int v;
    int n;
    std::cin >> v >> n;
    ListGraph graph(v);
    int u, w;
    for (int i = 0; i < n; i++) {
        std::cin >> u >> w;
        graph.AddEdge(u, w);
    }
    std::cin >> u >> w;
    std::cout << CountOfWays(graph, u, w) << std::endl;
}

int CountOfWays(IGraph const& graph, int u, int w) {
    std::vector<int> distance(graph.VerticesCount(), -1);
    std::vector<int> count_ways(graph.VerticesCount(), 0);
    std::vector<bool> visited(graph.VerticesCount(), 0);
    std::queue<int> q;
    q.push(u);
    distance[u] = 0;
    count_ways[u] = 1;
    visited[u] = true;
    while (!q.empty() && q.front() != w) {
        for (auto vertex : graph.GetVertices(q.front())) {
            if (distance[q.front()] + 1 < distance[vertex] || distance[vertex] == -1) {
                distance[vertex] = distance[q.front()] + 1;
                count_ways[vertex] = count_ways[q.front()];    
            } else if (distance[q.front()] + 1 == distance[vertex]) {
                count_ways[vertex] += count_ways[q.front()];
            }
            if (!visited[vertex]) {
                visited[vertex] = true;
                q.push(vertex);
            }
        }
        q.pop();
    }
    return count_ways[w];
}

/*

4
5
0 1
0 2
1 2
1 3
2 3

0 3
answer 2

7
8
0 1
0 2
1 3
2 3
3 4
3 5
4 6
5 6
0 6
answer 4
*/