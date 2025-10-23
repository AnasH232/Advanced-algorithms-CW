#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
using namespace std;
using namespace std::chrono;

void bubble_sort_count(int arr[], int size, int& count) {
    count = 0;
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
}

void selection_sort_count(int arr[], int size, int& count) {
    count = 0;
    int min_i;
    for (int i = 0; i < size - 1; i++) {
        min_i = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_i]) min_i = j;
            count++;
        }
        if (min_i != i) swap(arr[min_i], arr[i]);
    }
}

void insertion_sort_count(int arr[], int size, int& count) {
    count = 0;
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0) {
            count++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            else break;
        }
        arr[j + 1] = key;
    }
}

int* randomArray(int& size) {
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> Sdist(1, 30);
    size = Sdist(gen);

    uniform_int_distribution<> Vdist(0, 100);

    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = Vdist(gen);
    }

    return arr;
}

int* sortedArray(int& size) {
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> Sdist(1, 30);
    size = Sdist(gen);

    //starting number randomly chosen
    uniform_int_distribution<> Ndist(0, 100);
    int num = Ndist(gen);

    //number added to last element randomly chosed
    uniform_int_distribution<> Vdist(0, 10);
    int add;

    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = num;
        add = Vdist(gen);
        num += add;
    }

    return arr;
}

int* inverseArray(int& size) {
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> Sdist(1, 30);
    size = Sdist(gen);

    //starting number randomly chosen
    uniform_int_distribution<> Ndist(0, 400);
    int num = Ndist(gen);

    //number added to last element randomly chosed
    uniform_int_distribution<> Vdist(0, 10);
    int sub;

    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = num;
        sub = Vdist(gen);
        num -= sub;
    }

    return arr;
}

