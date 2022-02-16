#include <iostream>
#include <string>

using namespace std;

template <class T>
class DLinkedList {
public:
    class Node; // Forward declaration
protected:
    Node* head;
    Node* tail;
    int count;
public:
    DLinkedList() : head(NULL), tail(NULL), count(0) {};
    ~DLinkedList() {
        while (head != NULL) {
            Node* temp = head->next;
            delete head;
            head = temp;
        }
    }
    void    add(const T& e);
    void    add(int index, const T& e);
    int     size();
    string toString();
    //Bai 2
    int     size();
    bool    empty();
    T       get(int index);
    void    set(int index, const T& e);
    int     indexOf(const T& item);
    bool    contains(const T& item);
    //Bai 3
    T       removeAt(int index);
    bool    removeItem(const T& item);
    void    clear();

    Iterator begin()
    {
        return Iterator(this, true);
    }
    Iterator end()
    {
        return Iterator(this, false);
    }
public:
    class Node
    {
    private:
        T data;
        Node* next;
        Node* previous;
        friend class DLinkedList<T>;

    public:
        Node()
        {
            this->previous = NULL;
            this->next = NULL;
        }

        Node(const T& data)
        {
            this->data = data;
            this->previous = NULL;
            this->next = NULL;
        }
    };
    class Iterator
    {
    private:
        DLinkedList<T>* pList;
        Node* current;
        int index; // is the index of current in pList
    public:
        Iterator(DLinkedList<T>* pList, bool begin);
        Iterator& operator=(const Iterator& iterator);
        void set(const T& e);
        T& operator*();
        bool operator!=(const Iterator& iterator);
        void remove();

        // Prefix ++ overload
        Iterator& operator++();

        // Postfix ++ overload
        Iterator operator++(int);
    };
};

#pragma region Bai 4 iterator
/*
 * TODO: Implement class Iterator's method
 * Note: method remove is different from DLinkedList, which is the advantage of DLinkedList
 */
template <class T>
DLinkedList<T>::Iterator::Iterator(DLinkedList<T>* pList, bool begin)
{
    this->pList = pList;
    if (begin) {
        if (pList != NULL) {
            this->index = 0;
            this->current = this->pList->head;
        }
        else {
            this->current = NULL;   //Updated
            this->index = -1;
        }
    }
    else {
        this->current = NULL;
        if (this->pList != NULL) {
            this->index = this->pList->size();
        }
        else {
            this->index = 0;
        }
    }
}

template <class T>
typename DLinkedList<T>::Iterator& DLinkedList<T>::Iterator::operator=(const DLinkedList<T>::Iterator& iterator)
{
    this->current = iterator.current;
    this->index = iterator.index;
    this->pList = iterator.pList;
    return *this;
}

template <class T>
void DLinkedList<T>::Iterator::set(const T& e)
{
    if (this->current == NULL) {
        throw std::out_of_range("Segmentation fault!");
    }
    this->current->data = e;
}

template<class T>
T& DLinkedList<T>::Iterator::operator*()
{
    if (this->current == NULL) {
        throw std::out_of_range("Segmentation fault!");
    }
    return this->current->data;
}

template<class T>
void DLinkedList<T>::Iterator::remove()
{
    /*
    * TODO: delete Node in pList which Node* current point to.
    *       After that, Node* current point to the node before the node just deleted.
    *       If we remove first node of pList, Node* current point to nullptr.
    *       Then we use operator ++, Node* current will point to the head of pList.
    */
    if (this->current == NULL) {
        throw std::out_of_range("Segmentation fault!");
    }
    /*
    this->pList->removeAt(this->index);
    index -= 1;
    */
    if (this->current == this->pList->head) {
        this->current = NULL;
        this->pList->removeAt(this->index);
        this->index = -1;
        return;
    }
    

    this->current = this->current->previous;
    this->pList->removeAt(this->index);
   
    /*
    DLinkedList<T>::Node* iter = this->pList->head;
    while (iter->next != this->current) {
        iter = iter->next;
    }
    this->current = iter;
    this->pList->removeAt(this->index);
    */
    this->index--;
    
}

template<class T>
bool DLinkedList<T>::Iterator::operator!=(const DLinkedList::Iterator& iterator)
{
    return ((this->current != iterator.current) || (this->index != iterator.index));
}

template<class T>
typename DLinkedList<T>::Iterator& DLinkedList<T>::Iterator::operator++()
{
    /*
    if (this->current == NULL) {
        throw std::out_of_range("Segmentation fault!");
    }
    */

    if (index == -1) {
        index = 0;
        this->current = this->pList->head;
    }
    else {
        this->current = this->current->next;
        this->index++;
    }

   

    return *this;
}

template<class T>
typename DLinkedList<T>::Iterator DLinkedList<T>::Iterator::operator++(int)
{
    //if (this->current == NULL || index == -1) {
    //    throw std::out_of_range("Segmentation fault!");
    //}

    /*
    if (index == -1) {
        indx = 0;
        this->current = this->pList->head;
    }
    else {
        this->current = this->current->next;
        this->index++;
    }*/
   
    DLinkedList<T>::Iterator iter = *this;
    ++* this;
    return iter;
}
#pragma endregion


