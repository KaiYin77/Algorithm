//
//  C++ code
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits.h>
#include <map>
#include <vector>
#include <iomanip>

const int Max_Weight = INT_MAX;

class GraphMST;

class Node{
    public:
        friend class GraphMST;
        int x, y;
        Node(): x(0), y(0){}
        Node(int x, int y): x(x), y(y){}


};


class GraphMST{
    private:
        int num_vertex;
        std::vector< Node* > vertice;
        std::vector< std::vector<int> > AdjMatrix;
        
    public:
        GraphMST():num_vertex(0){};
        GraphMST(int num):num_vertex(num){
            AdjMatrix.resize(num_vertex);
            for (int i=0; i < num_vertex; i++){
                AdjMatrix[i].resize(num_vertex);
            }
        }

        void AddVertex(int x, int y);
        void BuildAdjMatrix();
        void ShowAdjMatrix();
        void AddEdge(int from, int to);
        
        void PrimMST(int Start, std::ofstream & output);
        friend int MinKeyExtract(int *key, bool *visited, int size);
};

int MinKeyExtract(int *key, bool *visited, int size){

  int min = Max_Weight, min_idx = 0;
  for (int i = 0; i < size; i++){
    if (visited[i] == false && key[i] < min) {
      min = key[i];
      min_idx = i;
    }
  }
  return min_idx;
}


void GraphMST::AddVertex(int x, int y){
    Node* node = new Node(x, y);
    vertice.push_back(node);

}


void GraphMST::BuildAdjMatrix(){
    for(int i = 0; i < vertice.size(); i++){
        for (int j=0; j < vertice.size(); j++){
            AdjMatrix[i][j] = abs(vertice[i]->x-vertice[j]->x) + abs(vertice[i]->y-vertice[j]->y);
        }
    }
 
}

void GraphMST::AddEdge(int from, int to){
        AdjMatrix[from][to] = -1;
        AdjMatrix[to][from] = -1;
}

void GraphMST::ShowAdjMatrix(){
    for(int i = 0; i < vertice.size(); i++){
        for (int j=0; j < vertice.size(); j++){
            std::cout << AdjMatrix[i][j] << " ";
        }
        std::cout << "\n";
    }
 
}

void GraphMST::PrimMST(int Start, std::ofstream& output){
    
    int key[num_vertex], predecessor[num_vertex];
    bool visited[num_vertex];

    for (int i = 0; i < num_vertex; i++) {
        key[i] = Max_Weight;
        predecessor[i] = -1;
        visited[i] = false;
    }

    key[Start] = 0;
    for (int i = 0; i < num_vertex; i++){
            int u = MinKeyExtract(key, visited, num_vertex);
            visited[u] = true;
            for (int j = 0; j < num_vertex; j++){

                if (visited[j] == false  && AdjMatrix[u][j]!=0 && AdjMatrix[u][j]<key[j]) {
                    predecessor[j] = u;
                    key[j] = AdjMatrix[u][j];
                }
            }
    }

    int i = (Start+1)%num_vertex;

    //Display result
    // std::cout << std::setw(3) << "v1" << " - " << std::setw(3) << "v2"<< " : weight\n";
    // while (i != Start) {
    //     std::cout << std::setw(3) << predecessor[i] << " - " << std::setw(3) << i
    //               << " : " << std::setw(4) << AdjMatrix[predecessor[i]][i] <<"\n";
    //     i = (++i)%num_vertex;       
    // }
    
    //Output to file
    int cost = 0;
    i = (Start+1)%num_vertex;
    while (i != Start) {
        if (AdjMatrix[predecessor[i]][i] != -1)
            cost += AdjMatrix[predecessor[i]][i];
        i = (++i)%num_vertex;       
    }

    output << cost << std::endl;
    
    i = (Start+1)%num_vertex;
    while (i != Start) {
        if (AdjMatrix[predecessor[i]][i] != -1)
            output << predecessor[i] << " " << i << std::endl;
        i = (++i)%num_vertex;      
    }

}




int main(int argc, char**argv) {
    // Setting Usage
    if ( argc < 3 || argc > 3 ){
        std::cout << "Warning!!" << std::endl;
        std::cout << "[Usage]: ./Lab2 input.txt output.txt" << std::endl;
        return 1;
    }
    
    // Input Output file
    std::ifstream inputFile;
    inputFile.open(std::string(argv[1]));
    std::ofstream outputFile;
    outputFile.open(std::string(argv[2]));

    // Read how many number of pins
    std::string line;
    std::getline(inputFile, line);
    int number_of_pins = std::stoi(line);
    
    // [1] Create Graph
    GraphMST myGraph(number_of_pins);

    // [2] Add Vertex : coordinate(x, y) of pin
    for (int i=0; i < number_of_pins; i++){
        
        std::getline(inputFile, line);
        std::stringstream buffer(line);
        int x, y;
        buffer >> x >> y;
        myGraph.AddVertex(x, y);
        // std::cout << x << " " << y << std::endl;
    }
    
    // [3] Build AdjMatrix
    myGraph.BuildAdjMatrix();

    // Edge : existing routing segment(segment connects pin x and pin y)
    while (std::getline(inputFile, line) ){
        std::stringstream buffer(line);
        int x, y;
        buffer >> x >> y;
        myGraph.AddEdge(x,y);
        // std::cout << x << " " << y << std::endl;
    }
    // Find Minimum Spanning Tree & Output Cost & Routing Segment
    myGraph.PrimMST(0, outputFile);
    
    // ShowAdjMatrix
    // myGraph.ShowAdjMatrix();

    outputFile.close();
    
    return 0;


}