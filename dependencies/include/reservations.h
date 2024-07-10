#ifndef RESERVATION_H
#define RESERVATION_H

#include <vector>
#include <customerdetails.h>
using namespace std;
class Reservations
{
private:
    vector<struct CustomerDetails *> reservationList;

public:
    Reservations();
    ~Reservations();
    void addReservation(struct CustomerDetails *c);
    int findReservation(string ID);
    bool removeReservation(string ID);
    CustomerDetails* getCustomerDetails( string ID);
    void updateFile();
};

#endif