/*****************************************************************
//
//  NAME:        Alessandra Gudoy
//
//  HOMEWORK:    Project 1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        March 22, 2024
//
//  FILE:        record.h
//
//  DESCRIPTION: Defines a struct record, consisting of an int
//               for the account number, two character arrays
//               for name and address, and a pointer to the next
//               address in the database.
//
****************************************************************/

struct record
{
    int                accountno;
    char               name [25];
    char               address [45];
    struct record *    next;
};
