/*************************************************
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
//  FILE: record.h
//
//  DESCRIPTION: The header file for a record.
//
//  REFERENCES: None.
//
 ************************************************/

#ifndef RECORD_H
#define RECORD_H

struct record
{
    int             accountno;
    char            name[25];
    char            address[45];
    struct record*  next;
};

#endif
