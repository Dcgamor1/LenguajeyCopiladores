#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
using namespace std;

// Criba tradicional para obtener primos base
vector<int> cribaBase(int limite)
{
    vector<bool> esPrimo((size_t)limite + 1, true);
    vector<int> primos;
    esPrimo[0] = esPrimo[1] = false;

    for (int i = 2; i * i <= limite; i++)
    {
        if (esPrimo[i])
        {
            for (int j = i * i; j <= limite; j += i)
                esPrimo[j] = false;
        }
    }

    for (int i = 2; i <= limite; i++)
        if (esPrimo[i])
            primos.push_back(i);

    return primos;
}

// Criba segmentada
long long contarPrimos(long long n)
{
    long long limite = sqrt(n);
    vector<int> primos = cribaBase((int)limite);

    long long inicio = limite;
    long long fin = 2 * limite;

    long long total = primos.size();

    while (inicio < n)
    {
        if (fin > n)
            fin = n;

        vector<bool> esPrimo((size_t)(fin - inicio + 1), true);

        for (int p : primos)
        {
            long long base = (inicio / p) * p;
            if (base < inicio)
                base += p;
            for (long long j = base; j <= fin; j += p)
                esPrimo[(size_t)(j - inicio)] = false;
        }

        for (long long i = inicio; i <= fin; i++)
            if (esPrimo[(size_t)(i - inicio)])
                total++;

        inicio = fin + 1;
        fin = inicio + limite;
    }

    return total;
}

int main()
{
    long long n = 20000000; // 20 millones
    auto inicio = chrono::high_resolution_clock::now();

    long long total = contarPrimos(n);

    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double> tiempo = fin - inicio;

    cout << "Total de primos <= " << n << ": " << total << endl;
    cout << "Tiempo: " << tiempo.count() << " segundos\n";

    return 0;
}
