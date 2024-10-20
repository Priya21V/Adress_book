/*
Name        : V Priyanka
Date        : 13/08/2024
Description : Address Book
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

// function defintion of search() to search the given key is present or not
int search(AddressBook *addressBook, char *key, int opt)
{
    // searching the key upto contactCount times
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        switch (opt)
        {
        case 1:
            // searching the given name is present in contact names using strcmp()
            if (strcmp(addressBook->contacts[i].name, key) == 0)
            {
                return i; // returning the index where the name is present
            }
            break;

        case 2:
            // searching the given mobile number is present in contact numbers using strcmp()
            if (strcmp(addressBook->contacts[i].phone, key) == 0)
            {
                return i; // returning the index where the mobile number is present
            }
            break;

        case 3:
            // searching the given mail id is present in contact mail ids' using strcmp()
            if (strcmp(addressBook->contacts[i].email, key) == 0)
            {
                return i; // returning the index where the mail id is present
            }
            break;
        }
    }
    return -1; // returning -1 if key is not found
}

// function definition of listContacts() to display all the contacts
void listContacts(AddressBook *addressBook)
{
    // displaying all contacts present in the addressbook
    printf("\n--------------------------------------------------------------------------------\n");
    printf("SL.NO  Contact Name\t\tMobile Number\t\tE-mail Id\n");
    printf("---------------------------------------------------------------------------------");
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("\n%d.\t%-20s\t%-20s\t%-20s", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    printf("\n--------------------------------------------------------------------------------\n");
}

/*void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);

    // Load contacts from file during initialization (After files)
    // loadContactsFromFile(addressBook);
}*/

//function definition of saveAndExit()
void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file  function call of saveContactsToFile()
    exit(EXIT_SUCCESS);              // Exit the program
}

// function definition of createContact() to add contact
void createContact(AddressBook *addressBook)
{
    char c;
    do
    {
        // getchar();
        printf("Enter Contact name: ");
        // reading the contact name from the user
        scanf("%[^\n]", addressBook->contacts[addressBook->contactCount].name);
        getchar();
        int duplicate = 0;
        while (1)
        {

            printf("Enter Mobile number: ");
            // reading the contact number from the user
            scanf("%[^\n]", addressBook->contacts[addressBook->contactCount].phone);
            getchar();
            // checking the length of given mobile number is 10
            if (strlen(addressBook->contacts[addressBook->contactCount].phone) == 10)
            {
                int i = 0;
                int flag = 0;
                // checking the given number has 0-9 digits
                while (i < strlen(addressBook->contacts[addressBook->contactCount].phone))
                {
                    if (addressBook->contacts[addressBook->contactCount].phone[i] >= '0' && addressBook->contacts[addressBook->contactCount].phone[i] <= '9')
                    {
                        i++;
                    }
                    else
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag)
                {
                    printf("\nEnter 0-9 digits only!\n");
                    continue;
                }
                else
                {
                    // checking the number is already present in the contacts or not
                    for (int i = 0; i < addressBook->contactCount; i++)
                    {
                        if (strcmp(addressBook->contacts[i].phone, addressBook->contacts[addressBook->contactCount].phone) == 0)
                        {
                            printf("\nEntered Mobile number already exists!\n");
                            duplicate = 1;
                            break;
                        }
                    }
                    if (duplicate)
                    {
                        duplicate = 0;
                        continue; // if already present re-reading the mobile number from the user
                    }
                    else
                    {
                        break; // storing the number
                    }
                }
            }
            else
            {
                printf("\nPlease enter 10 digit number!\n");
            }
        }
        while (1)
        {
            if (duplicate == 0) // checking the mobile number is not present in the contacts
            {

                printf("Enter E-mail ID: ");
                // reading the email-id from the user
                scanf("%[^\n]", addressBook->contacts[addressBook->contactCount].email);
                getchar();
                // validating email-id whether it contains '@' and '.com'
                char *s = strstr(addressBook->contacts[addressBook->contactCount].email, "@");
                char *c = strstr(addressBook->contacts[addressBook->contactCount].email, ".com");
                if (s == NULL || c == NULL)
                {
                    printf("\nPlease enter a valid E-mail ID!\n");
                    continue; // if '@' and '.com' are not present in the re-reading the mail-id from the user
                }
                else
                {
                    // incrementing the contactCount if valid mobile number and mail-id is entered
                    addressBook->contactCount++;
                    printf("\nContact added successfully...\n");
                    break;
                }
            }
        }
        // asking the user whether he want to continue to add contact or not
        printf("\nDo you want to continue to Add contact(y/n): ");
        scanf(" %c", &c); // reading the choice from the user
        getchar();
    } while (c != 'n');
}

