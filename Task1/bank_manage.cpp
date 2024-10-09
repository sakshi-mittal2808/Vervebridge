#include<iostream>
#include<vector>
#include<iomanip> // for setprecision and fixed value
using namespace std;

// Structure to store information of the account
typedef struct Account
{
    int accNum;
    string accHolderName;
    string password;
    float balance;
    vector<string>THistory;
} acc;

// USER AUTHENTICATION MENU
void showMenu()
{
    cout<<"\n******WELCOME TO BANK MANAGEMENT SYSTEM******\n";
    cout<<"1. Create Account\n";
    cout<<"2. LogIn\n";\
    cout<<"3. Exit\n";
}

// MENU FUNCTION
void showBankMenu()
{
    cout<<"\n******BANK MENU******\n";
    cout<<"1. Deposit Money\n";
    cout<<"2. Withdraw Money\n";
    cout<<"3. Balance Inquiry\n";
    cout<<"4. Account Statement\n";
    cout<<"5. Transfer Money\n";
    cout<<"6. LogOut\n";
}

// FINDING ACCOUNT
int findAcc(vector<acc>& account, int accNum)
{
    for(int i = 0; i < account.size(); i++)
        if(account[i].accNum == accNum)
            return i;

    return -1;  //if acc not found, return -1
}

// Changing password
void changePass(char c, vector<acc>& account, int accNum)
{
    string pass;
    cout<<"Enter password: ";
    cin.ignore( ); //ignoring blankilne (\n)
    getline(cin,pass);

    int index=findAcc(account,accNum); // finding index
    account[index].password=pass;

    cout<<"Password Changed Successfully...!!!"<<endl;
}

//AUTHENTICATION
bool authenticate(vector<acc>& account, int accNum)
{
    string password;
    int index=findAcc(account,accNum); //finding index
    if(index==-1)
    {
        cout<<"Account not found...!!!\n";
        return 0;
    }

    cout<<"Enter password: "; //scanning password
    cin.ignore( );
    getline(cin,password);

    if(account[index].password==password)
    {
        cout<<"\nLogIn Successfully...!!!\n";
        return 1;
    }
    else
    {
        char choice;
        cout<<"\nIncorrect password...!!!\n";
        cout<<"Forget Password...???"<<endl<<"Want to change it...??"<<endl<<"Enter 'y' or 'n': ";
        cin>>choice;
        switch(choice)
        {
            case 'y': changePass(choice,account,accNum);
                    return 0;
            case 'n': return 0;
        }
    }
}

// Account creation
void createAcc(vector<acc>& account)
{
    acc newAcc;
    if(account.size() == 0)
        newAcc.accNum = 11111111; // first account number
    else
    {
        int last = account[account.size() - 1].accNum;
        newAcc.accNum = last + 1; // new account number one more than the last
    }

    cout<<"Enter Account Holder Name: ";
    cin.ignore();
    getline(cin, newAcc.accHolderName);  // inputting string

    cout<<"Enter password: ";
    getline(cin,newAcc.password);

    newAcc.balance = 0.0; //by default, balance is 0
    newAcc.THistory.push_back("Account with Account number created with balance 0.0 Rupee");

    // pushing structure into vector
    account.push_back(newAcc);
    cout<<endl<<"******Account created successfully*****"<<endl;
    cout<<"Your account number is: "<<newAcc.accNum<<endl;
}

// Deposit money
void deposit(vector<acc>& account, int accNum)
{
    float amount;
    
    // find if the account exists
    int index = findAcc(account, accNum);
    if(index != -1)
    {
        cout<<"Enter amount you want to deposit: ";
        cin>>amount;

        //checking weather the inout is less than or equal to 0
        if(amount<=0)
            cout<<"Enter valid amount to deposit\n";
        else
        {
            account[index].balance += amount;
            account[index].THistory.push_back("Amount Deposited: "+to_string(amount)+" Rupees");
            cout<<endl<<"Amount deposited successfully...!!"<<endl;
        }
    }
    else cout<<endl<<"Account Not found...!!"<<endl<<"Create New Account to Deposit Money"<<endl;
}

