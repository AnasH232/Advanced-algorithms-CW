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

	int coins[3];

    uniform_int_distribution<> iDist(0, 2);
    int fake_index = iDist(gen);

    for (int i = 0; i < 3; i++) {
        if (i == fake_index) coins[i] = fake_weight;
        else coins[i] = real_weight;
    }

    int fake;
    int comp_coin = 0;

    if (coins[0] == coins[1]) fake = 2;
    else if (coins[0] == coins[2]) fake = 1;
    else {
        fake = 0;
        comp_coin = 1;
    }

	cout << "The fake coin is at index: " << fake << endl;

    if (coins[fake] < coins[comp_coin]) cout << "The fake coin is lighter than the real coins" << endl;
    else cout << "The fake coin is heavier than the real coins" << endl;
}
