#include <iostream>
#include <chrono>
#include <cmath>
#include <algorithm>
#include <random>
#include <vector>

using namespace std;


void merge(vector<vector<int>>& arr, int start, int end, int d) {
    int n = end - start + 1;
    int len = n / d;

    vector<vector<vector<int>>> sub_arr(d, vector<vector<int>>(len, vector<int>(2)));
    vector<int> sub_arr_ptr(d, 0);

    for (int i = 0; i < d; i++) {
        for (int j = 0; j < len; j++) {
            sub_arr[i][j][0] = arr[start + i * len + j][0];
            sub_arr[i][j][1] = arr[start + i * len + j][1];
        }
    }

    for (int c = 0; c < n; c++) {
        int ptr = 0;
        while (sub_arr_ptr[ptr] > len - 1) {
            ptr++;
        }

        const vector<int>& min = sub_arr[ptr][sub_arr_ptr[ptr]];
        int min_ptr = ptr;

        for (int i = 0; i < d; i++) {
            if (sub_arr_ptr[i] > len - 1) {
                continue;
            }

            const vector<int>& mc = sub_arr[i][sub_arr_ptr[i]];
            if (mc[0] < min[0]) {
                min_ptr = i;
            }
        }

        arr[start + c][0] = min[0];
        arr[start + c][1] = min[1];
        sub_arr_ptr[min_ptr]++;
    }
}

void mergeSort(vector<vector<int>>& arr, int start, int end, int d) {
    if (start >= end) {
        return;
    }

    int n = end - start + 1;
    if (n < d) {
        merge(arr, start, end, n);
        return;
    }

    int len = n / d;
    for (int cut = start; cut < (end - start); cut += len) {
        mergeSort(arr, cut, cut + len - 1, d);
    }

    merge(arr, start, end, d);
}

void display(const vector<vector<int>>&arr) {
    for (const vector<int>& v : arr) {
        cout << "(" << v[0] <<","<<v[1]<< ") ";
    }
    cout << endl;
    return;
}

vector<vector<int>> generateRandomArray(int n) {
    vector<vector<int>> arr(n, vector<int>(2));
    for (int i = 0; i < n; i++) {
        arr[i][0] = rand() % 10;
        arr[i][1] = i;
    }
    return arr;
}

int main(){
    vector<vector<int>> ola(10,vector<int>(2));
    for (int i = 0; i < 10; i++) {
        ola[i][0] = (i+5)%11;
        ola[i][1] = i+1;
    }
    display(ola);
    return 0;
}