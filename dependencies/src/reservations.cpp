#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/exception.h>
#include <reservations.h>
#include <utility.h>
#include "../../env.h"
using namespace std;
using namespace sql;

Reservations::Reservations()
{
    try {
        driver = mysql::get_mysql_driver_instance();
        connection = unique_ptr<Connection>(driver->connect("tcp://127.0.0.1:3306", "root",MYSQL_PASSWORD));
        connection->setSchema("reservation_system");
        
        cout << "Connected to MySQL database successfully!" << endl;
    }
    catch (SQLException &e) {
        cerr << "MySQL connection failed: " << e.what() << endl;
        cerr << "Error code: " << e.getErrorCode() << endl;
        cerr << "SQL state: " << e.getSQLState() << endl;
    }
}

Reservations::~Reservations()
{
    // Connection will be automatically closed when unique_ptr goes out of scope
}

void Reservations::addReservation(struct CustomerDetails *c)
{
    try {
        unique_ptr<PreparedStatement> pstmt(connection->prepareStatement(
            "INSERT INTO reservations (name, date, number_of_guests, ID) VALUES (?, ?, ?, ?)"
        ));
        
        pstmt->setString(1, c->name);
        pstmt->setString(2, c->date);
        pstmt->setInt(3, c->number_of_guests);
        pstmt->setString(4, c->ID);
        
        pstmt->executeUpdate();
        cout << "Reservation added successfully for ID: " << c->ID << endl;
    }
    catch (SQLException &e) {
        cerr << "Error adding reservation: " << e.what() << endl;
        cerr << "Error code: " << e.getErrorCode() << endl;
    }
}

CustomerDetails* Reservations::getCustomerDetails(string ID)
{
    try {
        unique_ptr<PreparedStatement> pstmt(connection->prepareStatement(
            "SELECT name, date, number_of_guests, ID FROM reservations WHERE ID = ?"
        ));
        
        pstmt->setString(1, ID);
        unique_ptr<ResultSet> res(pstmt->executeQuery());
        
        if (res->next()) {
            CustomerDetails* customer = new CustomerDetails;
            customer->name = res->getString("name");
            customer->date = res->getString("date");
            customer->number_of_guests = res->getInt("number_of_guests");
            customer->ID = res->getString("ID");
            return customer;
        }
    }
    catch (SQLException &e) {
        cerr << "Error getting customer details: " << e.what() << endl;
        cerr << "Error code: " << e.getErrorCode() << endl;
    }
    
    return nullptr;
}

bool Reservations::removeReservation(string ID)
{
    try {
        unique_ptr<PreparedStatement> pstmt(connection->prepareStatement(
            "DELETE FROM reservations WHERE ID = ?"
        ));
        
        pstmt->setString(1, ID);
        int rowsAffected = pstmt->executeUpdate();
        
        if (rowsAffected > 0) {
            cout << "Reservation removed successfully for ID: " << ID << endl;
            return true;
        } else {
            cout << "No reservation found with ID: " << ID << endl;
            return false;
        }
    }
    catch (SQLException &e) {
        cerr << "Error removing reservation: " << e.what() << endl;
        cerr << "Error code: " << e.getErrorCode() << endl;
        return false;
    }
}

// Replacement for findReservation - now returns boolean
bool Reservations::reservationExists(string ID)
{
    try {
        unique_ptr<PreparedStatement> pstmt(connection->prepareStatement(
            "SELECT COUNT(*) as count FROM reservations WHERE ID = ?"
        ));
        
        pstmt->setString(1, ID);
        unique_ptr<ResultSet> res(pstmt->executeQuery());
        
        if (res->next()) {
            return res->getInt("count") > 0;
        }
    }
    catch (SQLException &e) {
        cerr << "Error checking reservation existence: " << e.what() << endl;
        cerr << "Error code: " << e.getErrorCode() << endl;
    }
    
    return false;
}

// Get all reservations with optional WHERE clause
vector<CustomerDetails*> Reservations::getAllReservations(const string& whereClause)
{
    vector<CustomerDetails*> results;
    
    try {
        string query = "SELECT name, date, number_of_guests, ID FROM reservations";
        if (!whereClause.empty()) {
            query += " WHERE " + whereClause;
        }
        
        unique_ptr<Statement> stmt(connection->createStatement());
        unique_ptr<ResultSet> res(stmt->executeQuery(query));
        
        while (res->next()) {
            CustomerDetails* c = new CustomerDetails;
            c->name = res->getString("name");
            c->date = res->getString("date");
            c->number_of_guests = res->getInt("number_of_guests");
            c->ID = res->getString("ID");
            
            results.push_back(c);
        }
    }
    catch (SQLException &e) {
        cerr << "Error getting all reservations: " << e.what() << endl;
        cerr << "Error code: " << e.getErrorCode() << endl;
    }
    
    return results;
}

// Get reservations by date
vector<CustomerDetails*> Reservations::getReservationsByDate(string date)
{
    vector<CustomerDetails*> results;
    
    try {
        unique_ptr<PreparedStatement> pstmt(connection->prepareStatement(
            "SELECT name, date, number_of_guests, ID FROM reservations WHERE date = ?"
        ));
        
        pstmt->setString(1, date);
        unique_ptr<ResultSet> res(pstmt->executeQuery());
        
        while (res->next()) {
            CustomerDetails* c = new CustomerDetails;
            c->name = res->getString("name");
            c->date = res->getString("date");
            c->number_of_guests = res->getInt("number_of_guests");
            c->ID = res->getString("ID");
            
            results.push_back(c);
        }
    }
    catch (SQLException &e) {
        cerr << "Error getting reservations by date: " << e.what() << endl;
        cerr << "Error code: " << e.getErrorCode() << endl;
    }
    
    return results;
}

// Update existing reservation
bool Reservations::updateReservation(string ID, CustomerDetails* newData)
{
    try {
        unique_ptr<PreparedStatement> pstmt(connection->prepareStatement(
            "UPDATE reservations SET name = ?, date = ?, number_of_guests = ? WHERE ID = ?"
        ));
        
        pstmt->setString(1, newData->name);
        pstmt->setString(2, newData->date);
        pstmt->setInt(3, newData->number_of_guests);
        pstmt->setString(4, ID);
        
        int rowsAffected = pstmt->executeUpdate();
        
        if (rowsAffected > 0) {
            cout << "Reservation updated successfully for ID: " << ID << endl;
            return true;
        } else {
            cout << "No reservation found with ID: " << ID << endl;
            return false;
        }
    }
    catch (SQLException &e) {
        cerr << "Error updating reservation: " << e.what() << endl;
        cerr << "Error code: " << e.getErrorCode() << endl;
        return false;
    }
}

// Get total number of reservations
int Reservations::getReservationCount()
{
    try {
        unique_ptr<Statement> stmt(connection->createStatement());
        unique_ptr<ResultSet> res(stmt->executeQuery("SELECT COUNT(*) as total FROM reservations"));
        
        if (res->next()) {
            return res->getInt("total");
        }
    }
    catch (SQLException &e) {
        cerr << "Error getting reservation count: " << e.what() << endl;
        cerr << "Error code: " << e.getErrorCode() << endl;
    }
    
    return 0;
}