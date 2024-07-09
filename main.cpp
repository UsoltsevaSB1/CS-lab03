#include <iostream>
#include <vector>
#include <string>
#include "histogram.h"
#include "svg.h"

using namespace std;

vector<double> input_numbers(size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}

// Функция для создания гистограммы
vector<size_t> make_histogram(const vector<double>& numbers, size_t bin_count) {
    double max, min;
    find_minmax(numbers, max, min);

    vector<size_t> bins(bin_count);
    for (double number : numbers) {
        size_t bin = (size_t)((number - min) / (max - min) * bin_count);
        if (bin == bin_count) {
            bin--;
        }
        bins[bin]++;
    }
    return bins;
}

int main() {
    // Ввод данных
    size_t number_count;
    //cerr << "Enter number count: ";
    cin >> number_count;

    //cerr << "Enter numbers: ";
    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    //cerr << "Enter column count: ";
    cin >> bin_count;

    // Создание и вывод гистограммы
    const auto bins = make_histogram(numbers, bin_count);
    //show_histogram_text(bins);
    show_histogram_svg(bins);
}
