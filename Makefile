all: compile run

compile:
    g++ main.cpp dependencies/src/reservations.cpp dependencies/src/utility.cpp dependencies/src/customerdetails.cpp dependencies/src/menu.cpp dependencies/src/order.cpp dependencies/src/bill.cpp -Idependencies/include -o main.exe

run:
    .\main.exe

