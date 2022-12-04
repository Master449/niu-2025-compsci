#include "htable.h"

#define N1 10  // num of decimal digits
#define N2 26  // num of upper-case letters

// Hash function, you may NOT modify this function
int HT::hash(const string &s) {
    int n = (N2 * N1) * (s[0] - 'A') + N1 * (s[1] - 'A') + (s[2] - '0');

    return n % hsize;
}

/**
 * @brief Construct a new HT object
 *
 * @param hs 
 **************************************************************************/
HT::HT(const unsigned &hs) {
    hTable.resize(hs);
    hsize = hs;
}

/**
 * @brief Destructor for the HT object
 *
 * the destructor of the hash table first frees the memory for all list 
 * containers and then frees the memory for the vector containers for the 
 * hash table and the pointer table.
 *
 **************************************************************************/
HT::~HT() {
    // free the memory for all list containers
    for (int i = 0; i < int(hsize); i++) {
        hTable[i].clear();
    }

    // free the memory for the vector containers
    hTable.clear();
    pTable.clear();
}

/**
 * @brief Insert a new item into the hash table
 *
 * This function inserts the record of the item e:(key, desc, num) in the 
 * hash table. If the key already exists in the table, then the function 
 * prints an error message; otherwise, it prints the index value of the 
 * inserted record in the hash table and it also inserts the address of 
 * the record (in the hash table) into the pointer table.
 * 
 * @param e entry to be inserted to both hash table and pointer table
 **************************************************************************/
void HT::insert(const Entry &e) {
    // get the hash value of the key
    int i = hash(e.key);

    // check if the key already exists in the table
    auto it = find_if(hTable[i].begin(), hTable[i].end(), [&](const Entry& entry) { 
        return entry.key == e.key;
    });

    // check if the iterator is at the end of the list
    if (it == hTable[i].end()) {
        // push the entry into the list
        hTable[i].push_front(e);
        
        // push_back the address of the record into the pointer table
        pTable.push_back(&hTable[i].front());

        // print the new entry
        cout << " entry =  " << i << endl;

    } else { // if it is not at the end of the list, then the key already exists in the table
        cout << " not inserted - duplicate key!!!" << endl;
    }
}

/**
 * @brief Searches the has table
 *
 * This public function searches the hash table for a record with key.
 * 
 * @param s 
 *************************************************************************/
void HT::search(const string &s) {
    // get the hash value of the key
    int i = hash(s);

    // search the hash table for a record with key
    list<Entry>::iterator it = find_if(hTable[i].begin(), hTable[i].end(), [s](Entry &entry) {
        return !(bool(entry.key.compare(s))); // compare stl function casted to bool
    });

    // if the iterator is at the end, then the key does not exist in the table
    if (it == hTable[i].end()) {
        cout << " not in table!!\n";
    } else { // otherwise, print entry
        cout << " ==> number:";
        cout << setw(5) << right << it->num << " - " << "item:";
        cout << setw(24) << left << it->desc << endl;
    }
}

/**
 * @brief Prints the subscripts of all (and only) the 
 *        active records in the hash table
 **************************************************************************/
void HT::hTable_print() {
    cout << endl;

    // loop through the hash table vector
    for (size_t i = 0; i < hsize; i++) {
        
        // get the sub list
        list<Entry> &subTable = hTable[i];

        // loop through the sub list, this uses auto, because I don't know how long the sub list is
        for (auto j : subTable) {
            // These are a bunch of couts so I
            // could get the formatting right
            cout << setw(4) << left << i << ":";
            cout << setw(7) << left << j.key << "- ";
            cout << setw(6) << left << j.num << " -  ";
            cout << setw(24) << j.desc;
            cout << endl;
        }
    }
}

/**
 * @brief Prints the contents of all (and only) the 
 *        active records in the hash table
 *************************************************************************/
void HT::pTable_print() {
    
    // Sort the pointer table
    sort(pTable.begin(), pTable.end(), [](Entry *q, Entry *p) {
        return q->key < p->key;
    });

    // Print the pointer table - This is the same as the hTable_print sub loop
    for (auto it : pTable) {
        // Once again, a bunch of couts to get the formatting right
        cout << setw(6) << right << it->key << "  - ";
        cout << setw(5) << right << it->num << "  -  ";
        cout << setw(24) << left << it->desc;
        cout << endl;
    }
}
