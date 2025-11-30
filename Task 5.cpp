#include <iostream>
using namespace std;

int bubbleSort(char arr[], int n) {
    int m = 0;
    bool swapped;
    for (int i = 0; i < n-1; i++) {
        swapped = false;
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j]  < arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
                m++;
            }
        }
        if (!swapped) break;
    }
    return m;
}

void printArr(char arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    int n;
    cout << "Enter n: ";
    cin >> n;

    char* disks = new char[2 * n];

    for (int i = 0; i < 2 * n; i += 2) {
        disks[i] = 'D';
        disks[i + 1] = 'L';
    }

    cout << "Disks before sorting: ";
    printArr(disks, 2 * n);

    int moves = bubbleSort(disks, 2 * n);
    cout << "Disks after sorting: ";
    printArr(disks, 2 * n);

    cout << "Number of moves: " << moves << endl;
    delete[] disks;
}
