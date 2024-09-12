/***********************************************
//
//  NAME: Ralph Ramos
//
//  HOMEWORK: Project 2
//
//  CLASS: ICS212
//
//  INSTRUCTOR: Ravi Narayan
//
//  DATE: April 10, 2024
//
//  FILE: llist.h
//
//  DESCRIPTION: The header file for a llist
//
//  REFERENCES: None
//
***********************************************/

#ifndef LLIST_H
#define LLIST_H

#include <string>
#include "record.h"

using namespace std;

class llist
{
private:
    record *    start;
    char        filename[20];
    int         readfile();
    int         writefile();
    void        cleanup();
 public:
    llist();
    llist(char[]);
    ~llist();
    int addRecord(int, char[], char[]);
    int findRecord(int);
    void printAllRecords();
    int deleteRecord(int);
};

#endif
