#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <map>
using namespace std;


struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f, Node* l = nullptr, Node* r = nullptr)
            : ch(c), freq(f), left(l), right(r) {}

    bool isLeaf() const { return !left && !right; }
};


//struct Cmp {
//    bool operator()(Node* a, Node* b) {
//        if (a->freq != b->freq) return a->freq > b->freq;
//        if (a->isLeaf() != b->isLeaf()) return !a->isLeaf();
//        if (a->isLeaf()) return a->ch > b->ch;
//        return false;
//    }
//};


Node* buildTrie(map<char, int>& freq) {
    priority_queue<Node *> pq;
    for (auto &[ch, f]: freq)
    {
        pq.push(new Node(ch, f));
    }
    while (pq.size() > 1) {
        Node* x = pq.top(); pq.pop();
        Node* y = pq.top(); pq.pop();
        pq.push(new Node('\0', x->freq + y->freq, x, y));
    }
    return pq.top();
}


void buildCodes(Node* node, const string& prefix,
                map<char,string>& codes) {
    if (!node) return;
    if (node->isLeaf()) {
        codes[node->ch] = prefix.empty() ? "0" : prefix;
        return;
    }
    buildCodes(node->left,  prefix + "0", codes);
    buildCodes(node->right, prefix + "1", codes);
}

void freeTrie(Node* n) {
    if (!n) return;
    freeTrie(n->left);
    freeTrie(n->right);
    delete n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    // Частоты
    map<char,int> freq;
    for (char c : s) freq[c]++;

    // Дерево
    Node* root = buildTrie(freq);

    // Коды
    map<char,string> codes;
    buildCodes(root, "", codes);

    // Закодированная строка
    string encoded;
    encoded.reserve(s.size() * 4);
    for (char c : s) encoded += codes[c];

    // Вывод
    cout << freq.size() << " " << encoded.size() << "\n";
    for (auto& [ch, code] : codes)
        cout << ch << ": " << code << "\n";
    cout << encoded << "\n";

    freeTrie(root);
    return 0;
}