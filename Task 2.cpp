// Online C++ compiler to run C++ program online
#include <iostream>
using namespace std;
int i = 1;

void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod) {
    if (n == 0) return;
    towerOfHanoi(n - 1, from_rod, to_rod, aux_rod);
    cout << "Move no. " << i << ".. ";
    cout << "Move disk " << n << " from rod " << from_rod << " to rod " << aux_rod << endl;
    i++;
    towerOfHanoi(n - 1, to_rod, from_rod, aux_rod);
    cout << "Move no. " << i << ".. ";
    cout << "Move disk " << n << " from rod " << aux_rod << " to rod " << to_rod << endl;
    i++;
    towerOfHanoi(n - 1, from_rod, to_rod, aux_rod);
}

int main() {
    int N;
    cout << "Enter the number of disks: ";
    cin >> N;
    towerOfHanoi(N, 'A', 'C', 'B');

    return 0;
}
