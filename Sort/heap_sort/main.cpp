#include <iostream>
#include <vector>

void max_heapify(std::vector<int>& arr, int root, int length) {
    int left = 2*root;
    int right = 2*root + 1;
    int largest;

    if (left <= length && arr[left] > arr[root]) {
        largest = left;
    } else {
        largest = root;
    }
    
    if (right <= length && arr[right] > arr[largest]) {
        largest = right;
    }
    if (largest != root) {
        std::swap(arr[largest], arr[root]);
        max_heapify(arr, largest, length);
    }

}

void build_max_heap(std::vector<int>& arr) {
    for (int i=arr.size()/2; i>=1; i--) {
        max_heapify(arr, i, arr.size()-1);
    }
}


void heap_sort(std::vector<int>& arr) {
    arr.insert(arr.begin(), 0);

    build_max_heap(arr);
    
    int size = arr.size()-1;
    for(int i=arr.size()-1; i>=1; i--) {
        std::swap(arr[1], arr[i]);
        size--;
        max_heapify(arr, 1, size);
    }
    arr.erase(arr.begin());
}

void print_array(const std::vector<int>& arr) {
    for (auto a : arr) {
        std::cout << a << " ";
    }
    std::cout << std::endl;
}
int main(int argc, char* argv[]) {
    std::vector<int> arr{4, 5, 3, 7, 9, 2};
    std::cout << "Before: " << std::endl;
    print_array(arr);

    heap_sort(arr);
    std::cout << "Sorted: " << std::endl;
    print_array(arr);
    return 0;
}
