#include <iostream>
#include <map> // For using the map container
#include <set> // For using the set container
#include <string>
#include <utility> // For using pairs
#include <limits>
#include <iomanip> // For formatting output
using namespace std;

// Function to clear the console screen
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Function to validate total number of friends
bool validateFriendsCount(int friends) {
    const int MAX_FRIENDS = 50; // Maximum allowed number of friends
    const int MIN_FRIENDS = 2;  // Minimum allowed number of friends

    if (friends < MIN_FRIENDS) {
        cout << "Error: Number of friends must be at least " << MIN_FRIENDS << "." << endl;
        cout << "The expense management tool requires at least 2 people to track expenses." << endl;
        return false;
    }

    if (friends > MAX_FRIENDS) {
        cout << "Error: Number of friends (" << friends << ") exceeds the maximum limit of " << MAX_FRIENDS << "." << endl;
        cout << "Please reduce the number of friends to manage expenses effectively." << endl;
        return false;
    }

    return true;
}

// Function to minimize cash flow
template<typename MapType>
void minimizeCashFlow(MapType& net) {
    auto comparator = [](pair<string, int> p1, pair<string, int> p2) {
        return p1.second < p2.second;
    };
    multiset<pair<string, int>, decltype(comparator)> m(comparator);
    for (const auto& p : net) {
        if (p.second != 0) {
            m.insert(p);
        }
    }

    if (m.empty()) {
        cout << "No transactions are needed." << endl;
        return;
    }

    int transaction_count = 0;
    while (!m.empty()) {
        auto low = m.begin();
        auto high = prev(m.end());
        string debit_person = low->first;
        int debit = low->second;
        string credit_person = high->first;
        int credit = high->second;

        m.erase(low);
        m.erase(high);

        int settled_amount = min(abs(debit), abs(credit));
        debit += settled_amount;
        credit -= settled_amount;
        transaction_count++;
        cout << debit_person << " will pay " << settled_amount << " rupees to " << credit_person << endl;

        net[debit_person] = debit;
        net[credit_person] = credit;

        if (debit != 0) m.insert(make_pair(debit_person, debit));
        if (credit != 0) m.insert(make_pair(credit_person, credit));
    }
    cout << "Total number of transactions made were: " << transaction_count << endl;
}

// Function to display balances of each person
void displayBalances(const map<string, int>& net) {
    cout << "\n=================== Current Balances ===================\n";
    cout << left << setw(20) << "Person" << "Balance (rupees)" << endl;
    cout << "------------------------------------------------------\n";
    for (const auto& p : net) {
        cout << left << setw(20) << p.first << p.second << endl;
    }
    cout << "======================================================\n";
}

// Function to add a transaction
void addTransaction(map<string, int>& net, set<string>& unique_people, int friends) {
    string x, y;
    int amount;

    cout << "\n========== Add a Transaction ==========" << endl;

    cout << "Enter the name of the person that has to pay: ";
    cin >> x;
    cout << "Enter the name of the person that gets the money: ";
    cin >> y;

    if (x == y) {
        cout << "Invalid transaction as payer and payee are the same." << endl;
        return;
    }

    // Check if adding a new person exceeds the limit
    if (unique_people.find(x) == unique_people.end() && unique_people.size() >= friends) {
        cout << "Error: Adding '" << x << "' exceeds the total number of specified friends (" << friends << ").\n";
        return;
    }
    if (unique_people.find(y) == unique_people.end() && unique_people.size() >= friends) {
        cout << "Error: Adding '" << y << "' exceeds the total number of specified friends (" << friends << ").\n";
        return;
    }

    // Validate the amount input
    while (true) {
        cout << "Enter the amount: ";
        if (cin >> amount && amount > 0) {
            break; // Exit loop if valid input
        } else {
            cout << "Invalid input. Please enter a positive integer for the amount.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // Add the people to the set if they are new
    unique_people.insert(x);
    unique_people.insert(y);

    // Update balances
    net[x] -= amount;
    net[y] += amount;

    cout << "Transaction added successfully!\n";
}

// Function to display the main menu
void displayMenu() {
    cout << "\n=================== Expense Management ===================" << endl;
    cout << "1. Add a Transaction" << endl;
    cout << "2. View Current Balances" << endl;
    cout << "3. Minimize Cash Flow" << endl;
    cout << "4. Exit Program" << endl;
    cout << "=========================================================" << endl;
    cout << "Choose an option: ";
}

// Main function
int main() {
    int friends;

    clearScreen();
    cout << "========== Welcome to Expense Management Tool ==========" << endl;

    // Validate input for 'friends'
    while (true) {
        cout << "Enter the total number of people: ";
        if (cin >> friends) {
            // Use the new validation function
            if (validateFriendsCount(friends)) {
                break; // Exit loop if valid input
            }
        } else {
            cout << "Invalid input. Please enter a positive integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    map<string, int> net; // Map to track balances
    set<string> unique_people; // Set to track unique people involved in transactions

    int option;
    do {
        displayMenu();

        // Validate menu option input
        while (!(cin >> option)) {
            cout << "Invalid input. Please enter a number between 1 and 4.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Choose an option: ";
        }

        clearScreen();

        switch (option) {
            case 1:
                addTransaction(net, unique_people, friends);
                break;

            case 2:
                displayBalances(net);
                break;

            case 3:
                cout << "\n========== Minimizing Cash Flow ==========" << endl;
                minimizeCashFlow(net);
                break;

            case 4:
                cout << "Thank you for using the Expense Management Tool. Goodbye!\n";
                break;

            default:
                cout << "Invalid option. Please try again.\n";
                break;
        }
    } while (option != 4);

    return 0;
}