// C++ code
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <list>
#include <utility>          // for std::pair<>
#include <iomanip>          // for std::setw()
#include <cmath>            // for std::floor
#include <queue>

const int Max_Distance = INT_MAX;

struct HeapNode{
    int element, key;
    HeapNode():element(0),key(0){};
    HeapNode(int node, int key):element(node), key(key){};
};

class BinaryHeap{
    private:
        std::vector<HeapNode> heap;        // 存放HeapNode資料的矩陣
        void swap(struct HeapNode &p1, struct HeapNode &p2);
        int FindPosition(int node);
        int GetParentNode(int node){return std::floor(node/2);};
    public:
        BinaryHeap(){               // default constructor會把heap[0]給預留 
            heap.resize(1);         // 之後若新增HeapNode, 會從heap[1]開始新增
        }
        BinaryHeap(int n){
            heap.resize(n + 1);
        }
        bool IsHeapEmpty(){return (heap.size()<1);};

        // Min-Priority Queue
        void MinHeapify(int node, int length);
        void BuildMinHeap(std::vector<int> array);
        void DecreaseKey(int node, int newKey);
        void MinHeapInsert(int node, int key);
        int Minimum();                  // 回傳vertex的位置index
        int ExtractMin();               // 回傳vertex的位置index

};
void BinaryHeap::MinHeapify(int node, int length){

    int left = 2*node,          // 取得left child
        right = 2*node + 1,     // 取得right child
        smallest;               // smallest用來記錄包含root與child, 三者之中Key最小的node

    if (left <= length && heap[left].key < heap[node].key)
        smallest = left;
    else
        smallest = node;

    if (right <= length && heap[right].key < heap[smallest].key)
        smallest = right;

    if (smallest != node) {                 // 如果目前node的Key不是三者中的最小
        swap(heap[smallest], heap[node]);   // 就調換node與三者中Key最小的node之位置
        MinHeapify(smallest, length);       // 調整新的subtree成Min Heap
    }
}
void BinaryHeap::BuildMinHeap(std::vector<int> array){

    // 將array[]的資料放進 heap之矩陣中, 並預留 heap[0] 不做使用
    for (int i = 0; i < array.size(); i++) {     
        heap[i + 1].element = i;                 // 把array[]的idx視為element
        heap[i + 1].key = array[i];              // 把array[]的數值視為key
    }
    for (int i = (int)heap.size()/2; i >= 1 ; i--) {
        MinHeapify(i, (int)heap.size()-1);     // length要減一, 因為heap從從1開始存放資料
    }
}
void BinaryHeap::swap(struct HeapNode &p1, struct HeapNode &p2){

    struct HeapNode temp = p1;
    p1 = p2;
    p2 = temp;
}
int BinaryHeap::FindPosition(int node){

    int idx = 0;
    for (int i = 1; i < heap.size(); i++) {
        if (heap[i].element == node) {
            idx = i;
        }
    }
    return idx;
}
int BinaryHeap::Minimum(){
    return heap[1].element;
}
int BinaryHeap::ExtractMin(){

    if (IsHeapEmpty()) {
        std::cout << "error: heap is empty\n";
        exit(-1);
    }
    int min = heap[1].element;    // 此時heap的第一個node具有最小key值
                                  // 便以min記錄其element, 最後回傳min
    // delete the first element/vertex
    heap[1] = heap[heap.size()-1];            // 把最後一個element放到第一個位置,
    heap.erase(heap.begin()+heap.size()-1);   // 再刪除最後一個element
    MinHeapify(1, (int)heap.size());          // 目前, heap[1]具有最大Key, 需要進行調整

    return min;       // 回傳heap中具有最小key的element
}
void BinaryHeap::DecreaseKey(int node, int newKey){

    int index_node = FindPosition(node);      // 找到node所在的位置index

    if (newKey > heap[index_node].key) {      // 如果不是把node的Key下修, 便終止此函式
        // std::cout << "new key is larger than current key\n";
        return;
    }
    heap[index_node].key = newKey;            // 更新node之Key後, 需要檢查是否新的subtree滿足Min Heap
    while (index_node > 1 && heap[GetParentNode(index_node)].key > heap[index_node].key) {
        swap(heap[index_node], heap[GetParentNode(index_node)]);
        index_node = GetParentNode(index_node);
    }
}
void BinaryHeap::MinHeapInsert(int node, int key){

    heap.push_back(HeapNode(node,key));    // 在heap[]尾巴新增一個node
    DecreaseKey(node, key);
}

