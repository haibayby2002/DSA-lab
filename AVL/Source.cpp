#include <iostream>
#include <math.h>
#include <queue>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}

void printInteger(int& n)
{
    cout << n << " ";
}

template<class T>
class AVLTree
{
public:
    class Node;
private:
    Node* root;
protected:
    int getHeightRec(Node* node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() {}
    int getHeight()
    {
        return this->getHeightRec(this->root);
    }
    void printTreeStructure()
    {
        int height = this->getHeight();
        if (this->root == NULL)
        {
            cout << "NULL\n";
            return;
        }
        queue<Node*> q;
        q.push(root);
        Node* temp;
        int count = 0;
        int maxNode = 1;
        int level = 0;
        int space = pow(2, height);
        printNSpace(space / 2);
        while (!q.empty())
        {
            temp = q.front();
            q.pop();
            if (temp == NULL)
            {
                cout << " ";
                q.push(NULL);
                q.push(NULL);
            }
            else
            {
                cout << temp->data;
                q.push(temp->pLeft);
                q.push(temp->pRight);
            }
            printNSpace(space);
            count++;
            if (count == maxNode)
            {
                cout << endl;
                count = 0;
                maxNode *= 2;
                level++;
                space /= 2;
                printNSpace(space / 2);
            }
            if (level == height)
                return;
        }
    }

    //Helping function
    /*
    Node* rightRotate(Node* y)
    {
        Node* x = y->pLeft;
        Node* T2 = x->pRight;

        // Perform rotation
        x->pRight = y;
        y->pLeft = T2;

        // Update heights
        y->height = max(height(y->pLeft), height(y->pRight)) + 1;
        x->height = max(height(x->pLeft), height(x->pRight)) + 1;

        // Return new root
        return x;
    }
    */

    Node* rotateRight(Node* root) {
        Node* tempPtr = root->pLeft;
        root->pLeft = tempPtr->pRight;
        tempPtr->pRight = root;
        return tempPtr;
    }

    Node* rotateLeft(Node* root) {
        Node* tempPtr = root->pRight;
        root->pRight = tempPtr->pLeft;
        tempPtr->pLeft = root;
        return tempPtr;
    }

    Node* leftBalance(Node* root, bool &taller) {
        Node* leftTree = root->pLeft;
        if (leftTree->balance == BalanceValue::LH) {
            root->balance = BalanceValue::EH;
            leftTree->balance = BalanceValue::EH;
            root = rotateRight(root);
            taller = false;
        }
        else if(leftTree->balance == BalanceValue::RH){
            Node* rightTree = leftTree->pRight;
            if (rightTree->balance == BalanceValue::LH) {
                root->balance = BalanceValue::RH;
                leftTree->balance = BalanceValue::EH;
            }
            else if (rightTree->balance == BalanceValue::EH) {
                leftTree->balance = BalanceValue::EH;
            }
            else {  //RH
                root->balance = BalanceValue::EH;
                leftTree->balance = BalanceValue::LH;
            }
            rightTree->balance = BalanceValue::EH;
            root->pLeft = rotateLeft(leftTree);
            root = rotateRight(root);
            taller = false;
        }
        return root;
    }

    Node* rightBalance(Node* root, bool& taller) {
        Node* rightTree = root->pRight;
        if (rightTree->balance == BalanceValue::RH) { 
            root->balance = BalanceValue::EH;
            rightTree->balance = BalanceValue::EH;
            root = rotateLeft(root);
            taller = false;
        }
        else if(rightTree->balance == BalanceValue::LH){
            Node* leftTree = rightTree->pLeft;
            if (leftTree->balance == BalanceValue::RH) {
                root->balance = BalanceValue::LH;
                rightTree->balance = BalanceValue::EH;
            }
            else if (leftTree->balance == BalanceValue::EH) {
                rightTree->balance = BalanceValue::EH;
            }
            else {
                root->balance = BalanceValue::EH;
                rightTree->balance = BalanceValue::RH;
            }
            leftTree->balance = BalanceValue::EH;
            root->pRight = rotateRight(rightTree);
            root = rotateLeft(root);
            taller = false;
        }
        return root;
    }

    Node* AVLInsert(Node *root, Node *newPtr, bool &taller) {
        if (root == NULL) {
            root = newPtr;
            taller = true;
            return root;
        }
        if (newPtr->data < root->data) {
            root->pLeft = AVLInsert(root->pLeft, newPtr, taller);
            //Left subtree is taller
            if (taller) {
                if (root->balance == BalanceValue::LH) {
                    root = leftBalance(root, taller);
                }
                else if (root->balance == BalanceValue::EH) {
                    root->balance = BalanceValue::LH;
                }
                else {
                    root->balance = BalanceValue::EH;
                    taller = false;
                }
            }
        }
        else {
            root->pRight = AVLInsert(root->pRight, newPtr, taller);
            //Right subtree is taller
            if (taller) {
                if (root->balance == BalanceValue::LH) {
                    root->balance = BalanceValue::EH;
                    taller = false;
                }
                else if (root->balance == BalanceValue::EH) {
                    root->balance = BalanceValue::RH;
                }
                else {
                    root = rightBalance(root, taller);
                }
            }
        }
        return root;
    }

    void insert(const T& value)
    {
        //TODO
        bool taller = false;
        this->root = AVLInsert(this->root, new Node(value), taller);

    }

    Node* deleteRightBalance(Node* root, bool& shorter) {
        if (root->balance == BalanceValue::LH) {
            root->balance = BalanceValue::EH;
        }
        else if (root->balance == BalanceValue::EH) {
            root->balance = BalanceValue::RH;
            shorter = false;
        }
        else {  //RH
            Node* rightTree = root->pRight;
            if (rightTree->balance == BalanceValue::LH) {
                Node* leftTree = rightTree->pLeft;
                if (leftTree->balance == BalanceValue::LH) {
                    rightTree->balance = BalanceValue::RH;
                    root->balance = BalanceValue::EH;
                }
                else if (leftTree->balance == BalanceValue::EH) {
                    root->balance = BalanceValue::LH;
                    rightTree->balance = BalanceValue::EH;
                }
                else {  //RH
                    root->balance = BalanceValue::LH;
                    rightTree->balance = BalanceValue::EH;
                }
                leftTree->balance = BalanceValue::EH;
                root->pRight = rotateRight(rightTree);
            }
            else {
                if (rightTree->balance != BalanceValue::EH) {
                    root->balance = BalanceValue::EH;
                    rightTree->balance = BalanceValue::EH;
                }
                else {
                    root->balance = BalanceValue::RH;
                    rightTree->balance = BalanceValue::LH;
                    shorter = false;
                }
                root = rotateLeft(root);
            }
        }
        return root;
    }

    Node* deleteLeftBalance(Node* root, bool& shorter) {
        if (root->balance == BalanceValue::EH) {
            root->balance = BalanceValue::EH;
        }
        else if (root->balance == BalanceValue::EH) {
            root->balance = BalanceValue::LH;
            shorter = false;
        }
        else {
            Node* leftTree = root->pLeft;
            if (leftTree->balance == BalanceValue::RH) {
                Node* rightTree = leftTree->pRight;
                if (rightTree->balance == BalanceValue::RH) {
                    leftTree->balance = BalanceValue::LH;
                    root->balance = BalanceValue::EH;
                }
                else if (rightTree->balance == BalanceValue::EH) {
                    root->balance = BalanceValue::RH;
                    leftTree->balance = BalanceValue::EH;
                }
                else {
                    root->balance = BalanceValue::RH;
                    leftTree->balance = BalanceValue::EH;
                }
                rightTree->balace = BalanceValue::EH;
                root->pLeft = rotateLeft(leftTree);
            }
            else {
                if (leftTree->balance != BalanceValue::EH) {
                    root->balance = BalanceValue::EH;
                    leftTree->balance = BalanceValue::EH;
                }
                else {
                    root->balance = BalanceValue::LH;
                    leftTree->balance = BalanceValue::RH;
                    shorter = false;
                }
                root = rotateRight(root);
            }
        }
        return root;
    }

    Node* AVLDelete(Node* root, T deleteKey, bool& shorter, bool& success) {
        if (root == NULL) {
            shorter = false;
            success = false;
            return NULL;
        }
        if (deleteKey < root->data) {   //Delete on left
            root->pLeft = AVLDelete(root->pLeft, deleteKey, shorter, success);
            if (shorter) {
                root = deleteRightBalance(root, shorter);
            }
        }
        else {
            Node* deleteNode = root;
            if (root->pRight == NULL) {
                Node* newRoot = root->pLeft;
                success = true;
                shorter = true;
                delete deleteNode;
                return newRoot;
            }
            else if (root->pLeft == NULL) {
                Node* newRoot = root->pRight;
                success = true;
                shorter = true;
                delete deleteNode;
                return newRoot;
            }
            else {
                Node* exchPtr = root->pLeft;
                while (exchPtr->pRight != NULL) {
                    exchPtr = exchPtr->pRight;
                }
                root->data = exchPtr->data;
                root->pLeft = AVLDelete(root->pLeft, exchPtr->data, shorter, success);
                if (shorter) {
                    root = deleteRightBalance(root, shorter);
                }
            }
        }
        return root;
    }

    void remove(const T& value)
    {
        //TODO
        bool shorter = false, success = false;
        this->root = AVLDelete(root, value, shorter, success);
    }

    void printInorder(Node* root) {
        if (root == NULL) {
            return;
        }
        printInorder(root->pLeft);
        cout << root->data << " ";
        printInorder(root->pRight);
    }

    void printInorder() {
        //TODO
        printInorder(this->root);
    }

    bool search(Node* root, T value) {
        if (root == NULL) {
            return false;
        }
        if (root->data == value) {
            return true;
        }
        else if (root->data > value) {
            return search(root->pLeft, value);
        }
        else {
            return search(root->pRight, value);
        }
    }

    bool search(const T& value) {
        //TODO
        return search(this->root, value);
    }

    void clear() {

    }

    class Node
    {
    private:
        T data;
        Node* pLeft, * pRight;
        BalanceValue balance;
        friend class AVLTree<T>;

    public:
        Node(T value) : data(value), pLeft(NULL), pRight(NULL), balance(EH) {}
        ~Node() {}
    };
};

int main() {
    AVLTree<int> avl;
    int arr[] = { 10,52,98,32,68,92,40,13,42,63,99,100 };
    for (int i = 0; i < 12; i++) {
        avl.insert(arr[i]);
    }
    cout << avl.search(0);
    cout << endl;
    avl.printInorder();
    cout << endl;
    avl.insert(45);
    cout << avl.search(45);
    cout << endl;
    avl.printInorder();
    return 0;
}

