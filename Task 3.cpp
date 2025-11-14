#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Node {
public:
    string key;
    Node* left;
    Node* right;
    int height;

    Node(string k) {
        key = k;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class avlTree {
    Node* root;

    int getHeight(Node* n) {
        if (n == nullptr) return 0;
        return n->height;
    }

    int getBalance(Node* n) {
        if (n == nullptr) return 0;
        return getHeight(n->left) - getHeight(n->right);
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* z = y->left;

        y->left = x;
        x->right = z;

        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        return y;
    }

    Node* rightRotate(Node* x) {
        Node* y = x->left;
        Node* z = y->right;

        y->right = x;
        x->left = z;

        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        return y;
    }

    Node* insert(Node* node, string key) {
        if (node==nullptr) return new Node(key);

        //finding location for new node
        if (key < node->key) node->left = insert(node->left, key);
        else if (key > node->key) node->right = insert(node->right, key);
        else return node;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int b = getBalance(node);

        //rotating subtrees to correct balance
        //LL
        if (b > 1 && key < node->left->key) return rightRotate(node);
        //RR
        if (b<-1 && key>node->right->key) return leftRotate(node);
        //LR
        if (b > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        //RL
        if (b < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    void findMatches(Node* node, string prefix, vector<string>& suggestions) {
        if (!node) return;

        if (node->key.compare(0, prefix.length(), prefix) >= 0)
            findMatches(node->left, prefix, suggestions);

        if (node->key.compare(0, prefix.length(), prefix) == 0)
            suggestions.push_back(node->key);

        if (node->key.compare(0, prefix.length(), prefix) <= 0)
            findMatches(node->right, prefix, suggestions);
        
    }

public:
    avlTree() {
        root = nullptr;
    }

    void insert(string key) {
        root = insert(root, key);
    }

    vector<string> findAllWithPrefix(string prefix) {
        vector<string> suggestions;

        findMatches(root, prefix, suggestions);
        return suggestions;
    }
};

int main()
{
    avlTree t;

    ifstream dict("dictionary.txt");
    string word, prefix;
    char input;

    while (dict >> word) {
        if (word == "" || word == " ") continue;
        t.insert(word);
    }


    cout << "Enter letter (- to exit): ";
    cin >> input;

    while (input!= '-') {
		prefix += input;
		cout << "Current prefix: " << prefix << endl;

        vector<string> suggestions = t.findAllWithPrefix(prefix);
        
        if (suggestions.empty()) {
            cout << "No matches found" << endl;
            break;
        }
        else {
            cout << "Suggestions: " << endl;
            for (string w : suggestions) {
                cout << w << endl;
            }
			cout << endl;
        }
        cout << "Enter letter (- to exit): ";
        cin >> input;
    }
}
