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
        inv_perm[perm[i]-1] = i+1;
    }
    return inv_perm;
}  

void mainforcase (int n){
    //int n = 4;    
    //int arr[n] = {3, 2, 1, 4, 5, 6, 7, 8, 9, 10};
    
    //int n = int(pow(2,20)); // size of array
    int *arr = new int[n];
    // Fill array with 1 to n con std::iota
    std::iota(arr, arr + n, 1);

    // Shuffle the array randomly
    std::shuffle(arr, arr + n, std::mt19937{std::random_device{}()});


    /*
    para debuguear
    //Se printea el arreglo input como un arreglo al estilo [1 2 ...]
    cout << "[ ";
    for(int i=0; i<n; i++){
        cout << arr[i] << " ";
    }
    cout << "]" << endl;*/

    //Se inicia el cronometro
    auto inicio = chrono::high_resolution_clock::now();
    //Se calcula la permutacion inversa
    int *ip = inverse_perm(arr, n);

    /*
    para debuguear
    //se printea la permutacion inversa como un arreglo al estilo [1 2 ...]
    cout << "[ ";
    for(int i=0; i<n; i++){
        cout << ip[i] << " ";
    }
    cout << "]" << endl;*/




    //Se finaliza el cronometro
    auto fin = chrono::high_resolution_clock::now();

    //escribe en un archivo llamado resultados_algoritmo_permutacion.txt
    //el elemento inv_perm[perm[n-1]-1] y el elemento perm[n-1]
    FILE *f = fopen("resultados_algoritmo_permutacion.txt", "a");
    fprintf(f, "Para n = %d\n", n);
    fprintf(f, "El elemento inv_perm[perm[n-1]-1] es %d y el elemento perm[n-1] es %d\n", ip[arr[n-1]-1], arr[n-1]);
    //ademas se guardan los tiempos en el archivo
    fprintf(f, "La funcion tardo %ld milisegundos en ejecutarse.\n\n", std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio).count());
    fclose(f);


    //Se calcula el tiempo transcurrido
    auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio).count();
    cout << "La funcion tardo " << duracion << " milisegundos en ejecutarse." << endl;
    free(ip);
    delete[] arr;
}

int main(){
    int n;
    //testeamos de 2^20 a 2^30
    for(int i=30; i<=30; i++){
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

