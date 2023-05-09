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
    //arreglo de al posicion del minimo elemento no guardado de cada sub_arreglo
    //int sub_arr_ptr[d];
    int sub_arr_ptr[d];
    for(int i=0; i<d; i++){
        sub_arr[i]=new int*[len];
        for(int j=0;j<len;j++){
            sub_arr[i][j]=new int[2]{arr[start+i*len+j][0],arr[start+i*len+j][1]};
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
        int min[2]={sub_arr[ptr][sub_arr_ptr[ptr]][0],sub_arr[ptr][sub_arr_ptr[ptr]][1]};
        int min_ptr=ptr;
        //busco el minimo elemento de los sub arreglos
        for(int i=0;i<d;i++){
            //si el subarreglo esta vacio voy al siguiente
            if(sub_arr_ptr[i]>len-1){
                continue;
            }
            //obtengo el minimo
            int mc[2]={sub_arr[i][sub_arr_ptr[i]][0],sub_arr[i][sub_arr_ptr[i]][1]};
            if(mc[0]<min[0]){
                min[0]=mc[0];
                min[1]=mc[1];
                min_ptr=i;
            }
        }
        //guardo el minimo en el arreglo
        arr[start+c][0]=min[0];
        arr[start+c][1]=min[1];
        //saco el elemento del subarreglo que tenia el minimo
        sub_arr_ptr[min_ptr]+=1;
    }

    //por revisar si se borro bien
    for (int i = 0; i < d; i++) {
      for (int j = 0; j < len; j++) {
        delete[] sub_arr[i][j]; // liberas la memoria de cada subarreglo de dos enteros
        }
        delete[] sub_arr[i]; // liberas la memoria de cada subarreglo de punteros a enteros
    }
    delete[] sub_arr; // liberas la memoria del arreglo principal de punteros a punteros a enteros    

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
    iota(A, A + n, 1);

    //Se permuta el arreglo de manera aleatoria
    shuffle(A, A + n, mt19937{random_device{}()});
    
    //Se inicia el cronometro
    auto inicio = chrono::high_resolution_clock::now();
    
    //Se crea un arreglo de tuplas dimension n x 2 
    //Se inicializa el arreglo de tuplas con arr_par[i]=[valor_i,posicion_i]
    int **arr=new int*[n];
    for(int k=0;k<n;k++){
        arr[k]=new int[2]{A[k],k+1};
    }
    delete[] A; //del arreglo input
    

    //Se calcula la permutación inversa con merge sort
    mergeSort(arr, 0, n-1, d);

    int *B = new int[n];
    //Se obtiene la permutacion inversa desde el arreglo de tuplas
    for(int k=0;k<n;k++){
        B[k]=arr[k][2];
    }
    //Se finaliza el cronometro
    auto fin = chrono::high_resolution_clock::now();

    //Se calcula el tiempo transcurrido
    auto duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio).count();

    //Se guarda el resultado en el arreglo de resultados
    res[j] = int(duracion);

    //Se abre el archivo donde se guardarán los tiempos
    FILE *f = fopen("resultados_merge_sort.txt", "a"); //append
    FILE *g = fopen("resultados_algoritmo_merge.csv", "a"); //append


    //Se escribe el numero del test
    fprintf(f, "Test %d:\n", j+1);
    fprintf(g, "Test %d;", j+1);

    //Se escribe el tiempo en el archivo
    fprintf(f, "La funcion tardo %ld milisegundos en ejecutarse.\n\n", duracion);
    fprintf(g, "%ld\n", duracion);


    //Se cierra el archivo
    fclose(f);
    fclose(g);

    delete[] B; //del arreglo permutacion inversa
    for (int k = 0; k < n; k++) {
        delete[] arr[k]; // liberas la memoria de cada subarreglo
    }    
    delete[] arr;//del arreglo creado
}
void display(int **arr, int size) {
  for (int i = 0; i < size; i++)
    cout << "("<< arr[i][0] << ","<< arr[i][1]<< ") ";
  cout << "\n"<< endl;
}

int main(){
    //Se crea el archivo donde se guardaran los resultados
    FILE *f = fopen("resultados_merge_sort.txt", "w+");
    fclose(f);
    
    int n; //Tamaño del arreglo
    int d = 8; //Aridad de mergeSort

    const int size=8;
    int B[size]={3,4,2,1,8,7,6,5};
    int **arr=new int*[size];
    for(int i=0;i<size;i++){
        arr[i]=new int[2];
        arr[i][0]=B[i];
        arr[i][1]=i+1;
    }
    cout << "*********TEST PARA VER SI SIGUE ORDENANDO XD*********\nOriginal array \n";
    display(arr, size);  
  
    mergeSort(arr, 0, size-1,8);

    cout << "Sorted array \n";
    display(arr, size);    

    //Testeamos de 2^20 a 2^30
    for(int i=30; i<=30; i++){
        //Se calcula el n
        n = int(pow(2,i)); //El arreglo debe ser de tamaño 2^i

        //Se abre el archivo donde se guardarán los tiempos 
        FILE *f = fopen("resultados_merge_sort.txt", "a");
        fprintf(f, "**************Para N=2^%d d=%d**************\n", i, d);
        fclose(f);

        FILE *g = fopen("resultados_algoritmo_merge.csv", "a");
        fprintf(g, "****************Para N=2^%ld****************\n", i);
        fclose(g);

        //Se declara el arreglo de resultados
        int res[10];

        //Testeamos 10 veces para el n dado
        for(int j=0; j<10; j++){
            mainforcase(n,i,j,res,d);
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
