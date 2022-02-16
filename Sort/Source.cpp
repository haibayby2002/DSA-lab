#include <iostream>
#include <sstream>
using namespace std;

template <class T>
class SLinkedList {
public:
    class Node; // Forward declaration
protected:
    Node* head;
    Node* tail;
    int count;
public:
    SLinkedList()
    {
        this->head = nullptr;
        this->tail = nullptr;
        this->count = 0;
    }
    ~SLinkedList() {};
    void add(T e)
    {
        Node* pNew = new Node(e);

        if (this->count == 0)
        {
            this->head = this->tail = pNew;
        }
        else
        {
            this->tail->next = pNew;
            this->tail = pNew;
        }

        this->count++;
    }
    int size()
    {
        return this->count;
    }
    void printList()
    {
        stringstream ss;
        ss << "[";
        Node* ptr = head;
        while (ptr != tail)
        {
            ss << ptr->data << ",";
            ptr = ptr->next;
        }

        if (count > 0)
            ss << ptr->data << "]";
        else
            ss << "]";
        cout << ss.str() << endl;
    }
public:
    class Node {
    private:
        T data;
        Node* next;
        friend class SLinkedList<T>;
    public:
        Node() {
            next = 0;
        }
        Node(T data) {
            this->data = data;
            this->next = nullptr;
        }
    };

    void bubbleSort();
};

template <class T>
void SLinkedList<T>::bubbleSort()
{
    //SLinkedList<T>::Node *temp = this->head;
    for (int i = 0; i < this->count - 1; i++) {
        for (SLinkedList<T>::Node* temp = this->head; temp != this->tail; temp = temp->next) {
            if (temp->data > temp->next->data) {
                swap(temp->data, temp->next->data);
            }
        }
        this->printList();
    }
}

template <class T>
class Sorting
{
public:
    /* Function to print an array */
    static void printArray(T* start, T* end)
    {
        int size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }

    static void oddEvenSort(T* start, T* end);


    static void sortSegment(T* start, T* end, int segment_idx, int cur_segment_total) {
        int n = end - start;
        for (int i = segment_idx; i < n; i += cur_segment_total) {
            for (int j = i + cur_segment_total; j < n; j+=cur_segment_total) {
                if (start[i] > start[j]) {
                    swap(start[i], start[j]);
                }
            }
        }
    }

public:
    static void ShellSort(T* start, T* end, int* num_segment_list, int num_phases) {
        for (int i = num_phases - 1; i >= 0; i--) {     //Duyet qua num_segment_list
            for (int j = 0; j < num_segment_list[i]; j++) {
                sortSegment(start, end, j, num_segment_list[i]);
            }
            cout << num_segment_list[i] << " segments: ";
            printArray(start, end);
        }
    }

    static void selectionSort(T* start, T* end);

    static void merge(T* left, T* middle, T* right) {
        int l = 0;
        int r = right - left;
        int m = middle - left;
        int len1 = m - l + 1, len2 = r - m;
        int _left[10000], _right[10000];
        for (int i = 0; i < len1; i++)
            _left[i] = left[l + i];
        for (int i = 0; i < len2; i++)
            _right[i] = left[m + 1 + i];

        int i = 0;
        int j = 0;
        int k = l;

        // After comparing, we
        // merge those two array
        // in larger sub array
        while (i < len1 && j < len2)
        {
            if (_left[i] <= _right[j])
            {
                left[k] = _left[i];
                i++;
            }
            else
            {
                left[k] = _right[j];
                j++;
            }
            k++;
        }

        // Copy remaining elements of left, if any
        while (i < len1)
        {
            left[k] = _left[i];
            k++;
            i++;
        }

        // Copy remaining element of right, if any
        while (j < len2)
        {
            left[k] = _right[j];
            k++;
            j++;
        }
    }
public:
    static void InsertionSort(T* start, T* end) {
        int left = 0;
        int right = end - start - 1;
        for (int i = left + 1; i <= right; i++)
        {
            int temp = start[i];
            int j = i - 1;
            while (j >= left && start[j] > temp)
            {
                start[j + 1] = start[j];
                j--;
            }
            start[j + 1] = temp;
        }
    }
    static void TimSort(T* start, T* end, int min_size) {
        int RUN = min_size;
        int n = end - start;
        // Sort individual subarrays of size RUN
        for (int i = 0; i < n; i += RUN)
        {
            InsertionSort(start + i, start + min((i + RUN), (n)));
        }
        cout << "Insertion Sort: ";
        printArray(start, end);

        int count = 0;
        for (int size = RUN; size < n; size = 2 * size)
        {

            for (int left = 0; left < n; left += 2 * size)
            {
                int mid = left + size - 1;
                int right = min((left + 2 * size - 1), (n - 1));

                if (mid < right) {
                    merge(start + left, start + mid, start + right);
                }

                count++;
                cout << "Merge " << count << ": ";
                printArray(start, end);

            }
        }
    }


//Advanced
private:
    //static T* Partition(T* start, T* end);

public:
    /*
    static void printArray(T* start, T* end)
    {
        int size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }
    */

