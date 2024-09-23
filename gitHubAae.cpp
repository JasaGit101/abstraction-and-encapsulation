#include <iostream>
#include <limits>

using namespace std;

class Account
{
protected:
    double balance;

public:
    Account(double initial_balance = 0.0) : balance(initial_balance) {}

    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
    virtual void checkBalance() const {
        cout << "Current Balance: " << balance << " php" << endl;
    }

    virtual void showSubMenu() = 0;
};

class savingsAccount : public Account 
{
private:
    const double min_balance = 1000.0; // Minimum balance

public:
    savingsAccount(double initial_balance = 1000.0) : Account(initial_balance) {}

    void deposit(double amount) override 
    {
        if (amount <= 0)
        {
            cout << "Invalid deposit amount. Must be greater than 0." << endl;
        }
        else
        {
            balance += amount;
            cout << "Deposited: " << amount << " php" << endl;
        }
    }

    void withdraw(double amount) override
    {
        if (amount <= 0)
        {
            cout << "Invalid withdrawal amount. Must be greater than 0." << endl;
        }
        else if (balance - amount < min_balance)
        {
            cout << "Insufficient funds. You must maintain a minimum balance of " << min_balance << " php." << endl;
        }
        else
        {
            balance -= amount;
            cout << "Withdrew: " << amount << " php \nRemaining balance: " << balance << " php" << endl;
        }
    }

    void showSubMenu() override
    {
        int choice;
        double amount;

        do 
        {
            cout << "\nSavings Account Sub Menu\n";
            cout << "1 - Deposit\n";
            cout << "2 - Withdraw\n";
            cout << "3 - Check Balance\n";
            cout << "4 - Back\n";
            cout << "Enter your choice: ";

            // Input validation for choice
            while (!(cin >> choice) || (choice < 1 || choice > 4))
            {
                cout << "Invalid choice. Please enter a number between 1 and 4: ";
                cin.clear(); // Clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            }
            cout << "\n";

            switch (choice)
            {
                case 1:
                    cout << "Enter amount to deposit: ";

                    while (!(cin >> amount) || amount <= 0) // Input validation for amount
                    {
                        cout << "Invalid amount. Please enter a positive number: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    deposit(amount);
                    break;

                case 2:
                    cout << "Enter amount to withdraw: ";

                    while (!(cin >> amount) || amount <= 0) // Input validation for amount
                    {
                        cout << "Invalid amount. Please enter a positive number: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    withdraw(amount);
                    break;

                case 3:
                    checkBalance();
                    break;

                case 4:
                    cout << "Returning to Main Menu...\n";
                    break;
                
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        }
        while (choice != 4);
    }
};

class currentAccount : public Account
{
public:
    currentAccount(double initial_balance = 0.0) : Account(initial_balance) {}

    void deposit(double amount) override
    {
        if (amount <= 0)
        {
            cout << "Invalid deposit amount. Must be greater than 0." << endl;
        }
        else
        {
            balance += amount;
            cout << "Deposited: " << amount << " php" << endl;
        }
    }

    void withdraw(double amount) override
    {
        if (amount <= 0)
        {
            cout << "Invalid withdrawal amount. Must be greater than 0." << endl;
        }
        else if (balance < amount)
        {
            cout << "Insufficient funds." << endl;
        }
        else
        {
            balance -= amount;
            cout << "Withdrew: " << amount << " php" << endl;
        }
    }

    void showSubMenu() override
    {
        int choice;
        double amount;

        do
        {
            cout << "\nCurrent Account Sub Menu\n";
            cout << "1 - Deposit\n";
            cout << "2 - Withdraw\n";
            cout << "3 - Check Balance\n";
            cout << "4 - Back\n";
            cout << "Enter your choice: ";

            // Input validation for choice
            while (!(cin >> choice) || (choice < 1 || choice > 4))
            {
                cout << "Invalid choice. Please enter a number between 1 and 4: ";
                cin.clear(); // Clear the error state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            }
            cout << "\n";

            switch (choice)
            {
                case 1:
                    cout << "Enter amount to deposit: ";

                    while (!(cin >> amount) || amount <= 0) // Input validation for amount
                    {
                        cout << "Invalid amount. Please enter a positive number: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    deposit(amount);
                    break;
                    
                case 2:
                    cout << "Enter amount to withdraw: ";

                    while (!(cin >> amount) || amount <= 0) // Input validation for amount
                    {
                        cout << "Invalid amount. Please enter a positive number: ";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    withdraw(amount);
                    break;

                case 3:
                    checkBalance();
                    break;

                case 4:
                    cout << "Returning to Main Menu...\n";
                    break;

                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        }
        while (choice != 4);
    }
};

void showMainMenu()
{
    cout << "\nMain Menu\n";
    cout << "1 - Savings Account\n";
    cout << "2 - Current Account\n";
    cout << "3 - Exit\n";
}

int main()
{
    int mainChoice = 0;

    savingsAccount* mySavingsAccount = new savingsAccount(1000);
    currentAccount* myCurrentAccount = new currentAccount(0);

    do
    {
        showMainMenu();
        cout << "Enter your choice: ";

        // Input validation for main choice
        while (!(cin >> mainChoice) || (mainChoice < 1 || mainChoice > 3))
        {
            cout << "Invalid choice. Please enter a number between 1 and 3: ";
            cin.clear(); // Clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }

        switch (mainChoice)
        {
            case 1:
                cout << "You selected Savings Account.\n";
                mySavingsAccount->showSubMenu();
                break;

            case 2:
                cout << "You selected Current Account.\n";
                myCurrentAccount->showSubMenu();
                break;

            case 3:
                cout << "Exiting the program. Resetting all account information...\n";

                // Reset the accounts by deleting and re-initializing them
                delete mySavingsAccount;
                delete myCurrentAccount;

                // Reinitialize accounts with the original starting balances
                mySavingsAccount = new savingsAccount(1000); // Minimum balance for savings
                myCurrentAccount = new currentAccount(0);    // No minimum balance for current

                cout << "All accounts have been reset to their initial state.\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
    while (mainChoice != 3);

    // Clean up dynamically allocated memory before exiting
    delete mySavingsAccount;
    delete myCurrentAccount;

    return 0;
}
