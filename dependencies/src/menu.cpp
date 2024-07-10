#include <menu.h>
#include <iostream>
#include <utility.h>

MenuItem::MenuItem(string n, double p, string d) : name(n), price(p), description(d) {} // constructor

void MenuItem::print()
{
    cout << this->name << ": Rs." << this->price << " - " << this->description << endl;
}

Menu::Menu()
{
    makeMenu(this);
}
void Menu::addItem(MenuItem *item)
{
    items.push_back(item);
}

void Menu::displayMenu()
{
    for (size_t i = 0; i < items.size(); ++i)
    {
        items[i]->print();
    }
}

int Menu::itemExists(const string &itemName)
{
    for (size_t i = 0; i < items.size(); ++i)
    {
        if (compareIgnoreCase(items[i]->name, itemName))
        {
            return i;
        }
    }
    return -1;
}

MenuItem *Menu::getItem(const string &itemName)
{
    int i = itemExists(itemName);
    if (i != -1)
    {
        return items[i];
    }

    return nullptr;
}
Menu::~Menu()
{
    for (MenuItem *item : items)
    {
        delete item;
    }
}