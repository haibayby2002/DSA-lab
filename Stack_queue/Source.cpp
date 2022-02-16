#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>

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
    DLinkedList();
    ~DLinkedList();
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
        friend class DLinkedList<T>;
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
        DLinkedList<T>* pList;
        Node* current;
        int index; // corresponding with current node
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

template <class T>
class Stack {
protected:
    DLinkedList<T> list;
public:
    Stack() {}
    void push(T item) {
        this->list.add(item);
    }
    T pop() {
        return  this->list.removeAt(this->list.size() - 1);
    }
    T top() {
        return this->list.get(this->list.size() - 1);
    }
    bool empty() {
        return this->list.empty();
    }
    int size() {
        return this->list.size();
    }
    void clear() {
        this->list.clear();
    }
};

template<class T>
class Queue {
protected:
    DLinkedList<T> list;
public:
    Queue() {}
    void push(T item) {
        this->list.add(item);
    }
    T pop() {
        return  this->list.removeAt(0);
    }
    T top() {
        return this->list.get(0);
    }
    bool empty() {
        return this->list.empty();
    }
    int size() {
        return this->list.size();
    }
    void clear() {
        this->list.clear();
    }
};



int baseballScore(string ops) {
    /*TODO*/
    int n = ops.length();
    stack<int> myStack;
    for (int i = 0; i < n; i++) {
        if (ops[i] >= '0' && ops[i] <= '9') {
            myStack.push((int)(ops[i] - 48));
        }
        else if (ops[i] == 'C') {
            myStack.pop();
        }
        else if (ops[i] == 'D') {
            int temp = myStack.top();
            myStack.push(temp * 2);
        }
        else if (ops[i] == '+') {
            int temp = myStack.top();
            myStack.pop();
            int temp2 = myStack.top();
            myStack.push(temp);
            myStack.push(temp + temp2);
        }
    }
    int res = 0;
    while (!myStack.empty()) {
        res += myStack.top();
        myStack.pop();
    }
    return res;
}


void bfs(vector<vector<int>> graph, int start) {
    queue<int> q;
    bool visited[10000] = {};
    
    int n = graph.size();
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }
    q.push(start);
    
   
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        if (!visited[current]) {
            cout << current << " ";
            visited[current] = true;
            for (int i = 0; i < graph[current].size(); i++) {
                int index = graph[current][i];
                if (!visited[index]) {
                    q.push(index);
                }
            }
        }
    }
}

vector<int> topologicalSorting(vector<vector<int>> graph) {
    int n = graph.size();
    int in_degree[10000];
    int count = 0;
    vector<int> res;
    for (int i = 0; i < n; i++) {
        in_degree[i] = 0;
    }
    
    //Tim so dinh vao^^
    for (int i = 0; i < n; i++) {       // i vao index
        for (size_t j = 0; j < graph[i].size(); j++) {
            int index = graph[i][j];
            in_degree[index]++;
        }
    }

    //Lam
    //queue<int> q;
    for (count=0;count < n ;count++ ) {   //Chay n lan
        bool flat = false;
        for (int i = 0; i < n; i++) {
            if (in_degree[i] == 0) {    //Ha cac dinh ke cua no xuong
                for (size_t j = 0; j < graph[i].size(); j++) {  //Giam indegree cua cac node can xuong
                    int index = graph[i][j];
                    in_degree[index]--;
                }

                res.push_back(i);
                in_degree[i] = -1;  //Done processing
                flat = true;
                break;
            }
        }
        if (!flat) {
            return vector<int>();
        }
    }
    return res;   //Empty
}

bool isBipartite(vector<vector<int>> graph) {
    queue<int> q;
    int mark[10000] = {};

    int n = graph.size();
    for (int i = 0; i < n; i++) {
        mark[i] = 0;
    }
    

    for (int i = 0; i < n; i++) {
        if (mark[i] == 0) {
            q.push(i);
            mark[i] = 1;

            while (!q.empty()) {
                int current = q.front();
                q.pop();

                for (int i = 0; i < graph[current].size(); i++) {
                    int index = graph[current][i];
                    if (mark[index] == 0) {
                        q.push(index);
                        if (mark[current] == 1) {
                            mark[index] = 2;
                        }
                        else if (mark[current] == 2) {
                            mark[index] = 1;
                        }
                    }
                    else {
                        if (mark[index] == mark[current]) {
                            return false;
                        }
                    }
                }

            }
        }
        
    }
    return true;
    
}

int main() {
    int n = 6;
    int G[6][6] = { {0, 1, 0, 1, 0, 0},
                    {0, 0, 1, 1, 0, 0},
                    {0, 0, 0, 1, 1, 1},
                    {0, 0, 0, 0, 1, 1},
                    {0, 0, 0, 0, 0, 1},
                    {0, 0, 0, 0, 0, 0} };
    vector<vector<int>> graph(n, vector<int>());
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (G[i][j] == 1) graph[i].push_back(j);
        }
    }

    vector<int> res = topologicalSorting(graph);
    if (res.empty()) printf("-1");
    else {
        for (int e : res) printf("%d ", e);
    }

	return 0;
}