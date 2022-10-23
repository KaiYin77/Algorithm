#include <iostream>
#include <vector>

int partition(std::vector<int>& arr, int front, int end) {
    int pivot = arr[end];
    int i = front - 1;
    for (int j = front; j < end; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    i++;
    std::swap(arr[i], arr[end]);
    return i;
}

void quick_sort(std::vector<int>& arr, int front, int end) {
    if (front < end) {
        int pivot = partition(arr, front, end);
        quick_sort(arr, front, pivot - 1);
        quick_sort(arr, pivot + 1, end);
    }
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

    quick_sort(arr, 0, arr.size() - 1);
    std::cout << "Sorted: " << std::endl;
    print_array(arr);
    return 0;
}
