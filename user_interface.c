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
//  FILE:        user_interface.c
//
//  DESCRIPTION: This is the user interface. This allows the user
//               to interact with the database, such as adding,
//               deleting, finding, and printing the records.
//
****************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "record.h"
#include "database.h"

void getaddress (char [], int);

int debug_mode = 0;

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   The main function interacts with the user allowing 
//                 them to interact with the database and add, find,
//                 and delete records and print all the records in the
//                 database.
//
//  Parameters:    argc (int) : The number of elements in argv
//                 argv (char*[]) : An array of arguments passed
//                                  to the program.
//
//  Return values:  0 : success
//
****************************************************************/

int main(int argc, char* argv[])
{
    struct record * start = NULL;

    char filename [25] = "record_file.txt";

    char name [25];
    char address [45];
    int account;

    char menu_opt [25];
    char tmp [25];
    char add_opt [10] = "add\0";
    char print_opt [10] = "printall\0";
    char find_opt [10] = "find\0";
    char delete_opt [10] = "delete\0";
    char quit_opt [10] = "quit\0";

    int  quitting = 0;
    int  valid_acc = 0;
    
    char debug_str [10] = "debug\0";
    debug_mode = 0;

    if(argc == 2 && strcmp(argv[1], debug_str) == 0)
    {
        printf("***** in DEBUG MODE\n\n");
        debug_mode = 1;
    }

    else if(argc > 2 || (argc >= 2 && strcmp(argv[1], debug_str)) != 0)
    {
        printf("Error: Only debug mode\n**EXITING");
        exit(0);
    }

    readfile(&start, filename);

    printf("This is the user interface to manage bank records ");
    printf("in the database.\n");

    printf("Manage bank records by choosing one of the following ");
    printf("by typing in the name of the menu options.");

    while(quitting != 1)
    {
        printf("\nMenu:\n");
        printf("add: Add a new record in the database.\n");
        printf("printall: Print all records in the database.\n");
        printf("find: Find record(s) with a sepcified account number.\n");
        printf("delete: Delete exisitng record(s) from the database ");
        printf("using the account number as a key.\n");
        printf("quit: Quit the program.\n");
        
        fgets(menu_opt, 10, stdin);
        menu_opt [strlen(menu_opt) - 1] = 0;

        if(strlen(menu_opt) <= strlen(add_opt) && menu_opt[0] == 97)
        {
            if(strncmp(menu_opt, add_opt, strlen(menu_opt)) == 0)
            {
                printf("Please enter an account number: ");
                
                do
                {
                    valid_acc = scanf("%d", &account);
                    fgets(tmp, 25, stdin);
                    
                    if(account <= 0 || valid_acc == 0)
                    {
                        printf("Account number is invalid. ");
                        printf("Please input a positive integer: ");
                        valid_acc = 0;
                    }

                }
                while(valid_acc == 0); 

                printf("Please enter your name: ");
                fgets(name, 25, stdin);
                name[strlen(name) - 1] = 0;
            
                getaddress(address, 45);
                fgets(tmp, 25, stdin);

                addRecord(&start, account, name, address);
            }

            else
            {
                printf("Given input is an invalid option. ");
                printf("Please enter a valid option: \n");
            }
        }

        else if(strlen(menu_opt) <= strlen(print_opt) && menu_opt[0] == 112)
        {
            if(strncmp(menu_opt, print_opt, strlen(menu_opt)) == 0)
            {
                printAllRecords(start);
            }

            else
            {
                printf("Given input is an invalid option. ");
                printf("Please enter a valid option: \n");
            }
        }

        else if(strlen(menu_opt) <= strlen(find_opt) && menu_opt[0] == 102)
        {
            if(strncmp(menu_opt, find_opt, strlen(menu_opt)) == 0)
            {
                printf("\nEnter the account number to find: ");

                do
                {
                    valid_acc = scanf("%d", &account);
                    fgets(tmp, 25, stdin);

                    if(account <= 0 || valid_acc == 0)
                    {
                        printf("Account number is invalid. ");
                        printf("Please input a positive integer: ");
                        valid_acc = 0;
                    }

                }
                while(valid_acc == 0);
            
                findRecord(start, account);
            }

            else
            {
                printf("Given input is an invalid option. ");
                printf("Please enter a valid option: \n");
            }
        }

        else if(strlen(menu_opt) <= strlen(delete_opt) && menu_opt[0] == 100)
        {
            if(strncmp(menu_opt, delete_opt, strlen(menu_opt)) == 0)
            {
                printf("Enter the account number to delete: ");

                do
                {
                    valid_acc = scanf("%d", &account);
                    fgets(tmp, 25, stdin);

                    if(account <= 0 || valid_acc == 0)
                    {
                        printf("Account number is invalid. ");
                        printf("Please input a positive integer: ");
                        valid_acc = 0;
                    }

                }
                while(valid_acc == 0);

                deleteRecord(&start, account);
            }

            else
            {
                printf("Given input is an invalid option. ");
                printf("Please enter a valid option: \n");
            }
        }

        else if(strlen(menu_opt) <= strlen(quit_opt) && menu_opt[0] == 113)
        {
            if(strncmp(menu_opt, quit_opt, strlen(menu_opt)) == 0)
            {
                writefile(start, filename);
                quitting = 1;
            }

            else
            {
                printf("Given input is an invalid option. ");
                printf("Please enter a valid option: \n");
            }
        }

        else
        {
            printf("Given input is an invalid option. ");
            printf("Please enter a valid option: \n");
        }

    }

    cleanup(&start);

    return 0;
}

/*****************************************************************
//
//  Function name: getadress
//
//  DESCRIPTION:   This function obtains address information
//                 from the user input.
//
//  Parameters:    address_holder (char []) : The array that stores
//                                            the address.
//                 length         (int)     : The lenght of the array.
//
//  Return values: none
//
****************************************************************/

void getaddress(char address_holder [],  int length)
{
    int index = 0;
    char prev_char;

    printf("Please enter your address. End your input with a ");
    printf("question mark and press <ENTER>.\n");

    do
    {
        prev_char = fgetc(stdin);
        *(address_holder + index) = prev_char;
        index = index + 1;
    }
    while(prev_char != 63 && 0 <= index && index < length);

    *(address_holder + index - 1) = 0;

}
