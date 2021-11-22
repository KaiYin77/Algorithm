#include <iostream>
#include <vector>
#include <list>
#include <iomanip>

struct Edge{
  int from, to, weight;
  Edge(){};
  Edge(int u, int v, int w):from(u), to(v), weight(w){};
};

class GraphMST{
private:
  int num_vertex;
  std::vector<std::vector<int> > AdjMatrix;
public:
  GraphMST():num_vertex(0){};
  GraphMST(int n):num_vertex(n){
    AdjMatrix.resize(num_vertex);
    for (int i=0; i < num_vertex; i++){
      AdjMatrix[i].resize(num_vertex);
    }
  }
  
  void AddEdge(int from, int to, int weight);

  void KruskalMST();
  void GetSortedEdge(std::vector<struct Edge> &vec);
  friend int FindSetCollapsing(int *subset, int i);
  friend void UnionSet(int *subset, int i, int j);
};

int FindSetCollapsing(int *subset, int i){
  
  int root;
  for (root = i; subset[root] >=0; root = subset[root]);

  // Start collapsing
  while (i != root){
    int parent = subset[i];
    subset[i] = root;
    i = parent;
  }

  return root;

}

void UnionSet (int *subset, int x, int y){
  
  int xroot = FindSetCollapsing(subset, x);
  int yroot = FindSetCollapsing(subset, y);
  
  //the less the rank are, the more the elements have

  if (subset[xroot] <= subset[yroot]) {
    subset[xroot] += subset[yroot];
    subset[yroot] = xroot;
  }
  else{ 
    subset[yroot] += subset[xroot];
    subset[xroot] = yroot;
  }

}

bool WeightComp(struct Edge e1, struct Edge e2){
  return (e1.weight < e2.weight);
}

void GraphMST::GetSortedEdge(std::vector<struct Edge> &edgearray){
 
  for (int i = 0; i < num_vertex-1; i++) {
    for (int j = 0; j < num_vertex; j++){
      if (AdjMatrix[i][j] != 0) {
        edgearray.push_back(Edge(i, j, AdjMatrix[i][j]));
      }
    }
  }
  std::sort(edgearray.begin(), edgearray.end(), WeightComp);

}

void GraphMST::KruskalMST() {

  struct Edge *edgesetMST = new struct Edge[num_vertex-1];
  int edgesetcount = 0;

  int subset[num_vertex];
  for (int i = 0; i < num_vertex; i++){
    subset[i] = -1;
  }

  std::vector<struct Edge> increaseWeight;
  GetSortedEdge(increaseWeight);

  for (int i = 0; i < increaseWeight.size(); i++) {
    // Check: not in the same set == Prevent construct cycle
    if (FindSetCollapsing(subset, increaseWeight[i].from) != FindSetCollapsing(subset, increaseWeight[i].to)){
      edgesetMST[edgesetcount++] = increaseWeight[i];
      UnionSet(subset, increaseWeight[i].from, increaseWeight[i].to); 
    }
  }

  std::cout << std::setw(3) << "v1" << " -" << std::setw(3) << "v2" << ": weight\n";
  for (int i = 0; i < num_vertex-1; i++){
    std::cout << std::setw(3) << edgesetMST[i].from << " -"\
	      << std::setw(3) << edgesetMST[i].to << ":"\
	      << std::setw(4) << edgesetMST[i].weight << "\n";
  }
}

void GraphMST::AddEdge(int from, int to, int weight){
  AdjMatrix[from][to] = weight;
}

int main() {

  GraphMST g6(7);
  g6.AddEdge(0, 1, 5);g6.AddEdge(0, 5, 3);
  g6.AddEdge(1, 0, 5);g6.AddEdge(1, 2, 10);g6.AddEdge(1, 4, 1);g6.AddEdge(1, 6, 4);
  g6.AddEdge(2, 1, 10);g6.AddEdge(2, 3, 5);g6.AddEdge(2, 6, 8);
  g6.AddEdge(3, 2, 5);g6.AddEdge(3, 4, 7);g6.AddEdge(3, 6, 9);
  g6.AddEdge(4, 1, 1);g6.AddEdge(4, 3, 7);g6.AddEdge(4, 5, 6);g6.AddEdge(4, 6, 2);
  g6.AddEdge(5, 0, 3);g6.AddEdge(5, 4, 6);
  g6.AddEdge(6, 1, 4);g6.AddEdge(6, 2, 8);g6.AddEdge(6, 3, 9);g6.AddEdge(6, 4, 2);

  std::cout << "MST found by kruskal:\n";
  g6.KruskalMST();

  return 0;
}
