#ifndef ORDER_H
#define ORDER_H

#include <menu.h>

#include <vector>
using namespace std;

class Order {
private:

    vector<pair<MenuItem*,int>>orderList;

public:
    void addItem(MenuItem* item,int quantity);
    vector<pair<MenuItem *,int>>getOrderList();
};

#endif
