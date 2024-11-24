/***************************************************
This Program demonstrates a Simple Banking System

Date of Creation: 18th August 2022

@authors:
    Dajeel Dulal (ID:8672)
    Sushant Adhikari(ID:8543)
    Arpit Sharma(ID:8130)
    Samprada Das(ID:8557)
    Bijay Jhenga Magar(ID:8664)

***************************************************/



#include<iostream>
#include<fstream>
#include<stdio.h>
#include<conio.h>
#include<string>
#include<cstring>
using namespace std;


void Login(); //Declaring Login Function

//***********************************************************************
//Account class declaration  
//***********************************************************************
class Account
{
protected:
    double balance; //declaring balance
    char name[40]; //declaring size 40 of char name
    int accNo; //declaring account number
    int no_of_deposits = 0; //declaring and initializing no_Of_Deposits
    int no_of_withdraws = 0; //declaring and initializing no_Of_Deposits

public:
    float yearlyInterestRate; // declaring yearly intrest rate
    double monthlyCharge = 0;  //declaring and initializing monthlycharge
    int z; //declaring a simple variable for bank account

    //***********************************************************************
    //DEFAULT CONSTRUCTOR, SETS THE BALACE AND ANNUAL INTEREST RATE TO ZERO *
    //***********************************************************************
    Account()
    {
        balance = 0;
        yearlyInterestRate = 0;
    }

    //*******************************************************************************
    //PARAMETERIZED CONSTRUCTOR, ASSIGNS VALUES TO BALANCE AND ANNUAL INTEREST RATE *
    //*******************************************************************************
    Account(float b, float yearly)
    {
        balance = b;
        yearlyInterestRate = yearly;
    }

    //***********************************************************
    //VIRTUAL FUNCTION, UPDATES DEPOSITS AND NUMBER OF DEPOSITS *
    //***********************************************************
    virtual void makeDeposit(double d)
    {
        balance = balance + d;
        no_of_deposits = ++no_of_deposits;
    }

    //*****************************************************************
    //VIRTUAL FUNCTION, UPDATES WITHDRAWALS AND NUMBER OF WITHDRAWALS *
    //*****************************************************************
    virtual void makeWithdrawal(double w)
    {
        balance = balance - w;
        no_of_withdraws = ++no_of_withdraws;
    }

    //*******************************************************
    //CALCULATES THE DIFFERENT VALUES IMPORTANT TO THE BANK *
    //*******************************************************
    virtual void calcInt()
    {
        float monthlyInterestRate = yearlyInterestRate / 12; //declaring and initialzing monthly interest rate
        float monthlyInterest = balance * monthlyInterestRate; //declaring and initializing monthly interest rate
        balance = balance + monthlyInterest;
    }

    //****************************************
    //UPDATES VALUES AT THE END OF THE MONTH *
    //****************************************
    virtual void monthlyProc()
    {
        balance = balance - monthlyCharge;
        calcInt();
        no_of_deposits = 0;
        no_of_withdraws = 0;
        monthlyCharge = 0;
    }

    //*********************
    //DISPLAYS THE VALUES *
    //*********************
    void display()
    {
        cout <<"Account no : "<<accNo<<endl;
        cout<<"Name :"<<name<<endl;
        cout<<"Balance : "<<balance<<endl;
        cout<<"No of Deposits : "<<no_of_deposits<<endl;
        cout<<"No of Withdrawals : "<< no_of_withdraws<<endl;
        cout<<"Yearly Interest rate : "<<yearlyInterestRate<<endl;
        cout<<endl;
    }

    //*********************
    //RETURNS THE BALANCE *
    //*********************
    double getBalance()
    {
        return balance;
    }

    //********************************
    //RETURNS THE NUMBER OF DEPOSITS *
    //********************************
    int getDeposits()
    {
        return no_of_deposits;
    }

