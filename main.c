/*  Name : Nithin B.J
    Batch:25021_A
    Title: Address Book
    Date :25/09/2025
    Descrption : The Address Book Management System is a command-line-based application designed to store,
                manage, and retrieve contact information of individuals. The system allows users to add new contacts,
                search for existing ones, update details, delete contacts, and view all saved contacts in a structured format.
                The primary goal is to simplify the management of personal or professional contact lists using structured data and file handling.
*/



#include <stdio.h>
#include "contact.h"

int main() 
{
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts\n");		
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:          
                listContacts(&addressBook);
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);
    
       return 0;
}
