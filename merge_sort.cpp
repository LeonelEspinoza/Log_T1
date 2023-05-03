#include <iostream> // Para printear
#include <chrono>   // Para medir el tiempo 
#include <math.h>   // Para pow (potencias)

#include <algorithm> //Para lograr
#include <random>   // garantizar que el arreglo sea aleatorio

using namespace std;

/*
void merge(int arr[][],int start, int len, int end, int d){
    
    //arreglo de sub arreglos
    int sub_arr[d][len][2];
    int sub_arr_ptr[d];
    for(int i=0;i<d;i++){
        for(int j=0;j<len;j++){
            sub_arr[i][j]=arr[start+i*len+j];
        }
        sub_arr_ptr[i]=0;
    }
    //hasta que se ordenen end-start+1==n elementos
    for(int c=0;c<end-start+1;c++){
        //ver cual es el primer sub_arreglo no vacio
        int ptr=0;
        while(sub_arr_ptr[ptr]>len){
            ptr++;
        }
        //obtener el primer elemento del primer sub_arreglo no vacio
        int *min=sub_arr[ptr][sub_arr_ptr[ptr]];
        int min_ptr=ptr;
        //busco el minimo elemento de los sub arreglos
        for(int i=0;i<d;i++){
            //si el subarreglo esta vacio voy al siguiente
            if(sub_arr_ptr[i]>len){
                continue;
            }
            //obtengo el minimo
            int *mc=sub_arr[i][sub_arr_ptr[i]];
            if(mc[1]<min[1]){
                min=mc;
                min_ptr=i;
            }
        }
        //guardo el minimo en el arreglo
        arr[start+c]=min;
        //saco el elemento del subarreglo que tenia el minimo
        sub_arr_ptr[min_ptr]++;
    }
    return;
}

//Merge Sort con aridad d 
void mergesort(int arr[][],int start,int end,int d,int n){
    //si termina antes de empezar return
    if(start>=end){
        return;
    }
    
    //si hay menos elementos en el arreglos que aridad
    if(n<d){
        //ordeno de a 1 elemento
        merge(arr,start,1,end,n);
        return;
    } 
    //obtengo largo de los subarreglos
    int len=int(n/d);
    for(int cut=start; cut<(end-start); cut+=len){
        mergesort(arr[][],cut,cut+len-1,d,len);
    }
    merge(arr, start, len, end, d);
    return;
}*/

int *init_arr(int arr[],int n){
    int arr_par[n][2];
    for(int i=0;i<n;i++){
        arr_par[i][1]=arr[i];
        arr_par[i][2]=i;
    }

    return arr_par;
}

// inverse_perm: int[] x int -> int[]
// Calcula la inversa de una permutacion con merge sort
// Ejemplo:
// Input: 2 3 4 0 1
// Output:3 4 0 1 2
int *inverse_perm_merge(int perm[][], int n){
    int n_2= int(n/2);
    int left[n_2][2];
    int right[n-n_2][2];

    for(int i=0;i<n_2;i++){
        left[i]=perm[i];
        right[i]=perm[i+n_2];
    }

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
    
    //Se crea un arreglo de tamaño n arreglos de dos int
    int arr_par[n][2];
    
    //Se inicializa el arreglo de pares con arr_par[i]=[valor_i,posicion_i]
    for(int i=0;i<n;i++){
        //Se guarda el valor
        arr_par[i][1]=arr[i];
        //Se guarda su posicion
        arr_par[i][2]=i+1;
    }
    
    //Se inicia el cronometro
    auto inicio = chrono::high_resolution_clock::now();

    //Se calcula la permutación inversa con merge sort
    int *ip = inverse_perm_merge(arr_par, n);

    //Se finaliza el cronometro
    auto fin = chrono::high_resolution_clock::now();

    //Se calcula el tiempo transcurrido
    auto duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio).count();

    //Se guarda el resultado en el arreglo de resultados
    res[j] = int(duracion);

    //Se abre el archivo donde se guardarán los tiempos
    FILE *f = fopen("resultados_merge_sort.txt", "a"); //append

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
    FILE *f = fopen("resultados_merge_sort.txt", "w+");
    fclose(f);
    
    int n; //Tamaño del arreglo
    //Testeamos de 2^20 a 2^30
    for(int i=20; i<=30; i++){
        //Se calcula el n
        n = int(pow(2,i)); //El arreglo debe ser de tamaño 2^i

        //Se abre el archivo donde se guardarán los tiempos
        FILE *f = fopen("resultados_merge_sort.txt", "a");
        fprintf(f, "****************Para N=2^%ld****************\n", i);
        fclose(f);

        //Se declara el arreglo de resultados
        int res[10];

        //Testeamos 10 veces para el n dado
        for(int j=0; j<10; j++){
            mainforcase(n,i,j,res);
        }
        
        //Se abre el archivo para escribir el promedio y la desviacion estandar
        f = fopen("resultados_merge_sort.txt", "a");
        
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
