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
    explicit MapGraph(int size) : maps_(size) {}

    void AddEdge(int from, int to, int weight) {
        assert(0 <= from && from < maps_.size());
        assert(0 <= to && to < maps_.size());
        maps_[from].insert(std::make_pair(to, weight));
        maps_[to].insert(std::make_pair(from, weight));
    }
    int VerticesCount() const { return maps_.size(); }

    std::map<int, int> GetVertices(int vertex) const {
        assert(0 <= vertex && vertex < maps_.size());
        return maps_[vertex];
    }
private:
    std::vector<std::map<int, int>> maps_; // first - вершина, second - вес
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
    std::priority_queue<int> set;
    set.push(from);
    while (!set.empty()) {
        auto curr = set.top();
        set.pop();
        
        for (auto way : graph.GetVertices(curr)) {
            if (distance[way.first] == -1 || distance[curr] + way.second <  distance[way.first]) {
                distance[way.first] = distance[curr] + way.second;
                
                set.push(way.first);
            }
        }
    }
    return distance[to];
}
