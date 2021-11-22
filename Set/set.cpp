#include <iostream>
#include <iomanip>

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

void PrintArray(int *array, int size){
  
  for (int i=0; i < size; i++){
    std::cout << std::setw(3) << i;
  }
  std::cout << std::endl;
  
  for (int i=0; i < size; i++){
    std::cout << std::setw(3) << array[i];
  }
  std::cout << std::endl;
}

int main(){
  
  const int size = 6;
  int array[size] = {-1, -1, -1, -1, -1, -1};
  PrintArray(array, size);

  UnionSet(array, 1, 2);
  std::cout << "After union(1,2):\n";
  PrintArray(array, size);

  UnionSet(array, 0, 2);
  std::cout << "After union(0,2):\n";
  PrintArray(array, size);

  UnionSet(array, 3, 5);
  std::cout << "After union(3,5):\n";
  PrintArray(array, size);
  
  UnionSet(array, 2, 5);
  std::cout << "After union(2,5):\n";
  PrintArray(array, size);

  
  std::cout << "element(5) belongs to Set(" << FindSetCollapsing(array, 5) << ").\n";
  std::cout << "After collapsing:\n";
  PrintArray(array, size);

  return 0;
}
