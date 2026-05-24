#ifndef SET_9_SORTS_H
#define SET_9_SORTS_H

#include <string>
#include <vector>
#include <cstdint>

using CharCmpCount = int64_t;

void stdMergeSort(std::vector<std::string>& arr, CharCmpCount& cmp);

void stdQuickSort(std::vector<std::string>& arr, CharCmpCount& cmp);

void stringMergeSort(std::vector<std::string>& arr, CharCmpCount& cmp);

void stringQuickSort(std::vector<std::string>& arr, CharCmpCount& cmp);

void msdRadixSort(std::vector<std::string>& arr, CharCmpCount& cmp);

void msdRadixSortHybrid(std::vector<std::string>& arr, CharCmpCount& cmp);


#endif //SET_9_SORTS_H
