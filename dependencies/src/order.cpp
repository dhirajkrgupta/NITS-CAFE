#include <order.h>
// #include <menu.h>
#include <iostream>

void Order::addItem(MenuItem* item,int quantity) {
        orderList.push_back({item,quantity});
}

vector<pair<MenuItem*,int>> Order::getOrderList(){
        return orderList;
}