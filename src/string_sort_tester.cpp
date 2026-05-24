#include "string_sort_tester.h"
#include "string_generator.h"

#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

SortResult StringSortTester::measure(
        const string& name,
        function<void(vector<string>&, CharCmpCount&)> sortFn,
        const vector<string>& arr,
        const string& arrayType)
{
    double totalTime = 0.0;
    int64_t totalCmp = 0;

    for (int r = 0; r < REPEATS; r++) {
        vector<string> tmp = arr;
        CharCmpCount cmp = 0;

        auto start = high_resolution_clock::now();
        sortFn(tmp, cmp);
        auto end = high_resolution_clock::now();

        totalTime += duration_cast<microseconds>(end - start).count();
        totalCmp  += cmp;
    }

    SortResult res;
    res.algorithmName = name;
    res.arrayType     = arrayType;
    res.arraySize     = (int)arr.size();
    res.timeUs        = totalTime / REPEATS;
    res.charCmp       = totalCmp  / REPEATS;
    return res;
}

vector<SortResult> StringSortTester::runAll(
        const vector<string>& baseRandom,
        const vector<string>& baseReverse,
        const vector<string>& baseNearlySorted)
{
    // все алгоритмы с именами
    vector<pair<string, function<void(vector<string>&, CharCmpCount&)>>> algos = {
            {"StdMergeSort",      stdMergeSort},
            {"StdQuickSort",      stdQuickSort},
            {"StringMergeSort",   stringMergeSort},
            {"StringQuickSort",   stringQuickSort},
            {"MsdRadixSort",      msdRadixSort},
            {"MsdRadixSortHybrid",msdRadixSortHybrid},
    };

    // базовые массивы с именами
    vector<pair<string, const vector<string>*>> bases = {
            {"random",        &baseRandom},
            {"reverse",       &baseReverse},
            {"nearly_sorted", &baseNearlySorted},
    };

    vector<SortResult> results;

    for (int size = StringGenerator::MIN_SIZE;
         size <= StringGenerator::MAX_SIZE;
         size += StringGenerator::STEP)
    {
        cout << "size=" << size << "..." << flush;

        for (auto& [typeName, base] : bases) {
            // срез нужного размера из базового массива
            vector<string> slice(base->begin(), base->begin() + size);

            for (auto& [algoName, fn] : algos) {
                SortResult r = measure(algoName, fn, slice, typeName);
                results.push_back(r);
            }
        }
        cout << " done\n";
    }

    return results;
}