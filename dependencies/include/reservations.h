#ifndef RESERVATIONS_H
#define RESERVATIONS_H

#include <string>
#include <vector>
#include <memory>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include "customerdetails.h"
using namespace std;
using namespace sql;

// Assuming you have this struct defined elsewhere


class Reservations {
private:
    Driver* driver;
    unique_ptr<Connection> connection;
    
public:
    Reservations();
    ~Reservations();
    
    // Core methods (modified from your original)
    void addReservation(struct CustomerDetails* c);
    CustomerDetails* getCustomerDetails(string ID);
    bool removeReservation(string ID);
    
    // New/modified methods
    bool reservationExists(string ID);  // Replaces findReservation
    vector<CustomerDetails*> getAllReservations(const string& whereClause = "");
    vector<CustomerDetails*> getReservationsByDate(string date);
    bool updateReservation(string ID, CustomerDetails* newData);
    int getReservationCount();
};

#endif