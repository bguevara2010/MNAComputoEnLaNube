#include <iostream>
#include <omp.h>

#define N 10000000
#define chunk 1000
#define mostrar 10

void imprimeArreglo(float *d);

int main() {
    int i;

    // ===============================
    // MEMORIA DINÁMICA (HEAP)
    // ===============================
    float *a = new float[N];
    float *b = new float[N];
    float *c = new float[N];

    // Inicializar arreglos
    for (i = 0; i < N; i++) {
        a[i] = i * 10.0f;
        b[i] = (i + 3) * 3.7f;
    }

    // ===============================
    // SUMA SECUENCIAL
    // ===============================
    double inicio_seq = omp_get_wtime();
    for (i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }
    double fin_seq = omp_get_wtime();

    std::cout << "Tiempo secuencial: "
              << (fin_seq - inicio_seq) << " segundos\n";

    // ===============================
    // SUMA PARALELA
    // ===============================
    double inicio_par = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        {
            std::cout << "Numero de hilos utilizados: "
                      << omp_get_num_threads() << std::endl;
        }

        #pragma omp for schedule(static, chunk)
        for (i = 0; i < N; i++) {
            c[i] = a[i] + b[i];
        }
    }

    double fin_par = omp_get_wtime();

    std::cout << "Tiempo paralelo: "
              << (fin_par - inicio_par) << " segundos\n";

    // ===============================
    // RESULTADOS
    // ===============================
    std::cout << "\nPrimeros valores del arreglo A:\n";
    imprimeArreglo(a);

    std::cout << "Primeros valores del arreglo B:\n";
    imprimeArreglo(b);

    std::cout << "Primeros valores del arreglo C (A+B):\n";
    imprimeArreglo(c);

    // ===============================
    // LIBERAR MEMORIA
    // ===============================
    delete[] a;
    delete[] b;
    delete[] c;

    return 0;
}

void imprimeArreglo(float *d) {
    for (int x = 0; x < mostrar; x++)
        std::cout << d[x] << " - ";
    std::cout << std::endl;
}

