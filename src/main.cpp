#include "string_generator.h"
#include "string_sort_tester.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    cout << "Generating base arrays..." << endl;

    StringGenerator gen(42);

    // генерируем три базовых массива по 3000 строк
    // из них тестер будет брать срезы нужного размера
    auto baseRandom  = gen.generateBase(ArrayType::RANDOM);
    auto baseReverse = gen.generateBase(ArrayType::REVERSE_SORTED);
    auto baseNearly  = gen.generateBase(ArrayType::NEARLY_SORTED);

    cout << "Running experiments..." << endl;

    StringSortTester tester;
    auto results = tester.runAll(baseRandom, baseReverse, baseNearly);

    // пишем результаты в CSV
    const string filename = "../results/results.csv";
    ofstream out(filename);
    if (!out.is_open()) {
        cerr << "Failed to open " << filename << endl;
        return 1;
    }

    // заголовок
    out << "algorithm,array_type,array_size,time_us,char_cmp\n";

    for (auto& r : results) {
        out << r.algorithmName << ","
            << r.arrayType     << ","
            << r.arraySize     << ","
            << r.timeUs        << ","
            << r.charCmp       << "\n";
    }

    out.close();
    cout << "Done! Results written to " << filename << endl;
    cout << "Total rows: " << results.size() << endl;

    return 0;
}