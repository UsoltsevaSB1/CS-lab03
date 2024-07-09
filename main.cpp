#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<double> input_numbers(size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}

void find_minmax(const vector<double>& numbers, double& max, double& min) {
    max = numbers[0];
    min = numbers[0];
    for (auto number: numbers) {
        if (number > max) {
            max = number;
        }
        if (number < min) {
            min = number;
        }
    }
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


void
svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>\n";
}

/*void svg_rect(double x, double y, double width, double height) {
    cout << "<rect x='" << x << "' y='" << y << "' width='"
         << width << "' height='" << height << "'/>\n";
}*/
void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black"){
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height
         << "' stroke='" << stroke << "' fill='" << fill << "' />\n";
}

void
svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end() {
    cout << "</svg>\n";
}
void
show_histogram_svg(const vector<size_t>& bins) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    size_t max_count = 0;
    for (size_t bin : bins) {
        if (bin > max_count) {
            max_count = bin;
        }
    }
    double scaling_factor = 1.0;
    if ((max_count * BLOCK_WIDTH) > (IMAGE_WIDTH - TEXT_WIDTH)) {
        scaling_factor = (double)(IMAGE_WIDTH - TEXT_WIDTH) / (max_count * BLOCK_WIDTH);
    }
    svg_text(TEXT_LEFT, TEXT_BASELINE, to_string(bins[0]));
    //svg_rect(TEXT_WIDTH, 0, bins[0] * BLOCK_WIDTH, BIN_HEIGHT);
    svg_rect(0, 0, 100, 200, "blue", "#aaffaa");
    double top = 0;
    for (size_t bin : bins) {
        const double bin_width = BLOCK_WIDTH * bin;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width * scaling_factor, BIN_HEIGHT);
        top += BIN_HEIGHT;
       }
     svg_end();
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
