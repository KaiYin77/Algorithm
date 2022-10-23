#include <iostream>
#include <vector>

void insertion_sort(std::vector<int>& arr) {
    for(int i=1; i< arr.size(); i++) {
        int key = arr[i];
        int j = i-1;
        while(key < arr[j] && j>=0){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
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

    insertion_sort(arr);
    std::cout << "Sorted: " << std::endl;
    print_array(arr);
    return 0;
}
