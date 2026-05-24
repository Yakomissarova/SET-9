#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    getline(cin, s);
    unordered_map<string, int> table;
    for (int i = 0; i < 128; i++)
        table[string(1, (char)i)] = i;
    int next_code = 128;

    vector<int> result;
    string w = "";

    for (char c : s) {
        string wc = w + c;
        if (table.count(wc)) {
            w = wc;
        } else {
            result.push_back(table[w]);
            table[wc] = next_code++;
            w = string(1, c);
        }
    }

    if (!w.empty())
        result.push_back(table[w]);

    cout << result.size() << "\n";
    for (int i = 0; i < (int)result.size(); i++) {
        if (i) cout << " ";
        cout << result[i];
    }
    cout << "\n";

    return 0;
}