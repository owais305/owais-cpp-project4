#include <iostream>
#include <string>
using namespace std;

class BankAccount {
protected:
    int accountNumber;
    string accountHolderName;
    double balance;

public:
    BankAccount(int accNo, string name, double bal = 0.0) {
        accountNumber = accNo;
        accountHolderName = name;
        balance = bal;
    }

    virtual ~BankAccount() {}

    void deposit(double amount) {
        balance += amount;
        cout << "Amount deposited successfully.\n";
    }

    virtual void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            cout << "Amount withdrawn successfully.\n";
        } else {
            cout << "Insufficient balance.\n";
        }
    }

    double getBalance() const {
        return balance;
    }

    virtual void displayAccountInfo() const {
        cout << "\nAccount Number: " << accountNumber;
        cout << "\nAccount Holder: " << accountHolderName;
        cout << "\nBalance: " << balance << endl;
    }

    virtual void calculateInterest() = 0;
};


class SavingsAccount : public BankAccount {
    double interestRate;

public:
    SavingsAccount(int accNo, string name, double bal, double rate)
        : BankAccount(accNo, name, bal), interestRate(rate) {}

    void calculateInterest() override {
        double interest = balance * interestRate / 100;
        cout << "Savings Account Interest: " << interest << endl;
    }
};

class CheckingAccount : public BankAccount {
    double overdraftLimit;

public:
    CheckingAccount(int accNo, string name, double bal, double limit)
        : BankAccount(accNo, name, bal), overdraftLimit(limit) {}

    void withdraw(double amount) override {
        if (amount <= balance + overdraftLimit) {
            balance -= amount;
            cout << "Withdrawal successful (Checking Account).\n";
        } else {
            cout << "Withdrawal exceeds overdraft limit.\n";
        }
    }

    void calculateInterest() override {
        cout << "Checking Account has no interest.\n";
    }
};

class FixedDepositAccount : public BankAccount {
    int term; 

public:
    FixedDepositAccount(int accNo, string name, double bal, int termMonths)
        : BankAccount(accNo, name, bal), term(termMonths) {}

    void calculateInterest() override {
        double rate = 7.0; // fixed interest rate
        double interest = balance * rate * term / (12 * 100);
        cout << "Fixed Deposit Interest: " << interest << endl;
    }
};

int main() {
    BankAccount *account = nullptr;
    int choice;

    cout << "===== Bank Account Management System =====\n";

    do {
        cout << "\n1. Create Savings Account";
        cout << "\n2. Create Checking Account";
        cout << "\n3. Create Fixed Deposit Account";
        cout << "\n4. Deposit";
        cout << "\n5. Withdraw";
        cout << "\n6. Display Account Info";
        cout << "\n7. Calculate Interest";
        cout << "\n8. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        if (choice == 1) {
            account = new SavingsAccount(101, "Jinay", 5000, 5);
            cout << "Savings Account Created.\n";
        } else if (choice == 2) {
            account = new CheckingAccount(102, "Jinay", 3000, 2000);
            cout << "Checking Account Created.\n";
        } else if (choice == 3) {
            account = new FixedDepositAccount(103, "Jinay", 10000, 12);
            cout << "Fixed Deposit Account Created.\n";
        } else if (account != nullptr) {
            switch (choice) {
            case 4: {
                double amount;
                cout << "Enter amount to deposit: ";
                cin >> amount;
                account->deposit(amount);
                break;
            }
            case 5: {
                double amount;
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                account->withdraw(amount);
                break;
            }
            case 6:
                account->displayAccountInfo();
                break;
            case 7:
                account->calculateInterest();
                break;
            }
        } else if (choice != 8) {
            cout << "Please create an account first!\n";
        }

    } while (choice != 8);

    cout << "Thank you for using our system!\n";

    delete account;
    return 0;
}

