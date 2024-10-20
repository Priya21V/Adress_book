/*
Name        : V Priyanka
Date        : 13/08/2024
Description : Address Book
*/
#include <stdio.h>
#include "contact.h"
#include "file.h"

int main() {
    int choice;
    AddressBook addressBook;
    //initialize(&addressBook); // Initialize the address book
    loadContactsFromFile(&addressBook);  //function call of loadContactsFromFile()
     listContacts(&addressBook);  //function call of listContacts()


    do {
        printf("\nAddress Book Menu:\n");  //Adress book menu options
        printf("1. Add contact\n");
        printf("2. Edit contact\n");
        printf("3. Search contact\n");
        printf("4. Display contact\n");
        printf("5. Delete contacts\n");
        printf("6. Save contact\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);//reading the choice from the user
        getchar();      
        switch (choice) {
            case 1:
                createContact(&addressBook);   //function call of createContact()
                break;
            case 2:
                editContact(&addressBook);    //function call of editContact()
                break;
            case 3:
                searchContact(&addressBook);  //function call of searchContact()
                break;
            case 4:
                /*printf("Select sort criteria:\n");
                printf("1. Sort by name\n");
                printf("2. Sort by phone\n");
                printf("3. Sort by email\n");
                printf("Enter your choice: ");
                int sortChoice;
                scanf("%d", &sortChoice);*/
                listContacts(&addressBook);   //function call of listContact()
                break;
            case 5:
                deleteContact(&addressBook);  //function call of deleteContact()
                break;
            case 6:
                printf("Saving ...\n");
                saveContactsToFile(&addressBook);  //function call of saveContactsToFile()
                break;
            case 7:
                printf("Exiting...\n");    //exiting the program
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);  //continue the loop untill the user enter exit option
    return 0;
    
}
