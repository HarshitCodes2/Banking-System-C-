#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int counter = 0;    // keeps count of how many accounts have been created
int removedAcc = 0; // keeps count of number of accounts removed
int sizeV = 0;
int sizeRv = 0;
int noAcc = 0; // stores number of account created
class account; // declaration of class for account

vector<account> V;
vector<int> Rv;

void inputfailure()
{
    cin.clear();
    cin.ignore(512, '\n');
    cout << endl
         << "Invalid Input" << endl
         << "Re-enter Input" << endl;
}

class account
{
private:
    string FirstName;
    string LastName;
    int AccNo;
    int Balance;

public:
    account()
    {
        FirstName = " ";
        LastName = " ";
        AccNo = counter + 1;
        Balance = 0;
        counter++;
    }

    void setFName(string f);
    void setLName(string l);
    void setAccNo(int a);
    void setBalance(int b);

    string getFName();
    string getLName();
    int getAccNo();
    int getBalance();

    void createAcc();
    void printInfo(account a);
    void printAll();

    friend ofstream &operator<<(ofstream &ofs, account &acc); // friend declaration for saving file
    friend ifstream &operator>>(ifstream &ifs, account &acc);
};

ofstream &operator<<(ofstream &ofs, account &acc)
{
    ofs << acc.FirstName << endl;
    ofs << acc.LastName << endl;
    ofs << acc.AccNo << endl;
    ofs << acc.Balance << endl;
    return ofs;
}

ifstream &operator>>(ifstream &ifs, account &acc)
{
    ifs >> acc.FirstName;
    ifs >> acc.LastName;
    ifs >> acc.AccNo;
    ifs >> acc.Balance;
    return ifs;
}

void account::setFName(string f)
{
    FirstName = f;
}
void account::setLName(string l)
{
    LastName = l;
}
void account::setAccNo(int a)
{
    AccNo = a;
}
void account::setBalance(int b)
{
    Balance = b;
}

string account::getFName()
{
    return FirstName;
}
string account::getLName()
{
    return LastName;
}
int account::getAccNo()
{
    return AccNo;
}
int account::getBalance()
{
    return Balance;
}

void account::printInfo(account a)
{
    cout << endl;
    cout << "First Name     " << a.getFName() << endl;
    cout << "Last Name      " << a.getLName() << endl;
    cout << "Account Number " << a.getAccNo() << endl;
    cout << "Balance        " << a.getBalance() << endl;
    cout << endl;
}

void account::printAll()
{
    vector<account>::iterator itr;
    for (itr = V.begin(); itr != V.end(); itr++)
    {
        itr->printInfo(*itr);
    }
}

void account::createAcc()
{
    account newAcc;
    string Fname;
    string Lname;
    int balance;
    cout << "Enter First Name :";
    cin >> Fname;
    cout << "Enter Last Name :";
    cin >> Lname;
balanceinput:
{
    cout << "Enter Balance :";
    cin >> balance;
}
    if (cin.fail())
    {
        inputfailure();
        goto balanceinput;
    }

    newAcc.setFName(Fname);
    newAcc.setLName(Lname);
    newAcc.setBalance(balance);

    V.push_back(newAcc);

    newAcc.printInfo(newAcc);
    sizeV++;
}

