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
//  FILE:        database.c
//
//  DESCRIPTION: Contains the function definitions for the using the
//               database, which are addRecord, printAllRecords,
//               findRecord, deleteRecord, writefile, readfile,
//               and cleanup.
//
****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "record.h"

extern int debug_mode;

int findRecord(struct record *, int);
int addRecord(struct record **, int, char [], char []);

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   This is adds a record to the database.
//                 This function currently does not do anything.
//
//  Parameters:    start (struct record **) : pointer to the pointer
//                                            of the start of the list
//                 uaccountno (int) : The account number to be
//                                    associated with this bank record.
//                 uname (char []) : The name associated with this record.
//                 uaddress (char []) : The address associated with this record.
//
//  Return values:  0 : successfully added record
//                 -1 : cannot add record, unsuccessful
//
****************************************************************/

int addRecord(struct record ** start, int uaccountno, char uname [], char uaddress [])
{
    int return_value = 0;

    struct record * new_address = NULL;
    struct record * current_address = * start;
    struct record * prev_address = NULL;

    if(debug_mode == 1)
    {
        printf("\n***** DEBUG MODE ***************************");
        printf("\nAccount #: %d", uaccountno);
        printf("\nName: %s", uname);
        printf("\nAddress: %6s\n\n", uaddress);
    }

    if(current_address != NULL)
    {
        while(current_address != NULL && uaccountno > (*current_address).accountno)
        {
            prev_address = current_address;
            current_address = (*current_address).next;
        }

        if(current_address != NULL && uaccountno == (*current_address).accountno)
        {
            return_value = -1;
        }
    }

    if(return_value == 0)
    {
        new_address = (struct record *) malloc(sizeof (struct record));

        (*new_address).accountno = uaccountno;
        strcpy((*new_address).name, uname);
        strcpy((*new_address).address, uaddress);

        if(*start == NULL || prev_address == NULL)
        {
            *start = new_address;
        }
        else
        {
            (*prev_address).next = new_address;
        }

        (*new_address).next = current_address;
    }

    if(debug_mode == 1)
    {
        printf("\n\n***** return_value = %d", return_value);

        if(return_value == 1)
        {
            printf("Added:\n");

            printf("Account Number: %d", (*new_address).accountno);
            printf("\nName: %s", (*new_address).name);
            printf("\nAddress: %s\n\n", (*new_address).address);
        }
    }

            
    if(return_value == -1)
    {   
        printf("\nCannot add record. Account number must be unique.\n");
    }

    else
    {   
        printf("\nAdded record successfully.\n");
    }

    return return_value;
}

/*****************************************************************
//
//  Function name: printAllRecords
//
//  DESCRIPTION:   This prints all the bank records in the database.
//
//  Parameters:    start (struct record *) : pointer to the pointer
//                                           of the start of the list
//  
//  Return values: none
//
****************************************************************/

void printAllRecords(struct record * start)
{
    if(debug_mode == 1)
    {
        printf("\n***** DEBUG MODE ***************************");
        printf("\nPrint all records\n\n");
    }

    while(start != NULL)
    {
        printf("Account Number: %d", (*start).accountno);
        printf("\nName: %s", (*start).name);
        printf("\nAddress: %s\n\n", (*start).address);

        start = (*start).next;
    }

}

/*****************************************************************
//
//  Function name: findRecord
//
//  DESCRIPTION:   This function finds the bank record associated
//                 with the given account number.
//
//  Parameters:    start (struct record *) : address of the first
//                                           record in the database
//                 uaccountno (int) : The associated account number
//                                    to the bank record to find.
//
//  Return values: 0 : record found, success
//                -1 : no record found; unsuccessful
//
****************************************************************/

int findRecord(struct record * start, int uaccountno)
{
    int return_value = -1;

    struct record * current_address = start;

    if(debug_mode == 1)
    {   
        printf("\n***** DEBUG MODE ***************************");
        printf("\nAccount to find: %d\n\n", uaccountno);
    }

    if(current_address != NULL)
    {
        while(current_address != NULL && uaccountno > (*current_address).accountno)
        {
            current_address = (*current_address).next;
        }

        if(current_address != NULL && uaccountno == (*current_address).accountno)
        {
           printf("Record found\n");
           printf("Account Number: %d", (*current_address).accountno);
           printf("\nName: %s", (*current_address).name);
           printf("\nAddress: %s\n\n", (*current_address).address); 
            
            return_value = 0;
        }
    }

    if(debug_mode == 1)
    {
        printf("\n\n***** return_value = %d", return_value);
    }

    if(return_value == -1)
    {
        printf("\nCannot find record with account number %d.\n\n", uaccountno);
    }

    return return_value;
}

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   This function deletes the associated bank 
//                 record associated with the given account number.
//
//  Parameters:    start (struct record **) : pointer to the pointer
//                                            of the start of the list
//                 uaccountno (int) : The account number to be
//                                    associated with this bank record.
//  
//  Return values: 0 : found and deleted record successfully
//                -1 : record not cound, unsuccessful
//
****************************************************************/

