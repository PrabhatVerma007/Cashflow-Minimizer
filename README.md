# Cashflow-Minimizer
# Expense Management Tool

## Overview
The Expense Management Tool is a simple C++ program that helps a group of friends track and settle expenses efficiently. It keeps a record of transactions and minimizes cash flow by reducing the number of transactions required for settlement.

## Features
- **Add Transactions**: Record expenses between friends.
- **View Current Balances**: Display the net balance of each person.
- **Minimize Cash Flow**: Optimize payments to reduce the number of transactions.
- **User Input Validation**: Ensures correct input format and limits on the number of friends.
- **Clear Console Functionality**: Provides a clean interface for ease of use.

## Requirements
- C++ compiler (e.g., g++, clang++)
- Supports Windows and Linux-based systems

## Compilation & Execution
### Compiling the Program
To compile the program, use the following command:
```sh
 g++ -o expense_manager expense_manager.cpp
```

### Running the Program
After compilation, run the program with:
```sh
 ./expense_manager
```

## Usage Guide
1. Enter the total number of people sharing expenses (minimum 2, maximum 50).
2. Choose an option from the main menu:
   - **1: Add a Transaction** - Enter payer, payee, and amount.
   - **2: View Current Balances** - Display each person's balance.
   - **3: Minimize Cash Flow** - Optimize settlements.
   - **4: Exit Program** - Close the application.

## Example Interaction
```
========== Welcome to Expense Management Tool ==========
Enter the total number of people: 3

=================== Expense Management ===================
1. Add a Transaction
2. View Current Balances
3. Minimize Cash Flow
4. Exit Program
=========================================================
Choose an option: 1

Enter the name of the person that has to pay: Alice
Enter the name of the person that gets the money: Bob
Enter the amount: 500
Transaction added successfully!
```

## Code Structure
- `clearScreen()`: Clears the console.
- `validateFriendsCount(int friends)`: Ensures the number of friends is within the allowed range.
- `minimizeCashFlow(map<string, int>& net)`: Reduces the number of transactions.
- `displayBalances(const map<string, int>& net)`: Displays the balances.
- `addTransaction(map<string, int>& net, set<string>& unique_people, int friends)`: Adds a new transaction.
- `displayMenu()`: Shows the main menu.

## Contributions
Feel free to contribute by improving the logic, optimizing the cash flow algorithm, or enhancing the user interface.