int main()
{

    string newFname;
    string newLname;

    int Selector = 0, balanceEnquiry = 0, balanceAccW = 0, remove = 0, WithdrawAmt = 0, balanceAccD = 0, DepositAmt = 0;

    ifstream infile("Banking_system.txt");
    {
        infile >> noAcc;
        infile >> sizeV;
        infile >> sizeRv;

        V.resize(sizeV);
        Rv.resize(sizeRv);

        vector<account>::iterator itr;
        for (itr = V.begin(); itr != V.end(); itr++)
        {
            infile >> *itr;
        }

        vector<int>::iterator itr2;
        for (itr2 = Rv.begin(); itr2 != Rv.end(); itr2++)
        {
            infile >> *itr2;
        }
        infile.close();
        counter = noAcc;
    }

    int deletework = sizeRv;
    Rv.push_back(INT32_MAX);
    do
    {
    //#########################################>>>>>>>>>>>>>MENU<<<<<<<<<<<<<#################################################//////
    beginning:
        cout << endl;
        cout << "Welcome To The Bank Of J.H.A.S.P.R." << endl
             << endl;
        cout << "1   Open A New Account." << endl;
        cout << "2   Balance Enquiry." << endl;
        cout << "3   Withdraw Money from an Account." << endl;
        cout << "4   Deposit Money to an Account." << endl;
        cout << "5   Close an Account." << endl;
        cout << "6   Show All Account." << endl;
        cout << "7   Exit Application." << endl;
        cout << "Please Select From the Options Above" << endl;
        cin >> Selector;
        //#######################################>>>>>>>>>>>>>MENU-CLOSE<<<<<<<<<<<<<###############################################//////

        if (Selector == 1)
        {
            account *newAcc;
            newAcc->createAcc();
            goto endofwhile;
        }

        if (Selector == 2)
        {
            vector<account>::iterator enq;
            {
            balEnq:
            {
                cout << "Enter Account Number:";
                cin >> balanceEnquiry;
            }
                if (cin.fail())
                {
                    inputfailure();
                    goto balEnq;
                }
                for (enq = V.begin(); enq != V.end() + 1; enq++)
                {
                    int temp = enq->getAccNo();
                    if (temp == balanceEnquiry)
                    {
                        cout << "The balance is :" << enq->getBalance();
                        goto doneenq;
                    }
                }

                cout << "Invalid Account Number" << endl;
            doneenq:
                goto endofwhile;
            }
        }

        if (Selector == 3)
        {
            vector<account>::iterator wit;
            {
                int newBal = 0;
            balwitacc:
            {
                cout << "Enter Account Number:";
                cin >> balanceAccW;
            }
                if (cin.fail())
                {
                    inputfailure();
                    goto balwitacc;
                }
            balwitamt:
            {
                cout << "Enter Ammount:";
                cin >> WithdrawAmt;
            }
                if (cin.fail())
                {
                    inputfailure();
                    goto balwitamt;
                }
                for (wit = V.begin(); wit != V.end() + 1; wit++)
                {
                    int temp = wit->getAccNo();
                    if (temp == balanceAccW)
                    {
                        int tempBal = wit->getBalance();
                        if (tempBal >= WithdrawAmt)
                        {
                            wit->setBalance(tempBal - WithdrawAmt);
                        }
                        else
                        {
                            cout << "Withdrawal amount is greater than Balance." << endl;
                        }
                        goto donewith;
                    }
                }
                cout << "Invalid Account Number" << endl;
            donewith:
                goto endofwhile;
            }
        }

        if (Selector == 4)
        {
            vector<account>::iterator dep;
            {
                int newBal = 0;
            baldepacc:
            {
                cout << "Enter Account Number:";
                cin >> balanceAccD;
            }
                if (cin.fail())
                {
                    inputfailure();
                    goto baldepacc;
                }
            baldepamt:
            {
                cout << "Enter Ammount:";
                cin >> DepositAmt;
            }
                if (cin.fail())
                {
                    inputfailure();
                    goto baldepamt;
                }
                for (dep = V.begin(); dep != V.end() + 1; dep++)
                {
                    int temp = dep->getAccNo();
                    if (temp == balanceAccD)
                    {
                        int tempBal = dep->getBalance();
                        dep->setBalance(tempBal + DepositAmt);
                        goto donedep;
                    }
                }
                cout << "Invalid Account Number" << endl;
            donedep:
                goto endofwhile;
            }
        }

        if (Selector == 5)
        {
        remacc:
        {
            cout << "Select Which Account :";
            cin >> remove;
        }
            if (cin.fail())
            {
                inputfailure();
                goto remacc;
            }
            removedAcc = remove;

            vector<account>::iterator del;
            {
                int deleted = 0;
                int delCount = 0;
                for (del = V.begin(); del != V.end() + 1; del++)
                {
                    int temp = del->getAccNo();
                    if (temp == remove)
                    {
                        V.erase(V.begin() + delCount);
                        deleted++;
                    }
                    else
                    {
                    }
                    delCount++;
                }
                if (deleted == 0)
                {
                    cout << "Invalid Account Number";
                    goto endofwhile;
                }
            }
            Rv.push_back(removedAcc);
            sizeRv++;
            sizeV--;
            goto endofwhile;
        }

        if (Selector == 6)
        {
            account *showAll;
            showAll->printAll();
            goto endofwhile;
        }

        if (Selector == 7)
        {
            cout << "Thanks for using our App." << endl;
            goto ending;
        }

        if (cin.fail())
        {
            inputfailure();
            goto beginning;
        }

        else
        {
            cout << "Invalid Input!!" << endl;
            goto ending;
        }

    endofwhile:
        cout << endl;
    } while (Selector < 8 && Selector > 0);

ending:
    noAcc = counter;

    ofstream outfile("Banking_system.txt", ios::trunc);
    {

        outfile << noAcc << endl;
        outfile << sizeV << endl;
        outfile << sizeRv << endl;

        {
            vector<account>::iterator itr;
            for (itr = V.begin(); itr != V.end(); itr++)
            {
                outfile << *itr;
            }
        }
        {
            vector<int>::iterator itr2;
            for (itr2 = Rv.begin(); itr2 != Rv.end(); itr2++)
            {
                outfile << *itr2 << endl;
            }
        }
    }
    outfile.close();
}
