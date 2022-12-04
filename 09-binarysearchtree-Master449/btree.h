#ifndef H_BTREE
#define H_BTREE

//***************************************************************************
//
//	David Flowers II
//	Z1942130
//	CSCI 340 - 0004
//
//  I certify that this is my own work and where appropriate an extension 
//  of the starter code provided for the assignment.
//
//***************************************************************************

#include "btree.h"
#include "node.h"

// Random Side Functions Provided to us in the github
typedef enum { left_side, right_side } SIDE;
SIDE rnd ( ) { return rand ( ) % 2 ? right_side : left_side; }

template <typename T> class BinaryTree {

public:
    BinaryTree();                                      // default constructor
    unsigned     getSize() const;                      // returns size of tree
    unsigned     getHeight() const;                    // returns height of tree
    virtual void Insert(const T&);                     // inserts node in tree
    void         Inorder(void (*)(const T&));          // inorder traversal of tree

protected:
    Node<T> *root;                                      // root of tree

private:
    unsigned _getSize(Node<T> *) const;                 // private version of getSize()
    unsigned _getHeight(Node<T> *) const;               // private version of getHeight()
    void     _Insert(Node<T> *&, const T&);             // private version of Insert()
    void     _Inorder(Node<T> *, void (*)(const T&));   // private version of Inorder()
};



// ----------------------- Public Functions -----------------------
/**
 * @brief Construct a new Binary Tree object
 */
template <typename T>
BinaryTree <T>::BinaryTree() {
    root = nullptr;
}

/**
 * @brief Returns the size of the binary tree object using the private method
 *
 * Since root is protected, public functions cannot access it
 * directly, hence the use of the private version further down
 * 
 * @return unsigned size
 */
template <typename T>
unsigned BinaryTree <T>::getSize() const {
    return _getSize(root);
}

/**
 * @brief Returns the height of the binary tree using the private method
 * 
 * Since root is protected, public functions cannot access it
 * directly, hence the use of the private version further down
 *
 * @return unsigned Height
 */
template <typename T>
unsigned BinaryTree <T>::getHeight() const {
    return _getHeight(root);
}

/**
 * @brief Inserts a node into the tree using the private method
 *
 * Since root is protected, public functions cannot access it
 * directly, hence the use of the private version further down
 * 
 * @param node to be inserted
 */
template <typename T>
void BinaryTree <T>::Insert(const T& temp) {
    _Insert(root, temp);
}

/**
 * @brief Prints the tree using InOrder Traversal
 * 
 * Since root is protected, public functions cannot access it
 * directly, hence the use of the private version further down
 */
template <typename T>
void BinaryTree <T>::Inorder(void (*print)(const T&)) {
    _Inorder(root, print);
}



// ----------------------- Private Functions -----------------------
/**
 * @brief Private version of getSize()
 *
 * If the node is equal to 0, the size is 0
 * Otherwise uses recursion to find the size
 * of both sides added + 1
 * 
 * @return unsigned Size
 */
template <typename T>
unsigned BinaryTree <T>::_getSize(Node<T> * node) const {
    if (node == nullptr) {
        return 0;
    } else {
        return (_getSize(node->left) + 1 + _getSize(node->right));
    }
}

/**
 * @brief Private version of getHeight
 * 
 * If the node is equal to 0, the height is 0
 *
 * @return unsigned Height
 */
template <typename T>
unsigned BinaryTree <T>::_getHeight(Node<T> * node) const {
    if (node == nullptr) {
        return 0;
    } else {

        int hr = _getHeight(node->right);
        int hl = _getHeight(node->left);

        if (hl > hr) {
            return 1 + hl;
        } else {
            return 1 + hr;
        }
    }
}

/**
 * @brief Private version of Insert()
 *
 * If the root is 0, congrats thats a new root
 * if not, picks a random side use SIDE to insert
 * the new value to a node.
 * 
 * @param node this is the root of the tree
 * @param temp value to be inserted into the tree
 */
template <typename T>
void BinaryTree <T>::_Insert(Node<T> *& node, const T& temp ) {
    if (node == nullptr) {
        Node <T> * newNode;
        newNode = new Node <T>(temp);
        node = newNode;
    } else {
        SIDE s = rnd();

        if (s == right_side)
            _Insert(node->right, temp);
        else
            _Insert(node->left, temp);
    }
}

/**
 * @brief Private version of Inorder()
 * 
 * Uses recursion to print the values using InOrder
 *
 * @param node starting point
 * @param print this calls the print function to print a value
 */
template <typename T>
void BinaryTree <T>::_Inorder(Node<T> * node, void ( *print )( const T& )) {
    if (node != nullptr) {
        _Inorder( node->left, print);
        print(node->data);
        _Inorder(node->right, print);
    }
}

#endif // End of H_BTREE
