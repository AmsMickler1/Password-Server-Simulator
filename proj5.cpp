// Amber Mickler
// COP4530 Myers
// Assignment 5
// Hashtable and PassServer driver file

#include <iostream>
#include <string>
#include "passserver.h"
using namespace std;
void Menu();

int main() {
    size_t cap;
    cout << "Enter preferred hash table capacity: ";
    cin >> cap;

    PassServer server(cap);
    cout << server.capacity() << endl;

    bool ex = false;
    char input;
    string filename, user, pass, newpass;
    Menu();
    cin >> input;

    while (!ex) {
        switch (input) {
            case 'l':   // Load from file
                cout << "Enter password file name to load from: ";
                cin >> filename;
                if (server.load(filename.c_str()))
                    break;
                cout << "Error: Cannot open file " << filename << endl;
                break;
            case 'a':   // Add user
                cout << "Enter username: ";
                cin >> user;
                cout << "Enter password: ";
                cin >> pass;
                if (server.addUser(pair<string, string>(user,pass)))
                    cout << "User " << user << " added." << endl;
                else
                    cout << "*****Error: User already exists. Could not add user." << endl;
                break;
            case 'r':   // Remove user
                cout << "Enter username: ";
                cin >> user;
                if (server.removeUser(user))
                    cout << "User " << user << " deleted." << endl;
                else
                    cout << "*****Error: User not found. Could not delete user." << endl;
                break;
            case 'c':   // Change user password
                cout << "Enter username: ";
                cin >> user;
                cout << "Enter password: ";
                cin >> pass;
                cout << "Enter new password: ";
                cin >> newpass;
                if (server.changePassword(pair<string,string>(user,pass), newpass))
                    cout << "Password changed for user " << user << endl;
                else
                    cout << "*****Error: Could not change user password." << endl;
                break;
            case 'f':   // Find user
                cout << "Enter username: ";
                cin >> user;
                if (server.find(user))
                    cout << "User \'" << user << "\' found." << endl;
                else
                    cout << "User \'" << user << "\' not found." << endl;
                break;
            case 'd':   // Dump HashTable
                server.dump();
                break;
            case 's':   // HashTable Size
                cout << "Size of HashTable is " << server.size() << endl;
                break;
            case 'w':   // Write to Password File
                cout << "Enter password file name to write to: ";
                cin >> filename;
                server.write_to_file(filename.c_str());
                break;
            case 'x':   // Exit program
                ex = true;
                break;
            default:
                cout << "Not a valid input. Try again." << endl;
                break;
            }
        if (!ex){
            Menu();
            cin >> input;
        }
        else
            cout << "Bye!" << endl;

    }
    return 0;
}


void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}