    //***********************************
    //RETURNS THE NUMBER OF WITHDRAWALS *
    //***********************************
    int getWithdrawals()
    {
        return no_of_withdraws;
    }

    //*********************
    //GETS ACCOUNT NUMBER *
    //*********************
    void getAccNo()
    {
        cout << "Enter Account Number: ";
        cin >> z;
    }
};

int choice; //declaring choice for all the choices in the program
void dashboard();  //declaring dashboard 

//*******************************************************************
//SAVINGACCOUNTS CLASS DECLATARION, DERIVED FROM THE ACCOUNT CLASS *
//*******************************************************************
class SavingAccounts: public Account {

public:
    string status; //DEFINING A FLAG VARIABLE FOR THE ACCOUNT STATUS

    //********************************************************
    //DECLARING THE FUNCTIONS INSIDE THE  SAVINGACCOUNTS CLASS *
    //********************************************************
    void makeWithdrawal(double w1);
    void makeDeposit(double d1);
    void monthlyProc();
    void createAccount();
    void readDetails();
    void readAllDetails();
    void updateDetails();
    void deleteAccount();

    //**********************************
    //CHECKS THE STATUS OF THE ACCOUNT *
    //**********************************
    void statusCheck()
    {
        if (balance > 25) {
            status = "Active";
        }
        else {
            status = "Not Active";
        }
    }

    //****************************************
    //DEFAULT CONSTRUCTOR, CHECKS THE STATUS *
    //****************************************
    SavingAccounts()
    {
        statusCheck();
        balance = 0;
        yearlyInterestRate = 0;
    }

    //**********************************************************************
    //PARAMETERIZED CONSTRUCTOR, SETS THE BALANCE AND ANNUAL INTEREST RATE *
    //**********************************************************************
    SavingAccounts(float b1, float i1):Account(b1,i1)
    {
        statusCheck();
    }
};

//*************************************************************************
//THIS FUNCTION WITHDRAWS BALANCE FROM SAVING ACCOUNT & UPDATES THE BALANCE *
//*************************************************************************
void SavingAccounts :: makeWithdrawal(double w1)
{
    SavingAccounts s;
    int f = 0;
    fstream file1;
    file1.open("Savings Accounts.dat", ios::binary | ios:: in | ios::out);
    file1.seekg(0);

    if (!file1) {
        cout << "Sorry! Error in Opening the Records!!" << endl;
    }

    else{
        double b;
        getAccNo();
        while(file1.read((char*)&s,sizeof(s))) {
            if (s.accNo == z) {
                cout << "ACCOUNT INFO" << endl;
                s.statusCheck();
                f = 1;
                b = s.getBalance() - w1;
                if (s.status == "Active" && b>0) {
                    file1.seekp(-sizeof(s), ios::cur);
                    s.Account::makeWithdrawal(w1);
                    cout << endl << "UPDATED INFO" << endl << endl;
                    s.display();
                    cout << "New Balance: " << s.getBalance();
                    cout << "Status: " << s.status;
                    file1.write((char*)&s,sizeof(s));
                }

                else {
                    cout << "Sorry! Not Enough Balance!" << endl;
                }
            }
        }
    }

    if(f==0){
        cout << "Sorry, Account Not Found!!" << endl;
    }

    file1.close();
}

