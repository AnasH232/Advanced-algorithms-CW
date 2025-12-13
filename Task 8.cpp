#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

//Converts whole state of tubes to string, so can be added and compared to visited set
string stateToString(vector<vector<int>>& tubes) {
    string s;
    for (int i = 0; i < tubes.size(); i++) {
        s.push_back('|');
        for (int color : tubes[i]) {
            s.push_back(char('A' + color)); //numerical value of 'A' added to number of color then converted to character
        }
    }
    return s;
}

//used to check if a tube is already completed so no moves are performed from it
bool completeTube(vector<int>& tube, int capacity) {
    if (tube.size() != capacity || tube.empty()) return false;
    int color = tube[0];
    for (int i = 1; i < tube.size(); i++) {
        if (tube[i] != color) return false;
    }
    return true;
}

//checks if current state is completed by checking if every tube has one color or is empty
bool solved(vector<vector<int>>& tubes, int capacity) {
    for (int i = 0; i < tubes.size(); i++) {
        if (tubes[i].empty()) continue;
        if (!completeTube(tubes[i], capacity)) return false;
    }
    return true;
}

//checks if move from i to j is valid
bool validMove(vector<vector<int>>& tubes, int capacity, int i, int j) {
    //conditions that make move invalid
    if (i == j || tubes[i].empty()) return false;
    if (tubes[j].size() >= capacity) return false;

    int color = tubes[i].back();
    if (tubes[j].empty()) {
        //rule to remove valid moves that cause the same color to be split across tubes for no reason
        for (int x = 0; x < tubes.size(); x++) {
            if (x == i) continue;
            if (tubes[x].empty()) continue;
            if (tubes[x].back() == color && tubes[x].size() < capacity) return false;
        }
        return true;
    }
    if (tubes[j].back() == color) return true;
    return false;
}

// dfs function
bool dfs(vector<vector<int>>& tubes, int capacity, unordered_set<string>& visited, vector<int>& from, vector<int>& to) {
    //checks if current state has been visited before
    string state = stateToString(tubes);
    if (visited.contains(state)) return false;
    visited.insert(state);
    //checks if puzzle is solved
    if (solved(tubes, capacity)) return true;

    int n = tubes.size();
    //nested for loop performs moves on incomplete tubes
    for (int i = 0; i < n; i++) {
        if (completeTube(tubes[i], capacity)) continue;
        for (int j = 0; j < n; j++) {
            //conditions to make sure move is valid and isn't the reverse of the last move
            if (!validMove(tubes, capacity, i, j)) continue;
            if (!from.empty() && !to.empty()) {
                if (from.back() == j && to.back() == i) continue;
            }

            //perform move
            int color = tubes[i].back();
            tubes[i].pop_back();
            tubes[j].push_back(color);

            from.push_back(i);
            to.push_back(j);
            //recursively calls dfs to continue down path until unsolvable or solution found
            if (dfs(tubes, capacity, visited, from, to)) return true;
            //if path unsolvable last move is undone and loop continues
            from.pop_back();
            to.pop_back();
            tubes[i].push_back(color);
            tubes[j].pop_back();
        }
    }
    return false;
}

//prints all tubes in current state
void printState(vector<vector<int>>& tubes, int capacity) {
    for (int i = 0; i < tubes.size(); i++) {
        cout << "Stack " << i + 1 << ": [ ";
        for (int j = 0; j < tubes[i].size(); j++) {
            cout << tubes[i][j] + 1 << " ";
        }
        int empty = capacity - tubes[i].size();
        string space(2 * empty, ' ');
        cout << space << "]" << endl;
    } cout << endl;
}

int main()
{
    //user inputs
    int stacks, capacity, colors, emptyStacks;
    cout << "Enter number of stacks: ";
    cin >> stacks;
    cout << "Enter number of balls in each tube: ";
    cin >> capacity;
    cout << "Enter number of colors: ";
    cin >> colors;
    cout << "Enter how many of the stacks are empty: ";
    cin >> emptyStacks;

    vector<vector<int>> tubes(stacks);
    //nested loop populates vector using user inputs
    for (int i = 0; i < stacks-emptyStacks; i++) {
        cout << "Stack " << i + 1 << ": " << endl;
        cout << "Enter " << capacity << " colors as integers from bottom to top (between 1 and " << colors << "): ";
        for (int j=0; j < capacity; j++) {
            int c;
            cin >> c;
            tubes[i].push_back(c - 1);
        }
    }
    //data structures initialised
    vector<vector<int>> initial_state = tubes;
    unordered_set<string> visited;
    vector<int> from, to;

    //dfs called
    bool result = dfs(tubes, capacity, visited, from, to);
    cout << "\nInitial state: " << endl;
    printState(initial_state, capacity);
    //moves output and displayed
    if (result) {
        for (int move = 0; move < from.size(); move++) {
            int i = from[move];
            int j = to[move];

            int c = initial_state[i].back();
            initial_state[i].pop_back();
            initial_state[j].push_back(c);

            cout << "Move " << move + 1 << ": From stack " << from[move] + 1 << " to stack " << to[move] + 1 << endl;
            printState(initial_state, capacity);
        }
        cout << "\nSolution achieved in " << from.size() << " moves" << endl;
        cout << "Number of states explored: " << visited.size() << endl;
    }
    else cout << "No solution found" << endl;
}
