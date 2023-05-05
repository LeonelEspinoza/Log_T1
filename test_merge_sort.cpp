#include <iostream> // Para printear
#include <chrono>   // Para medir el tiempo 
#include <math.h>   // Para pow (potencias)

#include <algorithm> //Para lograr
#include <random>   // garantizar que el arreglo sea aleatorio

using namespace std;
void display(int **arr, int size);

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
    int *sub_arr_ptr=new int[d];
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
        int *min=new int[2]{sub_arr[ptr][sub_arr_ptr[ptr]][0],sub_arr[ptr][sub_arr_ptr[ptr]][1]};
        int min_ptr=ptr;
        //busco el minimo elemento de los sub arreglos
        for(int i=0;i<d;i++){
            //si el subarreglo esta vacio voy al siguiente
            if(sub_arr_ptr[i]>len-1){
                continue;
            }
            //obtengo el minimo
            int *mc=new int[2]{sub_arr[i][sub_arr_ptr[i]][0],sub_arr[i][sub_arr_ptr[i]][1]};
            if(mc[0]<min[0]){
                min[0]=mc[0];
                min[1]=mc[1];
                min_ptr=i;
            }
            delete[] mc;
        }
        //guardo el minimo en el arreglo
        arr[start+c][0]=min[0];
        arr[start+c][1]=min[1];
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

void display(int **arr, int size) {
  for (int i = 0; i < size; i++)
    cout << "("<< arr[i][0] << ","<< arr[i][1]<< ") ";
  cout << "\n"<< endl;
}

int main() {
  const int size=8;
  int A[size]={3,4,2,1,8,7,6,5};
  int **arr=new int*[size];
  for(int i=0;i<size;i++){
    arr[i]=new int[2];
    arr[i][0]=A[i];
    arr[i][1]=i+1;
  }
  

  cout << "Original array \n";
  display(arr, size);  
  
  mergeSort(arr, 0, size-1,8);

  cout << "Sorted array \n";
  display(arr, size);
  return 0;
}