//*************************************************************************
//THIS FUNCTION DEPOSITS BALANCE INTO SAVING ACCOUNT & UPDATES THE BALANCE *
//*************************************************************************
void SavingAccounts :: makeDeposit(double d1)
{
    SavingAccounts s;
    int f = 0;
    fstream file1;
    file1.open("Savings Accounts.dat", ios::binary | ios:: in | ios::out);
    file1.seekg(0);

    if (!file1) {
        cout << "Sorry! Error in Opening the Records!!" << endl;
    }

    else{
        getAccNo();
        while(file1.read((char*)&s,sizeof(s))) {
            if (s.accNo == z) {
                cout << "ACCOUNT INFO" << endl;
                s.display();
                s.statusCheck();
                f = 1;
                if (s.status == "Active") {
                    file1.seekp(-sizeof(s), ios::cur);
                    s.Account::makeDeposit(d1);
                    cout << endl << "UPDATED INFO" << endl << endl;
                    cout << "New Balance: " << s.getBalance();
                    cout << "Status: " << s.status;
                    file1.write((char*)&s,sizeof(s));
                }

                else {
                    if((s.balance + d1) > 25){
                        file1.seekp(-sizeof(s), ios::cur);
                        s.Account::makeDeposit(d1);
                        s.statusCheck();
                        cout << endl << "UPDATED INFO" << endl << endl;
                        cout << "New Balance: " << s.getBalance();
                        cout << "Status: " << s.status;
                        file1.write((char*)&s,sizeof(s));
                    }

                    else{
                        cout << "Sorry! Not Enough Balance!" << endl;
                    }
                }
            }
        }
    }

    if(f==0){
        cout << "Sorry, Account Not Found!!" << endl;
    }

    file1.close();
}

//*************************************************************************
//THIS FUNCTION CALCULATES END OF THE MONTH CONSIDERING NO OF WITHDRAWALS *
//*************************************************************************

void SavingAccounts :: monthlyProc()
{
    SavingAccounts s;

    ofstream tempFile("temp.dat", ios::out | ios::binary);
    ifstream file1("Savings Accounts.dat", ios::binary);
    file1.seekg(0);

    if (!file1) {
        cout << "Sorry! Error in Opening the Records!!" << endl;
    }

    else{
        while(file1.read((char*)&s,sizeof(s))) {
            if (s.no_of_withdraws > 4) {
                s.monthlyCharge = s.monthlyCharge + (1 * (s.no_of_withdraws - 4));
            }

            s.Account::monthlyProc();

            tempFile.write((char*)&s,sizeof(s));
            s.statusCheck();
        }
    }

    cout << "MONTHLY UPDATES UPDATED!!" << endl;
    system("PAUSE");
    dashboard();

    file1.close();
    tempFile.close();
    remove("Savings Accounts.dat");
    rename("temp.dat", "Savings Accounts.dat");

}

//*************************************************************************
//THIS FUNCTION CREATES ACCOUNT IN THE CLASS SAVINGACCOUNTS *
//*************************************************************************

void SavingAccounts :: createAccount()
{
    fstream create("Savings Accounts.dat", ios::app | ios::binary);
    SavingAccounts s;

    cout << "Please Enter Your Saving Account Details:" << endl << endl;

    cout << "Enter the bank account number: ";
    cin >> s.accNo;

    cout << "Enter your name: ";
    cin.ignore();
    cin.getline(s.name, 40);

    cout << "Starting balance (More than $25): ";
    cin >> s.balance;

    cout << "Annual Interest Rate: ";
    cin >> s.yearlyInterestRate;

    s.no_of_deposits = s.getDeposits();
    s.no_of_withdraws = s.getWithdrawals();
    s.status;

    if (s.balance > 25) {
        create.write((char*)&s,sizeof(s));
    }

    else {
        cout << "Sorry Insufficient balance!!" << endl;
    }

    create.close();
}
//*************************************************************************
//THIS FUNCTION DISPLAYES DETAILS *
//*************************************************************************

void SavingAccounts :: readDetails()
{
    ifstream file1;
    SavingAccounts s;
    file1.open("Savings Accounts.dat", ios::in);

    getAccNo();
    if (!file1) {
        cout << "Sorry! Error in Opening the Records!!" << endl;
    }

    else {
        do {
            if (z == s.accNo) {
                s.display();
                s.statusCheck();
                cout << endl << endl << "Status: " << s.status;
                z = 0;
            }
        } while(file1.read((char*)&s,sizeof(s)));

        if (z!=0) {
            cout << "Sorry!! This Account Number Does Not Exist!!" << endl;
        }
    }
    file1.close();
}

