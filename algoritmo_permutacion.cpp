#include <iostream>
#include <chrono>
#include <math.h>
#include <algorithm>
#include <random>
using namespace std;

// inverse_perm: int[] x int -> int[]
// Calcula la inversa de una permutacion
// Ejemplo:
// Input: 2 3 4 0 1
// Output:3 4 0 1 2
int *inverse_perm(int perm[], int n){
    int *inv_perm = (int *) malloc(n*sizeof(int));
    for(int i=0; i<n; i++){
        inv_perm[perm[i]-1] = i+1;
    }
    return inv_perm;
}

// Testeo de la funcion inverse_perm
void mainforcase (int n){
    //Se crea un arreglo de tamaño n
    int *arr = new int[n];

    //Se llena el arreglo con los numeros del 1 al n
    std::iota(arr, arr + n, 1);

    //Se permuta el arreglo de manera aleatoria
    std::shuffle(arr, arr + n, std::mt19937{std::random_device{}()});

    //Se inicia el cronometro
    auto inicio = chrono::high_resolution_clock::now();

    //Se calcula la permutación inversa
    int *ip = inverse_perm(arr, n);

    //Se finaliza el cronometro
    auto fin = chrono::high_resolution_clock::now();

    //Se calcula el tiempo transcurrido
    auto duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio).count();

    //Se abre el archivo donde se guardarán los tiempos
    FILE *f = fopen("resultados_algoritmo_permutacion.txt", "a"); //append

    //Se escribe el tiempo en el archivo
    fprintf(f, "La funcion tardo %ld milisegundos en ejecutarse.\n\n", duracion);

    fclose(f);
    
    cout << "La funcion tardo " << duracion << " milisegundos en ejecutarse." << endl;
    free(ip);
    delete[] arr;
}

int main(){
    //Se crea el archivo donde se guardaran los resultados
    FILE *f = fopen("resultados_algoritmo_permutacion.txt", "w+");
    fclose(f);    
    
    int n;
    //testeamos de 2^20 a 2^30
    for(int i=22; i<=22; i++){
        n = int(pow(2,i));
        cout << "Para n = " << n << endl;
        // testeamos 10 veces para el n dado
        for(int j=0; j<10; j++){ //se le colocara 1 por mientras
            cout << "Test " << j+1 << " con 2^" << i << endl;
            mainforcase(n);
        }
    }

    return 0;
}