class Graph_SP{             // SP serves as Shortest Path
    private:
        int num_vertex;
        std::vector<std::list<std::pair<int,int>>> AdjList;
        std::vector<int> predecessor, distance;
        std::vector<bool> visited;
    public:
        Graph_SP():num_vertex(0){};
        Graph_SP(int n):num_vertex(n){
            AdjList.resize(num_vertex);
        }
        void AddEdge(int from, int to, int weight);
        void PrintDataArray(std::vector<int> array, std::ofstream & output);
        void PrintIntArray(int *array);

        void InitializeSingleSource(int Start);     // 以Start作為起點
        void Relax(int X, int Y, int weight);       // edge方向：from X to Y

        std::vector<int> Dijkstra(int Start, std::ofstream & output);        // 需要Min-Priority Queue
        friend class BinaryHeap;             // 以Binary Heap實現Min-Priority Queue
};
std::vector<int> Graph_SP::Dijkstra(int Start, std::ofstream & output){

    InitializeSingleSource(Start);

    BinaryHeap minQueue(num_vertex);   // object of min queue
    minQueue.BuildMinHeap(distance);

    visited.resize(num_vertex, false);   // initializa visited[] as {0,0,0,...,0}

    while (!minQueue.IsHeapEmpty()) {
        int u = minQueue.ExtractMin();
        for (std::list<std::pair<int, int>>::iterator itr = AdjList[u].begin();
             itr != AdjList[u].end(); itr++) {

            Relax(u, (*itr).first, (*itr).second);
            minQueue.DecreaseKey((*itr).first, distance[(*itr).first]);
        }
    }
    // std::cout << "\nprint predecessor:\n";
    // PrintDataArray(predecessor);
    // std::cout << "\nprint distance:\n";
    PrintDataArray(distance, output);

    return predecessor;
}
void Graph_SP::InitializeSingleSource(int Start){

    distance.resize(num_vertex);
    predecessor.resize(num_vertex);

    for (int i = 0; i < num_vertex; i++) {
        distance[i] = Max_Distance;
        predecessor[i] = -1;
    }
    distance[Start] = 0;
}
void Graph_SP::Relax(int from, int to, int weight){

    if (distance[to] > distance[from] + weight) {
        distance[to] = distance[from] + weight;
        predecessor[to] = from;
    }
}
void Graph_SP::AddEdge(int from, int to, int weight){

    AdjList[from].push_back(std::make_pair(to,weight));
}
void Graph_SP::PrintDataArray(std::vector<int> array, std::ofstream & output){
    // for (int i = 0; i < num_vertex; i++)
    //     std::cout << std::setw(4) << i;
    // std::cout << std::endl;
    // for (int i = 0; i < num_vertex; i++)
    //     std::cout << std::setw(4) << array[i];
    // std::cout << std::endl;
    output << "s: " << array[0] << std::endl;
    output << "t: " << array[num_vertex-1] << std::endl;;
    for (int i = 1; i < num_vertex-1; ++i) {
        output << "a" << i << ": " << array[i] << std::endl;
    }

}

class Graph_FlowNetWorks{
    private:
        int num_vertex;
        std::vector<std::vector<int>> AdjMatrix;
    public:
        Graph_FlowNetWorks():num_vertex(0){};
        Graph_FlowNetWorks(int n);
        void AddEdge(int from, int to, int capacity);

        std::vector<std::vector<int>>  FordFulkerson(int source, int termination);
        bool BFSfindExistingPath(std::vector<std::vector<int>> graphResidual, 
                                int *predecessor, int source, int termination);
        int MinCapacity(std::vector<std::vector<int>> graphResidual, 
                        int *predecessor, int termination);

};
Graph_FlowNetWorks::Graph_FlowNetWorks(int n):num_vertex(n){
    // constructor
    AdjMatrix.resize(num_vertex);
    for (int i = 0; i < num_vertex; i++)
        AdjMatrix[i].resize(num_vertex);
}
bool Graph_FlowNetWorks::BFSfindExistingPath(std::vector<std::vector<int>> graph, 
                                             int *predecessor, int s, int t){
    int visited[num_vertex];

    for (int i = 0; i < num_vertex; i++){
        visited[i] = 0;     // 0 表示還沒有被找到
        predecessor[i] = -1;
    }

    std::queue<int> queue;
    // BFS 從 s 開始, 也可以規定s一律訂成vertex(0)
    queue.push(s);
    visited[s] = 1;
    while (!queue.empty()) {
        int exploring = queue.front();
        for (int j = 0; j < num_vertex; j++) {
            if (graph[exploring][j]!=0 && visited[j]==0) {
                queue.push(j);
                visited[j] = 1;
                predecessor[j] = exploring;
            }
        }
        queue.pop();
    }
    return (visited[t] == 1);   // 若t有被visited, 表示有path從s到t
                                // 也可以用 if (predecessor[t] != -1) 判斷
}
int Graph_FlowNetWorks::MinCapacity(std::vector<std::vector<int>> graph, 
                                    int *predecessor, int t){
    int min = 100;      // 確保min會更新, 假設graph上的capacity都小於100

    // 用predecessor[idx] 和 idx 表示一條edge
    // 找到在從s到t的path上, capacity最小的值, 存入min
    for (int idx = t; predecessor[idx] != -1; idx = predecessor[idx]){
        if (graph[predecessor[idx]][idx]!=0 && graph[predecessor[idx]][idx] < min) {
            min = graph[predecessor[idx]][idx];
        }
    }
    return min;
}
std::vector<std::vector<int>> Graph_FlowNetWorks::FordFulkerson(int source, int termination){

    // residual networks的初始狀態等於AdjMatrix
    std::vector<std::vector<int>> graphResidual(AdjMatrix);    
    int maxflow = 0;                                           
    int predecessor[num_vertex];
    // BFS finds augmenting path
    while (BFSfindExistingPath(graphResidual, predecessor, source, termination)) {
        int mincapacity = MinCapacity(graphResidual, predecessor, termination);
        maxflow = maxflow + mincapacity;
        for (int Y = termination; Y != source; Y = predecessor[Y]){
            // 更新 residual graph
            int X = predecessor[Y];
            graphResidual[X][Y] -= mincapacity;
            graphResidual[Y][X] += mincapacity;
        }
    }
    return graphResidual;
    // std::cout << "Possible Maximum Flow: " << maxflow << std::endl;

}
void Graph_FlowNetWorks::AddEdge(int from, int to, int capacity){

    AdjMatrix[from][to] = capacity;
}


