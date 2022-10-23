#include <iostream>
#include <vector>
void bubble_sort(std::vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr.size() - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
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
    bubble_sort(arr);
    print_array(arr);
    return 0;
}
