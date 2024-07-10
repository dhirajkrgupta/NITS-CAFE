#ifndef UTILITY_H
#define UTILITY_H
#include <string>
#include <reservations.h>
#include <menu.h>
#include <order.h>
#include <bill.h>
using namespace std;

string generateID();
bool isValidDate(int dd, int mm, int yyyy);
string getDate();
void pauseProgram(int time);
void clearConsole();
void makeReservation(Reservations &r);
void checkReservation(Reservations &r);
void cancelReservation(Reservations &r);
bool compareIgnoreCase(const string& str1, const string& str2);
void makeMenu(Menu *menu);
vector<pair<MenuItem*, int>> placeOrder(Order &order,Menu& menu);
void makeBill(vector<pair<MenuItem*, int>> userOrder,string ID,string name,string date);
void takeFeedback(string ID);
#endif