#include "sorts.h"
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

static int charAt(const string& s, int d) {
    if (d < (int)s.size()) return (unsigned char)s[d];
    return -1;
}

static int lcpCompare(const string& a, const string& b, int& lcp, CharCmpCount& cmp) {
    int minLen = min(a.size(), b.size());
    while (lcp < minLen && a[lcp] == b[lcp]) {
        cmp++;
        lcp++;
    }
    if (lcp < minLen) cmp++;
    if (lcp == minLen) {
        if (a.size() == b.size()) return 0;
        return a.size() < b.size() ? -1 : 1;
    }
    return a[lcp] < b[lcp] ? -1 : 1;
}


// СТАНДАРТНЫЙ MERGESORT
static int stdCompare(const string& a, const string& b, CharCmpCount& cmp) {
    int minLen = min(a.size(), b.size());
    for (int i = 0; i < minLen; i++) {
        cmp++;
        if (a[i] != b[i]) return a[i] < b[i] ? -1 : 1;
    }
    if (a.size() == b.size()) return 0;
    return a.size() < b.size() ? -1 : 1;
}

static void stdMerge(vector<string>& arr, int lo, int mid, int hi, CharCmpCount& cmp) {
    vector<string> L(arr.begin() + lo, arr.begin() + mid + 1);
    vector<string> R(arr.begin() + mid + 1, arr.begin() + hi + 1);

    int i = 0, j = 0, k = lo;
    while (i < (int)L.size() && j < (int)R.size()) {
        if (stdCompare(L[i], R[j], cmp) <= 0)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < (int)L.size()) arr[k++] = L[i++];
    while (j < (int)R.size()) arr[k++] = R[j++];
}

static void stdMergeSortHelper(vector<string>& arr, int lo, int hi,CharCmpCount& cmp) {
    if (lo >= hi) return;
    int mid = (lo + hi) / 2;
    stdMergeSortHelper(arr, lo, mid, cmp);
    stdMergeSortHelper(arr, mid + 1, hi, cmp);
    stdMerge(arr, lo, mid, hi, cmp);
}

void stdMergeSort(vector<string>& arr, CharCmpCount& cmp) {
    if (arr.empty()) return;
    stdMergeSortHelper(arr, 0, (int)arr.size() - 1, cmp);
}


// СТАНДАРТНЫЙ QUICKSORT
static void stdQuickSortHelper(vector<string>& arr, int lo, int hi,CharCmpCount& cmp) {
    if (lo >= hi) return;
    int lt = lo, gt = hi;
    string pivot = arr[lo];
    int i = lo + 1;

    while (i <= gt) {
        int c = stdCompare(arr[i], pivot, cmp);
        if (c < 0)       swap(arr[lt++], arr[i++]);
        else if (c > 0)  swap(arr[i], arr[gt--]);
        else             i++;
    }
    stdQuickSortHelper(arr, lo, lt - 1, cmp);
    stdQuickSortHelper(arr, gt + 1, hi, cmp);
}

void stdQuickSort(vector<string>& arr, CharCmpCount& cmp) {
    if (arr.empty()) return;
    stdQuickSortHelper(arr, 0, (int)arr.size() - 1, cmp);
}


// STRING MERGESORT С LCP
static void stringMerge(vector<string>& arr, vector<int>& lcpArr, int left, int mid, int right, CharCmpCount& cmp) {
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
        int res = lcpCompare(L[i], R[j], lcp, cmp);

        if (res <= 0) {
            arr[k] = L[i];
            int prevLcp = lcp;
            if (i + 1 < (int)L.size()) {
                if (lcpL[i] > prevLcp)      curLcp = prevLcp;
                else if (lcpL[i] < prevLcp) curLcp = lcpL[i];
                else                        curLcp = lcpL[i];
            }
            i++;
        } else {
            arr[k] = R[j];
            int prevLcp = lcp;
            if (j + 1 < (int)R.size()) {
                if (lcpR[j] > prevLcp)      curLcp = prevLcp;
                else if (lcpR[j] < prevLcp) curLcp = lcpR[j];
                else                        curLcp = lcpR[j];
            }
            j++;
        }
        k++;
    }
    while (i < (int)L.size()) arr[k++] = L[i++];
    while (j < (int)R.size()) arr[k++] = R[j++];

    for (int p = left; p < right; p++) {
        int l = 0;
        lcpCompare(arr[p], arr[p + 1], l, cmp);
        lcpArr[p] = l;
    }
}

