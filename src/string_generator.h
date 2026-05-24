#ifndef SET_9_STRING_GENERATOR_H
#define SET_9_STRING_GENERATOR_H


#include <string>
#include <vector>

enum class ArrayType {
    RANDOM,
    SORTED,
    REVERSE_SORTED,
    NEARLY_SORTED
};

class StringGenerator {
public:
    StringGenerator();
    explicit StringGenerator(unsigned int seed);

    // генерирует массив из count строк
    // длина каждой строки — случайная от MIN_LEN до MAX_LEN
    std::vector<std::string> generate(int count, ArrayType type) const;

    // строки начинаются с общего префикса
    std::vector<std::string> generateWithPrefix(int count, ArrayType type,
                                                int prefixLen) const;

    // генерирует базовый массив максимального размера
    std::vector<std::string> generateBase(ArrayType type) const;

    static const int MIN_LEN  = 10;
    static const int MAX_LEN  = 200;
    static const int MIN_SIZE = 100;
    static const int MAX_SIZE = 3000;
    static const int STEP     = 100;

private:
    mutable unsigned int seed_;

    // генерирует одну случайную строку длиной len
    std::string randomString(int len) const;

    // перемешивает массив
    void shuffle(std::vector<std::string>& arr) const;

    // делает массив почти отсортированным
    void makeNearlySorted(std::vector<std::string>& arr) const;

    static const char ALPHABET[];
    static const int  ALPHABET_SIZE;
};

#endif //SET_9_STRING_GENERATOR_H
