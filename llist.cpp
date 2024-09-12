/*****************************************************************
//
//  NAME:       Ralph Ramos
//
//  HOMEWORK:    Project 2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        April 10, 2024
//   
//  FILE:        llist.cpp
//
//  DESCRIPTION:  function definitions for database of the llist
//
//  REFERENCES: Cplusplus.com
//
// 
****************************************************************/

#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <ostream>
#include "llist.h"

using namespace std;

/*****************************************************************
//  
//  Function Name: llist
//
//  DESCRIPTION: The constructor of the llist
//
//  Parameters: None
//
//  Return Values: None
//
******************************************************************/

llist::llist()
{
#ifdef DEBUGMODE
    cout << "/****DEBUG: Entered llist constructor" << endl;
#endif
    start = NULL;
    strncpy(filename, "placeholderName", 25);
    readfile();
}

/****************************************************************
//  
//  Function Name: llist
//
//  DESCRIPTION: The constructor of the llist
//
//  Parameters:  filename (char[]): The file name to read and write to
//
//  Return Values: None
//
*****************************************************************/  

llist::llist(char filename[])
{
#ifdef DEBUGMODE
    cout << "/****DEBUG: Entered llist constructor\n";
    cout << "/****DEBUG: filename: " << filename << endl;
#endif
    start = NULL;
    strncpy(this -> filename, filename, 25);
    readfile();
}

/***************************************************************
//
//  Function name: ~llist
//
//  DESCRIPTION:   The destructor of the llist
//
//  Parameters:   None
//
//  Return values: None
//
****************************************************************/

llist::~llist()
{
#ifdef DEBUGMODE
    cout << "/****DEBUG: llist destructor called" << endl;
#endif
    writefile();
    cleanup();
}

/*************************************************************
//  
//  Function name: readfile
//
//  DESCRIPTION:  reads from the file and parsesdata to program 
//                database
//  
//  Parameters:   none
//  
//  Return Values: 0: successfully read from the file
//                 -1: unuccessful reading from file
//
**************************************************************/   

int llist::readfile()
{
#ifdef DEBUGMODE
    cout << "/****DEBUG: readfile called" << endl;
#endif
    int accountno;
    int endRead, valid;
    char name[25];
    char address[45];
    endRead = 0;
    valid = 0;

    ifstream file(filename, ifstream::in);

    if (file.good())
    {
        endRead = 0;
        while (endRead != 1)
        {
            file.get();
            if (file.good())
            {
                file.ignore();
                file.ignore(20, '\n');
                file >> accountno;
                file.get();
                file.getline(name, 25, '\n');
                file.getline(address, 45, '/');
                addRecord(accountno, name, address);
            }
            else
            {
                endRead = 1;
            }
        }
    }
    else
    {
        valid = -1;
    }
    return valid;
}

/***************************************************************
//
//  Function Name: writefile
//
//  DESCRIPTION:  writes the database and stores it into a file
//
//  Parameters: none
//
//  Return values: 0: successfully wrote to file
//                 -1: unsuccessful writing to file
//
***************************************************************/

int llist::writefile()
{
#ifdef DEBUGMODE
    cout << "/****DEBUG: writefile called" << endl;
#endif

    struct record *current;
    int valid;
    valid = 0;

    current = start;
    ofstream file(filename, ofstream::out);

    if (!file.is_open())
    {
        cout << "Error: Can't Open file\n";
        valid = -1;
    }
    if (start == NULL)
    {
        cout <<"No Records to write\n";
    }
    else
    {
        while (current != NULL)
        {
            file << "\n";
            file << "/****************\n";
            file << current->accountno << endl;
            file << current->name << endl;
            file << current-> address << "/";
            current = current->next;
        }
    }

    if (file.fail())
    {
        cout << "Failed to write to file" << endl;
        valid = -1;
    }

    file.close();
    return valid;
}

/************************************************************
//
//  Function Name: cleanup
//
//  DESCRIPTION: Clears the memory by deallocating all records in
//               the llist
//
//  Parameters:  none
//
//  Return Values: none
//
*************************************************************/

void llist::cleanup()
{
#ifdef DEBUGMODE
    cout << "/****DEBUG: cleanup called" << endl;
#endif
    struct record * current;
    struct record * delRec;
    current = start;

    while (current != NULL)
    {
        delRec = current;
        current = current->next;
        delete delRec;
    }
    start = NULL;
}

/*************************************************************
//
//  Function Name: addRecord
//
//  DESCRIPTION: Add a new record in the database
//
//  Parameters:  uaccountno (int): account number input
//               name (char[]):    name input
//               address (char[]): address input
//
//  Return Values: 0: success
//                 -1: the value was not found
//
**************************************************************/

