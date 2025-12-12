#include <iostream>
#include <vector>
using namespace std;

//bubble sort to sort items from least to most expensive (used in greedy version)
void bubbleSort(int cost[], int idx[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1; j++) {
			if (cost[j] > cost[j + 1]) {
				swap(cost[j], cost[j + 1]);
				swap(idx[j], idx[j + 1]);
			}
		}
	}
}

//dynamic programming version of knapsack
int knapsackDP(int W, int weights[], int n, int chosen[]) {
	//2d array to represent 2 way table
	vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

	//nested loop to fill table
	for (int i = 0; i <= n; i++) {
		for (int w = 0; w <= W; w++) {
			if (i == 0 || w == 0) dp[i][w] = 0; //no item or zero capacity
			else if (weights[i - 1] <= w) {
				dp[i][w] = max(1 + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]); //max used to include or exclude next item
			}
			else dp[i][w] = dp[i - 1][w]; //item excluded
		}
	}

	int count = 0;
	int remaining = W;

	//loop used store all chosen items in array
	for (int i = n; i > 0 && remaining > 0; i--) {
		if (dp[i][remaining] != dp[i - 1][remaining]) {
			chosen[count] = i - 1;
			count++;
			remaining -= weights[i - 1];
		}
	}

	//max number of items returned
	return dp[n][W];
}

//greedy version of algorithm
int knapsackGreedy(int W, int weights[], int n, int chosen[]) {
	int* cost = new int[n];
	int* idx = new int[n];

	//copy of prices array made with orginal index stored in different array (done so DP is not affected)
	for (int i = 0; i < n; i++) {
		cost[i] = weights[i];
		idx[i] = i;
	}

	//items sorted by price
	bubbleSort(cost, idx, n);

	int total = 0;
	int count = 0;

	//loop used to add items until budget is exceeded
	for (int i = 0; i < n; i++) {
		if (total + cost[i] <= W) {
			total += cost[i];
			chosen[count] = idx[i];
			count++;
		}
		else break;
	}

	delete[] cost, idx;
	return count; //max number of items returned
}

int main()
{
	int n, budget;
	//input for budget and number of items
	cout << "Enter shopping budget: ";
	cin >> budget;

	cout << "Enter how many items you want from the store: ";
	cin >> n;

	//dynamic arrays to store item info and chosen items for later
	string* names = new string[n];
	int* prices = new int[n];
	int* chosen = new int[n];

	//populate names and prices
	cout << "\nEnter the names and prices of each item: " << endl;
	for (int i = 0; i < n; i++) {
		cout << "Item " << i + 1 << " name: ";
		cin >> names[i];
		cout << "Item " << i + 1 << " price: ";
		cin >> prices[i];
	}

	//Dynamic knapsack results
	int maxCount = knapsackDP(budget, prices, n, chosen);

	cout << "\nSolution Using Dynamic Programming: " << endl;
	cout << "You can buy up to " << maxCount << " items" << endl;
	cout << "The items you should buy are: " << endl;
	
	//recommended items displayed and total calculated
	int total = 0;
	for (int i = 0; i < maxCount; i++) {
		int idx = chosen[i];
		cout << names[idx] << ": $" << prices[idx] << endl;
		total += prices[idx];
	}

	cout << "Total cost: " << total << endl;

	//greedy knapsack results
	maxCount = knapsackGreedy(budget, prices, n, chosen);

	cout << "\nSolution Using Greedy Algorithm: " << endl;
	cout << "You can buy up to " << maxCount << " items" << endl;
	cout << "The items you should buy are: " << endl;

	total = 0;
	for (int i = 0; i < maxCount; i++) {
		int idx = chosen[i];
		cout << names[idx] << ": $" << prices[idx] << endl;
		total += prices[idx];
	}

	cout << "Total cost: " << total << endl;
	delete[] names, prices, chosen;
}