// Withdraw amount
void withdraw(vector<acc>& account, int accNum)
{
    float amount;
    
    // find if the account exists
    int index = findAcc(account, accNum);
    if(index != -1)
    {
        cout<<"Enter amount you want to withdraw: ";
        cin>>amount;

        // checking if balance is sufficient
        if(account[index].balance >= amount)
        {
            account[index].balance -= amount;
            account[index].THistory.push_back("Amount Withdrawn: "+to_string(amount)+" Rupees");
            cout<<"Amount withdrawn successfully...!!"<<endl;
        }
        else
            cout<<"Insufficient Balance...!!!"<<endl;
    }
    else
        cout<<endl<<"Account Not found...!!"<<endl<<"Create New Account & Deposit Money"<<endl;
}

// Balance Inquiry
void inquiry(vector<acc>& account, int accNum)
{
    // find if the account exists
    int index = findAcc(account, accNum);
    if(index != -1)
    {
        cout<<"Account Number: "<<account[index].accNum<<endl;
        cout<<"Account Holder Name: "<<account[index].accHolderName<<endl;
        cout<<fixed<<setprecision(2)<<"Account Balance: "<<account[index].balance<<" Rupees"<<endl;
    }
    else
        cout<<endl<<"Account Not found...!!"<<endl;
}

// Account Statement
void statement(vector<acc>& account, int accNum)
{
    int index = findAcc(account, accNum);
    if(index != -1)
    {
        cout<<"Account Number: "<<account[index].accNum<<endl;
        cout<<"Account Holder Name: "<<account[index].accHolderName<<endl;
        cout<<fixed<<setprecision(2)<<"Account Balance: "<<account[index].balance<<" Rupees"<<endl;
        cout<<"Transaction History: \n";
        for(auto &t : account[index].THistory)
            cout<<" - "<<t<<endl;
    }
    else
        cout<<endl<<"Account Not found...!!"<<endl;
}

// Transfer money
void transferMoeny(vector<acc>& account, int senderAcc)
{
    int receiverAccNum;
    float amount; 
    cout<<"Enter receiver's account numbher: ";
    cin>>receiverAccNum;

    int senderIndex=findAcc(account,senderAcc);
    int receiverIndex=findAcc(account,receiverAccNum);

    if(senderIndex==-1)
    {
        cout<<"Sender Account not found...!!!\n";
        return;
    }
    if(receiverIndex==-1)
    {
        cout<<"Receiver Account not found...!!!\n";
        return;
    }

    cout<<"Enter amount to transfer: ";
    cin>>amount;

    if(amount<=0)   cout<<"Enter valid amount to deposit\n";
    if(account[senderIndex].balance>=amount)
    {
        account[senderIndex].balance-=amount;
        account[senderIndex].THistory.push_back("Transferred: "+to_string(amount)+" Rupees to Account "+to_string(receiverAccNum));

        account[receiverIndex].balance+=amount;
        account[receiverIndex].THistory.push_back("Received: "+to_string(amount)+" Rupees from Account "+to_string(senderAcc));

        cout<<"Transferred Successfully...!!!\n";
    }
    else cout<<"Insufficient Balance...!!!\n";
}

int main()
{
    vector<acc> account; // List of accounts
    int choice,accNum;

    while(true)
    {
        showMenu();
        cout<<"Enter your choice: ";
        cin>>choice;

        switch(choice)
        {
            case 1: createAcc(account);
                    break;
            case 2: cout<<"Enter account number: ";
                    cin>>accNum;
                    if(authenticate(account,accNum))
                    {
                        int bankChoice;
                        while(true)
                        {
                            showBankMenu();
                            cout<<"Enter your choice: ";
                            cin>>bankChoice;

                            switch (bankChoice)
                            {
                                case 1: deposit(account,accNum);
                                        break;
                                case 2: withdraw(account,accNum);
                                        break;
                                case 3: inquiry(account,accNum);
                                        break;
                                case 4: statement(account,accNum);
                                        break;
                                case 5: transferMoeny(account,accNum);
                                        break;
                                case 6: cout<<"Logging out...!!!\n";
                                        goto END;
                                default: cout<<"Invalid Choice...!! Please try again\n";
                            }
                        }
                    }
                    END: break;
            case 3: cout<<"Exiting program\n";
                    return 0;
            default: cout<<"Invalid Choice...!! Please try again\n";
        }
    }
}
