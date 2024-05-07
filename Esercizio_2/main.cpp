#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <sstream>
#include "SortingAlgorithm.hpp" // Modifica per includere SortingAlgorithm.hpp

using namespace std;
using namespace SortLibrary;

// Funzione per generare vettori casuali con un certo numero di valori randomici all'inizio
// e il resto ordinato
template<typename T>
vector<T> generateRandomVectorWithOrderedTail(int size, int randomValuesAtStart) {
    vector<T> vec(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<T> dis(0, 100); // Modifica 100 se necessario per il tuo range di valori

    // Genera valori randomici all'inizio
    for (int i = 0; i < randomValuesAtStart; ++i) {
        vec[i] = dis(gen);
    }

    // Genera valori ordinati
    for (int i = randomValuesAtStart; i < size; ++i) {
        vec[i] = i;
    }

    // Mescola casualmente il vettore
    shuffle(vec.begin(), vec.end(), gen);

    return vec;
}

// Funzione per calcolare il tempo di esecuzione di un algoritmo di ordinamento
template<typename T>
double measureSortingTime(void (*sortingFunction)(vector<T>&), vector<T>& vec) {
    auto start = chrono::high_resolution_clock::now();
    sortingFunction(vec);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;
    return diff.count();
}

int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <vector_size>" << endl;
        return 1;
    }

    // Verifica se argv[1] è un numero intero
    istringstream iss(argv[1]);
    int vectorSize;
    if (!(iss >> vectorSize)) {
        cerr << "Invalid input. Please provide a valid integer as vector size." << endl;
        return 1;
    }

    // Eseguo l'analisi per valori randomici crescenti all'inizio
    cout << "Analisi delle prestazioni con valori casuali crescenti all'inizio:" << endl;
    for (int i = 3; i <= vectorSize; i += 3) {
        vector<int> vec = generateRandomVectorWithOrderedTail<int>(vectorSize, i);
        double bubbleSortTime = measureSortingTime<int>(BubbleSort, vec);
        double mergeSortTime = measureSortingTime<int>(MergeSort, vec);
        cout << "Valori casuali all'inizio: " << i << ", Tempo BubbleSort: " << bubbleSortTime << "s, Tempo MergeSort: " << mergeSortTime << "s" << endl;
    }

    // Eseguo l'analisi per vettori totalmente randomici
    cout << "\nAnalisi delle prestazioni con vettori completamente casuali:" << endl;
    vector<int> completelyRandomVector = generateRandomVectorWithOrderedTail<int>(vectorSize, 0);
    double bubbleSortTimeRandom = measureSortingTime<int>(BubbleSort, completelyRandomVector);
    double mergeSortTimeRandom = measureSortingTime<int>(MergeSort, completelyRandomVector);
    cout << "Tempo BubbleSort: " << bubbleSortTimeRandom << "s, Tempo MergeSort: " << mergeSortTimeRandom << "s" << endl;

    return 0;
}
