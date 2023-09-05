#include <iostream>
#include <thread>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

double pi = 0.0;
int n;
int num_threads;

void calc_pi(int thread_id) {
    double local_sum = 0.0;
    int start = thread_id * (n / num_threads);
    int end = start + (n / num_threads);
    for (int i = start; i < end; i++) {
        if (i % 2 == 0) {
            local_sum += 1.0 / (2 * i + 1);
        } else {
            local_sum -= 1.0 / (2 * i + 1);
        }
    }
    pi += local_sum;
}

int main() {
    cout << "Ingrese el número de hilos: ";
    cin >> num_threads;
    cout << "Ingrese el número n (cantidad de ciclos): ";
    cin >> n;

    vector<thread> threads;
    for (int i = 0; i < num_threads; i++) {
        threads.push_back(thread(calc_pi, i));
    }

    for (auto &t : threads) {
        t.join();
    }

    pi *= 4;
    std::cout << std::fixed << std::setprecision(20);
    cout << "El valor aproximado de π es: " << pi << endl;
    return 0;
}
