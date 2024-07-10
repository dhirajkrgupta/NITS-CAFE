#ifndef BILL_H
#define BILL_H
using namespace std;
class BillItem
{
public:
    int serialNumber;
    string name;
    int quantity;
    double costPerItem;

    BillItem(int serial, const string &itemName, int itemQuantity, double itemCost);
    double getTotalCost() const;
};

class Bill
{
private:
    vector<BillItem> items;
    int nextSerialNumber;
    string customerID;
    string customerName;
    string date;

public:
    Bill(string ID,string name,string date);
    void addItem(const string &itemName, int itemQuantity, double itemCost);
    void printBill() const;
};

#endif