static void stringMergeSortHelper(vector<string>& arr, vector<int>& lcpArr, int left, int right, CharCmpCount& cmp) {
    if (left >= right) return;
    int mid = (left + right) / 2;
    stringMergeSortHelper(arr, lcpArr, left, mid, cmp);
    stringMergeSortHelper(arr, lcpArr, mid + 1, right, cmp);
    stringMerge(arr, lcpArr, left, mid, right, cmp);
}

void stringMergeSort(vector<string>& arr, CharCmpCount& cmp) {
    if (arr.empty()) return;
    int n = (int)arr.size();
    vector<int> lcpArr(n, 0);
    stringMergeSortHelper(arr, lcpArr, 0, n - 1, cmp);
}


// TERNARY STRING QUICKSORT
static void stringQuickSortHelper(vector<string>& arr, int lo, int hi, int d, CharCmpCount& cmp) {
    if (lo >= hi) return;

    int pivot = charAt(arr[lo], d);

    int lt = lo, gt = hi;
    int i = lo + 1;

    while (i <= gt) {
        cmp++;
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

    stringQuickSortHelper(arr, lo, lt - 1, d, cmp);
    if (pivot >= 0) {
        stringQuickSortHelper(arr, lt, gt, d + 1, cmp);
    }
    stringQuickSortHelper(arr, gt + 1, hi, d, cmp);
}

void stringQuickSort(vector<string>& arr, CharCmpCount& cmp) {
    if (arr.empty()) return;
    stringQuickSortHelper(arr, 0, (int)arr.size() - 1, 0, cmp);
}


// MSD RADIX SORT без переключения
static void msdRadixSortHelper(vector<string>& arr, vector<string>& aux, int lo, int hi, int d, CharCmpCount& cmp) {
    if (lo >= hi) return;

    const int R = 258;
    vector<int> count(R, 0);

    for (int i = lo; i <= hi; i++) {
        cmp++;
        int c = charAt(arr[i], d);
        count[c + 2]++;
    }

    for (int r = 0; r < R - 1; r++)
        count[r + 1] += count[r];

    for (int i = lo; i <= hi; i++) {
        int c = charAt(arr[i], d);
        aux[count[c + 1]] = arr[i];
        count[c + 1]++;
    }

    for (int i = lo; i <= hi; i++)
        arr[i] = aux[i - lo];

    for (int r = 0; r < 256; r++) {
        int bucketLo = lo + count[r + 1];
        int bucketHi = lo + count[r + 2] - 1;
        msdRadixSortHelper(arr, aux, bucketLo, bucketHi, d + 1, cmp);
    }
}

void msdRadixSort(vector<string>& arr, CharCmpCount& cmp) {
    if (arr.empty()) return;
    vector<string> aux(arr.size());
    msdRadixSortHelper(arr, aux, 0, (int)arr.size() - 1, 0, cmp);
}


// MSD RADIX SORT + QUICK SORT
static void msdRadixSortHybridHelper(vector<string>& arr, vector<string>& aux, int lo, int hi, int d, CharCmpCount& cmp) {
    if (lo >= hi) return;

    if (hi - lo + 1 < 74) {
        stringQuickSortHelper(arr, lo, hi, d, cmp);
        return;
    }

    const int R = 258;
    vector<int> count(R, 0);

    for (int i = lo; i <= hi; i++) {
        cmp++;
        int c = charAt(arr[i], d);
        count[c + 2]++;
    }

    for (int r = 0; r < R - 1; r++)
        count[r + 1] += count[r];

    for (int i = lo; i <= hi; i++) {
        int c = charAt(arr[i], d);
        aux[count[c + 1]] = arr[i];
        count[c + 1]++;
    }

    for (int i = lo; i <= hi; i++)
        arr[i] = aux[i - lo];

    for (int r = 0; r < 256; r++) {
        int bucketLo = lo + count[r + 1];
        int bucketHi = lo + count[r + 2] - 1;
        msdRadixSortHybridHelper(arr, aux, bucketLo, bucketHi, d + 1, cmp);
    }
}

void msdRadixSortHybrid(vector<string>& arr, CharCmpCount& cmp) {
    if (arr.empty()) return;
    vector<string> aux(arr.size());
    msdRadixSortHybridHelper(arr, aux, 0, (int)arr.size() - 1, 0, cmp);
}