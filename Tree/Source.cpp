#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"
template<class T>
class BinarySearchTree
{
public:
    class Node;
private:
    Node* root;
public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }

    //Helping function

    Node* findPlaceToInsert(Node* t , T value) {
        if (t == NULL) {
            return t;
        }
        if (t->value >= value) {
            return find(t->pLeft, value);
        }
        if (t->value < value) {
            return find(t->pRight, value);
        }
    }

    Node* find(Node* t, T value) {
        if (t == NULL) {
            return t;
        }
        if (t->value == value) {
            return t;
        }
        if (t->value > value) {
            return find(t->pLeft, value);
        }
        if (t->value < value) {
            return find(t->pRight, value);
        }
    }

    Node* findParentOf(Node* t, T value) {
        if (t == NULL) {
            return NULL;
        }
        if (t->left == value || t->pRight == value) {
            return t;
        }
        if (t->value > value) {
            return findParentOf(t->pLeft, value);
        }
        else if (t->value < value) {
            return findParentOf(t->pRight, value);
        }
        else {
            return t;
        }
    }


    Node* minValueNode(Node* node)
    {
        Node* current = node;

        /* loop down to find the leftmost leaf */
        while (current && current->pLeft != NULL)
            current = current->pLeft;

        return current;
    }
    
    Node* deleteNode(Node* root, int key)
    {
        // base case
        if (root == NULL)
            return root;

        // If the key to be deleted
        // is smaller than the root's
        // key, then it lies in left subtree
        if (key < root->value)
            root->pLeft = deleteNode(root->pLeft, key);

        // If the key to be deleted
        // is greater than the root's
        // key, then it lies in right subtree
        else if (key > root->value)
            root->pRight = deleteNode(root->pRight, key);

        // if key is same as root's key,
        // then This is the Node
        // to be deleted
        else {
            // Node with only one child or no child
            if (root->pLeft == NULL) {
                Node* temp = root->pRight;
                free(root);
                return temp;
            }
            else if (root->pRight == NULL) {
                Node* temp = root->pLeft;
                free(root);
                return temp;
            }

            // Node with two children:
            // Get the inorder successor
            // (smallest in the right subtree)
            Node* temp = minValueNode(root->pRight);

            // Copy the inorder
            // successor's content to this Node
            root->value = temp->value;

            // Delete the inorder va
            root->pRight = deleteNode(root->pRight, temp->value);
        }
        return root;
    }

    Node* insert(Node* node, T key)
    {
        /* If the tree is empty, return a new node */
        if (node == NULL) {
            return new Node(key);
        }
            

        /* Otherwise, recur down the tree */
        if (key <= node->value)
            node->pLeft = insert(node->pLeft, key);
        else if (key > node->value)
            node->pRight = insert(node->pRight, key);

        /* return the (unchanged) node pointer */
        return node;
    }

    void add(T value) {
        if (this->root == NULL) {
            this->root = insert(this->root, value);
        }
        else {
            insert(this->root, value);
        }
    }

   

    void deleteNode(T value) {
        this->root = deleteNode(this->root, value);
    }

    string inOrderRec(Node* root) {
        stringstream ss;
        if (root != nullptr) {
            ss << inOrderRec(root->pLeft);
            ss << root->value << " ";
            ss << inOrderRec(root->pRight);
        }
        return ss.str();
    }

    string inOrder() {
        return inOrderRec(this->root);
    }

    T getMin() {
        //TODO: return the minimum values of nodes in the tree.
        Node* temp = this->root;
        while (temp->pLeft != NULL) {
            temp = temp->pLeft;
        }
        return temp->value;
    }

    T getMax() {
        //TODO: return the maximum values of nodes in the tree.
        Node* temp = this->root;
        while (temp->pRight != NULL) {
            temp = temp->pRight;
        }
        return temp->value;
    }

 

    public:
        int getHeight(Node* t) {
            if (t == NULL) {
                return 0;
            }
            return 1 + max(getHeight(t->pLeft), getHeight(t->pRight));
        }

        int getDiameterAtNode(Node* t) {
            return getHeight(this->root->pLeft) + getHeight(this->root->pRight) + 1;
        }

        int getMaxDiameter(Node* t) {
            return max(max(getDiameterAtNode(t->pLeft), getDiameterAtNode(t->pRight)), getDiameterAtNode(t));
        }

        int getDiameter() {
            //TODO
            return getMaxDiameter(this->root);

        }

    class Node
    {
    private:
        T value;
        Node* pLeft, * pRight;
        friend class BinarySearchTree<T>;
    public:
        Node(T value) : value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
};

template<class K, class V>
class BinaryTree
{
public:
    class Node;
private:
    Node* root;
public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }
    class Node
    {
    private:
        K key;
        V value;
        Node* pLeft, * pRight;
        friend class BinaryTree<K, V>;
    public:
        Node(K key, V value) : key(key), value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
    void addNode(string posFromRoot, K key, V value)
    {
        if (posFromRoot == "")
        {
            this->root = new Node(key, value);
            return;
        }
        Node* walker = this->root;
        int l = (int)posFromRoot.length();
        for (int i = 0; i < l - 1; i++)
        {
            if (!walker)
                return;
            if (posFromRoot[i] == 'L')
                walker = walker->pLeft;
            if (posFromRoot[i] == 'R')
                walker = walker->pRight;
        }
        if (posFromRoot[l - 1] == 'L')
            walker->pLeft = new Node(key, value);
        if (posFromRoot[l - 1] == 'R')
            walker->pRight = new Node(key, value);
    }



    int getHeight(Node* t) {
        if (t == NULL) {
            return 0;
        }
        return 1 + max(getHeight(t->pLeft), getHeight(t->pRight));
    }

    int getDiameterAtNode(Node* t) {
        return getHeight(this->root->pLeft) + getHeight(this->root->pRight) + 1;
    }

    int getMaxDiameter(Node* t) {
        return max(max(getDiameterAtNode(t->pLeft), getDiameterAtNode(t->pRight)), getDiameterAtNode(t));
    }

    int getDiameter() {
        //TODO
        if (this->root == NULL) return 0;
        return getMaxDiameter(this->root);

    }
};

int main() {
    BinaryTree<int, int> binaryTree;
    cout << binaryTree.getDiameter();
    return 0;
}