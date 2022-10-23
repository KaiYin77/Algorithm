#include <iostream>
#include <vector>
void selection_sort(std::vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        int min_index = i;
        for (int j = i + 1; j < arr.size(); j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        std::swap(arr[i], arr[min_index]);
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
    selection_sort(arr);
    print_array(arr);
    return 0;
}
//  i  j
// [4, 5, 3, 7, 9 ,2]
// [2, ...]
// [2, ]
