#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fptr;
    fptr = fopen("Address_Book.csv", "w");                // Open file in write mode
    if(fptr == NULL) 
    {
        printf("Error opening file !!\n");
        return;
    }
    fprintf(fptr, "%d\n", addressBook->contactCount);        // Write the number of contactcount.
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        fprintf(fptr, "%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);            
    }
    fclose(fptr);
  
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fptr;
    fptr = fopen("Address_Book.csv", "r");
    if (fptr == NULL)
    {
        printf("Error opening file !!!\n");
        addressBook->contactCount = 0;  
        return;
    }
    fscanf(fptr,"%d\n",&addressBook->contactCount);               // Read the contact count
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        fscanf(fptr, " %[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
fclose(fptr);
}
