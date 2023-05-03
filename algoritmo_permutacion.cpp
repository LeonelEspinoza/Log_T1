#include <iostream> // Para printear
#include <chrono>   // Para medir el tiempo 
#include <math.h>   // Para pow (potencias)

#include <algorithm> //Para lograr
#include <random>   // garantizar que el arreglo sea aleatorio

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

// Testea la funcion inverse_perm para un caso
void mainforcase (int n, int i, int j, int res[]){
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

    //Se guarda el resultado en el arreglo de resultados
    res[j] = int(duracion);

    //Se abre el archivo donde se guardarán los tiempos
    FILE *f = fopen("resultados_algoritmo_permutacion.txt", "a"); //append

    //Se escribe el numero del test
    fprintf(f, "Test %d:\n", j+1);

    //Se escribe el tiempo en el archivo
    fprintf(f, "La funcion tardo %ld milisegundos en ejecutarse.\n\n", duracion);

    //Se cierra el archivo
    fclose(f);

    //Se libera la memoria
    free(ip);  //del arreglo creado en inverse_perm
    delete[] arr;//del arreglo creado
}

int main(){
    //Se crea el archivo donde se guardaran los resultados
    FILE *f = fopen("resultados_algoritmo_permutacion.txt", "w+");
    fclose(f);
    
    int n; //Tamaño del arreglo
    //Testeamos de 2^20 a 2^30
    for(int i=20; i<=30; i++){
        //Se calcula el n
        n = int(pow(2,i)); //El arreglo debe ser de tamaño 2^i

        //Se abre el archivo donde se guardarán los tiempos
        FILE *f = fopen("resultados_algoritmo_permutacion.txt", "a");
        fprintf(f, "****************Para N=2^%ld****************\n", i);
        fclose(f);

        //Se declara el arreglo de resultados
        int res[10];

        //Testeamos 10 veces para el n dado
        for(int j=0; j<10; j++){
            mainforcase(n,i,j,res);
        }
        
        //Se abre el archivo para escribir el promedio y la desviacion estandar
        f = fopen("resultados_algoritmo_permutacion.txt", "a");
        
        //Se calcula el promedio de los tiempos
        float prom = 0;
        for(int k=0; k<10; k++){
            prom += res[k];
        }
        prom = prom/10;
        
        //Se escribe el promedio en el archivo
        fprintf(f, "El promedio de tiempo es: %f milisegundos.\n", prom);
        
        //Se calcula la desviacion estandar de los tiempos
        float desv = 0;
        for(int k=0; k<10; k++){
            desv += pow(res[k]-prom,2);
        }
        desv = sqrt(desv/10);

        //Se escribe la desviacion estandar en el archivo
        fprintf(f, "La desviacion estandar es: %f milisegundos.\n\n", desv);

        //Se cierra el archivo
        fclose(f);
    }
    
    return 0;
}
