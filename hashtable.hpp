// Amber Mickler
// COP4530 Section 2
// Hashtable header definitions file

#include "hashtable.h"

using namespace cop4530;

// PUBLIC

template <typename K, typename V>
HashTable<K, V>::HashTable(size_t size) {
    table.resize(prime_below(size));
    //table = new vector<pair<K,V>>(prime_below(size));
    numElements = 0;
}   // constructor. Size of the vector is set to prime_below(size)

template <typename K, typename V>
HashTable<K, V>::~HashTable() {
    makeEmpty();
    table.clear();
}   // destructor. Delete all elements in hash table.

template <typename K, typename V>
bool HashTable<K, V>::contains(const K & k) const {
    for (auto itr = table[myhash(k)].begin(); itr != table[myhash(k)].end(); itr++) {
        if (itr->first == k)
            return true;
    }
    return false;
}   // check if key k is in the hash table.

template <typename K, typename V>
bool HashTable<K, V>::match(const pair<K, V> &kv) const {
    for (auto itr = table[myhash(kv.first)].begin(); itr != table[myhash(kv.first)].end(); itr++) {
        if (*itr == kv)
            return true;
    }
    return false;
}   // check if key-value pair is in the hash table.

template <typename K, typename V>
bool HashTable<K, V>::insert(const pair<K, V> & kv) {
    if (match(kv))
        return false;
    if (contains(kv.first)) {
        for (auto itr = table[myhash(kv.first)].begin(); itr != table[myhash(kv.first)].end(); itr++) {
            if (itr->first == kv.first)
                itr->second = kv.second;
        }
    }
    else {
        numElements++;
        if (numElements > table.size()) {
            rehash();
        }
        table[myhash(kv.first)].push_back(kv);
    }
    return true;
}   // add  the key-value pair kv into the hash table. Dont add if kv is already in the hash table. If the key is the hash table but with a different value, the value should be updated to the new one with kv. Return true if kv is inserted or the value is updated; return false otherwise (i.e., if kv is in the hash table).

template <typename K, typename V>
bool HashTable<K, V>::insert (pair<K, V> && kv) {
    if (match(kv))
        return false;
    if (contains(kv.first)) {
        for (auto itr = table[myhash(kv.first)].begin(); itr != table[myhash(kv.first)].end(); itr++) {
            if (itr->first == kv.first)
                itr->second = std::move(kv.second);
        }
    }
    else {
        numElements++;
        if (numElements > table.size()) {
            rehash();
        }
        table[myhash(kv.first)].push_back(std::move(kv));
    }
    return true;
}   // move version of insert.

template <typename K, typename V>
bool HashTable<K, V>::remove(const K & k) {
    pair<K,V> kv;
    if (contains(k)) {
        for (auto itr = table[myhash(k)].begin(); itr != table[myhash(k)].end(); itr++) {
            if (itr->first == k)
                kv = *itr;
        }
        table[myhash(k)].remove(kv);
        numElements--;
        return true;
    }
    return false;
}   // delete the key k and the corresponding value if it is in the hash table. Return true if k is deleted, return false otherwise (i.e., if key k is not in the hash table).

template <typename K, typename V>
void HashTable<K, V>::clear() {
    makeEmpty();
}   // delete all elements in the hash table

template <typename K, typename V>
bool HashTable<K, V>::load(const char *filename) {
    std::ifstream input(filename);
    string k;
    string v;
    if (!input.is_open())
        return false;
    while (!input.eof()) {
        input >> k;
        input >> v;
        insert(pair<K,V>(k,v));
    }
    input.close();
    return true;
}   // load the content of the file with name filename into the hash table. In the file, each line contains a single pair of key and value, separated by a white space.

template <typename K, typename V>
void HashTable<K, V>::dump() const {
    int i = 0;
    for (auto& lst : table) {
        std::cout << "v[" << i << "]";
        i++;
        if (lst.size() != 0) {
            for (auto pr : lst) {
                std::cout << ": " << pr.first << " " << pr.second << " ";
            }

        }
        else
            std::cout << ":";
        std::cout << std::endl;
    }
}   // display all entries in the hash table. If an entry contains multiple key-value pairs, separate them by a semicolon character (:) (see the provided executable for the exact output format).

template <typename K, typename V>
bool HashTable<K, V>::write_to_file(const char *filename) const {
    std::ofstream output(filename);
    if (!output)
        return false;
    for (int i = 0; i < table.size(); i++) {
        for (auto itr = table[i].begin(); itr != table[i].end(); itr++) {
            output << itr->first << " " << itr->second << std::endl;
        }
    }
    output.close();
    return true;
}   //write all elements in the hash table into a file with name filename. Similar to the file format in the load function, each line contains a pair of key-value pair, separated by a white space.

template <typename K, typename V>
int HashTable<K, V>::getSize() const {
    return numElements;
}

template <typename K, typename V>
size_t HashTable<K,V>::capacity() const {
    return table.size();
}

    // PRIVATE

template <typename K, typename V>
void HashTable<K, V>::makeEmpty() {
    for (int i = 0; i < table.size(); i++) {
        table[i].clear();
    }
    numElements = 0;
}   // delete all elements in the hash table. The public interface clear() will call this function.

template <typename K, typename V>
void HashTable<K, V>::rehash() {
    HashTable<K, V> reTable(table.size());
    for (int i = 0; i < table.size(); i++) {
        auto lst = table[i];
        for (auto& y : lst) {
            reTable.insert(y);
        }
    }
    makeEmpty();
    table.resize(prime_below(reTable.table.size()*2));
    std::cout <<"\nNew size: " << table.size() << std::endl;
    for (int i = 0; i < reTable.table.size(); i++) {
        auto lst = reTable.table[i];
        for (auto y : lst) {
            insert(y);
        }
    }
    numElements++;
}   // Rehash function. Called when the number of elements in the hash table is greater than the size of the std::vector.

template <typename K, typename V>
size_t HashTable<K, V>::myhash(const K &k) const {
    std::hash<string> h;
    size_t hash = h(k);
    return hash % table.size();
}   // return the index of the std::vector entry where k should be stored.


template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}   // returns largest prime number <= n or zero if input is too large

template <typename K, typename V>
void HashTable<K, V>::setPrimes(vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}   //Sets all prime number indexes to 1. Called by method prime_below(n)