//*************************************************************************
//*************THIS FUNCTION DISPLAYS ALL THE DETAILS *********************
//*************************************************************************

void SavingAccounts :: readAllDetails()
{
    ifstream file1;
    file1.open("Savings Accounts.dat");
    SavingAccounts s;

    if (!file1) {
        cout << "Sorry! Error in Opening the Records!!" << endl;
    }

    else {
        while(file1.read((char*)&s,sizeof(s))){
            s.display();
            s.statusCheck();
            s.status;
        }
    }

    cout << endl;
    system("PAUSE");
    dashboard();

    file1.close();

}

//*************************************************************************
//*************THIS FUNCTION DELETES ACCOUNT INFORMATION *****************
//*************************************************************************
void SavingAccounts :: deleteAccount()
{
    SavingAccounts s;

    ofstream tempFile("temp.dat", ios::app | ios::binary);
    ifstream file1("Savings Accounts.dat", ios::binary);

    getAccNo();

    if (!file1 || !tempFile) {
        cout << "Sorry! Error in Opening the Records!!" << endl;
    }

    else{
        while(file1.read((char*)&s,sizeof(s))) {
            if (z != s.accNo) {
                tempFile.write((char*)&s,sizeof(s));
            }
        }
    }

    cout << "Account Successfully Deleted!!" << endl;

    file1.close();
    tempFile.close();
    remove("Savings Accounts.dat");
    rename("temp.dat", "Savings Accounts.dat");
}

//*************************************************************************
//*************THIS FUNCTION UPDATES THE ACCOUNT INFORMATION *****************
//*************************************************************************

void SavingAccounts :: updateDetails()
{
    int f=0;
    SavingAccounts s;

    fstream file1;
    file1.open("Savings Accounts.dat", ios::binary | ios:: in | ios::out);
    file1.seekg(0);

    if (!file1) {
        cout << "Sorry! Error in Opening the Records!!" << endl;
    }

    else{
        system("CLS");
        cout << "UPDATE YOUR SAVINGS ACCOUNT" << endl << endl;
        getAccNo();
        while(file1.read((char*)&s,sizeof(s))) {
            if (s.accNo == z) {
                cout << "ACCOUNT INFO" << endl;
                s.display();
                s.statusCheck();
                f = 1;
                cout << endl << "ENTER NEW INFORMATION" << endl;

                cout << "Account Number (Given by the Bank): ";
                cin >> s.accNo;

                cout << "Name: ";
                cin.ignore();
                cin.getline(s.name, 40);

                s.no_of_deposits = s.getDeposits();
                s.no_of_withdraws = s.getWithdrawals();

                cout << "Starting balance (More than $25): ";
                cin >> s.balance;

                cout << "Annual Interest Rate: ";
                cin >> s.yearlyInterestRate;

                if (s.balance > 25) {
                    file1.seekp(-sizeof(s), ios::cur);
                    file1.write((char*)&s,sizeof(s));
                    cout << "Account Successfully Updated!!" << endl;
                }

                else {
                    cout << "Sorry Insufficient balance!!" << endl;
                }
            }
        }
    }

    if(f==0){
        cout << "Sorry, Account Not Found!!" << endl;
    }

    file1.close();
}

//*******************************************************************
//SAVINGACCOUNTS CLASS DECLATARION, DERIVED FROM THE ACCOUNT CLASS *
//*******************************************************************

class Checking: public Account {

public:
    Checking()
    {
    balance = 0;
    yearlyInterestRate = 0;
    }
    string status;
    void makeWithdrawal1(double w1);
    void makeDeposit1(double d1);
    void monthlyProc1();
    void createAccount1();
    void readDetails1();
    void readAllDetails1();
    void updateDetails1();
    void deleteAccount1();

    void operator -()
    {
        double x;
        x = -x;
    }

