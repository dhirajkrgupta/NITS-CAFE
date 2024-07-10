#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <bill.h>
using namespace std;

BillItem::BillItem(int serial, const string &itemName, int itemQuantity, double itemCost) : serialNumber(serial), name(itemName), quantity(itemQuantity), costPerItem(itemCost) {}

double BillItem::getTotalCost() const
{
    return quantity * costPerItem;
}

Bill::Bill(string ID, string name, string date) : nextSerialNumber(1), customerID(ID), customerName(name), date(date) {}

void Bill::addItem(const string &itemName, int itemQuantity, double itemCost)
{
    items.emplace_back(nextSerialNumber++, itemName, itemQuantity, itemCost);
}

void Bill::printBill() const
{
    if (items.size() == 0)
        return;

    time_t t = time(NULL);
    tm *now = localtime(&t);
    string time =to_string(now->tm_hour)+":"+to_string(now->tm_min)+":"+to_string(now->tm_sec);
    cout << "BILL:" <<endl;
    cout << "Reservation ID:" << customerID << "  "
         << "Name: " << customerName<<"\t"<< date << " " << time << '\n';
    cout << "---------------------------------------------------------------------------\n";
    cout << setw(5) << left << "S.No.";
    cout << setw(25) << left << "Item";
    cout << setw(15) << left << "Quantity";
    cout << setw(15) << left << "Cost/Item";
    cout << setw(15) << left << "Total Cost\n";
    cout << "\n---------------------------------------------------------------------------\n";

    double totalBill = 0.0;
    for (const auto &item : items)
    {
        cout << setw(5) << left << item.serialNumber;
        cout << setw(25) << left << item.name;
        cout << setw(15) << left << item.quantity;
        cout << setw(15) << left << item.costPerItem;
        cout << setw(15) << left << item.getTotalCost() << "\n";

        totalBill += item.getTotalCost();
    }

    cout << "\n---------------------------------------------------------------------------\n";
    cout << "Total Bill: " << totalBill << "\n";
    cout << "---------------------------------------------------------------------------\n";
}
