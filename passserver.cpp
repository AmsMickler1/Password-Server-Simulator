// Amber Mickler
// COP4530 Section 2
// Pass Server implementation

// public
#include "passserver.h"

PassServer::PassServer(size_t size) : passwords(size) {

}   // constructor, create a hash table of the specified size. You just need to pass this size parameter to the constructor of the HashTable. Therefore, the real hash table size could be different from the parameter size (because prime_below() will be called in the constructor of the HashTable).

PassServer::~PassServer() {
    passwords.clear();
}   // destructor. You need to decide what you should do based on your design of PassServer (how you develop the adaptor class based on the adaptee HashTable). In essence, we do not want to have memory leak.

bool PassServer::load(const char *filename) {
    return passwords.load(filename);
}   // load a password file into the HashTable object. Each line contains a pair of username and encrypted password.

bool PassServer::addUser(std::pair<string,  string> & kv) {
    kv.second = encrypt(kv.second);
    return passwords.insert(kv);
}   // add a new username and password.  The password passed in is in plaintext, it should be encrypted before insertion.

bool PassServer::addUser(std::pair<string, string> && kv) {
    kv.second = encrypt(kv.second);
    return passwords.insert(std::move(kv));
}   // move version of addUser.

bool PassServer::removeUser(const string & k) {
    return passwords.remove(k);
}   // delete an existing user with username k.

bool PassServer::changePassword(const pair<string, string> &p, const string & newpassword) {
    pair<string, string> old(p.first, encrypt(p.second));
    if (passwords.contains(old.first)) {
        old.second = encrypt(newpassword);
        return passwords.insert(old);     // if passwords are the same, this will return false
    }
    return false;
}   // change an existing users password. Note that both passwords passed in are in plaintext. They should be encrypted before you interact with the hash table. If the user is not in the hash table, return false. If p.second does not match the current password, return false. Also return false if the new password and the old password are the same (i.e., we cannot update the password).

bool PassServer::find(const string & user) const {
    return passwords.contains(user);
}   // check if a user exists (if user is in the hash table).

void PassServer::dump() const {
    passwords.dump();
}   // show the structure and contents of the HashTable object to the screen. Same format as the dump() function in the HashTable class template.

size_t PassServer::size() const {
    return passwords.getSize();
}   // return the size of the HashTable (the number of username/password pairs in the table).

size_t PassServer::capacity() const {
    return passwords.capacity();
}

bool PassServer::write_to_file(const char *filename) const {
    return passwords.write_to_file(filename);
} //save the username and password combination into a file. Same format as the write_to_file() function in the HashTable class template.


// private

string PassServer::encrypt(const string & str) {
    char salt[] = "$1$########";
    string scramble(crypt(str.c_str(), salt));
    return scramble.substr(12);
}   // encrypt the parameter str and return the encrypted string.