    void statusCheck()
    {
        if (balance > 25) {
            status = "Active";
        }
        else {
            status = "Not Active";
        }
    }

};
/*************************************************************************
//THIS FUNCTION WITHDHRAWS BALANCE FROM CHECKING ACCOUNT & UPDATES THE BALANCE *
//*************************************************************************/
void Checking :: makeWithdrawal1(double w1)
{
    Checking c;
    int f = 0;
    fstream file1;
    file1.open("Checking Accounts.dat", ios::binary | ios:: in | ios::out);
    file1.seekg(0);

    if (!file1) {
        cout << "Sorry! Error in Opening the Records!!" << endl;
    }

    else{
        double a;
        getAccNo();
        while(file1.read((char*)&c,sizeof(c))) {
            if (c.accNo == z) {
                cout << "ACCOUNT INFO" << endl;
                a = c.balance - z;
                f = 1;
                if (a > 0) {
                    c.Account::makeWithdrawal(w1);
                    c.display();
                    cout << endl << "UPDATED INFO" << endl << endl;
                    cout << "New Balance: " << c.getBalance();
                    file1.seekp(-sizeof(c), ios::cur);
                    file1.write((char*)&c,sizeof(c));
                }

                else {
                    cout << "Sorry! Insufficient Balance!!" << endl << endl;

                    cout << "YOUR UPDATED INFO" << endl;
                    if(c.balance > 25) {
                        c.balance -= 15;
                        cout << "The Bank took a Service Charge of $15." << endl;
                    }

                    else {
                        cout << "You did not have the sufficient balance to pay the Service Charge." << endl;
                        -c.getBalance();
                    }

                    cout << "Your new Balance is: " << c.getBalance() << endl;

                    file1.seekp(-sizeof(c), ios::cur);
                    file1.write((char*)&c,sizeof(c));
                }
            }
        }
    }

    if(f==0){
        cout << "Sorry, Account Not Found!!" << endl;
    }

    file1.close();
}

/*************************************************************************
//THIS FUNCTION DEPSOTIES BALANCE INTO CHECKING ACCOUNT & UPDATES THE BALANCE *
//*************************************************************************/
void Checking :: makeDeposit1(double d1)
{
    Checking c;
    int f = 0;
    fstream file1;
    file1.open("Checking Accounts.dat", ios::binary | ios:: in | ios::out);
    file1.seekg(0);

    if (!file1) {
        cout << "Sorry! Error in Opening the Records!!" << endl;
    }

    else{
        getAccNo();
        while(file1.read((char*)&c,sizeof(c))) {
            if (c.accNo == z) {
                cout << "ACCOUNT INFO" << endl;
                c.display();
                f = 1;
                c.display();
                file1.seekp(-sizeof(c), ios::cur);
                c.Account::makeDeposit(d1);
                cout << "UPDATED INFO" << endl;
                cout << "New Balance: " << c.getBalance();
                file1.write((char*)&c,sizeof(c));
            }
        }
    }

    if(f==0){
        cout << "Sorry, Account Not Found!!" << endl;
    }

    file1.close();
}

