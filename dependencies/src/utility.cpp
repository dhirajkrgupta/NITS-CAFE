#include <ctime>
#include <sstream>
#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <utility.h>

void clearConsole()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

string generateID()
{
    string ID;
    time_t currtime = time(0);
    ID = to_string(currtime);
    return ID;
}

bool isValidDate(int dd, int mm, int yyyy)
{
    if (mm <= 0 || mm > 12)
    {
        return false;
    }
    if (yyyy <= 0 || yyyy > 9999)
    {
        return false;
    }
    if (dd <= 0 || dd > 31)
    {
        return false;
    }
    switch (mm)
    {
    case 2:
        if ((yyyy % 4 == 0 && yyyy % 100 != 0) || (yyyy % 400 == 0)) // leap year condition
        {
            if (dd > 29)
                return false;
        }
        else if (dd > 28)
            return false;
        break;
    case 4:
        if (dd > 30)
        {
            return false;
        }

        break;
    case 6:
        if (dd > 30)
        {
            return false;
        }
        break;
    case 9:
        if (dd > 30)
        {
            return false;
        }
        break;
    case 11:
        if (dd > 30)
        {
            return false;
        }
        break;
    default:
        break;
    }
    return true;
}

string getDate()
{
    int dd, mm, yyyy;
    cout << "Date(dd/mm/yyyy): ";
    string input;
    getline(cin, input);
    if (input.empty())
    {
        getline(cin, input);
    }
    stringstream ss(input);
    char slash;
    if (!(ss >> dd >> slash >> mm >> slash >> yyyy) || slash != '/')
    {
        cout << "Invalid input. Please enter the date in the format (dd/mm/yyyy)." << endl;
        return getDate(); // Retry getting the date
    }

    string date = to_string(dd);
    date += "/" + to_string(mm);
    date += "/" + to_string(yyyy);

    if (isValidDate(dd, mm, yyyy))
    {
        time_t currTime = time(0);
        tm *now = localtime(&currTime);

        if (yyyy > now->tm_year + 1900)
        {
            return date;
        }
        else if (yyyy == now->tm_year + 1900)
        {
            if (mm > now->tm_mon + 1)
            {
                return date;
            }
            else if (mm == now->tm_mon + 1)
            {
                if (dd >= now->tm_mday)
                {
                    return date;
                }
            }
        }
    }
    cout << "Invalid Date. Please enter a valid date." << endl;
    return getDate();
}

void pauseProgram()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void makeReservation(Reservations &r)
{
    struct CustomerDetails *c = new CustomerDetails;
    cout << "Name:";
    getline(std::cin, c->name);
    if (c->name == "")
    {
        getline(std::cin, c->name);
    }

    c->date = getDate();
    cout << "Number of Guest:";
    cin >> c->number_of_guests;
    c->ID = generateID();
    r.addReservation(c);
    clearConsole();
    cout << "Reservation Status : Successful!" << endl;
    cout << "Reservation ID: " << c->ID << endl;
    fstream myFile;
    myFile.open("Data/reservationData.txt", ios_base::app);
    myFile << c->name << "," << c->date << "," << c->number_of_guests << "," << c->ID << "\n";
}
void checkReservation(Reservations &r)
{
    string ID;
    cout << "Enter your Reservation ID: ";
    cin >> ID;
    cout << "Checking reservation";
    pauseProgram();
    cout << ".";
    pauseProgram();
    cout << ".";
    pauseProgram();
    cout << ".";
    clearConsole();
    if (r.findReservation(ID) != -1)
    {
        cout << "Status : Found" << endl;
        r.getCustomerDetails(ID)->print();
        return;
    }
    cout << "Reservation Not Found\n";
    cout << "Do You Want to Make A Resevation(Y/N): ";
    char ch;
    cin >> ch;
    clearConsole();
    if (ch == 'Y' || ch == 'y')
        makeReservation(r);
};
void cancelReservation(Reservations &r)
{
    string ID;
    cout << "Enter your Reservation ID: ";
    cin >> ID;
    clearConsole();
    if (r.removeReservation(ID))
    {
        cout << "Removed reservation successfully! \n";
        r.updateFile();
    }
    else
    {
        cout << "Reservation Not Found\n";
        cout << "Do You Want to Make A Resevation(Y/N): ";
        char ch;
        cin >> ch;
        clearConsole();
        if (ch == 'Y' || ch == 'y')
            makeReservation(r);
    }
}
bool compareIgnoreCase(const string &str1, const string &str2)
{
    if (str1.size() != str2.size())
    {
        return false;
    }
    for (size_t i = 0; i < str1.size(); ++i)
    {
        if (tolower(str1[i]) != tolower(str2[i]))
        {
            return false;
        }
    }
    return true;
}
void makeMenu(Menu *menu)
{
    menu->addItem(new MenuItem("Pizza", 300.00, "Delicious cheese pizza"));
    menu->addItem(new MenuItem("Burger", 100.00, "Juicy chicken burger with fries"));
    menu->addItem(new MenuItem("Salad", 60.00, "Fresh garden salad"));
    menu->addItem(new MenuItem("Pasta", 250.00, "Homemade pasta with marinara sauce"));
    menu->addItem(new MenuItem("naan", 50.00, "Soft, fluffy Indian flatbread "));
    menu->addItem(new MenuItem("Fried rice", 90.00, "Stir fried rice mixed with vegetables"));
    menu->addItem(new MenuItem("Mutton Biriyani", 350.00, " Flavorful rice dish with tender mutton and aromatic spice"));
    menu->addItem(new MenuItem("Chicken Biriyani", 400.00, "Aromatic rice dish with marinated chicken and fragrant spices"));
    menu->addItem(new MenuItem("Butter Chicken", 250.00, "Tender chicken in acreamy, aromatic tomato gravy"));
}

vector<pair<MenuItem *, int>> placeOrder(Order &order, Menu &menu)
{
    string itemName;
    char choice;
    do
    {
        cout << "\nEnter item name to order: ";
        getline(cin, itemName);
        if (itemName == "")
        {
            getline(cin, itemName);
        }
        if (menu.itemExists(itemName) != -1)
        {
            int quantity;
            cout << "Enter the quantity of '" << itemName << "': ";
            cin >> quantity;
            cout << "Item added to order." << std::endl;
            // Add item to order
            order.addItem(menu.getItem(itemName), quantity);
        }
        else
        {
            cout << "Sorry, the item '" << itemName << "' is not available right now." << endl;
        }
        cout << "Do you want to order more items? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
    return order.getOrderList();
}

void makeBill(vector<pair<MenuItem *, int>> userOrder, string ID, string name, string date)
{
    Bill bill(ID, name, date);
    int n = userOrder.size();
    while (n--)
    {
        string itemName = userOrder[n].first->name;
        int quantity = userOrder[n].second;
        double cost = userOrder[n].first->price;
        bill.addItem(itemName, quantity, cost);
    }

    bill.printBill();
}
void takeFeedback(string ID)
{
    string feedback;
    cout << "Give Feedback:\n";
    getline(cin, feedback);
    if (feedback == "")
    {
        getline(cin, feedback);
    }

    cout << "Thank you for your feedback\n";
    fstream myFile;
    myFile.open("Data/feedbacks.txt", ios::app);
    if (myFile.is_open())
    {
        myFile << ID << ": \"" << feedback << "\"" << '\n';
    }
    myFile.close();
}
