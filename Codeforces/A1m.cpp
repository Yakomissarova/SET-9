#include <bits/stdc++.h>
using namespace std;

int lcpCompare(const string& a, const string& b, int& lcp) {
    int minLen = min(a.size(), b.size());
    while (lcp < minLen && a[lcp] == b[lcp]) {
        lcp++;
    }
    if (lcp == minLen) {
        if (a.size() == b.size()) return 0;
        return a.size() < b.size() ? -1 : 1;
    }
    return a[lcp] < b[lcp] ? -1 : 1;
}
void merge(vector<string>& arr, vector<int>& lcpArr,
           int left, int mid, int right) {
    // копируем левую и правую части
    vector<string> L(arr.begin() + left, arr.begin() + mid + 1);
    vector<string> R(arr.begin() + mid + 1, arr.begin() + right + 1);

    vector<int> lcpL(L.size(), 0);
    vector<int> lcpR(R.size(), 0);
    for (int i = 0; i + 1 < (int)L.size(); i++)
        lcpL[i] = lcpArr[left + i];
    for (int i = 0; i + 1 < (int)R.size(); i++)
        lcpR[i] = lcpArr[mid + 1 + i];

    int i = 0, j = 0, k = left;


    int curLcp = 0;

    while (i < (int)L.size() && j < (int)R.size()) {
        int lcp = curLcp;
        int cmp = lcpCompare(L[i], R[j], lcp);

        if (cmp <= 0) {
            arr[k] = L[i];


            int prevLcp = lcp;
            if (i + 1 < (int)L.size()) {
                if (lcpL[i] > prevLcp) {
                    curLcp = prevLcp;
                } else if (lcpL[i] < prevLcp) {
                    curLcp = lcpL[i];
                } else {
                    curLcp = lcpL[i];
                }
            }
            i++;
        } else {
            arr[k] = R[j];

            int prevLcp = lcp;
            if (j + 1 < (int)R.size()) {
                if (lcpR[j] > prevLcp) {
                    curLcp = prevLcp;
                } else if (lcpR[j] < prevLcp) {
                    curLcp = lcpR[j];
                } else {
                    curLcp = lcpR[j];
                }
            }
            j++;
        }
        k++;
    }

    while (i < (int)L.size()) {
        arr[k++] = L[i++];
    }
    while (j < (int)R.size()) {
        arr[k++] = R[j++];
    }

    for (int p = left; p < right; p++) {
        int l = 0;
        lcpCompare(arr[p], arr[p + 1], l);
        lcpArr[p] = l;
    }
}

void mergeSort(vector<string>& arr, vector<int>& lcpArr, int left, int right) {
    if (left >= right) return;

    int mid = (left + right) / 2;
    mergeSort(arr, lcpArr, left, mid);
    mergeSort(arr, lcpArr, mid + 1, right);
    merge(arr, lcpArr, left, mid, right);
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

    vector<int> lcpArr(n, 0);

    mergeSort(arr, lcpArr, 0, n - 1);

    for (int i = 0; i < n; i++) {
        cout << arr[i] << "\n";
    }

    return 0;
}