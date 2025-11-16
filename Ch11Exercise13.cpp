// Kristoffer Carlino
// C++ 310
// Dr. Robert Flowers
// Chapter 11 Exercise 13 Assignment (Module 9)

#include <iostream>
#include <iomanip>
using namespace std;

// ==========================
// Base Class: bankAccount
// ==========================
class bankAccount {
protected:
    int accountNumber;
    double balance;

public:
    bankAccount() : accountNumber(0), balance(0.0) {}
    bankAccount(int accNum, double bal) : accountNumber(accNum), balance(bal) {}

    void setAccountNumber(int accNum) { accountNumber = accNum; }
    int getAccountNumber() const { return accountNumber; }

    void setBalance(double amount) { balance = amount; }
    double getBalance() const { return balance; }

    virtual void deposit(double amount) {
        if (amount > 0)
            balance += amount;
        else
            cout << "Invalid deposit amount.\n";
    }

    virtual void withdraw(double amount) {
        if (amount > 0 && amount <= balance)
            balance -= amount;
        else
            cout << "Insufficient funds or invalid amount.\n";
    }

    virtual void printAccountInfo() const {
        cout << fixed << setprecision(2);
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: $" << balance << endl;
    }
};

// ==========================
// Derived Class: checkingAccount
// ==========================
class checkingAccount : public bankAccount {
private:
    double interestRate;
    double minimumBalance;
    double serviceCharge;

public:
    checkingAccount() : bankAccount(), interestRate(0.0), minimumBalance(500.0), serviceCharge(25.0) {}
    checkingAccount(int accNum, double bal, double rate)
        : bankAccount(accNum, bal), interestRate(rate), minimumBalance(500.0), serviceCharge(25.0) {
    }

    void postInterest() {
        balance += balance * (interestRate / 100);
    }

    void withdraw(double amount) override {
        if (amount <= 0) {
            cout << "Invalid withdrawal amount.\n";
            return;
        }

        if (amount > balance) {
            cout << "Insufficient funds.\n";
        }
        else {
            balance -= amount;
            if (balance < minimumBalance) {
                cout << "Below minimum balance. Service charge of $" << serviceCharge << " applied.\n";
                balance -= serviceCharge;
            }
        }
    }

    void printAccountInfo() const override {
        cout << "\n=== Checking Account Information ===\n";
        bankAccount::printAccountInfo();
        cout << "Interest Rate: " << interestRate << "%" << endl;
        cout << "Minimum Balance: $" << minimumBalance << endl;
        cout << "Service Charge: $" << serviceCharge << endl;
        cout << "====================================\n";
    }
};

// ==========================
// Derived Class: savingsAccount
// ==========================
class savingsAccount : public bankAccount {
private:
    double interestRate;

public:
    savingsAccount() : bankAccount(), interestRate(0.0) {}
    savingsAccount(int accNum, double bal, double rate)
        : bankAccount(accNum, bal), interestRate(rate) {
    }

    void postInterest() {
        balance += balance * (interestRate / 100);
    }

    void withdraw(double amount) override {
        if (amount <= 0) {
            cout << "Invalid withdrawal amount.\n";
        }
        else if (amount > balance) {
            cout << "Insufficient funds in savings account.\n";
        }
        else {
            balance -= amount;
        }
    }

    void printAccountInfo() const override {
        cout << "\n=== Savings Account Information ===\n";
        bankAccount::printAccountInfo();
        cout << "Interest Rate: " << interestRate << "%" << endl;
        cout << "===================================\n";
    }
};

// ==========================
// Main Program
// ==========================
int main() {
    int mainChoice;

    do {
        cout << "\n==============================\n";
        cout << "   BANK ACCOUNT MAIN MENU\n";
        cout << "==============================\n";
        cout << "1. Create Checking Account\n";
        cout << "2. Create Savings Account\n";
        cout << "3. Exit\n";
        cout << "Select an option: ";
        cin >> mainChoice;

        if (mainChoice == 1) {
            int accNum;
            double bal, rate;
            cout << "\nEnter account number: ";
            cin >> accNum;
            cout << "Enter opening balance: $";
            cin >> bal;
            cout << "Enter interest rate (%): ";
            cin >> rate;

            checkingAccount checkAcc(accNum, bal, rate);
            int choice;
            do {
                cout << "\n--- Checking Account Menu ---\n";
                cout << "1. Deposit\n";
                cout << "2. Withdraw\n";
                cout << "3. Post Interest\n";
                cout << "4. Display Account Info\n";
                cout << "5. Exit to Main Menu\n";
                cout << "Enter choice: ";
                cin >> choice;

                double amount;
                switch (choice) {
                case 1:
                    cout << "Enter amount to deposit: $";
                    cin >> amount;
                    checkAcc.deposit(amount);
                    break;
                case 2:
                    cout << "Enter amount to withdraw: $";
                    cin >> amount;
                    checkAcc.withdraw(amount);
                    break;
                case 3:
                    checkAcc.postInterest();
                    cout << "Interest posted successfully.\n";
                    break;
                case 4:
                    checkAcc.printAccountInfo();
                    break;
                case 5:
                    cout << "Returning to main menu...\n";
                    break;
                default:
                    cout << "Invalid option. Try again.\n";
                }
            } while (choice != 5);
        }

        else if (mainChoice == 2) {
            int accNum;
            double bal, rate;
            cout << "\nEnter account number: ";
            cin >> accNum;
            cout << "Enter opening balance: $";
            cin >> bal;
            cout << "Enter interest rate (%): ";
            cin >> rate;

            savingsAccount savAcc(accNum, bal, rate);
            int choice;
            do {
                cout << "\n--- Savings Account Menu ---\n";
                cout << "1. Deposit\n";
                cout << "2. Withdraw\n";
                cout << "3. Post Interest\n";
                cout << "4. Display Account Info\n";
                cout << "5. Exit to Main Menu\n";
                cout << "Enter choice: ";
                cin >> choice;

                double amount;
                switch (choice) {
                case 1:
                    cout << "Enter amount to deposit: $";
                    cin >> amount;
                    savAcc.deposit(amount);
                    break;
                case 2:
                    cout << "Enter amount to withdraw: $";
                    cin >> amount;
                    savAcc.withdraw(amount);
                    break;
                case 3:
                    savAcc.postInterest();
                    cout << "Interest posted successfully.\n";
                    break;
                case 4:
                    savAcc.printAccountInfo();
                    break;
                case 5:
                    cout << "Returning to main menu...\n";
                    break;
                default:
                    cout << "Invalid option. Try again.\n";
                }
            } while (choice != 5);
        }

        else if (mainChoice == 3) {
            cout << "\nThank you for banking with us!\n";
        }
        else {
            cout << "Invalid selection. Try again.\n";
        }

    } while (mainChoice != 3);

    return 0;
}
