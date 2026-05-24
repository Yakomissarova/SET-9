#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;
    vector<int> codes(k);
    for (int i = 0; i < k; i++)
        cin >> codes[i];

    unordered_map<int, string> table;
    for (int i = 0; i < 128; i++)
        table[i] = string(1, (char)i);
    int next_code = 128;

    string result = "";
    string prev = table[codes[0]];
    result += prev;

    for (int i = 1; i < k; i++) {
        int code = codes[i];
        string entry;
        if (table.count(code)) {
            entry = table[code];
        } else {
            entry = prev + prev[0];
        }

        result += entry;
        table[next_code++] = prev + entry[0];
        prev = entry;
    }

    cout << result << "\n";

    return 0;
}