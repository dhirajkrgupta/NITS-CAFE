#include <iostream>
#include <customerdetails.h>

bool operator==(CustomerDetails c1, CustomerDetails c2){
    return c1.name == c2.name && c1.date == c2.date && c1.number_of_guests == c2.number_of_guests;
}


void CustomerDetails::print(){
    cout << name << " for " << number_of_guests  
             << " on " << date  
	     << "\n";
}