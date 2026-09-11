//Tarea 1 INF221 2026-2 Sergio Fonseca 202404559-8

//GeeksforGeeks. (2026, 6 de agosto). Merge Sort.
//https://www.geeksforgeeks.org/dsa/merge-sort/

#include <vector>

// Merges two subarrays of arr[].
// First subarray is arr[left..mid]
// Second subarray is arr[mid+1..right]
static void merge(std::vector<int>& arr, int left, int mid, int right){

    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp vectors
    std::vector<int> L(n1), R(n2);

    // Copy data to temp vectors L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    // Merge the temp vectors back into arr[left..right]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// left is for left index and right is right index
// of the sub-array of arr to be sorted
static void mergeSort(std::vector<int>& arr, int left, int right){

    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Wrapper con firma uniforme para ser invocado desde sorting.cpp
std::vector<int> mergeSortArray(std::vector<int>& arr){
    if (!arr.empty())
        mergeSort(arr, 0, static_cast<int>(arr.size()) - 1);
    return arr;
}
