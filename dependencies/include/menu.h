#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
// #include <algorithm> // Include for std::transform
// #include <cctype>    // Include for std::tolower
using namespace std;

struct MenuItem
{

    string name;
    double price;
    string description;
    MenuItem(string n, double p, string d);
    void print();
    
};

class Menu
{
private:
    vector<MenuItem *> items;

public:
    Menu();
    int itemExists(const string &itemName);
    void addItem(MenuItem *item);
    void displayMenu();
    MenuItem *getItem(const string &itemName);
    ~Menu();
};

#endif
