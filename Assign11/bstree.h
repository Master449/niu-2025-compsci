#ifndef BSTREE_H
#define BSTREE_H

//*******************************************************************
//
//  bstree.h
//  CSCI 241 Assignment 11
//
//  Created by David Flowers II (z1942130)
//
//*******************************************************************

#include <iostream>

using std::cout;
using std::endl;

template <class K, class V>
struct node
{
    K key;
    V value;
	node<K, V>* left;
    node<K, V>* right;

	node(const K& key = K(), const V& value = V(), node<K,V>* left = nullptr, node<K,V>* right = nullptr){
        this->key = key;
        this->value = value;

        this->left = left;
        this->right = right;
	}
};

template <class K, class V>
class bstree {
    private:
        node<K, V>* root = nullptr;
        size_t treeSize;

        // These functions are private as they are used for recursion and
        // other functions that need to call root when they are called
        // Therefore, main should not access them.

        /**
        * node <K, V>* clone(node<K, V>*>
        *
        * This function recursively copies the bstree object
        *
        * @param node<K, V>* the public functions sends root for the node
        *
        * @return this as the new bstree
        *
        ********************************************************************************/
        node<K, V>* clone(node<K, V>*);

        /**
        * void destroy(node<K, V>*);
        *
        * Recursively deletes the nodes of a bstree object.
        *
        * @param node<k, V>* root (as root is a private data member)
        ********************************************************************************/
        void destroy(node<K, V>*);

        /**
        * size_t height(node<K, V>* p) const
        *
        * This function is sent root (as it is protected) to iterate through
        * the tree and find the highest one.
        *
        * @param node<K, V>* p (sent root)
        *
        * @return size_t (the height)
        ********************************************************************************/
        size_t height(node<K, V>* p) const;

        /**
        * void preorder(node<K, V>*) const
        *
        * This function traverses and prints the binary tree in preorder.
        * This function is used to start at root of the called tree, since
        * main cannot access root.
        *
        * @param node<K, V>* root of binary tree
        ********************************************************************************/
        void preorder(node<K, V>*) const;

        /**
        * void inorder(node<K, V>*) const
        *
        * This function traverses and prints the binary tree inorder.
        * This function is used to start at root of the called tree, since
        * main cannot access root.
        *
        * @param node<K, V>* root of binary tree
        ********************************************************************************/
        void inorder(node<K, V>*) const;

        /**
        * void postorder(node<K, V>*) const
        *
        * This function traverses and prints the binary tree in postorder.
        * This function is used to start at root of the called tree, since
        * main cannot access root.
        *
        * @param node<K, V>* root of binary tree
        ********************************************************************************/
        void postorder(node<K, V>*) const;

        /**
        * void print_level(node<K, V>*, size_t) const
        *
        * This function traverses and prints the binary tree using print level.
        * This function is used to start at root of the called tree, since
        * main cannot access root.
        *
        * @param node<K, V>* root of binary tree
        * @param size_t the size of the tree
        ********************************************************************************/
        void print_level(node<K, V>*, size_t) const;

    public:

        // These functions are the ones being used by the driver program
        // some of these will call the above functions to operate correctly

        /**
        * bstree();
        *
        * This is the constructor for the bstree class
        ********************************************************************************/
        bstree();

        /**
        * ~bstree()
        *
        * This is the deconstructor for the bstree class.
        * it calls the clear method to delete all nodes of an object
        ********************************************************************************/
        ~bstree();

        /**
        * bstree(const bstree<K, V>& x)
        *
        * This is the copy constructor. It is used to copy on object
        * by calling the clone function, which iterates through the tree
        * and copies all parent and child nodes
        *
        * @param const bstree<K, V>& x  the object to be copied
        ********************************************************************************/
        bstree(const bstree<K, V>& x);

        /**
        * bstree<K, V>& operator=(const bstree<K, V>& x)
        *
        * This is the overloaded assignment operator used to assign a tree and
        * all of its nodes to a new object (this pointer)
        *
        * @param bstree<K, V>& x Object to be copied
        ********************************************************************************/
        bstree<K, V>& operator=(const bstree<K, V>& x);

        /**
        * void clear()
        *
        * This function calls the private member destroy to recursively delete the tree
        ********************************************************************************/
        void clear();