int deleteRecord(struct record ** start, int uaccountno)
{
    int return_value = -1;

    struct record * current_address = * start;
    struct record * prev_address = NULL;

    if(debug_mode == 1)
    {
        printf("\n***** DEBUG MODE ***************************");
        printf("\nAccount to delete: %d\n\n", uaccountno);
    }

    if(current_address != NULL)
    {
        while(current_address != NULL && uaccountno > (*current_address).accountno)
        {
            prev_address = current_address;
            current_address = (*current_address).next;
        }

        if(current_address != NULL && uaccountno == (*current_address).accountno)
        {
            printf("Deleting record with account number %d", uaccountno);

            if(prev_address != NULL)
            {
                (*prev_address).next = (*current_address).next;
            }
            else
            {
                *start = (*current_address).next;
            }

            free(current_address);

            current_address = NULL;
            return_value = 0;
        }
    }

    if(return_value == -1)
    {
        printf("Unable to find and delete record with account number %d", uaccountno);
    }

    return return_value;    
}

/*****************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   This function writes the records in the database
//                 into a text file.
//                 
//  Parameters:    start (struct record *) : pointer to the start
//                                           of the list of records
//                 filename (char []) : the name of the file to write to
//
//  Return values:  0 : successfully written to the file
//                 -1 : unable to write to file
//
****************************************************************/

int writefile(struct record * start, char filename [])
{
    int return_value = -1;

    FILE * outfile = fopen(filename, "w");

    if(debug_mode == 1)
    {
        printf("\n***** DEBUG MODE ***************************");
        printf("\nStarting address of list of records: %p", (void *) start);
        printf("\nGiven file name: %s\n\n", filename);
    }

    if(outfile != NULL)
    {
        return_value = 0;

        while(start != NULL)
        {
            fprintf(outfile, "%d\n", (*start).accountno);
            fprintf(outfile, "%s\n", (*start).name);
            fprintf(outfile, "%s?\n", (*start).address);
        
            start = (*start).next;
        }

        fclose(outfile);
    }

    if(debug_mode == 1)
    {
        if(return_value == 0)
        {
            printf("*****Written to file successfully.\n\n");
        }
        
        else
        {
            printf("*****Unable to write to file.\n\n");
        }
    }

    return return_value;
}

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   This function reads from a text file of records
//                 and saves it into the database.
//                 
//  Parameters:    start (struct record **) : pointer to the pointer to
//                                           the start of the list of records
//                 filename (char []) : the name of the file to read from
//
//  Return values:  0 : successfully written to the file
//                 -1 : unable to write to file
//
****************************************************************/

int readfile(struct record ** start, char filename [])
{
    int return_value = -1;

    int uaccountno;
    char uname [25];
    char uaddress [45];
    char tmp [10];

    int address_index = 0;
    char prev_char;

    int checkEOF;

    FILE * infile = fopen(filename, "r");

    if(debug_mode == 1)
    {   
        printf("\n***** DEBUG MODE ***************************");
        printf("\nValue of start: %p", (void *) *start);
        printf("\nGiven file name: %s\n\n", filename);
    }

    if(infile != NULL)
    {   
        return_value = 0;
        
        checkEOF = fgetc(infile);

        while(checkEOF != EOF)
        {
            ungetc(checkEOF, infile);

            fscanf(infile, "%d", &uaccountno);
            fgets(tmp, 10, infile);

            fgets(uname, 25, infile);
            uname[strlen(uname) - 1] = '\0';

            do
            {
                prev_char = fgetc(infile);
                uaddress[address_index] = prev_char;

                address_index = address_index + 1;
            }
            while(prev_char != 63 && 0 <= address_index && address_index < 45);

            uaddress[address_index - 1] = '\0';

            fgets(tmp, 10, infile);
            checkEOF = fgetc(infile);

            addRecord(start, uaccountno, uname, uaddress);
            
        }
        
        fclose(infile);
    }

    if(debug_mode == 1)
    {   
        if(return_value == 0)
        {   
            printf("*****Read from file successfully.\n\n");
        }
        
        else
        {   
            printf("*****Unable to read from file.\n\n");
        }
    }

    return return_value;
}

/*****************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:   This function releases all the allocated spaces
//                 in the heap memory and assigns NULL to start
//                 to prevent a memory leak.
//
//  Parameters:    start (struct record **) : pointer to the pointer
//                                            to the start of the list
//                                            of records
//
//  Return values: none
//
****************************************************************/

void cleanup(struct record ** start)
{
    struct record * tmp_address = *start;

    if(debug_mode == 1)
    {   
        printf("\n***** DEBUG MODE ***************************");
        printf("\nCleaning up\n\n");
    }
    
    while(*start != NULL)
    {   
        tmp_address = *start;
        *start = (**start).next;

        if(debug_mode == 1)
        {
            printf("\n******Deallocating heap space for record with ");
            printf("account number %d\n\n", (*tmp_address).accountno);
        }

        free(tmp_address);
    }

    *start = NULL;
}
