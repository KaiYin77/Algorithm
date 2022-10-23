// C++ code
#include <iostream>
#include <list>
#include <queue>
#include <vector>

class Graph {
   private:
    int num_vertex;
    std::vector<std::list<int>> AdjList;
    int *color, *distance, *predecessor;

   public:
    Graph() : num_vertex(0){};
    Graph(int n) : num_vertex(n) { AdjList.resize(n); };
    void AddEdgeList(int from, int to);
    void BFS(int start);
    void Visualize();
};

void Graph::Visualize() {
    std::cout << "Distance: ";
    for (int i=0; i<num_vertex; i++) {
        std::cout << distance[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Predecessor: ";
    for (int i=0; i<num_vertex; i++) {
        std::cout << predecessor[i] << " ";
    }
    std::cout << std::endl;
}

void Graph::AddEdgeList(int from, int to) { AdjList[from].push_back(to); }

void Graph::BFS(int start) {
    color = new int[num_vertex];
    distance = new int[num_vertex];
    predecessor = new int[num_vertex];

    // initialize 3 array
    for (int i = 0; i < num_vertex; i++) {
        color[i] = 0;                  // 0:white; 1:gray; 2:black
        distance[i] = num_vertex - 1;  // set maximum dist.
        predecessor[i] = -1;           // set no predecessor
    }

    std::queue<int> q;
    int i = start;
    for (int j = 0; j < num_vertex; j++) {
        if (color[i] == 0) {
            color[i] = 1;
            distance[i] = 0;
            predecessor[i] = -1;
            q.push(i);
            while (!q.empty()) {
                int u = q.front();
                for (auto& itr : AdjList[u]) {
                    if (color[itr] == 0) {
                        color[itr] = 1;
                        distance[itr] = distance[u] + 1;
                        predecessor[itr] = u;
                        q.push(itr);
                    }
                }
                q.pop();
                color[u] = 2;
            }
        }
        i = j;
    }
}
int main() {
    Graph g1(9);
    g1.AddEdgeList(0, 1);
    g1.AddEdgeList(0, 2);
    g1.AddEdgeList(0, 3);
    g1.AddEdgeList(1, 0);
    g1.AddEdgeList(1, 4);
    g1.AddEdgeList(2, 0);
    g1.AddEdgeList(2, 4);
    g1.AddEdgeList(2, 5);
    g1.AddEdgeList(2, 6);
    g1.AddEdgeList(2, 7);
    g1.AddEdgeList(3, 0);
    g1.AddEdgeList(3, 7);
    g1.AddEdgeList(4, 1);
    g1.AddEdgeList(4, 2);
    g1.AddEdgeList(4, 5);
    g1.AddEdgeList(5, 2);
    g1.AddEdgeList(5, 4);
    g1.AddEdgeList(5, 8);
    g1.AddEdgeList(6, 2);
    g1.AddEdgeList(6, 7);
    g1.AddEdgeList(6, 8);
    g1.AddEdgeList(7, 2);
    g1.AddEdgeList(7, 3);
    g1.AddEdgeList(7, 8);
    g1.AddEdgeList(8, 5);
    g1.AddEdgeList(8, 6);

    g1.BFS(0);
    g1.Visualize();

    return 0;
}

