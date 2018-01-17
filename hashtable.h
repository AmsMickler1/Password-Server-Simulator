// Amber Mickler
// COP4530 Section 2
// Hashtable header file

#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <functional>
#include <fstream>

using std::vector;
using std::list;
using std::pair;
using std::string;
namespace cop4530{

    template<typename K, typename V>
    class HashTable{

    public:
        HashTable(size_t size = 101);                   // Create a hash table, where the size of the vector is set
                                                        // to prime_below(size) (where size is default  to 101)
        ~HashTable();                                   // destructor
        bool contains(const K & k) const;               // check if key k is in the hash table.
        bool match(const pair<K, V> &kv) const;         // check if key-value pair is in the hash table.
        bool insert(const pair<K, V> & kv);             // add  the key-value pair kv into the hash table. NO DUPLICATES!
                                                        // If the key is the hash table but with a different value, update to new value kv
                                                        // Return true if kv is inserted or the value is updated; return false otherwise (i.e., if kv is in the hash table).
        bool insert (pair<K,  V> && kv);                // move version of insert.
        bool remove(const K & k);                       // delete the key k and the corresponding value if it is in the hash table
                                                        // Return true if k is deleted, return false otherwise (i.e., if key k is not in the hash table).
        void clear();                                   // delete all elements in the hash table
        bool load(const char *filename);                // load the content of the file with name filename into the hash table
                                                        // In the file, each line contains a single pair of key and value, separated by a white space.
        void dump() const;                              // display all entries in the hash table. If an entry contains multiple key-value pairs, separate them by a semicolon (:)
        bool write_to_file(const char *filename) const; // write all elements in the hash table into a file with name filename
                                                        // Similar to the file format in the load function, each line contains a pair of key-value pair, separated by a white space.
        int getSize() const;                            // Returns number of elements in the table
        size_t capacity() const;                        // Returns size of table
    private:
        vector<list<pair<K,V>>> table;
        int numElements;

        static const unsigned int max_prime = 1301081;  // max_prime is used by the helpful functions provided to you.
        static const unsigned int default_capacity = 11;// the default_capacity is used if the initial capacity
                                                        // of the underlying vector of the hash table is zero.

        void makeEmpty();                               // delete all elements in the hash table - clear() will call this function.
        void rehash();                                  // Rehash function. Called when the number of elements in the hash table is greater than the size of the vector.
        size_t myhash(const K &k) const;                // return the index of the vector entry where k should be stored.
        unsigned long prime_below(unsigned long);
        void setPrimes(vector<unsigned long>&);         // Whenever you need to set hash table to a new size "sz", call prime_below(sz) to determine the new proper underlying vector size

    };  // end of class HashTable
    #include "hashtable.hpp"
}   // end of namespace cop4530

#endif