// function definition of searchContact() to search the contact if found printing the contact
void searchContact(AddressBook *addressBook)
{
    char c;
    do
    {

        int opt, index;
        // options to search
        printf("Choose the option to search\n");
        printf("1.Name\n");
        printf("2.Mobile Number\n");
        printf("3.E-mail ID\n");
        scanf("%d", &opt); // reading the option from the user
        getchar();
        char key[100];
        switch (opt)
        {
        case 1:
            printf("Enter the name to search: ");
            break;

        case 2:
            printf("Enter the Mobile Number to search: ");
            break;

        case 3:
            printf("Enter the E-mail ID to search: ");
            break;

        default:
            printf("\nPlease choose the correct option!\n");
            continue;
        }
        scanf("%[^\n]", key); // reading the key from user to search
        // function call to search the given key , if its found returns the index of the key else returns -1
        index = search(addressBook, key, opt);
        if (index == -1)
        {
            printf("\nContact not found!\n");
        }
        else
        {
            int duplicateIndices[10];
            int duplicateCount = 0;
            //loop for checking duplicate contacts are present or not
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(addressBook->contacts[i].name, key) == 0)
                {
                    duplicateIndices[duplicateCount++] = i;  //storing the indices of duplicate contacts
                }
            }
            if (duplicateCount > 1)  //if more than 1 duplicate contacts are present, displaying the contacts details
            {
                printf("\nSL.NO  Contact Name\t\tMobile Number\t\tE-mail ID\n");
                for (int i = 0; i < duplicateCount; i++)
                {
                    printf("%d.\t%-20s\t%-20s\t%-20s\n", i+1, addressBook->contacts[duplicateIndices[i]].name, addressBook->contacts[duplicateIndices[i]].phone, addressBook->contacts[duplicateIndices[i]].email);
                }
            }
            else
            {

                printf("\nContact found\n");
                printf("Contact Name\t\t\tMobile Number\t\t\tE-mail ID\n");
                // if its found printing the contact
                printf("%-15s\t%-15s\t%-15s\n", addressBook->contacts[index].name, addressBook->contacts[index].phone, addressBook->contacts[index].email);
            }
        }
        // asking the user whether he want to continue to search contact or not
        printf("\nDo you want to continue to Search Contact(y/n): ");
        scanf(" %c", &c); // reading the choice from the user
    } while (c != 'n');
}

