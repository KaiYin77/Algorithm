#include <iostream>
#include <vector>

const int MAX = 10000;

void merge(std::vector<int>& arr, int front, int mid, int end) {
    std::vector<int> left_sub(arr.begin() + front, arr.begin() + mid + 1);
    std::vector<int> right_sub(arr.begin() + mid + 1, arr.begin() + end + 1);

    left_sub.insert(left_sub.end(), MAX);
    right_sub.insert(right_sub.end(), MAX);

    int left_idx = 0, right_idx = 0;

    for (int i = front; i <= end; i++) {
        if (left_sub[left_idx] <= right_sub[right_idx]) {
            arr[i] = left_sub[left_idx];
            left_idx++;
        } else {
            arr[i] = right_sub[right_idx];
            right_idx++;
        }
    }
}
void merge_sort(std::vector<int>& arr, int front, int end) {
    if (front < end) {
        int mid = (front + end) / 2;
        merge_sort(arr, front, mid);
        merge_sort(arr, mid + 1, end);
        merge(arr, front, mid, end);
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

    merge_sort(arr, 0, arr.size()-1);
    std::cout << "Sorted: " << std::endl;
    print_array(arr);
    return 0;
}
