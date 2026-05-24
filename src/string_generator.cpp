#include "string_generator.h"

#include <algorithm>
#include <stdexcept>

const char StringGenerator::ALPHABET[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
        "0123456789!@#%:;^&*()-.";
const int StringGenerator::ALPHABET_SIZE = 74;

StringGenerator::StringGenerator()
        : seed_(42) {}

StringGenerator::StringGenerator(unsigned int seed)
        : seed_(seed) {}

// LCG рандом
static unsigned int lcg(unsigned int& seed) {
    seed = seed * 1664525u + 1013904223u;
    return seed;
}

std::string StringGenerator::randomString(int len) const {
    std::string s(len, ' ');
    for (int i = 0; i < len; i++) {
        s[i] = ALPHABET[lcg(seed_) % ALPHABET_SIZE];
    }
    return s;
}

void StringGenerator::shuffle(std::vector<std::string>& arr) const {
    int n = (int)arr.size();
    for (int i = n - 1; i > 0; i--) {
        int j = lcg(seed_) % (i + 1);
        std::swap(arr[i], arr[j]);
    }
}

void StringGenerator::makeNearlySorted(std::vector<std::string>& arr) const {
    std::sort(arr.begin(), arr.end());

    // делаем ~5% случайных свопов от размера массива
    int n = (int)arr.size();
    int swaps = std::max(5, (n / 100)*5);

    for (int k = 0; k < swaps; k++) {
        int i = lcg(seed_) % n;
        int j = lcg(seed_) % n;
        std::swap(arr[i], arr[j]);
    }
}

std::vector<std::string> StringGenerator::generate(int count, ArrayType type) const {
    if (count < 0 || count > MAX_SIZE) {
        throw std::invalid_argument("count must be in [0, MAX_SIZE]");
    }

    // генерируем count строк случайной длины
    std::vector<std::string> arr(count);
    for (int i = 0; i < count; i++) {
        int len = MIN_LEN + lcg(seed_) % (MAX_LEN - MIN_LEN + 1);
        arr[i] = randomString(len);
    }

    switch (type) {
        case ArrayType::RANDOM:
            shuffle(arr);
            break;
        case ArrayType::SORTED:
            std::sort(arr.begin(), arr.end());
            break;
        case ArrayType::REVERSE_SORTED:
            std::sort(arr.begin(), arr.end(), std::greater<std::string>());
            break;
        case ArrayType::NEARLY_SORTED:
            makeNearlySorted(arr);
            break;
    }

    return arr;
}

std::vector<std::string> StringGenerator::generateWithPrefix( int count, ArrayType type, int prefixLen) const {

    if (prefixLen < 0 || prefixLen >= MIN_LEN) {
        throw std::invalid_argument("prefixLen must be in [0, MIN_LEN)");
    }

    // общий префикс
    std::string prefix = randomString(prefixLen);

    std::vector<std::string> arr(count);
    for (int i = 0; i < count; i++) {
        // оставшаяся часть случайная
        int remainLen = MIN_LEN + lcg(seed_) % (MAX_LEN - MIN_LEN + 1) - prefixLen;
        if (remainLen < 1) remainLen = 1;
        arr[i] = prefix + randomString(remainLen);
    }

    switch (type) {
        case ArrayType::RANDOM:
            shuffle(arr);
            break;
        case ArrayType::SORTED:
            std::sort(arr.begin(), arr.end());
            break;
        case ArrayType::REVERSE_SORTED:
            std::sort(arr.begin(), arr.end(), std::greater<std::string>());
            break;
        case ArrayType::NEARLY_SORTED:
            makeNearlySorted(arr);
            break;
    }

    return arr;
}

std::vector<std::string> StringGenerator::generateBase(ArrayType type) const {
    return generate(MAX_SIZE, type);
}