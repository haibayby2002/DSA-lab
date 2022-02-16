#include <iostream>
#include <sstream>
#include <string>

using namespace std;

template <class K, class D, int M> // K: key, D: data, M: degree of BTree
class BTree {
    /// Convention: Left sub-tree < Root's key <= Right sub-tree

public:
    class Entry;
    class Node;

private:
    Node* root;

public:
    BTree() : root(0) {};
    ~BTree() {}

    ///////////////////////////////////////////////////
    ///             CLASS `Entry`                   ///
    ///////////////////////////////////////////////////
public:
    class Entry {
    private:
        K key;
        D data;
        Node* rightPtr;

        friend class BTree<K, D, M>;

    public:
        Entry(K key = K{}, D value = D{}) : key(key), data(value), rightPtr(0) {}
        ~Entry() {}

        string toString() {
            stringstream ss;
            ss << "<"
                << this->key << ","
                << this->data
                << ">";
            return ss.str();
        }

    };

    ///////////////////////////////////////////////////
    ///             CLASS `Node`                    ///
    ///////////////////////////////////////////////////
public:
    class Node {
    private:
        Node* firstPtr;
        int numEntries;
        Entry entries[M - 1];

        friend class BTree<K, D, M>;

    public:
        Node() : firstPtr(0), numEntries(0) {};
        ~Node() { }

        bool isFull() {
            return (numEntries >= M - 1);
        }

        /// BEGIN STUDENT CODE
        string toString() {
            stringstream ss;
            // Fill your code here
            ss << "[";
            ss << "(" << this->numEntries << ")";
            for (int i = 0; i < this->numEntries; i++) {
                ss << entries[i].toString();
            }
            ss << "]";
            return ss.str();
        }
        /// END STUDENT CODE

    };

    /////////////////////////////////////////////////////////////
    ///         CLASS `BTree`: method run sample test         ///
    /////////////////////////////////////////////////////////////
    void testPrintNode(K* keys, D* data, int size) {
        Node node;

        for (int idx = 0; idx < size; idx++) {
            node.entries[idx].key = keys[idx];
            node.entries[idx].data = data[idx];
        }
        node.numEntries = size;
        cout << node.toString() << endl;
    }

    /// BEGIN STUDENT CODE
    /// ==========================================================
    ///
    /// 
    /*
    string toStringPreOrder(Node* root) {
        stringstream ss;
        for (int i = 0; i < this->root.numEntries; i++) {
            ss << toStringPreOrder(this->root->entries[i].rightPtr);
        }
        return ss.str();
    }
    string toStringPreOrder() {
        return toStringPreOrder(this->root);
    }
    */

    string toStringPreOrder(Node* temp)
    {
        stringstream res;
        if (temp != NULL)
        {
            res << temp->toString() << " ";
            res << toStringPreOrder(temp->firstPtr);
            for (int i = 0; i < temp->numEntries; i++)
                res << toStringPreOrder(temp->entries[i].rightPtr);
        }
        return res.str();
    }

    string toStringPreOrder()
    {
        return toStringPreOrder(this->root);
    }

    /// END STUDENT CODE

    /// BEGIN STUDENT CODE
    /// ==================================================
    /// search(key, outNodePtr, outEntryIdx)
    bool search(const K& key, Node*& outNodePtr, int& outEntryIdx) {
        Node* temp = this->root;
        while (temp != NULL)
        {
            if (key < temp->entries[0].key)
                temp = temp->firstPtr;
            else
            {
                if (key > temp->entries[temp->numEntries - 1].key)
                    temp = temp->entries[temp->numEntries - 1].rightPtr;
                else
                {
                    for (int i = 0; i < temp->numEntries; i++)
                        if (key == temp->entries[i].key)
                        {
                            outNodePtr = temp;
                            outEntryIdx = i;
                            return true;
                        }
                    for (int i = 1; i < temp->numEntries; i++)
                        if ((temp->entries[i].key > key) && (temp->entries[i - 1].key < key))
                        {
                            temp = temp->entries[i - 1].rightPtr;
                            break;
                        }
                }
            }
        }
        return false;
    }

    void insertEntry(Node* pNode, int entryIdx, const Entry& newEntry) {
        int shifter = pNode->numEntries;
        while (shifter > entryIdx + 1)
        {
            pNode->entries[shifter] = pNode->entries[shifter - 1];
            shifter--;
        }
        pNode->entries[shifter] = newEntry;
    }

    void splitNode(Node* pNode, int entryIdx, Entry& upEntry) {
        int minEntries = (M % 2 ? (M + 1) / 2 : M / 2) - 1;
        int fromNdx;
        Node* rightPtr = new Node();
        if (entryIdx <= minEntries - 1)
            fromNdx = minEntries;
        else
            fromNdx = minEntries + 1;
        int toNdx = 0;

        while (fromNdx < pNode->numEntries)
        {
            rightPtr->entries[toNdx] = pNode->entries[fromNdx];
            fromNdx++;
            toNdx++;
        }
        rightPtr->numEntries = toNdx;
        pNode->numEntries = pNode->numEntries - rightPtr->numEntries;

        if (entryIdx <= minEntries - 1)
        {
            insertEntry(pNode, entryIdx, upEntry);
            pNode->numEntries++;
        }
        else
        {
            insertEntry(rightPtr, entryIdx - minEntries - 1, upEntry);
            rightPtr->numEntries++;

        }
        upEntry = pNode->entries[pNode->numEntries - 1];
        rightPtr->firstPtr = upEntry.rightPtr;
        upEntry.rightPtr = rightPtr;
        pNode->numEntries--;
    }

    int searchNode(Node* nodePtr, K key) {
        if (nodePtr->entries[0].key > key)
            return -1;
        else
        {
            int walker = nodePtr->numEntries - 1;
            while (key < nodePtr->entries[walker].key)
                walker--;
            return walker;
        }
    }

    bool insertNode(Node*& root, const K& key, const D& data, Entry& upEntry) {
        bool taller;
        if (root == NULL)
        {
            upEntry.key = key;
            upEntry.data = data;
            upEntry.rightPtr = NULL;
            taller = true;
        }
        else
        {
            int entryNdx = searchNode(root, key);
            Node* subTree;
            if (entryNdx >= 0)
                subTree = root->entries[entryNdx].rightPtr;
            else
                subTree = root->firstPtr;
            taller = insertNode(subTree, key, data, upEntry);
            if (taller == true)
            {
                if (root->isFull())
                {
                    splitNode(root, entryNdx, upEntry);
                    taller = true;
                }
                else
                {
                    insertEntry(root, entryNdx, upEntry);
                    root->numEntries++;
                    taller = false;
                }
            }
        }
        return taller;
    }

    void insert(Node*& root, const K& key, const D& data) {
        Entry upEntry = Entry(0, 0);
        bool taller = insertNode(root, key, data, upEntry);
        if (taller == true)
        {
            Node* newPtr = new Node();
            newPtr->entries[0] = upEntry;
            newPtr->firstPtr = root;
            newPtr->numEntries = 1;
            root = newPtr;
        }
    }

    /// TODO: Implement following method
    void insert(const K& key, const D& data) {
        insert(root, key, data);
    }

    /// END STUDENT CODE

    /// END STUDENT CODE
};

int main() {
    int keys[] = { 3, 6 };
    int data[] = { 33, 66 };
    int size = sizeof(keys) / sizeof(int);
    BTree<int, int, 5>().testPrintNode(keys, data, size);
    return 0;
}