//function defintion of editContact()
void editContact(AddressBook *addressBook)
{
    char c;
    do
    {
        int opt, index;
        // options to search
        printf("\nChoose the option to Search\n");
        printf("1.Name\n");
        printf("2.Mobile Number\n");
        printf("3.E-mail ID\n");
        scanf("%d", &opt); // reading the option from the user
        getchar();
        char key[100];
        char edit[100];
        switch (opt)
        {
        case 1:
            printf("Enter the name to search: ");
            break;

        case 2:
            printf("Enter the Mobile Number to search: ");
            break;

        case 3:
            printf("Enter the E-mail ID to search: ");
            break;
        default:
            printf("Please choose the correct option!\n");
            continue;
        }
        scanf("%[^\n]", key); // reading the key to search from the user
        getchar();
        // function call to search() to search the given key
        index = search(addressBook, key, opt);
        if (index == -1)
        {
            printf("\nEntered Contact not found\n");
        }
        else
        {
            if (opt == 1)
            {
                int duplicateIndices[10];
                int duplicateCount = 0;
                //loop for checking duplicate contacts are present or not
                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (strcmp(addressBook->contacts[i].name, key) == 0)
                    {
                        duplicateIndices[duplicateCount++] = i;   //storing the indices of duplicate contacts
                    }
                }
                if (duplicateCount > 1)   //if more than 1 duplicate contacts are present, displaying the contacts details
                {
                    printf("Multiple contacts are found with the same name\n");
                    printf("\nSL.NO Contact Name\t\tMobile Number\t\tE-mail ID\n");
                    for (int i = 0; i < duplicateCount; i++)
                    {
                        printf("%d.\t%-20s\t%-20s\t%-20s\n",i+1, addressBook->contacts[duplicateIndices[i]].name, addressBook->contacts[duplicateIndices[i]].phone, addressBook->contacts[duplicateIndices[i]].email);
                    }
                    printf("Please enter the mobile number to confirm: ");
                    char confirm[10];
                    scanf("%[^\n]", confirm);  //reading mobile number from user to confirm
                    getchar();
                    int confirmedIndex = -1;
                    for (int i = 0; i < duplicateCount; i++)
                    {
                        if (strcmp(addressBook->contacts[duplicateIndices[i]].phone, confirm) == 0)
                        {
                            confirmedIndex = duplicateIndices[i];
                            break;
                        }
                    }
                    if (confirmedIndex == -1)
                    {
                        printf("\nNo contact found with the given name and mobile number\n");
                        continue;
                    }
                    index = confirmedIndex;
                }
            }
            printf("\nEntered Contact found\n");
            int choice;
            printf("Choose the option to Edit\n");
            printf("1.Name\n");
            printf("2.Mobile Number\n");
            printf("3.E-mail ID\n");
            scanf("%d", &choice);  //reading choice from user
            getchar();
            switch (choice)
            {
            case 1:
                printf("Enter the new name : ");
                scanf("%[^\n]", edit);  //reading new name to edit
                getchar();
                strcpy(addressBook->contacts[index].name, edit);  
                printf("\nContact edited successfilly...\n");
                break;
            case 2:
                while (1)
                {

                    printf("Enter the new Mobile Number: ");
                    scanf("%[^\n]", edit);  //reading new mobile number to edit
                    getchar();

                    //validating the newly entered mobile number
                    if (strlen(edit) == 10)
                    {
                        int i = 0;
                        int flag = 0;
                        while (i < strlen(edit))
                        {
                            if (edit[i] >= '0' && edit[i] <= '9')
                            {
                                i++;
                            }
                            else
                            {
                                flag = 1;
                                break;
                            }
                        }
                        if (flag)
                        {
                            printf("\nEnter 0-9 digits only!\n");
                            continue;
                        }

                        int duplicate = 0;
                        for (int i = 0; i < addressBook->contactCount; i++)
                        {
                            if (strcmp(addressBook->contacts[i].phone, edit) == 0)
                            {
                                printf("\nEntered Mobile number already exists!\n");
                                duplicate = 1;
                                break;
                            }
                        }
                        if (duplicate)
                        {
                            duplicate = 0;
                            continue;
                        }

                        strcpy(addressBook->contacts[index].phone, edit);
                        printf("\nContact edited successfilly...\n");
                        break;
                    }
                    else
                    {
                        printf("\nPlease enter 10 digit number!\n");
                        continue;
                    }
                }
                break;
            case 3:
                while (1)
                {
                    printf("Enter the new E-mail ID: ");
                    scanf("%[^\n]", edit);   //reading new E-mail id to edit
                    getchar();

                    //validating the newly entered mail id
                    char *s = strstr(edit, "@");
                    char *c = strstr(edit, ".com");
                    if (s == NULL || c == NULL)
                    {
                        printf("\nPlease enter a valid E-mail ID!\n");
                        continue;
                    }
                    strcpy(addressBook->contacts[index].email, edit);
                    printf("\nContact edited successfilly...\n");
                    break;
                }
                break;
            }
        }
        // asking the user whether he want to continue to edit contact or not
        printf("\nDo you want to continue to Edit Contact(y/n): ");
        scanf(" %c", &c);
        getchar();
    } while (c != 'n');
}

