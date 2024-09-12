/*****************************************************************
//
//  NAME:        Ralph Ramos
//
//  HOMEWORK:    Project 2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        April 10, 2024
//
//  FILE:        user_interface.cpp
//
//  DESCRIPTION: The user interface for the bank database.
//
****************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <cstdlib>
#include "llist.h"

using namespace std;

int cmdCompare(string, string);
int validNum();
void getAddress(char[], int);

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:    Asks the user for the commands to modify the
//                  database and performs the command.
//
//  Parameters:    argc (int) : The number of elements in argv
//                 argv (char*[]) : An array of arguments passed
//                                  to the program. 
//
//  Return values:  0 : program ended successfully 
//
****************************************************************/

int main(int argc, char* argv[])
{
    int quit;
    int accountno;
    string userInput;
    string name;
    string address;
    const int nameMaxLen = 25;
    const int addressMaxLen = 45;
    char nameConv[25];
    char addressConv[45];
    char database_file[] = "database.txt";
    llist database(database_file);
    int validCmd;
    quit = 0;
    validCmd = 0;

#ifdef DEBUGMODE
    cout << "/*****DEBUG MODE ON*****/" << endl;
#endif

    cout << "Welcome to the Bank Database program\n\n";
    cout << "This program lets you to manage customer bank information. \n\n";

    while (quit != 1 || validCmd != 1)
    {
        cout <<"\n\nCommands:\n\n";
        cout << "add: Add a new record in the database.\n";
        cout << "printall: Print all records in the database.\n";
        cout << "find: Find record(s) with a specified account #.\n";
        cout << "delete: Delete existing record(s) from the database using the\n";
        cout << "account # as a key.\n";
        cout << "quit: Quit the program.\n\n";
        cout << "Enter your command: " << endl;

        getline(cin, userInput);
        cin.clear();

        if (cmdCompare(userInput, "add") == 1)
        {
            cout << "You are now using add command\n";
            validCmd = 1;
            accountno = validNum();
            cout << "Enter name:\n";
            getline(cin, name);
            strncpy(nameConv, name.c_str(), nameMaxLen);
            getAddress(addressConv, addressMaxLen);
            cout <<"\nAdding account: " << accountno << " to database\n";
            database.addRecord(accountno, nameConv, addressConv);
        }
        else if (cmdCompare(userInput, "printall") == 1)
        {
            validCmd = 1;
            cout <<"\nPrinting All Records\n\n";
            database.printAllRecords();
            validCmd = 0;
        }
        else if (cmdCompare(userInput, "find") == 1)
        {
            validCmd = 1;
            accountno = validNum();
            cout <<"\nFinding Record "<< accountno << " \n\n";
            database.findRecord(accountno);
            validCmd = 0;
        }
        else if (cmdCompare(userInput, "delete") == 1)
        {
            validCmd = 1;
            accountno = validNum();
            cout << "\nDeleting record with accountno: " << accountno << "\n\n";
            database.deleteRecord(accountno);
            validCmd = 0;
        }
        else if (cmdCompare(userInput, "quit") == 1)
        {
            cout << "Saving database to " << database_file << "\n";
            cout <<"Quitting program \n";
            validCmd = 1;
            quit = 1;
        }
        else
        {
            cout <<"Invalid Input\n";
        }
    }
    return 0;
}

/*****************************************************************
//
//  Function name:  cmdCompare 
//
//  DESCRIPTION:    Compares the input string to the command string.
//                  It checks for invalid inputs by iterating through each character.
//                  It first checks the value of the string compare then handles other
//                  special cases like white spaces
//
//  Parameters:     userInput (char []) : The string to store the the user's 
//                  input.
//                  cmd (char []): the command option to compare user input 
//
//  Return values:  1 : the user input is equal to the command
//                  0 : the user input is not equal to the command
//
****************************************************************/

int cmdCompare(string userInput, string cmd)
{
    int ifValid;
    ifValid = 0;

    const char* convertUI = userInput.c_str();
    const char* convertCMD = cmd.c_str();

    if (userInput.length() > cmd.length())
    {
        ifValid = 0;
    }
    else if (strncmp(convertUI, convertCMD, userInput.length())== 0)
    {
        ifValid = 1;
    }
    return ifValid;
}

/*****************************************************************
//
//  Function name:  validNum
//
//  DESCRIPTION:   Asks the user to enter a postive integer and makes
//                 sure that the input is valid. If not it asks again
//                 until it is valid.
//
//  Parameters:     none
//
//  Return values:  A valid positive integer from the user.
//
****************************************************************/

int validNum()
{
    int numInput;
    int valid;
    valid = 0;
    do
    {
        cout << "Enter a positive Integer:\n";
        cin >> numInput;

        if (cin.fail())
        {
            cout << "Erorr: User input Invalid, input must be an Integer\n";
            cin.clear();
            cin.ignore(100, '\n');
            valid = 0;
        }
        else if (numInput < 0)
        {
            cout << "Error: User input must Be Positive\n";
            valid = 0;
        }
        else
        {
            valid = 1;
        }
    }
    while (valid != 1);
    cin.clear();
    cin.ignore(100, '\n');

    return numInput;
}

/*****************************************************************
//
//  Function name:  getAddress 
//
//  DESCRIPTION:    gets an address from the user input.Reads every character 
//                  until the '/' and finishes once user hits  directly "enter"
//
//  Parameters:     str (char []) : The string to store the address in
//                  size (int): The maximum size of the string
//
//  Return values:  none 
//
****************************************************************/

void getAddress(char str[], int size)
{
    cout << "Enter Address and type '/' followed by enter to finish \n";
    cin.getline(str, size, '/');
    cin.ignore(100, '\n');
}
