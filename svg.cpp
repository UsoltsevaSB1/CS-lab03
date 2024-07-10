#include <iostream>
#include "svg.h"

void svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end() {
    cout << "</svg>\n";
}

void svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>\n";
}

void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black", double opacity = 1.0) {
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height
         << "' stroke='" << stroke << "' fill='" << fill << "' fill-opacity='" << opacity << "' />\n";
}
void show_histogram_svg(const vector<size_t>& bins) {
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

    double top = 0;
    for (size_t i = 0; i < bins.size(); ++i) {
        const double bin_width = BLOCK_WIDTH * bins[i];
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bins[i]));

        // ������������ ������������ � ����������� �� ������ �������
        double opacity = (double)bins[i] / max_count;

        svg_rect(TEXT_WIDTH, top, bin_width * scaling_factor, BIN_HEIGHT, "black", "black", opacity);

        top += BIN_HEIGHT;
    }

    svg_end();
}

