#include <iostream>
void swap(int *a, int *b){
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int Partition(int *arr, int front, int end){
  int pivot = arr[end];
  int i = front - 1;
  for (int j = front; j < end; j++){
    if(arr[j] < pivot){
      i++;
      swap(&arr[i], &arr[j]);
    }
  }
  i++;
  swap(&arr[i], &arr[end]);
  return i;
}


// divide and conquer
void QuickSort(int *arr, int front, int end){
  if (front < end){
    int pivot = Partition(arr, front, end);
    QuickSort(arr, front, pivot - 1);
    QuickSort(arr, pivot + 1, end);
  }
}

void printArray(int *arr, int size){
  for(int i=0; i < size; i++)
    std::cout << arr[i] << " ";
  std::cout << std::endl;
}

int main() {
  int n = 9;
  int array[] = {9, 4, 1, 6, 7, 3, 8, 2, 5}; 
  std::cout << "orginal:\n";
  printArray(array, n);

  QuickSort(array, 0, n-1);


  std::cout << "sorted:\n";
  printArray(array, n);
  
  return 0;
}