template <class T>
void DLinkedList<T>::add(const T& e) {
    /* Insert an element into the end of the list. */
    
    if (this->count == 0) {   //Not exist
        this->head = this->tail = new DLinkedList<T>::Node(e);
    }
    else {
        Node* new_node = new DLinkedList<T>::Node(e);
        this->tail->next = new_node;
        new_node->previous = this->tail;
        this->tail = this->tail->next;
    }

    this->count++;
}

template<class T>
void DLinkedList<T>::add(int index, const T& e) {
    if (this->count < index) {
        return;
    }
    else if (this->count == index) {  //Add tail
        this->add(e);
        return;
    }
    else {
        //Add head
        if (index == 0) {
            DLinkedList<T>::Node* item = new DLinkedList<T>::Node(e);
            item->next = this->head;
            this->head = item;
        }
        else {  //Add mid (count > index)
            DLinkedList<T>::Node* iter = this->head;
            while (index > 1) {
                index--;
                iter = iter->next;
            }
            DLinkedList<T>::Node* item = new DLinkedList<T>::Node(e);
            item->next = iter->next;
            item->previous = iter;

            iter->next = item;
        }
        this->count++;
    }
}

template<class T>
int DLinkedList<T>::size() {
    /* Return the length (size) of list */
    return this->count;
}

template<class T>
string DLinkedList<T>::toString()
{
    cout << "[";
    if (this->count != 0) {
        cout << this->head->data;
    }
    DLinkedList<T>::Node* temp = this->head;
    for (int i = 1; i < count; i++) {
        temp = temp->next;
        cout << ',' << temp->data;
    }
    cout << "]";
    return "";
}

template<class T>
T DLinkedList<T>::get(int index) {
    /* Give the data of the element at given index in the list. */
    DLinkedList<T>::Node* item = this->head;
    if (index >= this->count || index < 0) {
        throw std::out_of_range("");
    }
    for (int i = 0; i < index; i++) {
        item = item->next;
    }
    return item->data;
}

template <class T>
void DLinkedList<T>::set(int index, const T& e) {
    /* Assign new value for element at given index in the list */
    if (index >= this->count || index < 0) {
        throw std::out_of_range("");
    }
    DLinkedList<T>::Node* item = this->head;
    if (index >= this->count) {
        return;
    }
    for (int i = 0; i < index; i++) {
        item = item->next;
    }
    item->data = e;
}

template<class T>
bool DLinkedList<T>::empty() {
    /* Check if the list is empty or not. */
    return this->count == 0;
}

template<class T>
int DLinkedList<T>::indexOf(const T& item) {
    /* Return the first index wheter item appears in list, otherwise return -1 */
    int idx = 0;
    DLinkedList<T>::Node* i = this->head;
    while (i != NULL) {
        if (i->data == item) {
            return idx;
        }
        i = i->next;
        idx++;
    }
    return -1;
}

template<class T>
bool DLinkedList<T>::contains(const T& item) {
    /* Check if item appears in the list */
    DLinkedList<T>::Node* i = this->head;
    while (i != NULL) {
        if (i->data == item) {
            return true;
        }
        i = i->next;
    }
    return false;
}

//Bai 3
template <class T>
T DLinkedList<T>::removeAt(int index)
{
    /* Remove element at index and return removed value */
    if (index == 0)
    {
        if (count == 1)
        {
            Node* temp = head;
            T p = temp->data;
            head = NULL;
            tail = NULL;
            delete temp;
            count--;
            return p;
        }
        Node* temp = head;
        T p;
        head = head->next;
        head->previous = NULL;
        p = temp->data;
        delete temp;
        if (head == NULL)
            tail = NULL;
        count--;
        return p;
    }
    if (index == count - 1)
    {
        Node* temp = tail;
        T p = temp->data;
        tail->previous->next = NULL;
        tail = tail->previous;
        delete temp;
        count--;
        return p;
    }
    Node* temp = head;
    for (int i = 0; i < count; i++)
        if (i < index - 1)
            temp = temp->next;
    Node* Ntemp = temp->next;
    T p = Ntemp->data;
    temp->next = temp->next->next;
    temp->next->previous = temp;
    delete Ntemp;
    count--;
    return p;
}

template <class T>
bool DLinkedList<T>::removeItem(const T& item)
{
    /* Remove the first apperance of item in list and return true, otherwise return false */
    int dem = 0;
    for (DLinkedList<T>::Node* iter = this->head; iter != NULL; iter = iter->next) {
        if (iter->data == item) {
            removeAt(dem);
            return true;
        }
        dem++;
    }
    return false;
}

template<class T>
void DLinkedList<T>::clear() {
    /* Remove all elements in list */
    DLinkedList<T>::Node* iter = this->head;
    while (iter != NULL) {
        DLinkedList<T>::Node* temp = iter;
        iter = iter->next;
        delete temp;
    }
    this->head = this->tail = NULL;
    this->count = 0;
}