int main(int argc, char**argv) {
    // Execute Usage
    if ( argc < 4 || argc > 4 ){
        std::cout << "Warning!!" << std::endl;
        std::cout << "[Usage]: ./Lab3 input.txt short.txt max.txt" << std::endl;
        return 1;
    }
    
    // Declaration Input Output File stream
    std::ifstream input_file;
    std::ofstream output_file_short;
    std::ofstream output_file_max;
    input_file.open(std::string(argv[1]));
    output_file_short.open(std::string(argv[2]));
    output_file_max.open(std::string(argv[3]));

    // Parsing Input File

    // Read home node
    std::stringstream buffer;
    std::string homeKey, homeValue;
    buffer << input_file.rdbuf();
    buffer >> homeKey >> homeValue;
    
    // std::cout << homeKey << " " << homeValue << std::endl;

    // Read party node
    std::string partyKey, partyValue;
    buffer >> partyKey >> partyValue;
    // std::cout << partyKey << " " << partyValue << std::endl;

    // Read how many kinds of tangyuan
    std::string keyTangyuan;
    int kindsTangyuan;
    buffer >> keyTangyuan >> kindsTangyuan;
    // std::cout << keyTangyuan << " "<< kindsTangyuan << std::endl;

    // Read number of people
    std::string keyPeople;
    int numPeople;
    buffer >> keyPeople >> numPeople;
    // std::cout << keyPeople << " " << numPeople << std::endl;

    // Construct people table for different kinds of flavor
    std::vector<std::vector<int>> tablePeople(kindsTangyuan, std::vector<int> (kindsTangyuan));
    for (int i=0; i < numPeople-1; i++){
        int numTangyuan;
        buffer >> numTangyuan;
        for (int j=0; j < numTangyuan; j++){
            int kind;
            buffer >> kind;
            tablePeople[i][kind-1] += 1;
        }
    }
    
    // Read number of supermarket
    std::string supermarketKey;
    int numSupermarket;
    buffer >> supermarketKey >> numSupermarket;
    // std::cout << supermarketKey << " "<< numSupermarket << std::endl;
    
    // Create the Graph of Shortest Path 
    Graph_SP mySPGraph(2 + numSupermarket);

    std::vector<int> supermarket(numSupermarket);
    for (int i=0; i < numSupermarket; ++i){
        std::string keySupermarket;
        buffer >> keySupermarket >> supermarket[i];
        // std::cout << keySupermarket << " " << supermarket[i] << std::endl;
    }
    
    // Construct the Graph of Shortest Path 
    std::string line;
    while (getline(buffer, line)) {
        while (line.length()==0 )
            getline(buffer, line);
        std::stringstream buffer2(line);
        
        std::string destination, departure;
        int distance;
        buffer2 >> destination >> departure >> distance;
        // std::cout << destination << " " << departure << " " << distance << std::endl;

        int idx_dest, idx_depart;
        
        if (departure == "s")
            idx_depart = 0;
        
        else if (departure == "t")
            idx_depart = numSupermarket + 1;
        else {
            idx_depart = stoi(departure.substr(1));
        }

        if (destination == "s")
            idx_dest = 0;
        else if (destination == "t")
            idx_dest = numSupermarket + 1;
        else {
            idx_dest = stoi(destination.substr(1));
        }
        mySPGraph.AddEdge(idx_depart, idx_dest, distance);

        
    }

    // Perform Dijkstra return predecessor array
    std::vector<int> predecessor;
    predecessor = mySPGraph.Dijkstra(0, output_file_short);
    
    // Create Max-Flow Graph 
    int sizeMaxFlowGraph;
    sizeMaxFlowGraph = kindsTangyuan*(numPeople+1) + 2;
    Graph_FlowNetWorks myMaxFlowGraph(sizeMaxFlowGraph);
    
    // Backtrace predecessor to get exact shortest path
    std::vector<int> supply(kindsTangyuan);
    int from = (1 + numSupermarket);
    // std::cout << from;
    while(predecessor[from] != -1){
        // std::cout << " <- " << predecessor[from];
        if(predecessor[from] > 0 && predecessor[from] < 1+numSupermarket)
            supply[supermarket[predecessor[from]-1]-1] += 1;
        from = predecessor[from];
    }
    // std::cout << std::endl;
    
    // Construct Supply Layer of Max Flow Network
    int kindsBeforeExchange = 0;
    // std::cout << "supply[i]" << std::endl;
    for (int i=0; i < kindsTangyuan; i++) {
        // std::cout << supply[i] << " ";
        int from = 0;
        int to = i + 1;
        if (supply[i] > 0) { 
            kindsBeforeExchange += 1;
        }
        if (supply[i] > 1) {
            myMaxFlowGraph.AddEdge(from, to, supply[i]-1);
        }
    }
    // std::cout << std::endl;
    
    // Construct Hidden Layer of Max Flow Network for Exchange Rule
    for(int i=0; i < kindsTangyuan; i++) {
        for(int j=0; j < numPeople-1; j++) {
            for(int k=0; k < kindsTangyuan; k++){
                int from = i + 1;
                int to = (j + 1) * kindsTangyuan + (k + 1);
                if(i == k){
                    if((supply[i] > 1) && (tablePeople[j][k]==0)){
                        myMaxFlowGraph.AddEdge(from, to,  1);
                    }
                }
            }
        }
    }

    for(int j=0; j < numPeople-1; j++) {
        for(int k=0; k < kindsTangyuan; k++){
            if (tablePeople[j][k]!=0){
                continue;
            }
            for(int l=0; l < kindsTangyuan; l++){
                int from = (j + 1) * kindsTangyuan + (k + 1);
                int to = (j + 1) * kindsTangyuan + (l + 1);
                if (k == l){
                    continue;
                }
                else if (tablePeople[j][l] > 1) {
                    myMaxFlowGraph.AddEdge(from, to, 1);
                }
            }
        }
    }

    // Construct Demand Layer of Max Flow Network
    for (int j=0; j < numPeople-1; j++) {
        for (int k=0; k < kindsTangyuan; k++) {
            int from = (j + 1) * kindsTangyuan + (k + 1);
            int to = (numPeople) * kindsTangyuan + (k + 1);
            if (tablePeople[j][k] > 1) {
                myMaxFlowGraph.AddEdge(from, to, tablePeople[j][k] - 1);
            }
        }
    }

    // Construct Final Layer to optimize max kinds
    for (int k=0; k < kindsTangyuan; k++) {
        int from = (numPeople) * kindsTangyuan + (k + 1);;
        int to = sizeMaxFlowGraph-1;
        if (supply[k] == 0) {
            myMaxFlowGraph.AddEdge(from, to, 1);
        }
    }

    //Perform Ford-Fulkerson to get max flow
    std::vector<std::vector<int>> graphResidual;
    // std::cout << "kindsBeforeExchange: " << kindsBeforeExchange << std::endl;
    graphResidual = myMaxFlowGraph.FordFulkerson(0, sizeMaxFlowGraph-1); 

    std::vector<int> afterExchange(kindsTangyuan);
    for (int k=0; k < kindsTangyuan; k++) {
        int from = (numPeople) * kindsTangyuan + (k + 1);;
        int to = sizeMaxFlowGraph-1;
        if (graphResidual[to][from] > 0){
            afterExchange[k] += graphResidual[to][from];
        }
    }
    
    // for (int i = 0; i < kindsTangyuan; i++){
    //     // std::cout << supply[i] << " ";
    // }
    // std::cout << std::endl;

    int total = 0;
    for (int i = 0; i < kindsTangyuan; i++){
        // std::cout << afterExchange[i] << " ";
        if(afterExchange[i] > 0 || supply[i] > 0){
            total += 1;
        }
    }
    // std::cout << std::endl;

    //Final output
    // std::cout << total << std::endl;
    output_file_max << total << std::endl;

    output_file_short.close();
    output_file_max.close();
    
    return 0;
}