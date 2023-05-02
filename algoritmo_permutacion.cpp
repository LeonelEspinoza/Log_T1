#include <iostream>
#include <chrono>
#include <math.h>
#include <algorithm>
#include <random>
using namespace std;
// Calcula la inversa de una permutacion
// Ejemplo:
// input: 2 3 4 0 1
// output:3 4 0 1 2
int *inverse_perm(int perm[], int n){
    int *inv_perm = (int *) malloc(n*sizeof(int));
    for(int i=0; i<n; i++){
        inv_perm[perm[i]] = i;
    }
    return inv_perm;
}  

int main(){
    int n = pow(2,20); // size of array
    int arr[n];

    // Fill array with 0 to n-1
    std::iota(arr, arr + n, 0);

    // Shuffle the array randomly
    std::shuffle(arr, arr + n, std::mt19937{std::random_device{}()});

    //Se inicia el cronometro
    auto inicio = chrono::high_resolution_clock::now();
    //Se calcula la permutacion inversa
    int *ip = inverse_perm(arr, n);
    //Se finaliza el cronometro
    auto fin = chrono::high_resolution_clock::now();
    //Se calcula el tiempo transcurrido
    auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio).count();
    cout << "La funcion tardo " << duracion << " milisegundos en ejecutarse." << endl;
    free(ip);
    return 0;
}