/*************************************************************************
//THIS FUNCTION CALCULATES END OF THE MONTH BLANACEN OF CHECKING ACCOUNT *
//*************************************************************************/
void Checking :: monthlyProc1()
{
    Checking c;

    ofstream tempFile("temp.dat", ios::out | ios::binary);
    ifstream file1("Checking Accounts.dat", ios::binary);
    file1.seekg(0);

    if (!file1) {
        cout << "Sorry! Error in Opening the Records!!" << endl;
    }

    else{
        while(file1.read((char*)&c,sizeof(c))) {
            c.monthlyCharge = 5 + (0.10 * c.no_of_withdraws);
            c.Account::monthlyProc();
            tempFile.write((char*)&c,sizeof(c));
        }
    }

    file1.close();
    tempFile.close();
    remove("Checking Accounts.dat");
    rename("temp.dat", "Checking Accounts.dat");

}
/*************************************************************************
//THIS FUNCTION CREATES THE ACCOUNT FOR CHECKING CATEGORY *
//*************************************************************************/
void Checking :: createAccount1()
{
    fstream create("Checking Accounts.dat", ios::app | ios::binary);
    Checking c;

    cout << "Please Enter Your Checking Account Details" << endl << endl;

    cout << "Account Number (Given by the Bank): ";
    cin >> c.accNo;

    cout << "Name: ";
    cin.ignore();
    cin.getline(c.name, 40);

    cout << "Starting balance: ";
    cin >> c.balance;

    cout << "Annual Interest Rate: ";
    cin >> c.yearlyInterestRate;

    c.no_of_deposits = c.getDeposits();
    c.no_of_withdraws = c.getWithdrawals();

    if (c.balance > 0) {
        create.write((char*)&c,sizeof(c));
    }

    else {
        cout << "Sorry! Balance cannot be Negative!!" << endl;
    }

    create.close();
}
/*************************************************************************
//THIS FUNCTION DISPLAYS DETAILS OF CHECKING ACCOUNT *
//*************************************************************************/
void Checking :: readDetails1()
{
    ifstream file1;
    Checking c;
    file1.open("Checking Accounts.dat",ios::in);

    getAccNo();
    if (!file1) {
        cout << "Sorry! Error in Opening the Records!!" << endl;
    }

    else {
        do {
            if (z == c.accNo) {
                c.display();
                c.statusCheck();
                cout << endl << endl << "Status: " << c.status;
                z = 0;
            }
        } while(file1.read((char*)&c,sizeof(c)));

        if (z!=0) {
            cout << "Sorry!! This Account Number Does Not Exist!!" << endl;
        }
    }
    file1.close();
}



/*************************************************************************
//THIS FUNCTION DISPLAYS DETAILS OF ALL THE ACCOUNTS *
//*************************************************************************/
void Checking :: readAllDetails1()
{
    ifstream file1("Checking Accounts.dat", ios::in|ios::binary);
    Checking c;

    if (!file1) {
        cout << "Sorry! Error in Opening the Records!!" << endl;
    }

    else {
        while(file1.read((char*)&c,sizeof(c))){
            c.display();
        }
    }
    file1.close();
}
/*************************************************************************
//THIS FUNCTION DELETES THE PARTICULAR CHECKING ACCOUNT *
//*************************************************************************/
void Checking :: deleteAccount1()
{
    Checking c;

    ofstream tempFile("temp.dat", ios::app | ios::binary);
    ifstream file1("Checking Accounts.dat", ios::binary);

    getAccNo();

    if (!file1 || !tempFile) {
        cout << "Sorry! Error in Opening the Records!!" << endl;
    }

    else{
        while(file1.read((char*)&c,sizeof(c))) {
            if (z != c.accNo) {
                tempFile.write((char*)&c,sizeof(c));
            }
        }
    }

    cout << "Account Successfully Deleted!!" << endl;

    file1.close();
    tempFile.close();
    remove("Checking Accounts.dat");
    rename("temp.dat", "Checking Accounts.dat");
}
/*************************************************************************
//THIS FUNCTION UPDATES THE PARTICULAR CHECKING ACCOUNT *
//*************************************************************************/
void Checking :: updateDetails1()
{
    int f=0;
    Checking c;

    fstream file1;
    file1.open("Checking Accounts.dat", ios::binary | ios:: in | ios::out);
    file1.seekg(0);

    if (!file1) {
        cout << "Sorry! Error in Opening the Records!!" << endl;
    }

    else{
        cout << "UPDATE YOUR CHECKING ACCOUNT" << endl;
        getAccNo();
        while(file1.read((char*)&c,sizeof(c))) {
            if (c.accNo == z) {
                cout << "ACCOUNT INFO" << endl;
                c.display();
                cout << endl << "ENTER NEW INFORMATION" << endl;
                f = 1;

                cout << "Account Number (Given by the Bank): ";
                cin >> c.accNo;

                cout << "Name: ";
                cin.ignore();
                cin.getline(c.name, 40);

                c.no_of_deposits = c.getDeposits();
                c.no_of_withdraws = c.getWithdrawals();

                cout << "Starting balance: ";
                cin >> c.balance;

                cout << "Annual Interest Rate: ";
                cin >> c.yearlyInterestRate;

                if (c.balance > 0) {
                    file1.seekp(-sizeof(c), ios::cur);
                    file1.write((char*)&c,sizeof(c));
                    cout << "Account Successfully Updated!!" << endl;
                }

                else {
                    cout << "Sorry Insufficient balance!!" << endl;
                }
            }
        }
    }

    if(f==0){
        cout << "Sorry, Account Not Found!!" << endl;
    }

    file1.close();
}


