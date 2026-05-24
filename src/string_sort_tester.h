#ifndef SET_9_STRING_SORT_TESTER_H
#define SET_9_STRING_SORT_TESTER_H


#include "sorts.h"
#include <string>
#include <vector>
#include <functional>

struct SortResult {
    std::string algorithmName;
    std::string arrayType;
    int         arraySize;
    double      timeUs;      // ср. время в микросекундах
    int64_t     charCmp;     // ср. число посимвольных сравнений
};

class StringSortTester {
public:
    // кол-во попыток для усреднения
    static const int REPEATS = 10;

    SortResult measure(
            const std::string& name,
            std::function<void(std::vector<std::string>&, CharCmpCount&)> sortFn,
            const std::vector<std::string>& arr,
            const std::string& arrayType
    );

    std::vector<SortResult> runAll(
            const std::vector<std::string>& baseRandom,
            const std::vector<std::string>& baseReverse,
            const std::vector<std::string>& baseNearlySorted
    );
};


#endif //SET_9_STRING_SORT_TESTER_H
