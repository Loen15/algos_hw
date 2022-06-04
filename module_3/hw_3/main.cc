// Задача 3. «Города» (4 балла)  
// Обязательная задача  
// Требуется отыскать самый выгодный маршрут между городами.   
// Требования: время работы O((N+M)logN), где N-количество городов, M-известных дорог между ними.  
// Формат входных данных.  
// Первая строка содержит число N – количество городов.  
// Вторая строка содержит число M - количество дорог.  
// Каждая следующая строка содержит описание дороги (откуда, куда, время в пути).  
// Последняя строка содержит маршрут (откуда и куда нужно доехать).  
// Формат выходных данных.  
// Вывести длину самого выгодного маршрута.

#include <iostream>
#include <vector>
#include <cassert>
#include <queue>
#include <map>
#include <set>

class MapGraph {
public:
    explicit MapGraph(int size) : lists_(size) {}

    void AddEdge(int from, int to, int weight) {
        assert(0 <= from && from < lists_.size());
        assert(0 <= to && to < lists_.size());
        lists_[from].push_back(std::make_pair(to, weight));
        lists_[to].push_back(std::make_pair(from, weight));
    }
    int VerticesCount() const { return lists_.size(); }

    std::vector<std::pair<int, int>> GetVertices(int vertex) const {
        assert(0 <= vertex && vertex < lists_.size());
        return lists_[vertex];
    }
private:
    std::vector<std::vector<std::pair<int, int>>> lists_; // first - вершина, second - вес
};

void run();

int Dijkstra(MapGraph graph, int from, int to);

int main() {
    run();
    return 0;
}

void run() {
    int n;
    int m;
    int from;
    int to;
    int weight;
    std::cin >> n >> m;
    MapGraph graph(n);

    for (int i = 0; i < m; i++) {
        std::cin >> from >> to >> weight;
        graph.AddEdge(from, to, weight);
    }
    std::cin >> from >> to;
    std::cout << Dijkstra(graph, from, to) << std::endl;
}

int Dijkstra(MapGraph graph, int from, int to) {
    std::vector<int> distance(graph.VerticesCount(), -1);
    distance[from] = 0;
    std::queue<std::pair<int, int>> q;
    q.push(std::make_pair(from, 0));
    while (!q.empty()) {
        auto curr = q.front();
        q.pop();
        if (distance[curr.first] < curr.second)
            continue;

        for (auto way : graph.GetVertices(curr.first)) {
            if (distance[way.first] == -1) {
                distance[way.first] = distance[curr.first] + way.second;
                q.push(std::make_pair(way.first, way.second));
            } else if (distance[curr.first] + way.second <  distance[way.first]) {
                distance[way.first] = distance[curr.first] + way.second;
                q.push(std::make_pair(way.first, distance[way.second]));
            }
        }
    }
    return distance[to];
}
