#include "histogram.h"

#include <cassert>

void
test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 4);
}
void test_negative() {
    double min = 0;
    double max = 0;
    find_minmax({-1, -2, -3}, min, max);
    assert(min == -3);
    assert(max == -1);
}

void test_same() {
    double min = 0;
    double max = 0;
    find_minmax({5, 5, 5}, min, max);
    assert(min == 5);
    assert(max == 5);
}

void test_one() {
    double min = 0;
    double max = 0;
    find_minmax({10}, min, max);
    assert(min == 10);
    assert(max == 10);
}

void test_empty() {
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    //  Проверка, что min и max не были изменены
    assert(min == 0);
    assert(max == 0);
}

int main() {
    test_positive();
    test_negative();
    test_same();
    test_one();
    test_empty();

}
