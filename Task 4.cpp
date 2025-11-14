#include <iostream>
using namespace std;

string bubbleSort(string str) {
    int len = str.length();
    bool swapped;
    for (int i = 0; i < len-1; i++) {
        swapped = false;
        for (int j = 0; j < len-1; j++) {
            if (str[j] > str[j + 1]) {
                swap(str[j], str[j + 1]);
				swapped = true;
            }
        }
        if (!swapped) break;
    }
    return str;
}

void anagramCheck(string s1, string s2) {
    if (s1.length() != s2.length()) {
        cout << "Not anagrams" << endl;
        return;
    }
    for (int i = 0; i < s1.length(); i++) {
        s1[i] = tolower(s1[i]);
        s2[i] = tolower(s2[i]);
    }
    string sorted1 = bubbleSort(s1);
    string sorted2 = bubbleSort(s2);
    if (sorted1 == sorted2)
        cout << s1 << " and " << s2 << " are anagrams" << endl;
    else cout << s1 << " and " << s2 << " are not anagrams" << endl;
}

int main()
{
    string w1, w2;
    cout << "Enter a word: ";
    cin >> w1;
    cout << "Enter another word: ";
    cin >> w2;
    anagramCheck(w1, w2);
}