void printArr(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void test_comparisons() {
    ofstream comparisons("comparisons.csv");
    ofstream exTime("execution_times.csv");
    comparisons << "Size,Bubble Sort,Selection Sort,Insertion Sort\n";
    exTime << "Size,Bubble Sort,Selection Sort,Insertion Sort\n";

    int sz, count;
    int* arr1, * arr2, * arr3;

    cout << "===============================================================================================================" << endl;
    cout << "Random Arrays: \n" << endl;
    for (int i = 1; i <= 30; i++) {
        arr1 = randomArray(sz);
        arr2 = new int[sz];
        arr3 = new int[sz];

        for (int j = 0; j < sz; j++) {
            arr2[j] = arr1[j];
            arr3[j] = arr1[j];
        }

        cout << "Array before sorting: ";
        printArr(arr1, sz);

        auto start = high_resolution_clock::now();
        bubble_sort_count(arr1, sz, count);
        auto end = high_resolution_clock::now();
        auto bubbleTime = duration_cast<nanoseconds>(end - start);
        int bubbleComp = count;

        start = high_resolution_clock::now();
        selection_sort_count(arr2, sz, count);
        end = high_resolution_clock::now();
        auto selectionTime = duration_cast<nanoseconds>(end - start);
        int selectionComp = count;

        start = high_resolution_clock::now();
        insertion_sort_count(arr2, sz, count);
        end = high_resolution_clock::now();
        auto insertionTime = duration_cast<nanoseconds>(end - start);
        int insertionComp = count;

        cout << "Sorted array: ";
        printArr(arr1, sz);

        cout << "\nBubble sort comparisons made: " << bubbleComp;
        cout << "\nBubble sort execution time: " << bubbleTime.count() << " nanoseconds";
        cout << "\nSelection sort comparisons made: " << selectionComp;
        cout << "\nSelection sort execution time: " << selectionTime.count() << " nanoseconds";
        cout << "\nInsertion sort comparisons made: " << insertionComp;
        cout << "\nInsertion sort execution time: " << insertionTime.count() << " nanoseconds\n" << endl;

        comparisons << sz << "," << bubbleComp << "," << selectionComp << "," << insertionComp << "\n";
        exTime << sz << "," << bubbleTime.count() << "," << selectionTime.count() << "," << insertionTime.count() << "\n";

    }

    cout << "===============================================================================================================" << endl;
    cout << "Sorted arrays: \n" << endl;
    for (int i = 1; i <= 30; i++) {
        arr1 = sortedArray(sz);
        arr2 = new int[sz];
        arr3 = new int[sz];

        for (int j = 0; j < sz; j++) {
            arr2[j] = arr1[j];
            arr3[j] = arr1[j];
        }

        cout << "Array before sorting: ";
        printArr(arr1, sz);

        auto start = high_resolution_clock::now();
        bubble_sort_count(arr1, sz, count);
        auto end = high_resolution_clock::now();
        auto bubbleTime = duration_cast<nanoseconds>(end - start);
        int bubbleComp = count;

        start = high_resolution_clock::now();
        selection_sort_count(arr2, sz, count);
        end = high_resolution_clock::now();
        auto selectionTime = duration_cast<nanoseconds>(end - start);
        int selectionComp = count;

        start = high_resolution_clock::now();
        insertion_sort_count(arr2, sz, count);
        end = high_resolution_clock::now();
        auto insertionTime = duration_cast<nanoseconds>(end - start);
        int insertionComp = count;

        cout << "Sorted array: ";
        printArr(arr1, sz);

        cout << "\nBubble sort comparisons made: " << bubbleComp;
        cout << "\nBubble sort execution time: " << bubbleTime.count() << " nanoseconds";
        cout << "\nSelection sort comparisons made: " << selectionComp;
        cout << "\nSelection sort execution time: " << selectionTime.count() << " nanoseconds";
        cout << "\nInsertion sort comparisons made: " << insertionComp;
        cout << "\nInsertion sort execution time: " << insertionTime.count() << " nanoseconds\n" << endl;

        comparisons << sz << "," << bubbleComp << "," << selectionComp << "," << insertionComp << "\n";
        exTime << sz << "," << bubbleTime.count() << "," << selectionTime.count() << "," << insertionTime.count() << "\n";

    }

    cout << "===============================================================================================================" << endl;
    cout << "Inverse arrays: \n" << endl;
    for (int i = 1; i <= 30; i++) {
        arr1 = inverseArray(sz);
        arr2 = new int[sz];
        arr3 = new int[sz];

        for (int j = 0; j < sz; j++) {
            arr2[j] = arr1[j];
            arr3[j] = arr1[j];
        }

        cout << "Array before sorting: ";
        printArr(arr1, sz);

        auto start = high_resolution_clock::now();
        bubble_sort_count(arr1, sz, count);
        auto end = high_resolution_clock::now();
        auto bubbleTime = duration_cast<nanoseconds>(end - start);
        int bubbleComp = count;

        start = high_resolution_clock::now();
        selection_sort_count(arr2, sz, count);
        end = high_resolution_clock::now();
        auto selectionTime = duration_cast<nanoseconds>(end - start);
        int selectionComp = count;

        start = high_resolution_clock::now();
        insertion_sort_count(arr2, sz, count);
        end = high_resolution_clock::now();
        auto insertionTime = duration_cast<nanoseconds>(end - start);
        int insertionComp = count;

        cout << "Sorted array: ";
        printArr(arr1, sz);

        cout << "\nBubble sort comparisons made: " << bubbleComp;
        cout << "\nBubble sort execution time: " << bubbleTime.count() << " nanoseconds";
        cout << "\nSelection sort comparisons made: " << selectionComp;
        cout << "\nSelection sort execution time: " << selectionTime.count() << " nanoseconds";
        cout << "\nInsertion sort comparisons made: " << insertionComp;
        cout << "\nInsertion sort execution time: " << insertionTime.count() << " nanoseconds\n" << endl;

        comparisons << sz << "," << bubbleComp << "," << selectionComp << "," << insertionComp << "\n";
        exTime << sz << "," << bubbleTime.count() << "," << selectionTime.count() << "," << insertionTime.count() << "\n";

    }

    comparisons.close();
    exTime.close();
    delete[] arr1, arr2, arr3
}

int main() {
    test_comparisons();
    return 0;
}