int llist::addRecord(int uaccountno, char uname[], char uaddress[])
{
    struct record *newRec, *current, *previous;
    int result, dupeFound, positionFound;

    result = 0;
    dupeFound = 0;
    positionFound = 0;

#ifdef DEBUGMODE
    cout << "DEBUG: addRecord() called. Record added." << endl;
    cout << "DEBUG: Account Number: " << uaccountno << endl;
    cout << "DEBUG: Name: " << uname << endl;
    cout << "DEBUG: Address: " << uaddress << endl;
#endif

    if (start == NULL)
    {
        newRec = new struct record();
        start = newRec;
        newRec->accountno = uaccountno;
        strncpy(newRec->name, uname, 25);
        strncpy(newRec->address, uaddress, 45);
        newRec->next = NULL;
    }
    else
    {
        current = start;

        if (uaccountno == start->accountno)
        {
            dupeFound = 1;
            result = -1;
        }
        else if (uaccountno < start->accountno)
        {
            newRec = new struct record();
            newRec->accountno = uaccountno;
            strncpy(newRec->name, uname, 25);
            strncpy(newRec->address, uaddress, 45);
            newRec->next = start;
            start = newRec;
        }
        else if (uaccountno > start->accountno)
        {
            while ((current != NULL) && (dupeFound == 0))
            {
                if (current->accountno == uaccountno)
                {
                    dupeFound = 1;
                    result = -1;
                }
                else
                {
                    current = current->next;
                }
            }
            if (dupeFound == 0)
            {
                current = start;
                previous = NULL;
                while ((current != NULL) && (positionFound == 0))
                {
                    if (uaccountno < current->accountno)
                    {
                        newRec = new struct record();
                        newRec->accountno = uaccountno;
                        strncpy(newRec->name, uname, 25);
                        strncpy(newRec->address, uaddress, 45);
                        newRec->next = current;
                        if (previous != NULL)
                        {
                            previous->next = newRec;
                        }
                        else
                        {
                            start = newRec;
                        }
                        positionFound = 1;
                    }
                    else
                    {
                        previous = current;
                        current = current->next;
                    }
                }
                if (positionFound == 0)
                {
                    newRec = new struct record();
                    newRec->accountno = uaccountno;
                    strncpy(newRec->name, uname, 25);
                    strncpy(newRec->address, uaddress, 45);
                    newRec->next = NULL;
                    previous->next = newRec;
                }
            }
        }
    }
    return result;
}

/*********************************************************************
//
//  Function Name: findRecord
//
//  DESCRIPTION:   finds the record information
//
//  Parameters: uaccountno(int): account number input
//
//  Return Values:  0: success
//                  -1: the account / record was not found
//
*********************************************************************/                 

int llist::findRecord(int uaccountno)
{
#ifdef DEBUGMODE
    cout << "/****DEBUG: findRecord called" << endl;
    cout << "/****DEBUG: finding accountno: " << uaccountno << endl;
#endif
    struct record * current;
    int result, found;
    result = -1;
    found = 0;
    current = start;

    if (start == NULL)
    {
        cout << "There are 0 records in the database, record not found\n";
    }
    else
    {
        while ( (current != NULL) && (found == 0) )
        {
            if (current->accountno == uaccountno)
            {
                found = 1;
            }
            else
            {
                current = current->next;
            }
        }
        if (found != 0)
        {
            cout << "Record With Account Number: " << uaccountno << " Found\n";
            cout << "Accountno: " << current->accountno << "\n";
            cout << "Name: " << current->name << " \n";
            cout << "Address: \n" << current->address << " \n";
            result = 0;
        }
        else
        {
            cout << "Record With Account Number: " << uaccountno <<  " Not Found\n";
            result = -1;
        }
    }
    return result;
}

/***********************************************************************
//  
//  Function Name: printAllRecords
//
//  DESCRIPTION: prints all records
//
//  Parameters: none
//
//  Return values: none
//
************************************************************************/

void llist::printAllRecords()
{
#ifdef DEBUGMODE
    cout << "/****DEBUG: printAllRecords called" << endl;
#endif

    struct record *current;
    current = start;

    if (start == NULL)
    {
        cout << "There are 0 records in the database.\n";
    }
    else
    {
        while (current !=NULL)
        {
            cout << "***************" << endl;
            cout << "Accountno: " << current->accountno << endl;
            cout << "Name: " << current->name << endl;
            cout << "Address:\n\n" << current->address << endl;
            current = current->next;
        }
    }
}

/**********************************************************************
//
//  Function Name: deleteRecord
//
//  DESCRIPTION: deletes the record 
//  
//  Parameters: uaccountno (int): account number input for deletion
//
//  Return Values: 0: success
//                 -1: unable to delete, record not found
//                 
**********************************************************************/

int llist::deleteRecord(int uaccountno)
{
#ifdef DEBUGMODE
    cout << "/****DEBUG: deleteRecord called" << endl;
    cout << "/****DEBUG: delete accountno: " << uaccountno << endl;
#endif

    struct record * tempCurrent;
    struct record * tempNext;
    struct record * newNext;
    struct record * delRec;
    int result, currAccNo, delRecFound, nextAccNo;

    result = -1;
    delRecFound = 0;

    if (start != NULL)
    {
        tempCurrent = start;
        currAccNo = tempCurrent->accountno;
        if ( ((start)->next == NULL) && (currAccNo == uaccountno))
        {
            start = tempCurrent->next;
            delete(tempCurrent);
            result = 0;
            delRecFound = 1;
        }
        else
        {
            if (currAccNo == uaccountno)
            {
                tempNext = tempCurrent->next;
                start = tempNext;
                delete(tempCurrent);
                delRecFound = 1;
                result = 0;
            }
            while ( (currAccNo < uaccountno) && (delRecFound == 0) )
            {
                tempNext = tempCurrent->next;
                nextAccNo = tempNext->accountno;
                if ( tempNext->next == NULL )
                {
                    if ( nextAccNo == uaccountno )
                    {
                        tempCurrent->next = NULL;
                        delRec = tempNext;
                        delete(delRec);
                        delRecFound = 1;
                        result = 0;
                    }
                    else
                    {
                        cout << "Failed to delete, accountno: " << uaccountno << endl;
                        cout << " does not exist" << endl;
                        delRecFound = -1;
                    }
                 }
                else
                {
                    if ( nextAccNo == uaccountno )
                    {
                        delRec = tempNext;
                        newNext = delRec->next;
                        tempCurrent->next = newNext;
                        delete(delRec);
                        delRecFound = 1;
                        result = 0;
                    }
                    else
                    {
                        tempCurrent = tempNext;
                        currAccNo = tempCurrent->accountno;
                    }
                }
            }
        }
    }
    return result;
}
