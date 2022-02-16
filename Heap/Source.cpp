#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"
template<class T>
class Heap {
protected:
    T* elements;
    int capacity;
    int count;
public:
    Heap()
    {
        this->capacity = 10;
        this->count = 0;
        this->elements = new T[capacity];
    }
    ~Heap()
    {
        delete[]elements;
    }
    void push(T item);
    void clear();

    bool isEmpty();
    bool contains(T item);
    T peek();
    bool pop();
    int size();
    int getItem(T item);
    void remove(T item);

    void printHeap()
    {
        cout << "Max Heap [ ";
        for (int i = 0; i < count; i++)
            cout << elements[i] << " ";
        cout << "]\n";
    }
private:
    void ensureCapacity(int minCapacity);
    void reheapUp(int position);
    void reheapDown(int position);
};
//Your code goes here
template<class T>
int Heap<T>::size() {
    return this->count;
}

template<class T>
bool Heap<T>::isEmpty() {
    return this->count == 0;
}

template<class T>
T Heap<T>::peek() {
    if (this->isEmpty()) {
        //return -1;
    }
    return this->elements[0];
}

template<class T>
bool Heap<T>::contains(T item) {
    for (int i = 0; i < this->count; i++) {
        if (this->elements[i] == item) {
            return true;
        }
    }
    return false;
}

template<class T>
bool Heap<T>::pop() {
    if (this->isEmpty()) return false;
    this->elements[0] = this->elements[this->count - 1];
    this->reheapDown(0);
    this->count--;
    return true;
}

template<class T>
void Heap<T>::clear() {
    // TODO: delete all elements in heap
    delete this->elements;
    this->count = 0;
    this->capacity = 10;

}

//--Bai 2
template<class T>
void Heap<T>::push(T item) {
    this->ensureCapacity(this->count+1);
    this->elements[this->count] = item;
    this->reheapUp(this->count);
    this->count++;
}

template<class T>
void Heap<T>::ensureCapacity(int minCapacity) {
    if (minCapacity > this->capacity) {
        //Work here
        this->capacity *= 2;
        T* temp = this->elements;   //old
        this->elements = new T[this->capacity]; //new

        //move element to new memory
        for (int i = 0; i < this->count; i++) {
            this->elements[i] = temp[i];
        }

        delete temp;
    }
}

template<class T>
void Heap<T>::reheapUp(int position) {
    if (this->count <= 1 || position >= this->count || position < 0) {
        //return;
    }
    if (position > 0) {
        int parent = (position - 1) / 2;
        if (this->elements[position] > this->elements[parent]) {
            swap(this->elements[position], this->elements[parent]);
            this->reheapUp(parent);
        }
    }
}

template<class T>
void Heap<T>::reheapDown(int position)
{
    if (this->count <= 1 || position >= this->count || position < 0) {
        return;
    }
    int leftChild = position * 2 + 1;
    int rightChild = position * 2 + 2;
    int largeChild = leftChild;     //Cho no la left truoc
    if (leftChild < this->count) { //It nhat 1
        if (rightChild < this->count) {    //Ca 2
            if (this->elements[rightChild] > this->elements[leftChild]) {
                largeChild = rightChild;    //Neu right lon thi set lai cho no
            }
        }
        if (this->elements[largeChild] > this->elements[position]) {
            swap(this->elements[largeChild], this->elements[position]);
            reheapDown(largeChild);
        }
    }
}

//Bai 3
template<class T>
int Heap<T>::getItem(T item) {
    // TODO: return the index of item in heap
    for (int i = 0; i < this->count; i++) {
        if (this->elements[i] == item) {
            return i;
        }
    }
    return -1;
}

template<class T>
void Heap<T>::remove(T item) {
    // TODO: remove the element with value equal to item
    int index = this->getItem(item);
    if (index == -1) {  //Khong co element de xoa
        return;
    }
    this->elements[index] = this->elements[--count];    //Xoa
    
    if (this->count != 0) {
        this->reheapDown(index);
        this->reheapUp(index);
    }
    
}

