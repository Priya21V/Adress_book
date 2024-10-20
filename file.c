/*
Name        : V Priyanka
Date        : 13/08/2024
Description : Address Book
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

//function defintion of saveContactsToFile()
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fptr;
    fptr = fopen("contacts.csv", "w");  //opening the file in write mode
    if (fptr == NULL)
    {
        printf("File failed to open");
        return;
    }

    fprintf(fptr, "#%d\n", addressBook->contactCount);  //adding the contact count from addressbook to file
    
    //adding the contacts from addressbook to file
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fptr, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }

    fclose(fptr);  //closing the file
}

//function definition of loadContactsFromFile()
void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fptr;
    fptr = fopen("contacts.csv", "r");  //opening the file in read mode
    if (fptr == NULL)
    {
        printf("File failed to open\n");
        return;
    }

    char str[5];
    if (fgets(str, sizeof(str), fptr) != NULL && str[0] == '#')
    {
        addressBook->contactCount = atoi(str + 1);   //reading contact count from file to address book
    }

    //reading contacts from file to address book 
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fscanf(fptr, "%25[^,],%25[^,],%25[^\n]\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }

    fclose(fptr);  //closing the file
}