/*************************************************************************
//THIS FUNCTION IS USED TO LOGIN INTO THE DASHBOARD TO MAKE IT MORE SECURE *
//*************************************************************************/
void Login(){
    int k = 0;
    const char BACKSPACE = 8;
    const char ENTER = 13;
    char password[10] = "admin",Username[10]="admin",US[10],ch,c,pass[10];
    int i = 0 , j = 0;
    bool iscorrect = 0;
    re_enter_1:
    while((iscorrect == false && (j<3))){
        cout<<"\nEnter Username : ";
        cin>>US;
        if(strcmp(Username,US)== 0){
            re_enter:
            while ((c=getchar())!= EOF){
                i = 0;
                cout<<"\nEnter the password : ";iscorrect= true;
                do{
                    ch=getch();
                    pass[i]=ch;
                    if (ch!= ENTER && ch!=BACKSPACE){
                        cout<<"*";
                    }
                    else{
                        pass[i]= '\0';
                    }
                    i++;
                    } while (ch != ENTER);
                    if (strcmp(password,pass)==0){
                        cout<<"\n\nLogin Successful";
                        cout<<"\nPress Enter to continue...";
                        cin.get();
                        break;
                    }
                    else{
                        cout<<"\nUnauthorized Access";
                        goto re_enter;
                        }
            }
        }
        else{
            cout<<"Wrong Password or Username\n";
            j++;
            goto re_enter_1;
        }
    }
}

//DASHBOARD NAI DASHBOARD KO WORLD

void subdashboard(); //DECLARING SUBDASBOARD

/*************************************************************************
//THIS DASHBOARD IS USED TO PERFROM DIFFERENT ACTIVITIES *
//*************************************************************************/

