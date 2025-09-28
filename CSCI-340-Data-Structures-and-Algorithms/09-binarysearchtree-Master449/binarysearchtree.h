#ifndef __BINARYSEARCHTREE_H__
#define __BINARYSEARCHTREE_H__

#include "node.h"
#include "btree.h"

template <typename T>
class BinarySearchTree : public BinaryTree<T> {
public:
    void Insert(const T &x);       // inserts node with value x
    bool Search(const T &x) const; // searches leaf with value x
    bool Remove(const T &x);       // removes leaf with value x
private:
    void _Insert(Node<T> *&, const T &);      // private version of insert
    bool _Search(Node<T> *, const T &) const; // private version of search
    void _Remove(Node<T> *&, const T &);      // private version of remove
    bool _Leaf(Node<T> *node) const;          // checks if node is leaf
};

// ------------------------------- Public Functions -------------------------------
/**
 * @brief Inserts a node with value x into the tree
 * 
 * calls private version of insert
 *
 * @param x value to be inserted
 */
template<typename T>
void BinarySearchTree<T>::Insert(const T &x) {
    _Insert(this->root, x);
}

/**
 * @brief Searches for a node with value x in the tree
 * 
 * calls private version of search
 *
 * @param x node to be searched for
 *
 * @return true if found
 * @return false if not found
 */
template<typename T>
bool BinarySearchTree<T>::Search(const T &x) const {
    if (_Search(this->root, x)) {
        return true;
    }
    return false;
}

/**
 * @brief Removes a node with value x from the tree
 * 
 * calls private version of remove, after searching for the node
 *
 * @param x value to be removed
 *
 * @return true if it was removed
 * @return false if it was not removed
 */
template<typename T>
bool BinarySearchTree<T>::Remove(const T &x) {
    if (Search(x)) {
        _Remove(this->root, x);
        return true;
    }
    return false;
}

// ------------------------------- Private Functions -------------------------------
/**
 * @brief Private version of insert
 */
template<typename T>
void BinarySearchTree<T>::_Insert(Node<T> *&node, const T &value) {
    if (node == nullptr) {
        node = new Node<T>(value);
    } else if (value < node->data) {
        _Insert(node->left, value);
    } else if (value > node->data) {
        _Insert(node->right, value);
    }
}

/**
 * @brief Private version of search
 * 
 * @param node the root
 * @param x node to be found
 * @return true if found
 * @return false if not found
 */
template<typename T>
bool BinarySearchTree<T>::_Search(Node<T> *node, const T &value) const {;
    if (node == nullptr) {
        return false;
    } else if (value < node->data && !(_Leaf(node))) {
        return _Search(node->left, value);
    } else if (value > node->data && !(_Leaf(node))) {
        return _Search(node->right, value);
    } else {
        return true;
    }
}

/**
 * @brief Private version of remove
 *
 * @param node the root
 * @param x value to traverse the bst
 */
template<typename T>
void BinarySearchTree<T>::_Remove(Node<T> *&node, const T &value) {
    if (node == nullptr) {
        return;
    } else if (value < node->data) {
        _Remove(node->left, value);
    } else if (value > node->data) {
        _Remove(node->right, value);
    } else {
        if (_Leaf(node)) {
            delete node;
            node = nullptr;
        }
    }
}

/**
 * @brief Checks if node is a leaf
 * 
 * @param node to be checked 
 *
 * @return true if the node is a leaf
 * @return false if the node is not a leaf
 */
template<typename T>
bool BinarySearchTree<T>::_Leaf(Node<T> *node) const {
    if (node->left == nullptr && node->right == nullptr) {
        return true;
    }
    return false;
}

#endif // __BINARYSEARCHTREE_H__