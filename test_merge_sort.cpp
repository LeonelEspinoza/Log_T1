#include <iostream> // Para printear
#include <chrono>   // Para medir el tiempo 
#include <math.h>   // Para pow (potencias)

#include <algorithm> //Para lograr
#include <random>   // garantizar que el arreglo sea aleatorio

using namespace std;


void merge(int arr[][2],int start, int end, int d){
    //cantidad de elementos a ordenar
    int n=end-start+1;
    //tamaño sub arreglos
    int len=int(n/d);
    //arreglo de sub_arreglos
    int sub_arr[d][len][2];
    int sub_arr_ptr[d];
    for(int i=0;i<d;i++){
        for(int j=0;j<len;j++){
            sub_arr[i][j][0]=arr[start+i*len+j][0];
            sub_arr[i][j][1]=arr[start+i*len+j][1];
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
        int min[2]={sub_arr[ptr][sub_arr_ptr[ptr]][0],sub_arr[ptr][sub_arr_ptr[ptr]][1]};
        int min_ptr=ptr;
        //busco el minimo elemento de los sub arreglos
        for(int i=0;i<d;i++){
            //si el subarreglo esta vacio voy al siguiente
            if(sub_arr_ptr[i]>len){
                continue;
            }
            //obtengo el minimo
            int mc[2]={sub_arr[i][sub_arr_ptr[i]][0],sub_arr[i][sub_arr_ptr[i]][1]};
            if(mc[1]<min[1]){
                min[0]=mc[0];
                min[1]=mc[1];
                min_ptr=i;
            }
        }
        //guardo el minimo en el arreglo
        arr[start+c][0],arr[start+c][1]=min[0],min[1];
        //saco el elemento del subarreglo que tenia el minimo
        sub_arr_ptr[min_ptr]++;
    }
    return;
}

//Merge Sort con aridad d 
void mergeSort(int arr[][2],int start,int end,int d){
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

void display(int arr[][2], int size) {
  for (int i = 0; i < size; i++)
    cout << "("<< arr[i][0] << ","<< arr[i][1]<< ") ";
  cout << endl;
}

int main() {

  int arr[][2] = {{2,1},{1,2},{4,3},{3,4}};
  int size = 4;

  cout << "Original array \n";
  display(arr, size);  
  
  mergeSort(arr, 0, size-1,2);

  cout << "Sorted array \n";
  display(arr, size);
  return 0;
}