#include <iostream>

class MinHeap {
private:
    int*** arr;
    int capacity;
    int size;

public:
    MinHeap(int capacity) {
        this->capacity = capacity;
        arr = new int**[capacity];
        size = 0;
    }

    ~MinHeap() {
        delete[] arr;
    }

    int getParentIndex(int childIndex) {
        return (childIndex - 1) / 2;
    }

    int getLeftChildIndex(int parentIndex) {
        return (2 * parentIndex) + 1;
    }

    int getRightChildIndex(int parentIndex) {
        return (2 * parentIndex) + 2;
    }

    void swap(int** &a, int** &b) {
        int** temp = a;
        a = b;
        b = temp;
    }

    void heapifyUp(int index) {
        int parentIndex = getParentIndex(index);
        if (index > 0 && (*arr[index])[0] < (*arr[parentIndex])[0]) {
            swap(arr[index], arr[parentIndex]);
            heapifyUp(parentIndex);
        }
    }

    void heapifyDown(int index) {
        int smallest = index;
        int leftChildIndex = getLeftChildIndex(index);
        int rightChildIndex = getRightChildIndex(index);

        if (leftChildIndex < size && (*arr[leftChildIndex])[0] < (*arr[smallest])[0])
            smallest = leftChildIndex;

        if (rightChildIndex < size && (*arr[rightChildIndex])[0] < (*arr[smallest])[0])
            smallest = rightChildIndex;

        if (smallest != index) {
            swap(arr[index], arr[smallest]);
            heapifyDown(smallest);
        }
    }

    void insert(int** value) {
        if (size >= capacity) {
            std::cout << "Heap is full. Cannot insert value.\n";
            return;
        }

        arr[size] = value;
        heapifyUp(size);
        size++;
    }

    int** remove() {

        int** min = arr[0];
        arr[0] = arr[size - 1];
        size--;
        heapifyDown(0);
        return min;
    }

    void print() {
        for (int i = 0; i < size; i++) {
            std::cout << "("<<(*arr[i])[0] << ","<<(*arr[i])[1] << ") ";
        }
        std::cout << std::endl;
    }
};

int main() {
    const int d = 5;  // Number of tuples
    const int tupleSize = 2;  // Size of each tuple

    int*** tuples = new int**[d];
    for (int i = 0; i < d; i++) {
        tuples[i] = new int*[tupleSize];
        for (int j = 0; j < tupleSize; j++) {
            tuples[i][j] = new int;
        }
    }

    // Populate the tuples array
    (*tuples[0])[0] = 20;
    (*tuples[0])[1] = 40;
    (*tuples[1])[0] = 15;
    (*tuples[1])[1] = 30;
    (*tuples[2])[0] = 10;
    (*tuples[2])[1] = 25;
    (*tuples[3])[0] = 30;
    (*tuples[3])[1] = 50;
    (*tuples[4])[0] = 5;
    (*tuples[4])[1] = 35;

    MinHeap heap(d);

    for (int i = 0; i < d; i++) {
        heap.insert(tuples[i]);
    }

    heap.print();  // Output: 5 10 20 30 15

    int **min=heap.remove();

    heap.print();  // Output: 10 15 20 30

    std::cout << "Minimo: ("<<(*min)[0] << ","<<(*min)[1] << ") " << std::endl;  // Output: (5,35)
    // Deallocate memory for tuples array
    
    delete[] tuples;

    return 0;
}