        /**
        * size_t size() const
        *
        * This just returns the treeSize variable
        *
        * @return size_t treeSize
        *
        ********************************************************************************/
        size_t size() const;

        /**
        * size_t height() const
        *
        * This function calls the private height function to get the root recursively
        *
        * @return size_t the height of the tree
        *
        ********************************************************************************/
        size_t height() const;

        /**
        * bool empty() const
        *
        * Checks to see if the tree is empty
        *
        * @return true if its empty
        *         false if it is not
        *
        ********************************************************************************/
        bool empty() const;

        /**
        * const K& min() const
        *
        * This member function returns the minimum key in the tree
        *
        * @return K& min key
        ********************************************************************************/
        const K& min() const;

        /**
        * const K& max() const
        *
        * This member function returns the maximum key in the tree
        *
        * @return K& max key
        ********************************************************************************/
        const K& max() const;

        /**
        * bool insert(const K& key, const V& value)
        *
        * This member function attempts to insert a key and value into the tree.
        *
        * @param K& key to be inserted
        * @param V& value to be inserted
        *
        * @return true if it was successfully inserted
        *         false if it failed (already exists in the tree)
        *
        ********************************************************************************/
        bool insert(const K& key, const V& value);

        /**
        * bool remove(const K& key)
        *
        * This function attempts to remove a key from the binary tree.
        *
        * @param K& to be removed.
        *
        * @return true if the matching key was removed and size updated
        *         false if the key is not in the tree
        *
        ********************************************************************************/
        bool remove(const K& key);

        /**
        * const node<K,V>* find(const K& key) const
        *
        * This function attempts to find the specified key in the tree.
        *
        * @param K& needed to be found
        *
        * @return the key
        *         if its not there returns nullptr
        *
        ********************************************************************************/
        const node<K,V>* find(const K& key) const;

        /**
        * void preorder() const
        *
        * This function prints the tree using the preorder method. All it does is
        * call its corresponding private function to start at the root.
        ********************************************************************************/
        void preorder() const;

        /**
        * void inorder() const
        *
        * This function prints the tree using the inorder method. All it does is
        * call its corresponding private function to start at the root.
        ********************************************************************************/
        void inorder() const;

        /**
        * void postorder() const
        *
        * This function prints the tree using the postorder method. All it does is
        * call its corresponding private function to start at the root.
        ********************************************************************************/
        void postorder() const;

        /**
        * void level_order() const
        *
        * This function prints the tree using the level order method. All it does is
        * call its corresponding private function to start at the root.
        ********************************************************************************/
        void level_order() const;
};

template <class K, class V>
bstree<K, V>::bstree(){
    root = nullptr;
    treeSize = 0;
}

template <class K, class V>
bstree<K, V>::~bstree() {
    clear();
}

template <class K, class V>
bstree<K, V>::bstree(const bstree<K, V>& x) {
    treeSize = x.treeSize;

    root = clone(x.root);
}

template <class K, class V>
bstree<K, V>& bstree<K, V>::operator=(const bstree<K, V>& x) {
    if (this != &x) {
        clear();

        treeSize = x.treeSize;

        root = clone(x.root);
    }

    return *this;
}

template <class K, class V>
node<K, V>* bstree<K, V>::clone(node<K, V>* p) {
    if (p != nullptr){
        node<K, V>* new_node = new node<K, V>(p->key, p->value);
        new_node->key = p->key;
        new_node->value = p->value;

        new_node->left = clone(p->left);
        new_node->right = clone(p->right);

        return new_node;
    } else {
        return nullptr;
    }
}

template <class K, class V>
void bstree<K, V>::clear() {
    destroy(root);
    root = nullptr;
    treeSize = 0;
}

template <class K, class V>
void bstree<K, V>::destroy(node<K, V>* p) {
    if (p != nullptr) {
        destroy(p->left);
        destroy(p->right);

        delete p;
    }
}

template <class K, class V>
size_t bstree<K, V>::size() const {
    return treeSize;
}

template <class K, class V>
size_t bstree<K, V>::height() const {
    return height(root);
}

