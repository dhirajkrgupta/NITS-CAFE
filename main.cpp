#include <iostream>
#include <string>
#include <ctime>
// #include <cstdlib>
// #include <cctype>

// #include <customerdetails.h>
// #include <bill.h>
#include <reservations.h>
#include <menu.h>
#include <order.h>
#include <utility.h>

int main()
{
    Reservations r;
    string ID;
    clearConsole();
    cout << "WELCOME TO NITS CAFE RESERVATION\n";

reservation:

    cout << "1. Make Reservation\n";
    cout << "2. Check Reservation\n";
    cout << "3. Cancel Reservation\n";
    cout << "4. Exit Reservation and go to NITS Cafe\n";

    int x;
    cin >> x;
    clearConsole();
    switch (x)
    {
    case 1:
        makeReservation(r);
        goto reservation;
        break;
    case 2:
        checkReservation(r);
        goto reservation;
        break;
    case 3:
        cancelReservation(r);
        goto reservation;
        break;
    case 4:
        goto cafe;
        break;
    default:
        break;
    }

cafe:

    cout << "WELCOME TO NITS CAFE\n";
    cout << "================================================================\n";
    cout << "1.End Proccess " << endl;
    cout << "2.Procceed " << endl;
    int proccess;
    cin >> proccess;
    if (proccess == 1)
        goto end;

    // Login
    cout << "Enter your Reservation ID: ";
    cin >> ID;
    clearConsole();
    if (r.findReservation(ID) != -1)
    {
        string name = r.getCustomerDetails(ID)->name;
        string date = r.getCustomerDetails(ID)->date;
        // time_t t = time(NULL);
        // struct tm *now = localtime(&t);
        cout << "Welcome " << name << "                                            " << date << endl;
    menu:
        Menu menu;
        cout << "===================================================================================================";
        cout << "\nMENU:" << endl;
        menu.displayMenu();
        cout << "===================================================================================================";

        Order order;
        vector<pair<MenuItem *, int>> UserOrders = placeOrder(order, menu);
        clearConsole();
        makeBill(UserOrders, ID, name, date);
        takeFeedback(ID);
        r.removeReservation(ID);
    }
    else
    {
        cout << "Sorry Reservation Not Found\n";
        cout << "Do You Want to Make A Resevation(Y/N): ";
        char ch;
        cin >> ch;
        clearConsole();
        if (ch == 'Y' || ch == 'y')
        {
            makeReservation(r);
            goto cafe;
        }
    }

end:
    cout << "Thank you for using our services! \nHave a nice day." << endl;
    return 0;
}
