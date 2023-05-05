#include <iostream> // Para printear
#include <chrono>   // Para medir el tiempo 
#include <math.h>   // Para pow (potencias)

#include <algorithm> //Para lograr
#include <random>   // garantizar que el arreglo sea aleatorio

using namespace std;

void merge(int **arr,int start, int end, int d){
    //cantidad de elementos a ordenar
    int n=end-start+1;
    //tamaño sub arreglos
    int len=int(n/d);
    //arreglo de sub_arreglos
    //int sub_arr[d][len][2];
    int ***sub_arr=new int**[d];
    for(int i=0; i<d; i++){
        sub_arr[i]=new int*[len];
        for(int j=0;j<len;j++){
            sub_arr[i][j]=new int[2];
        }
    }
    //arreglo de al posicion del minimo elemento no guardado de cada sub_arreglo
    //int sub_arr_ptr[d];
    int *sub_arr_ptr=new int[d];
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
        while(sub_arr_ptr[ptr]>len-1){
            ptr++;
        }
        //obtener el primer elemento del primer sub_arreglo no vacio
        int *min=new int[2];
        min[0]=sub_arr[ptr][sub_arr_ptr[ptr]][0];
        min[1]=sub_arr[ptr][sub_arr_ptr[ptr]][1];
        int min_ptr=ptr;
        //busco el minimo elemento de los sub arreglos
        for(int i=0;i<d;i++){
            //si el subarreglo esta vacio voy al siguiente
            if(sub_arr_ptr[i]>len-1){
                continue;
            }
            //obtengo el minimo
            int *mc=new int[2];
            mc[0]=sub_arr[i][sub_arr_ptr[i]][0];
            mc[1]=sub_arr[i][sub_arr_ptr[i]][1];
            if(mc[0]<min[0]){
                min[0]=mc[0];
                min[1]=mc[1];
                min_ptr=i;
            }
            delete[] mc;
        }
        //guardo el minimo en el arreglo
        arr[start+c]=min;
        //saco el elemento del subarreglo que tenia el minimo
        sub_arr_ptr[min_ptr]+=1;
        delete [] min;
    }
    delete [] sub_arr;
    delete [] sub_arr_ptr;
    return;
}

//Merge Sort con aridad d 
void mergeSort(int **arr,int start,int end,int d){
    //si termina antes de empezar return
    if(start>=end){
        return;
    }
    int n=end-start+1;
    //si hay menos elementos en el arreglos que aridad
    if(n<d){
        //ordeno de a 1 elemento
        merge(arr,start,end,n);
        return;
    } 
    //largo de los subarreglos
    int len=int(n/d);
    for(int cut=start; cut<(end-start); cut+=len){
        mergeSort(arr,cut,cut+len-1,d);
    }
    merge(arr, start, end, d);
    return;
}

// inverse_perm: int[] x int -> int[]
// Calcula la inversa de una permutacion con merge sort
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
/*
n:tamaño del arreglo
i:exponente
j:numero del test
res:arreglo con la duracion de los tests
d:aridad de mergeSort
*/
void mainforcase (int n, int i, int j, int res[],int d){
    //Se crea un arreglo de tamaño n
    int *A = new int[n];

    //Se llena el arreglo con los numeros del 1 al n
    std::iota(A, A + n, 1);

    //Se permuta el arreglo de manera aleatoria
    std::shuffle(A, A + n, std::mt19937{std::random_device{}()});
    
    //Se inicia el cronometro
    auto inicio = chrono::high_resolution_clock::now();
    
    //Se crea un arreglo de tuplas dimension n x 2 
    //Se inicializa el arreglo de tuplas con arr_par[i]=[valor_i,posicion_i]
    int **arr=new int*[n];
    for(int k=0;k<n;k++){
        arr[k]=new int[2];
        arr[k][0]=A[k];
        arr[k][1]=k+1;
    }

    //Se calcula la permutación inversa con merge sort
    mergeSort(arr, 0, n-1, d);

    //Se obtiene la permutacion inversa desde el arreglo de tuplas
    for(int k=0;k<n;k++){
        A[k]=arr[k][2];
    }
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

    delete[] arr;//del arreglo creado
    delete[] A;
}

int main(){
    //Se crea el archivo donde se guardaran los resultados
    FILE *f = fopen("resultados_merge_sort.txt", "w+");
    fclose(f);
    
    int n; //Tamaño del arreglo
    //Testeamos de 2^20 a 2^30
    for(int i=20; i<=20; i++){
        //Se calcula el n
        n = int(pow(2,i)); //El arreglo debe ser de tamaño 2^i

        //Se abre el archivo donde se guardarán los tiempos 
        FILE *f = fopen("resultados_merge_sort.txt", "a");
        fprintf(f, "**************Para N=2^%ld d=8**************\n", i);
        fclose(f);

        //Se declara el arreglo de resultados
        int res[10];

        //Testeamos 10 veces para el n dado
        for(int j=0; j<10; j++){
            mainforcase(n,i,j,res,2);
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
            desv += pow(res[k]-prom,8);
        }
        desv = sqrt(desv/10);

        //Se escribe la desviacion estandar en el archivo
        fprintf(f, "La desviacion estandar es: %f milisegundos.\n\n", desv);

        //Se cierra el archivo
        fclose(f);
    }
    
    return 0;
}
