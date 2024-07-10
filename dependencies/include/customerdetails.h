#ifndef CUSTOMERDETAILS
#define CUSTOMERDETAILS
#include <string>
using namespace std;
struct CustomerDetails
{
public:
    string name;
    string date;
    int number_of_guests;
    string ID;
    void print();
};

#endif