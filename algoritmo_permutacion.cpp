#include <iostream>
using namespace std;

// Calcula la inversa de una permutacion
// Ejemplo:
// input: 2 3 4 0 1
//(input,posicion)->(2,1)(3,2)(1,3)(4,4)(5,5)
//
// output:3 4 0 1 2
int *inverse_perm(int perm[], int n){
    int *inv_perm = (int *) malloc(n*sizeof(int));
    for(int i=0; i<5; i++){
        inv_perm[perm[i]] = i;
    }
    //wait
    return inv_perm;
}  

int main(){
    int perm[] = {2, 3, 4, 0, 1};
    int n = sizeof(perm)/sizeof(int);
    int *ip = inverse_perm(perm, n);
    for(int i=0; i<5; i++){
        cout<<ip[i]<<" "<<endl;
    }
    return 0;
}