    static void insertionSort(T* start, T* end);

    static void hybridQuickSort(T* start, T* end, int min_size);



private:
    static T* Partition(T* start, T* end) {
        // TODO: return the pointer which points to the pivot after rearrange the array.

        /*
        int p = *start;
        int i = 0;
        int j = end - start + 1;
        do {
            do{i++;}while(start[i] >= p);
            do{j--;}while(start[j] <= p);
            swap(start[i], start[j]);
        }while(i >= j);
        swap(start[i], start[j]);
        swap(start[0], start[j]);
        return start + j;
        */
        int pivot = start[0];
        int i = 1, j = end - start;
        if (i >= j)
            return start;
        while (i <= j) {
            while (start[i] < pivot)
                i++;
            while (start[j] > pivot)
                j--;
            if (i <= j)
                swap(start[i], start[j]);
        }
        swap(start[0], start[j]);
        return start + j;

    }
    
public:
    

    static void QuickSort(T* start, T* end) {
        //int n = end - start;
        if (start < end) {   //Dieu kien dung
            T* pivot = Sorting<T>::Partition(start, end);
            cout << pivot - start << " ";
            //cout << "Quick sort: ";
            //printArray(start, end);
            QuickSort(start, pivot);
            QuickSort(pivot + 1, end);
        }
    }
};

/*
template <class T>
T* Sorting<T>::Partition(T* start, T* end)
{
    /*
    int n = end - start;
    int low = 0;
    int high = n - 1;
    int pivot = start[0]; // pivot 
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot 
        if (start[j] < pivot)
        {
            i++; // increment index of smaller element 
            swap(start[i], start[j]);
        }
    }
    swap(start[i + 1], start[high]);
    return (start + i + 1);
    */
    /*
    int n = end - start;
    int l = 0;
    int r = n - 1;
    int pivot = start[0];

    int i = l+1, j = r;
    while (i < j) {
        while (start[i] > pivot) {
            i++;
        }

        while (start[j] < pivot)
            j--;
        if (i <= j) {
            swap(start[i], start[j]);
        }
    };
    swap(start[0], start[j]);
    return start + j;
    
    cout << "Quick sort: ";
    printArray(start, end);
    int pivot = start[0];
    int i = 1, j = end - start - 1;
    while (i < j) {
        while (start[i] < pivot)
            i++;
        while (start[j] > pivot)
            j--;
        if (i <= j)
            swap(start[i], start[j]);
    }
    swap(start[0], start[j]);
    return start + j;
    
}

*/
template <class T>
void Sorting<T>::insertionSort(T* start, T* end)
{
    int left = 0;
    int right = end - start - 1;
    for (int i = left + 1; i <= right; i++)
    {
        int temp = start[i];
        int j = i - 1;
        while (j >= left && start[j] > temp)
        {
            start[j + 1] = start[j];
            j--;
        }
        start[j + 1] = temp;
    }
}

template <class T>
void Sorting<T>::hybridQuickSort(T* start, T* end, int min_size)
{
   
    int n = end - start;
    if (n == 0) {   //Dieu kien dung
        return;
    }
    if (n < min_size) {
        cout << "Insertion sort: ";
        printArray(start, end);
        insertionSort(start, end);
    }
    else {
        T* pivot = Partition(start, end);
        //cout << "Quick sort: ";
        //printArray(start, end);
        hybridQuickSort(start, pivot, min_size);
        hybridQuickSort(pivot + 1, end, min_size);
    }
}

template <class T>
void Sorting<T>::selectionSort(T* start, T* end)
{
    int n = end - start;

    for (int i = 0; i < n - 1; i++) {
        int index = i;
        for (int j = i + 1; j < n; j++) {
            if (start[j] < start[index]) {
                index = j;
            }
        }
        swap(start[i], start[index]);
        printArray(start, end);
    }

}


template <class T>
void Sorting<T>::oddEvenSort(T* start, T* end)
{
    /*TODO*/
    int n = end - start;
    bool isSorted = false; // Initially array is unsorted

    while (!isSorted)
    {
        isSorted = true;

        // Perform Bubble sort on even indexed element
        for (int i = 0; i <= n - 2; i = i + 2)
        {
            if (start[i] > start[i + 1])
            {
                swap(start[i], start[i + 1]);
                isSorted = false;
            }
        }

        // Perform Bubble sort on odd indexed element
        for (int i = 1; i <= n - 2; i = i + 2)
        {
            if (start[i] > start[i + 1])
            {
                swap(start[i], start[i + 1]);
                isSorted = false;
            }
        }

        

        Sorting<T>::printArray(start, end);
    }
}

int main() {
    int array[] = { 3, 5, 7, 10 ,12, 14, 15, 13, 1, 2, 9, 6, 4, 8, 11, 16, 17, 18, 20, 19 };
    cout << "Index of pivots: ";
    Sorting<int>::QuickSort(&array[0], &array[20]);
    cout << "\n";
    cout << "Array after sorting: ";
    for (int i : array) cout << i << " ";
    return 0;
}