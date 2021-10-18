#include <iostream>
#include <vector>

// Util Swap fn
void swap(int &p1, int &p2){
  int tmp = p2;
  p2 = p1;
  p1 = tmp;
}

// Binary Heap -> Max Heap -> fisrt node has max value
void MaxHeapify(std::vector<int>& array, int root, int length){
  int left = 2*root;
  int right = 2*root + 1;
  int largest;

  if (left<=length && array[left] > array[root])
    largest = left;
  else
    largest = root;
  if (right<=length && array[right] > array[largest])
    largest = right;

  if (largest != root){
    swap(array[largest], array[root]);
    MaxHeapify(array, largest, length);
  }
}

void BuildMaxHeap(std::vector<int> &array){
  for(int i=(int)array.size()/2; i>=1; i--){
    MaxHeapify(array, i, (int)array.size()-1);
  }
}

// Implement HeapSort by binary heap
void HeapSort(std::vector<int> &array){
  array.insert(array.begin(), 0);

  BuildMaxHeap(array);

  int size = (int)array.size()-1;
  for(int i=(int)array.size()-1; i >= 2; i--){
    swap(array[1], array[i]);
    size--;
    MaxHeapify(array, 1, size);
  }

  array.erase(array.begin());
}

void printArray(std::vector<int> &arr){
  for(int i=0; i < arr.size(); i++)
    std::cout << arr[i] << " ";
  std::cout << std::endl;
}

int main() {

  int arr[] = {9, 4, 1, 6, 7, 3, 8, 2, 5};
  std::vector<int> array(arr, arr+sizeof(arr)/sizeof(int));
  
  std::cout << "orginal:\n";
  printArray(array);

  HeapSort(array);
  printArray(array);
  
  return 0;
}
