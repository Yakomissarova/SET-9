#include <bits/stdc++.h>
using namespace std;

int charAt(const string& s, int d) {
    if (d < (int)s.size()) return (unsigned char)s[d];
    return -1;
}

void stringQuickSort(vector<string>& arr, int lo, int hi, int d) {
    if (lo >= hi) return;

    int mid = lo + (hi - lo) / 2;
    if (charAt(arr[mid], d) < charAt(arr[lo], d)) swap(arr[lo], arr[mid]);
    if (charAt(arr[hi], d) < charAt(arr[lo], d)) swap(arr[lo], arr[hi]);
    if (charAt(arr[mid], d) < charAt(arr[hi], d)) swap(arr[mid], arr[hi]);

    int pivot = charAt(arr[lo], d);

    int lt = lo, gt = hi;
    int i = lo + 1;

    while (i <= gt) {
        int c = charAt(arr[i], d);
        if (c < pivot) {
            swap(arr[lt], arr[i]);
            lt++;
            i++;
        } else if (c > pivot) {
            swap(arr[i], arr[gt]);
            gt--;
        } else {
            i++;
        }
    }

    stringQuickSort(arr, lo, lt - 1, d);
    if (pivot >= 0) {
        stringQuickSort(arr, lt, gt, d + 1);
    }

    stringQuickSort(arr, gt + 1, hi, d);
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

    stringQuickSort(arr, 0, n - 1, 0);

    for (int i = 0; i < n; i++) {
        cout << arr[i] << "\n";
    }

    return 0;
}