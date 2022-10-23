#include <iomanip>
#include <iostream>
#include <list>
#include <vector>
class Graph {
   private:
    int num_vertex;
    std::vector<std::list<int>> AdjList;
    int *color, *predecessor, *discover, *finish;

   public:
    Graph() : num_vertex(0){};
    Graph(int n) : num_vertex(n) { AdjList.resize(num_vertex); };
    void AddEdgeList(int from, int to);
    void DFS(int start);
    void DFSVisit(int vertex, int& time);
};

void Graph::AddEdgeList(int from, int to) { AdjList[from].push_back(to); }

void Graph::DFS(int start) {
    color = new int[num_vertex];
    predecessor = new int[num_vertex];
    discover = new int[num_vertex];
    finish = new int[num_vertex];

    int time = 0;
    for (int i = 0; i < num_vertex; i++) {
        color[i] = 0;  // 0:white; 1:gray; 2:black;
        predecessor[i] = -1;
        discover[i] = 0;
        finish[i] = 0;
    }

    int k = start;
    for (int j = 0; j < num_vertex; j++) {
        if (color[k] == 0) {
            DFSVisit(k, time);
        }
        k = j;
    }
    std::cout << "predecessor:" << std::endl;  // 印出 A(0) ~ H(7)的predecessor
    for (int i = 0; i < num_vertex; i++) {
        std::cout << std::setw(4) << i;
    }
    std::cout << std::endl;
    for (int i = 0; i < num_vertex; i++) {
        std::cout << std::setw(4) << predecessor[i];
    }
    std::cout << "\ndiscover time:"
              << std::endl;  // 印出 A(0) ~ H(7)的discover time
    for (int i = 0; i < num_vertex; i++) {
        std::cout << std::setw(4) << i;
    }
    std::cout << std::endl;
    for (int i = 0; i < num_vertex; i++) {
        std::cout << std::setw(4) << discover[i];
    }
    std::cout << "\nfinish time:"
              << std::endl;  // 印出 A(0) ~ H(7)的finish time
    for (int i = 0; i < num_vertex; i++) {
        std::cout << std::setw(4) << i;
    }
    std::cout << std::endl;
    for (int i = 0; i < num_vertex; i++) {
        std::cout << std::setw(4) << finish[i];
    }
}

void Graph::DFSVisit(int vertex, int& time) {
    color[vertex] = 1;
    discover[vertex] = ++time;
    for (std::list<int>::iterator itr = AdjList[vertex].begin();
         itr != AdjList[vertex].end(); itr++) {
        if (color[*itr] == 0) {
            predecessor[*itr] = vertex;
            DFSVisit(*itr, time);
        }
    }
    color[vertex] = 2;
    finish[vertex] = ++time;
}

int main() {
    Graph g2(8);

    g2.AddEdgeList(0, 1);
    g2.AddEdgeList(0, 2);
    g2.AddEdgeList(1, 3);
    g2.AddEdgeList(2, 1);
    g2.AddEdgeList(2, 5);
    g2.AddEdgeList(3, 4);
    g2.AddEdgeList(3, 5);
    // AdjList[4] is empty
    g2.AddEdgeList(5, 1);
    g2.AddEdgeList(6, 4);
    g2.AddEdgeList(6, 7);
    g2.AddEdgeList(7, 6);

    g2.DFS(0);

    return 0;
}