void deleteContact(AddressBook *addressBook)
{
    
    char c;
    do
    {
        int opt, index;
        printf("Choose the option to Delete\n");
        printf("1.Name\n");
        printf("2.Mobile Number\n");
        printf("3.E-mail ID\n");
        scanf("%d", &opt);  //reading the option from user
        getchar();
        char key[100];
        char delete[100];
        switch (opt)
        {
        case 1:
            printf("Enter the name you want to Delete: ");
            scanf("%[^\n]", key);
            getchar();
            index = search(addressBook, key, 1);  //checking the key present or not
            if (index == -1)
            {
                printf("\nContact not found!\n");
            }
            else
            {
                int duplicateIndices[10];
                int duplicateCount = 0;

                 //loop for checking duplicate contacts are present or not
                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (strcmp(addressBook->contacts[i].name, key) == 0)
                    {
                        duplicateIndices[duplicateCount++] = i;  //storing the indices of duplicate contacts
                    }
                }
                if (duplicateCount > 1)  //if more than 1 duplicate contacts are present, displaying the contacts details
                {
                    printf("Multiple contacts are found with the same name\n");
                    printf("\nSL.NO Contact Name\t\tMobile Number\t\tE-mail ID\n");
                    for (int i = 0; i < duplicateCount; i++)
                    {
                        printf("%d.\t%-20s\t%-20s\t%-20s\n",i+1, addressBook->contacts[duplicateIndices[i]].name, addressBook->contacts[duplicateIndices[i]].phone, addressBook->contacts[duplicateIndices[i]].email);
                    }
                    printf("Please enter the mobile number to confirm: ");
                    char confirm[10];
                    scanf("%[^\n]", confirm);  //reading mobile number from user to confirm
                    getchar();
                    int confirmedIndex = -1;
                    for (int i = 0; i < duplicateCount; i++)
                    {
                        if (strcmp(addressBook->contacts[duplicateIndices[i]].phone, confirm) == 0)
                        {
                            confirmedIndex = duplicateIndices[i];
                            break;
                        }
                    }
                    if (confirmedIndex == -1)
                    {
                        printf("\nNo contact found with the given name and mobile number\n");
                        continue;
                    }
                    index = confirmedIndex;
                }
                for (int i = index; i < addressBook->contactCount; i++)
                {
                    addressBook->contacts[i] = addressBook->contacts[i + 1];
                }
                addressBook->contactCount--;
                printf("\nContact deleted successfilly...\n");
            }
            break;

        case 2:
            printf("Enter the Mobile Number to Delete: ");
            scanf("%[^\n]", key);  //reading the mobile number to search
            getchar();
            index = search(addressBook, key, 2);  //checking whether given number present or not
            if (index == -1)
            {
                printf("\nContact not found!\n");
            }
            else
            {
                for (int i = index; i < addressBook->contactCount; i++)
                {
                    addressBook->contacts[i] = addressBook->contacts[i + 1];
                }
                addressBook->contactCount--;
                printf("\nContact deleted successfilly...\n");
            }
            break;

        case 3:
            printf("Enter the E-mail ID to Delete: ");
            scanf("%[^\n]", key);   //reading e-mail from user
            getchar();
            index = search(addressBook, key, 3);  //checking the entered mail present or not
            if (index == -1)
            {
                printf("\nContact not found!\n");
            }
            else
            {
                for (int i = index; i < addressBook->contactCount; i++)
                {
                    addressBook->contacts[i] = addressBook->contacts[i + 1];
                }
                addressBook->contactCount--;
                printf("\nContact deleted successfilly...\n");
            }
            break;
        default:
            printf("Please choose the correct option!");
            continue;
        }
        // asking the user whether he want to continue to edit contact or not
        printf("Do you want to continue to Delete Contact(y/n): ");
        scanf(" %c", &c);
        getchar();
    } while (c != 'n');
}