//Bai 4
void reheapDown(int maxHeap[], int numberOfElements, int index)
{
    if (numberOfElements <= 1 || index >= numberOfElements || index < 0) {
        return;
    }
    int leftChild = index * 2 + 1;
    int rightChild = index * 2 + 2;
    int largeChild = leftChild;     //Cho no la left truoc
    if (leftChild < numberOfElements) { //It nhat 1
        if (rightChild < numberOfElements) {    //Ca 2
            if (maxHeap[rightChild] > maxHeap[leftChild]) {
                largeChild = rightChild;    //Neu right lon thi set lai cho no
            }
        }
        if (maxHeap[largeChild] > maxHeap[index]) {
            swap(maxHeap[largeChild], maxHeap[index]);
            reheapDown(maxHeap, numberOfElements, largeChild);
        }
    }
}

void reheapUp(int maxHeap[], int numberOfElements, int index)
{
    if (numberOfElements <= 1 || index >= numberOfElements || index < 0) {
        return;
    }
    if (index > 0) {
        int parent = (index - 1) / 2;
        if (maxHeap[index] > maxHeap[parent]) {
            swap(maxHeap[index], maxHeap[parent]);
            reheapUp(maxHeap, numberOfElements, parent);
        }
    }
    
}

//Bai 5, lam cach chong doi (Interchange sort hoac buble sort cho nhanh)
template <class T>
class Sorting {
public:
    /* Function to print an array */
    static void printArray(T* start, T* end)
    {
        long size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }

    //Helping functions go here --Bai 5
    static void heapSort(T* start, T* end) {
        //TODO
        /*
        int n = end - start;
       
        Heap<T> heap;   //Build heap
        for (int i = 0; i < n; i++) {
            heap.push(start[i]);
        }
        
        for (int i = n-1; i >= 0; i--) {
            start[i] = heap.peek();
            heap.pop();
        }*/

        Sorting<T>::printArray(start, end);
    }

};

//clear da co o bai 1 (o tren)

//Bai 6
struct Job {
    int arrivalTime, completeTime;
};
//*
/*bool operator<(Job j1, Job j2) {
    return j1.completeTime > j2.completeTime;
}
*/
bool operator>(Job j1, Job j2) {
    return j1.completeTime  < j2.completeTime;
}

//*/
ostream& operator<<(ostream& os, const Job& j)
{
    os << j.arrivalTime << ' ' << j.completeTime << ' ';
    return os;
}
Job createJob(int arrivalTime, int completeTime) {
    Job t;
    t.arrivalTime = arrivalTime;
    t.completeTime = completeTime;
    return t;
}

int minWaitingTime(int n, int arrvalTime[], int completeTime[]) {
    // YOUR CODE HERE
    Job job[1000000];
    for (int i = 0; i < n; i++) {
        job[i] = createJob(arrvalTime[i], completeTime[i]);
    }
    int totalWating = 0;
    int currentTime = job[0].arrivalTime;
    
    Heap<Job> h;
    h.push(job[0]);
    job[0].arrivalTime = -1;
    //job[0].arrivalTime = -1;

    while (!h.isEmpty()) {
        Job temp = h.peek();
        
        currentTime += temp.completeTime;
        int waitTime = currentTime - temp.arrivalTime;
        //cout << temp.arrivalTime << " " << temp.completeTime << " " << waitTime << endl;
        totalWating += waitTime;
        h.pop();

        bool flag = false;
        for (int i = 0; i < n; i++) {
            if (job[i].arrivalTime <= currentTime
                && job[i].arrivalTime != -1) {
                h.push(job[i]);
                //cout << job[i].arrivalTime << " " << job[i].completeTime << endl;
                job[i].arrivalTime = -1;
                flag = true;
            }
        }
        if (!flag) {
            for (int i = 0; i < n; i++) {
                if (job[i].arrivalTime != -1) {
                    h.push(job[i]);
                    currentTime = job[i].arrivalTime;
                    break;
                }
            }
        }
        //h.printHeap();
        //cout << endl;
    }

    return totalWating;
}
int main() {
    int n = 3;
    int arrvalTime[] = { 0, 1, 2 };
    int completeTime[] = { 3, 9, 6 };

    cout << minWaitingTime(n, arrvalTime, completeTime);
    return 0;
}