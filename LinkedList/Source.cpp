#include <iostream>
#include <string>

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
    SLinkedList();
    ~SLinkedList();
    void    add(const T& e);
    void    add(int index, const T& e);
    int     size();
    string toString();
    bool    empty();
    T       get(int index);
    void    set(int index, const T& e);
    int     indexOf(const T& item);
    bool    contains(const T& item);
    T removeAt(int index);
    bool removeItem(const T&);
    void clear();
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
        Node(Node* next) {
            this->next = next;
        }
        Node(T data, Node* next) {
            this->data = data;
            this->next = next;
        }
    };
    class Iterator
    {
    private:
        SLinkedList<T>* pList;
        Node* current;
        int index; // corresponding with current node
    public:
        Iterator(SLinkedList<T>* pList, bool begin);
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

class Polynomial;
class Term {
private:
    double coeff;
    int exp;
    friend class Polynomial;
public:
    Term(double coeff = 0.0, int exp = 0) {
        this->coeff = coeff;
        this->exp = exp;
    }
    bool operator==(const Term& rhs) const {
        return this->coeff == rhs.coeff && this->exp == rhs.exp;
    }
    friend ostream& operator<<(ostream& os, const Term& term) {
        cout << endl;
        cout << "Term: " << "(" << term.coeff << " " << term.exp << ")";
        return os;
    }
};
class Polynomial {
private:
    SLinkedList<Term>* terms;
public:
    Polynomial() {
        this->terms = new SLinkedList<Term>();
    }
    ~Polynomial() {
        this->terms->clear();
    }
    void insertTerm(const Term& term);
    void insertTerm(double coeff, int exp);
    void print() {
        SLinkedList<Term>::Iterator it;
        cout << "[";
        for (it = this->terms->begin(); it != this->terms->end(); it++) {
            cout << (*it);
        }
        cout << endl << "]";
    }
};

template <class T>
SLinkedList<T>::SLinkedList() {
    count = 0;
    head = tail = NULL;
}

template <class T>
SLinkedList<T>::~SLinkedList() {
    SLinkedList<T>::Node *temp = head;
    while (this->count != 0) {
        head = head->next;
        delete temp;
        temp = head;
        this->count--;
    }
}

template <class T>
void SLinkedList<T>::add(const T& e) {
    /* Insert an element into the end of the list. */
    if (count == 0) {
        this->head = this->tail = new SLinkedList<T>::Node(e, NULL);
    }
    else {
        this->tail->next = new SLinkedList<T>::Node(e, NULL);
        this->tail = this->tail->next;
    }
    this->count++;
}

template<class T>
void SLinkedList<T>::add(int index, const T& e) {
    /* Insert an element into the list at given index. */
    //List Null
    if (this->count < index) {
        return;
    }
    else if(this->count == index){  //Add tail
        this->add(e);
        return;
    }
    else {  
        //Add head
        if (index == 0) {
            SLinkedList<T>::Node* item = new SLinkedList<T>::Node(e, this->head);
            this->head = item;
        }
        else {  //Add mid (count > index)
            SLinkedList<T>::Node* iter = this->head;
            while (index > 1) {
                index--;
                iter = iter->next;
            }
            SLinkedList<T>::Node* item = new SLinkedList<T>::Node(e, iter->next);
            iter->next = item;
        }   
        this->count++;
    }

}

template<class T>
int SLinkedList<T>::size() {
    /* Return the length (size) of list */
    return this->count;
    // 0;
}

template<class T>
string SLinkedList<T>::toString()
{
    cout <<"[";
    if (this->count != 0) {
        cout << this->head->data;
    }
    SLinkedList<T>::Node *temp = this->head;
    for (int i = 1; i < count; i++) {
        temp = temp->next;
        cout << ',' << temp->data;
    }
    cout << "]";
    return "";
}

template<class T>
bool SLinkedList<T>::empty()
{
    return this->count == 0;
}

template<class T>
T SLinkedList<T>::get(int index)
{
    SLinkedList<T>::Node *item = this->head;
    if (index >= this->count || index < 0) {
        throw std::out_of_range("");
    }
    for (int i = 0; i < index; i++) {
        item = item->next;
    }
    return item->data;
}

template<class T>
void SLinkedList<T>::set(int index, const T& e)
{
    if (index >= this->count || index < 0) {
        throw std::out_of_range("");
    }
    SLinkedList<T>::Node* item = this->head;
    if (index >= this->count) {
        return;
    }
    for (int i = 0; i < index; i++) {
        item = item->next;
    }
    item->data = e;
}

template<class T>
int SLinkedList<T>::indexOf(const T& item)
{
    int idx = 0;
    SLinkedList<T>::Node* i = this->head;
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
bool SLinkedList<T>::contains(const T& item) {
    /* Check if item appears in the list */
    SLinkedList<T>::Node *i = this->head;
    while (i != NULL) {
        if (i->data == item) {
            return true;
        }
        i = i->next;
    }
    return false;
}

template <class T>
T SLinkedList<T>::removeAt(int index)
{
    /* Remove element at index and return removed value */
    SLinkedList<T>::Node* iter = this->head;
    if (index == 0) {
        SLinkedList<T>::Node* temp = this->head;
        this->head = this->head->next;
        T data = temp->data;
        delete temp;
        count--;
        return data;
    }
    for (int i = 0; i < index - 1; i++) {
        iter = iter->next;
    }
    //delete
    SLinkedList<T>::Node* temp = iter->next;    //Truoc do -1
    iter->next = temp->next;
    T data = temp->data;
    if (temp == this->tail) {
        this->tail = iter;
    }
    delete temp;
    count--;
    return data;
}

template <class T>
bool SLinkedList<T>::removeItem(const T& item)
{
    /* Remove the first apperance of item in list and return true, otherwise return false */
    int dem = 0;
    for (SLinkedList<T>::Node* iter = this->head; iter != NULL; iter = iter->next) {
        if (iter->data == item) {
            removeAt(dem);
            return true;
        }
        dem++;  
    }
    return false;
}

template<class T>
void SLinkedList<T>::clear() {
    /* Remove all elements in list */
    SLinkedList<T>::Node* iter = this->head;
    while (iter != NULL) {
        SLinkedList<T>::Node* temp = iter;
        iter = iter->next;
        delete temp;
    }
    this->head = this->tail = NULL;
    this->count = 0;
}

template <class T>
SLinkedList<T>::Iterator::Iterator(SLinkedList<T>* pList, bool begin)
{
    /*
        Constructor of iterator
        * Set pList to pList
        * begin = true:
        * * Set current (index = 0) to pList's head if pList is not NULL
        * * Otherwise set to NULL (index = -1)
        * begin = false:
        * * Always set current to NULL
        * * Set index to pList's size if pList is not NULL, otherwise 0
    */
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
typename SLinkedList<T>::Iterator& SLinkedList<T>::Iterator::operator=(const Iterator& iterator)
{
    /*
        Assignment operator
        * Set this current, index, pList to iterator corresponding elements.
    */
    this->current = iterator.current;
    this->index = iterator.index;
    this->pList = iterator.pList;
    return *this;
}

template <class T>
void SLinkedList<T>::Iterator::remove()
{
    /*
        Remove a node which is pointed by current
        * After remove current points to the previous node of this position (or node with index - 1)
        * If remove at front, current points to previous "node" of head (current = NULL, index = -1)
        * Exception: throw std::out_of_range("Segmentation fault!") if remove when current is NULL
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
    SLinkedList<T>::Node *iter = this->pList->head;
    while (iter->next != this->current) {
        iter = iter->next;
    }
    this->current = iter;
    this->pList->removeAt(this->index);
    this->index--;
    /*
    SLinkedList<T>::Node* iter = this->head;
    if (index == 0) {
        SLinkedList<T>::Node* temp = this->head;
        this->head = this->head->next;
        T data = temp->data;
        delete temp;
        count--;
        return data;
    }
    for (int i = 0; i < index - 1; i++) {
        iter = iter->next;
    }
    //delete
    SLinkedList<T>::Node* temp = iter->next;    //Truoc do -1
    iter->next = temp->next;
    T data = temp->data;
    if (temp == this->tail) {
        this->tail = iter;
    }
    delete temp;
    count--;
    return data;*/
}

template <class T>
void SLinkedList<T>::Iterator::set(const T& e)
{
    /*
        Set the new value for current node
        * Exception: throw std::out_of_range("Segmentation fault!") if current is NULL
    */
    if (this->current == NULL) {
        throw std::out_of_range("Segmentation fault!");
    }
    this->current->data = e;
}

template <class T>
T& SLinkedList<T>::Iterator::operator*()
{
    /*
        Get data stored in current node
        * Exception: throw std::out_of_range("Segmentation fault!") if current is NULL
    */
    if (this->current == NULL) {
        throw std::out_of_range("Segmentation fault!");
    }
    return this->current->data;
}

template <class T>
bool SLinkedList<T>::Iterator::operator!=(const Iterator& iterator)
{
    /*
        Operator not equals
        * Returns true if two iterators points the same node and index
    */
    return ((this->current != iterator.current) || (this->index != iterator.index));
}
// Prefix ++ overload
template <class T>
typename SLinkedList<T>::Iterator& SLinkedList<T>::Iterator::operator++()
{
    /*
        Prefix ++ overload
        * Set current to the next node
        * If iterator corresponds to the previous "node" of head, set it to head
        * Exception: throw std::out_of_range("Segmentation fault!") if iterator corresponds to the end
    */
    if (this->current == NULL || index == -1) {
        throw std::out_of_range("Segmentation fault!");
    }

    this->current = this->current->next;
    this->index++;

    return *this;
}
// Postfix ++ overload
template <class T>
typename SLinkedList<T>::Iterator SLinkedList<T>::Iterator::operator++(int)
{
    /*
        Postfix ++ overload
        * Set current to the next node
        * If iterator corresponds to the previous "node" of head, set it to head
        * Exception: throw std::out_of_range("Segmentation fault!") if iterator corresponds to the end
    */
    if (this->current == NULL || index == -1) {
        throw std::out_of_range("Segmentation fault!");
    }

    SLinkedList<T>::Iterator iter = *this;

    this->current = this->current->next;
    this->index++;

    return iter;
}

int main()
{
    SLinkedList<int> list;
    int size = 10;

    for (int index = 0; index < size; index++) {
        cout << list.empty() << endl;
        list.add(index);
        list.set(0, 4);
    }
    cout << list.get(5);
    cout << list.indexOf(2);
    cout << list.contains(8);

    cout << list.toString();
    return 0;
}
