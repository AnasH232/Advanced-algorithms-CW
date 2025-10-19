#include <iostream>
using namespace std;

void bubble_sort_count(int arr[], int size) {
    int count = 0;
    bool swapped;
    for (int i = 0; i < size - 1; i++) {
        swapped = false;
        for (int j = 0; j < size - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
            count++;
        }
        if (!swapped) break;
    }
    cout << count << " comparisons made" << endl;
}

void selection_sort_count(int arr[], int size) {
    int count = 0;
    int min_i;
    for (int i = 0; i < size - 1; i++) {
        min_i = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_i]) min_i = j;
            count++;
        }
        if (min_i != i) swap(arr[min_i], arr[i]);
    }
    cout << count << " comparisons made" << endl;
}

void insertion_sort_count(int arr[], int size) {
    int count = 0;
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0) {
            count++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            } else break;
        }
        arr[j + 1] = key;
    }
    cout << count << " comparisons made" << endl;
}

void printArr(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arr[] = { 20,4,17,47,12 };
    int sz = sizeof(arr) / sizeof(arr[0]);
    //bubble_sort_count(arr, sz);
    //selection_sort_count(arr, sz);
    insertion_sort_count(arr, sz);
    printArr(arr, sz);


    return 0;
}
