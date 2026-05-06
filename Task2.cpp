#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <cstdint> // Библиотека для uint64_t

using namespace std;

// 1. Решето Эратосфена для получения простых чисел до 500
vector<uint64_t> sieveOfEratosthenes(uint64_t n) {
    vector<bool> prime(n + 1, true);
    for (uint64_t p = 2; p * p <= n; p++) {
        if (prime[p]) {
            for (uint64_t i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }
    vector<uint64_t> result;
    for (uint64_t p = 2; p <= n; p++) {
        if (prime[p]) result.push_back(p);
    }
    return result;
}

// Вспомогательная функция для быстрого возведения в степень по модулю (a^b mod n)
uint64_t power(uint64_t a, uint64_t b, uint64_t n) {
    uint64_t res = 1;
    a %= n;
    while (b > 0) {
        if (b % 2 == 1) res = (__uint128_t)res * a % n;
        a = (__uint128_t)a * a % n;
        b /= 2;
    }
    return res;
}

// 2. Процедура генерации простого числа по ГОСТ Р.34.10-94
// Для простоты примера используем uint64_t, что ограничивает разрядность (bits)
uint64_t generatePrime(int t, uint64_t q, int &rejected) {
    while (true) {
        double xi = (double)rand() / RAND_MAX; // Случайное число от 0 до 1
        
        // Вычисляем N по формуле из ГОСТ
        uint64_t N = (uint64_t)(pow(2, t - 1) / q) + (uint64_t)((pow(2, t - 1) * xi) / q);
        
        if (N % 2 != 0) N++; // Если N нечетное, делаем четным (N := N + 1)

        for (uint64_t u = 0; ; u += 2) {
            uint64_t p = (N + u) * q + 1; // Кандидат p

            // Если вышли за границы разрядности, возвращаемся к генерации xi
            if (p > pow(2, t)) break;

            // Условие теоремы Диемитко (Шаг 6)
            // a^(p-1) = 1 (mod p) и a^(N+u) != 1 (mod p) при a=2
            if (power(2, p - 1, p) == 1 && power(2, N + u, p) != 1) {
                return p; // Число достоверно простое
            }
            
            rejected++; // Число отвергнуто
        }
    }
}

int main() {
    srand(time(0));
    setlocale(LC_ALL, "Russian");

    int bits;
    cout << "Введите требуемую разрядность: ";
    cin >> bits;

    // Шаг 1: Таблица малых простых чисел
    vector<uint64_t> smallPrimes = sieveOfEratosthenes(500);

    // Подбираем q для ГОСТ (разрядность [t/2])
    // Для простоты возьмем простое число из решета, подходящее по разрядности
    uint64_t q = 0;
    int targetQBits = (bits + 1) / 2;
    for (uint64_t p : smallPrimes) {
        if (p >= pow(2, targetQBits - 1) && p < pow(2, targetQBits)) {
            q = p;
            break;
        }
    }

    if (q == 0) {
        cout << "Не удалось подобрать q для такой разрядности." << endl;
        return 1;
    }

    // Вывод таблицы (Шаги 3-6)
    cout << "\nРезультаты выполнения тестов:\n";
    cout << "--------------------------------------------------------------------------------------\n";
    cout << left << setw(15) << "№" << " | ";
    for (int i = 1; i <= 10; i++) cout << setw(7) << i;
    cout << "\n--------------------------------------------------------------------------------------\n";

    vector<uint64_t> results;
    vector<int> rejectedCounts;

    for (int i = 0; i < 10; i++) {
        int rejected = 0;
        uint64_t p = generatePrime(bits, q, rejected);
        results.push_back(p);
        rejectedCounts.push_back(rejected);
    }

    cout << left << setw(15) << "Простое число" << " | ";
    for (auto val : results) cout << setw(7) << val;
    cout << endl;

    cout << left << setw(17) << "Тест" << " | ";
    for (int i = 0; i < 10; i++) cout << setw(7) << "T";
    cout << endl;

    cout << left << setw(13) << "Rejected" << " | ";
    for (auto val : rejectedCounts) cout << setw(7) << val;
    cout << "\n--------------------------------------------------------------------------------------\n";

    return 0;
}