void dashboard()
{
    system("CLS");
    cout<<"\n\t\t\t-------------------------------------------"<<endl;
    cout<<"\t\t\t        Welcome to Bank ABDSS        "<<endl;
    cout<<"\t\t\t---------------------------------------------"<<endl<<endl;
    cout << "1. Create an account" << endl;
    cout << "2. Deposit money on existing account" << endl;
    cout << "3. Withdraw money on existing account" << endl;
    cout << "4. Display an account" << endl;
    cout << "5. Update an account" << endl;
    cout << "6. Close an account" << endl;
    cout << "7. Display all accounts" << endl;
    cout << "8. End of the month" << endl;
    cout << "9. Exit" << endl << endl<<endl;

    cout << "Make your choice(1-9): ";
    cin >> choice;

    cout << endl;

    if (choice < 1 || choice > 9) {
        cout << "Wrong Number. Please enter between 1 and 9: ";
    }
    else if(choice==7){
        SavingAccounts s;
        Checking c;
        cout << "CHECKING ACCOUNTS" << endl;
        c.readAllDetails1();
        cout << endl << endl;
        cout << "SAVINGS ACCOUNTS" << endl;
        s.readAllDetails();
    }

    else if(choice==8){
        SavingAccounts s;
        Checking c;
        c.monthlyProc1();
        s.monthlyProc();
    }

    else if(choice == 9) {
        exit(0);
    }

    else {
        subdashboard();
    }
}
/*************************************************************************
//THIS SUBDASHBOARD FUNCTION IS USED TO CHOOSE THE ACCOUNT TYPE*
//*************************************************************************/
void subdashboard()
{
    char answer = 'Y';
    int type;

    do {
        system("CLS");
        cout<<"\n\t\t\t-------------------------------------------"<<endl;
        cout<<"\t\t\t        Choose the account type        "<<endl;
        cout<<"\t\t\t---------------------------------------------"<<endl;
        cout << "1. Saving Account" << endl;
        cout << "2. Checking Account" << endl;
        cout << "3. Go back to dashboard."<<endl;

        cout << "\nPlease choose one of the options above : ";
        cin >> type;
        cout << endl << endl;

        switch(type)
        {
        case 1:
            {   system("CLS");
                SavingAccounts s;

                if(choice == 1){
                    s.createAccount();
                    cout<<"\nPress Enter to continue...";
                    cin.get();
                    subdashboard();
                }

                if(choice == 2){
                    double k;
                    cout << "Enter balance to be deposited: ";
                    cin >> k;
                    s.makeDeposit(k);
                    cout<<"\nPress Enter to continue...";
                    cin.get();
                    subdashboard();
                }

                if(choice == 3){
                    double l;
                    cout << "Enter balance to be withdrawan: ";
                    cin >> l;
                    s.makeWithdrawal(l);
                    cout<<"\nPress Enter to continue...";
                    cin.get();
                    subdashboard();
                }

                if(choice == 4){
                    s.readDetails();
                    cout<<"\nPress Enter to continue...";
                    cin.get();
                    subdashboard();
                }

                if(choice == 5){
                    s.updateDetails();
                    cout<<"\nPress Enter to continue...";
                    cin.get();
                    subdashboard();
                }

                if(choice == 6){
                    s.deleteAccount();
                    cout<<"\nPress Enter to continue...";
                    cin.get();
                    subdashboard();
                }
            }

                break;

        case 2:
            {
                Checking c;

                if(choice == 1){
                    system("CLS");
                    c.createAccount1();
                    cout<<"\nPress Enter to continue...";
                    cin.get();
                    subdashboard();
                }

                if(choice == 2){
                    double k;
                    cout << "Enter balance to be deposited: ";
                    cin >> k;
                    c.makeDeposit1(k);
                    cout<<"\nPress Enter to continue...";
                    cin.get();
                    subdashboard();
                }

                if(choice == 3){
                    double l;
                    cout << "Enter balance to be withdrawan: ";
                    cin >> l;
                    c.makeWithdrawal1(l);
                    cout<<"\nPress Enter to continue...";
                    cin.get();
                    subdashboard();
                }

                if(choice == 4){
                    c.readDetails1();
                    cout<<"\nPress Enter to continue...";
                    cin.get();
                    subdashboard();
                }

                if(choice == 5){
                    c.updateDetails1();
                    cout<<"\nPress Enter to continue...";
                    cin.get();
                    subdashboard();
                }

                if(choice == 6){
                    c.deleteAccount1();
                    cout<<"\nPress Enter to continue...";
                    cin.get();
                    subdashboard();
                }

                break;
            }
        case 3:
            {
            dashboard();
            }
            break;
        default:
        {
            cout << "Invalid Choice! Do you want to try again? (Y/N): ";
            cin >> answer;
            break;
        }
        }

    } while (answer == 'Y');
    

    system("PAUSE");
    dashboard();
    
};

/*************************************************************************
//********************** MAIN FUNCTION ***********************************
//*************************************************************************/
int main()
{
    Login(); //CALLS THE FUNCTION LOGIN
    dashboard(); //CALLS THE FUNCTION DASHBOARD
    return 0;
}