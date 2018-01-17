// Amber Mickler
// COP4530 Section 2
// Pass server header file

#ifndef PASSSERVER_H
#define PASSERVER_H
#include "hashtable.h"
#include <string>
#include <crypt.h>
using namespace cop4530;
using std::string;
using std::pair;
class PassServer{

public:
    PassServer(size_t size = 101);                      // create a hash table of the specified size
    ~PassServer();                                      // destructor
    bool load(const char *filename);                    // load a password file into the HashTable object - Each line contains a pair of username and encrypted password
    bool addUser(pair<string,  string> & kv);           // add a new username and password.  The password passed in is in plaintext, it should be encrypted before insertion.
    bool addUser(pair<string, string> && kv);           // move version of addUser.
    bool removeUser(const string & k);                  // delete an existing user with username k.
    bool changePassword(const pair<string, string> &p, const string & newpassword);
        //change an existing users password - both passwords are passed in as plaintext & need to be Encrypted
        // If the user is not in the hash table, If p.second does not match the current password, or new password and the old password are the same, return false
    bool find(const string & user) const;               // check if a user exists (if user is in the hash table).
    void dump() const;                                  // show the structure and contents of the HashTable object to the screen. Same format as the dump() function in the HashTable class template.
    size_t size() const;                                // return the size of the HashTable (the number of username/password pairs in the table).
    size_t capacity() const;                            // returns size of available storage
    bool write_to_file(const char *filename) const;     // save the username and password combination into a file. Same format as the write_to_file() function in the HashTable class template.

private:
    HashTable<string, string> passwords;

    string encrypt(const string & str);                 //encrypt the parameter str and return the encrypted string.


};  // end of class PassServer
#endif
