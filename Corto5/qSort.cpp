/**
 * 
 * Javier Mombiela
 * Carne: 20067
 * 
 * Progra Paralela Corto 5
*/

#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <iomanip>
#include <omp.h>

using namespace std;

int n;

void quicksortSecuencial(int* arr, int low, int high) {
  if (low < high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
      if (arr[j] < pivot) {
        i++;
        swap(arr[i], arr[j]);
      }
    }

    swap(arr[i + 1], arr[high]);

    int pi = i + 1;

    quicksortSecuencial(arr, low, pi - 1);
    quicksortSecuencial(arr, pi + 1, high);
  }
}

void quicksortParalelo(int* arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = low;

        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                swap(arr[i], arr[j]);
                i++;
            }
        }

        swap(arr[i], arr[high]);

        #pragma omp task
        {
            quicksortParalelo(arr, low, i - 1);
        }

        #pragma omp task
        {
            quicksortParalelo(arr, i + 1, high);
        }
    }
}


int main() {
    cout << "Ingrese cantidad de numeros: ";
    cin >> n;

    int* arrSec = new int[n];
    int* arrPar = new int[n];

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1000);

    for(int i = 0; i < n; i++) {
        arrSec[i] = dis(gen);
        arrPar[i] = arrSec[i];
    }

    ofstream file;
    file.open("numerosGenerados.csv");

    for(int i = 0; i < n - 1; i++) {
        file << arrSec[i] << ",";
    }
    file << arrSec[n - 1];  // El último número sin coma al final

    file.close();

    auto start = chrono::high_resolution_clock::now();
    quicksortSecuencial(arrSec, 0, n - 1);
    auto stop = chrono::high_resolution_clock::now();
    auto durationSec = chrono::duration_cast<chrono::duration<double>>(stop - start);

    cout << fixed << setprecision(4);
    cout << "Tiempo secuencial: " << durationSec.count() << " segundos" << endl;

    ofstream fileSec;
    fileSec.open("numerosOrdenadosSec.csv");
    for(int i = 0; i < n; i++) {
        fileSec << arrSec[i] << "\n";
    }
    fileSec.close();

    start = chrono::high_resolution_clock::now();
    #pragma omp parallel
    {
        #pragma omp single nowait
        quicksortParalelo(arrPar, 0, n - 1);
    }
    stop = chrono::high_resolution_clock::now();
    auto durationPar = chrono::duration_cast<chrono::duration<double>>(stop - start);

    cout << "Tiempo paralelo: " << durationPar.count() << " segundos" << endl;

    ofstream filePar;
    filePar.open("numerosOrdenadosPar.csv");
    for(int i = 0; i < n; i++) {
        filePar << arrPar[i] << "\n";
    }
    filePar.close();

    delete[] arrSec;
    delete[] arrPar;

    return 0;
}