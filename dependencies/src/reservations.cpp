#include <iostream>
#include <string>
#include <sstream>
// #include <cstdlib>
// #include <thread>
// #include <chrono>
#include <fstream>
#include <reservations.h>
#include <utility.h>

Reservations::Reservations()
{
    fstream myFile;
    myFile.open("Data/reservationData.txt", ios::in);

    string line;
    while (getline(myFile, line))
    {
        CustomerDetails *c = new CustomerDetails;
        vector<string> row;
        stringstream ss(line);
        string cell;
        while (getline(ss, cell, ','))
        {
            row.push_back(cell);
        }
        c->name = row[0];
        c->date = row[1];
        c->number_of_guests = stoi(row[2]);
        c->ID = row[3];

        reservationList.push_back(c);
    }
}
Reservations::~Reservations()
{
    for (CustomerDetails *customer : reservationList)
    {
        delete customer;
    }
}
void Reservations::addReservation(struct CustomerDetails *c)
{
    reservationList.push_back(c);
}

CustomerDetails *Reservations::getCustomerDetails(string ID)
{
    for (int i = 0; i < reservationList.size(); ++i)
    {
        if (reservationList[i]->ID == ID)
        {
            return reservationList[i];
        }
    }
    return nullptr;
}

int Reservations::findReservation(string ID)
{
    for (int i = 0; i < reservationList.size(); ++i)
    {
        if (reservationList[i]->ID == ID)
            return i;
    }
    return -1;
}

void Reservations::updateFile()
{
    fstream myFile;
    myFile.open("Data/reservationData.txt", ios::out);
    myFile.close();
    myFile.open("Data/reservationData.txt", ios::app);
    for (int i = 0; i < reservationList.size(); i++)
    {
        myFile << reservationList[i]->name << "," << reservationList[i]->date << "," << reservationList[i]->number_of_guests << "," << reservationList[i]->ID << '\n';
    }
}
bool Reservations::removeReservation(string ID)
{
    int d = findReservation(ID);
    if (d != -1)
    {
        delete reservationList[d];
        reservationList.erase(reservationList.begin() + d);
        updateFile();
        return true;
    }
    return false;
}
