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

using namespace std;
using namespace sql;



class Reservations {
private:
    Driver* driver;
    unique_ptr<Connection> connection;
    
public:
    Reservations();
    
    
    void addReservation(struct CustomerDetails* c);
    CustomerDetails* getCustomerDetails(string ID);
    bool removeReservation(string ID);
    
    bool reservationExists(string ID);  
    vector<CustomerDetails*> getAllReservations(const string& whereClause = "");
    vector<CustomerDetails*> getReservationsByDate(string date);
    bool updateReservation(string ID, CustomerDetails* newData);
    int getReservationCount();
};

#endif