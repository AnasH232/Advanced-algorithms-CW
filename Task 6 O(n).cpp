#include <iostream>
#include <random>
using namespace std;

int main()
{
    random_device rd;
	mt19937 gen(rd());
    uniform_int_distribution<> wDist(1, 15);
	
    int real_weight = wDist(gen);
    int fake_weight = wDist(gen);
    while (fake_weight == real_weight) fake_weight = wDist(gen);

    int n;
    cout << "Enter number of coins: ";
    cin >> n;

	int* coins = new int[n];

    uniform_int_distribution<> iDist(0, n-1);
    int fake_index = iDist(gen);

    for (int i = 0; i < n; i++) {
        if (i == fake_index) coins[i] = fake_weight;
		else coins[i] = real_weight;
	}

    int fake;
    int comp_coin = 0;

    if (coins[0] == coins[1]) {
        for (int i = 2; i < n; i++) {
            if (coins[0] != coins[i]) {
                fake = i;
                break;
            }
        }
    }
    else if (coins[0] == coins[2]) fake = 1;
    else {
        fake = 0;
        comp_coin = 1;
    }

    cout << "Fake coin found at index: " << fake << endl;

    if (coins[fake] < coins[comp_coin]) cout << "The fake coin is lighter than the real coins" << endl;
	else cout << "The fake coin is heavier than the real coins" << endl;

    delete[] coins;
}
