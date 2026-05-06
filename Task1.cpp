#include <iostream>
#include <cmath> // Для корня и логарифма
#include <iomanip> // Для красивого вывода таблицы

using namespace std;

int main() {
    double xStart = -7.5;
    double xEnd = 5.0;
    double dx = 0.5;

    cout << setw(10) << "x" << " | " << setw(10) << "y" << endl;
    cout << "---------------------------" << endl;

    for (double x = xStart; x <= xEnd; x += dx) {
        double y;

        if (x <= -6) {
            // Линия: y = -2x - 14
            y = -2 * x - 14;
        } 
        else if (x > -6 && x <= -2) {
            // Полуокружность R=2 с центром (-4, -2): y = -2 + sqrt(4 - (x+4)^2)
            y = -2 + sqrt(4 - pow(x + 4, 2));
        } 
        else if (x > -2 && x <= 2) {
            // Логарифм: y = log2(x + 2)
            // В C++ log2(x) вычисляется через log(x)/log(2) или функцией log2()
            y = log2(x + 2);
        } 
        else if (x > 2 && x <= 4) {
            // Полуокружность R=1 с центром (3, 0): y = sqrt(1 - (x-3)^2)
            y = sqrt(1 - pow(x - 3, 2));
        } 
        else {
            // Прямая вдоль оси X: y = 0
            y = 0;
        }

        cout << setw(10) << fixed << setprecision(2) << x << " | " 
             << setw(10) << y << endl;
    }

    return 0;
}