template <class K, class V>
size_t bstree<K, V>::height(node<K, V>* p) const {
    if (p == nullptr)
        return 0;

    if (height(p->left) > height(p->right))
        return 1 + height(p->left);
    else
        return 1 + height(p->right);
}

template <class K, class V>
bool bstree<K, V>::empty() const {
    if (treeSize == 0) 
        return true;
    else
        return false;
}

template <class K, class V>
const K& bstree<K, V>::min() const {
    node<K, V>* current = this->root;

    while (current->left != nullptr){
        current = current->left;
    }

    return (current->key);
}

template <class K, class V>
const K& bstree<K, V>::max() const {
    node<K, V>* current = this->root;

    while (current->right != nullptr){
        current = current->right;
    }

    return (current->key);
}

template <class K, class V>
bool bstree<K, V>::insert(const K& key, const V& value) {
    node<K, V>* p = this->root;
    node<K, V>* parent = nullptr;

    while (p != nullptr && key != p->key){
        parent = p;
        if (key < p->key)
            p = p->left;
        else
            p = p->right;
    }

    if (p != nullptr) {
        return false;
    }
    
    node<K, V>* new_node = new node<K, V>(key, value);

    if (parent == nullptr) {
        root = new_node;
    } else {
        if (new_node->key < parent->key)
            parent->left = new_node;
        else
            parent->right = new_node;
    }

    treeSize = treeSize + 1;
    return true;
}

template <class K, class V>
bool bstree<K, V>::remove(const K& key) {
    node<K, V>* p = root;
    node<K, V>* parent = nullptr;
    node<K, V>* replace;
    node<K, V>* replace_parent;

    while (p != nullptr && key != p->key) {
        parent = p;
        if (key < p->key) {
            p = p->left;
        } else {
            p = p->right;
        }
    }

    if (p == nullptr) {
        return false;
    }

    if (p->left == nullptr) {
        replace = p->right;
    } else if (p->right == nullptr) {
        replace = p->left;
    } else {
        replace_parent = p;
        replace = p->left;

        while (replace->right != nullptr) {
            replace_parent = replace;
            replace = replace->right;
        }

        if (replace_parent != p){
            replace_parent->right = replace->left;
            replace->left = p->left;
        }
        replace->right = p->right;
    }

    if (parent == nullptr) {
        root = replace;
    } else {
        if (p->key < parent->key)
            parent->left = replace;
        else
            parent->right = replace;
    }

    delete p;
    treeSize = treeSize - 1;

    return true;
}

template <class K, class V>
const node<K, V>* bstree<K, V>::find(const K& key) const {
    node<K, V>* current = root;

    while (current) {
        if (key < current->key) {
            current = current->left;
        } else if (key > current->key) {
            current = current->right;
        } else {
            return current;
        }
    }
    return nullptr;
}

template <class K, class V>
void bstree<K, V>::preorder() const {
    preorder(root);
}

template <class K, class V>
void bstree<K, V>::preorder(node<K, V>* p) const {
    if (p != nullptr){
        cout << p->key << ": " << p->value << endl;
        preorder(p->left);
        preorder(p->right);
    }
}

template <class K, class V>
void bstree<K, V>::inorder() const {
    inorder(root);
}

template <class K, class V>
void bstree<K, V>::inorder(node<K, V>* p) const {
    if (p != nullptr){
        inorder(p->left);
        cout << p->key << ": " << p->value << endl;
        inorder(p->right);
    }
}

template <class K, class V>
void bstree<K, V>::postorder() const {
    postorder(root);
}

template <class K, class V>
void bstree<K, V>::postorder(node<K, V>* p) const {
    if (p != nullptr) {
        postorder(p->left);
        postorder(p->right);
        cout << p->key << ": " << p->value << endl;
    }
}

template <class K, class V>
void bstree<K, V>::level_order() const {
    size_t h = height(root);

    size_t i = 1;

    while (i <= h){
        print_level(root, i);
        i++;
    }
}

template <class K, class V>
void bstree<K, V>::print_level(node<K, V>* p, size_t level) const {
    if (p == nullptr)
        return;

    if (level == 1){
        cout << p->key << ": " << p->value << endl;
    } else if (level > 1){
        print_level(p->left, level-1);
        print_level(p->right, level-1);
    }
}

#endif
