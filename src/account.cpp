#include <iostream>

using namespace std;

#include <iostream.h>
#include <iomanip.h>
#include <conio.h>

class Account
{
    int acc_no;
    char *name;
    float balance;

public:
    void opbal(void);
    void deposit(void);
    void withdraw(void);
    void display(void);
};

void bank ::opbal(void)
{
    cout << endl
         << endl;
    cout << "Enter Name :-";
    cin >> name;
    cout << "Enter A/c no. :-";
    cin >> acno;
    cout << "Enter A/c Type :-";
    cin >> actype;
    cout << "Enter Opening Balance:-";
    cin >> bal;
}

void bank ::deposit(void)
{
    cout << "Enter Deposit amount :-";
    int deposit = 0;
    cin >> deposit;
    deposit = deposit + bal;
    cout << "\nDeposit Balance = " << deposit;
    bal = deposit;
}

void bank ::withdraw(void)
{
    int withdraw;
    cout << "\nBalance Amount = " << bal;
    cout << "\nEnter Withdraw Amount :-";
    cin >> withdraw;
    bal = bal - withdraw;
    cout << "After Withdraw Balance is " << bal;
}

void bank ::display(void)
{
    cout << endl
         << endl
         << endl;
    cout << setw(50) << "DETAILS" << endl;
    cout << setw(50) << "name      " << name << endl;
    cout << setw(50) << "A/c. No.     " << acno << endl;
    cout << setw(50) << "A/c Type      " << actype << endl;
    cout << setw(50) << "Balance     " << bal << endl;
}

void main()
{
    clrscr();
    bank o1;
    int choice;
}