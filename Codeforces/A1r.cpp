#include <bits/stdc++.h>
using namespace std;

int charAt(const string& s, int d) {
    if (d < (int)s.size()) return (unsigned char)s[d];
    return -1;
}

void msdRadixSort(vector<string>& arr, vector<string>& aux, int lo, int hi, int d) {
    if (lo >= hi) return;

    const int R = 258;

    vector<int> count(R, 0);

    for (int i = lo; i <= hi; i++) {
        int c = charAt(arr[i], d);
        count[c + 2]++;
    }

    for (int r = 0; r < R - 1; r++) {
        count[r + 1] += count[r];
    }

    for (int i = lo; i <= hi; i++) {
        int c = charAt(arr[i], d);
        aux[count[c + 1]] = arr[i];
        count[c + 1]++;
    }

    for (int i = lo; i <= hi; i++) {
        arr[i] = aux[i - lo];
    }
    for (int r = 0; r < 256; r++) {
        int bucketLo = lo + count[r + 1];
        int bucketHi = lo + count[r + 2] - 1;
        msdRadixSort(arr, aux, bucketLo, bucketHi, d + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    if (n == 0) return 0;

    vector<string> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    vector<string> aux(n);
    msdRadixSort(arr, aux, 0, n - 1, 0);

    for (int i = 0; i < n; i++) {
        cout << arr[i] << "\n";
    }

    return 0;
}