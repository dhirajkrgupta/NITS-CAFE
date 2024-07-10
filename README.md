## Compile and Run Instructions

### Using the Makefile to Compile and Run

To compile and run the project using the provided Makefile, follow these steps:

#### Prerequisites

- Ensure you have `make` and `g++` installed on your system.

#### Steps to Compile and Run

1. **Compile the Project**:

   Open a terminal and navigate to the directory containing the Makefile. Run the following command to compile the project:
   ```sh
   make compile
2. **Run the Executable**:

   After compiling, execute the program by running:
   ```sh
   make run
   
### Compile and Run Without Makefile

### On Windows

1. **Compile the Project**:

   Open a command prompt and navigate to the project directory. Run the following command to compile the project:
   ```sh
   g++ main.cpp dependencies/src/reservations.cpp dependencies/src/utility.cpp dependencies/src/customerdetails.cpp dependencies/src/menu.cpp dependencies/src/order.cpp dependencies/src/bill.cpp -Idependencies/include -o main.exe

2. **Run the Executable**:

   After compiling, run the executable by entering:
   ```sh
   .\main.exe
   
### On macOS

1. **Compile the Project**:

   Open a terminal and navigate to the project directory. Run the following command to compile the project:
   ```sh
   g++ main.cpp dependencies/src/reservations.cpp dependencies/src/utility.cpp dependencies/src/customerdetails.cpp dependencies/src/menu.cpp dependencies/src/order.cpp dependencies/src/bill.cpp -Idependencies/include -o main
   
2. **Run the Executable**:

   After compiling, run the executable by entering:
   ```sh
   ./main


   
   
