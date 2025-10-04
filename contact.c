#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook) 
{
    if (addressBook->contactCount == 0)
    {
        printf("\nNo contacts to display.\n");
        return;
    }

    printf("\n-------Saved Contacts------\n");
    printf("-------------------------------------------------------------------------------\n");
    printf("%s %s %s %s\n", "S.No", "Name", "Mobile No.", "Email");
    printf("-------------------------------------------------------------------------------\n");
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        printf("%d %s %s %s\n",i + 1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
}


void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
    char mail[100];
    char namearr[20];
    char ph_no[20];
    val_name(namearr);                                                                  //function call to validate the name                      
    val_no(ph_no);                                                                      //function call to validate the phone number
    ph_duplicate(addressBook,ph_no);                                                    //function call to check duplicate phone number
    val_email(mail);                                                                    //function call to validate the email
    mail_duplicate(addressBook,mail);                                                   //function call to check duplicate email
    strcpy(addressBook->contacts[addressBook->contactCount].name, namearr);             //storing the validated data into the structure
    strcpy(addressBook->contacts[addressBook->contactCount].phone, ph_no);
    strcpy(addressBook->contacts[addressBook->contactCount].email, mail);

    addressBook->contactCount++;                                                         //incrementing the contact count
    printf("\n ---------contact created successfully------\n");
}

void searchContact(AddressBook *addressBook) 
{
    if (addressBook->contactCount == 0) 
    {
        printf("No contacts available to search.\n");
        return;
    }
    int search;                                                                          // asking the user to enter the option to search.
    char name[50], ph_no[20], mail[50];                                                  // taking temporary variables to  serach
    int found;
    do
    {
    printf("-----Search by the below mentioned criteria.-----\n");                         // asking the user to enter an option to search
    printf("1. By Name\n");
    printf("2. By ph_no\n");
    printf("3. By mail\n");
    printf("Enter option to search: ");
    scanf("%d", &search);
    getchar();                                                                             // Clear newline                                                                            
    if(search < 1 || search > 3)                                                           // validating the search key 
    {
        printf("Invalid option. Please renter the option to search.\n");
        continue;
    }                                                                               
    switch (search) 
    {
        case 1:
            val_name(name);                                                                       // Validate name
            found = 0;
            for (int i = 0; i < addressBook->contactCount; i++) 
            {
                if (strcmp(addressBook->contacts[i].name, name) == 0)                             // Compare names to match 
                {
                    printf("Contact found:\n");
                    printf("Name: %s\n", addressBook->contacts[i].name);                          // Display contact details if found
                    printf("Phone: %s\n", addressBook->contacts[i].phone);
                    printf("Email: %s\n", addressBook->contacts[i].email);
                    found = 1;                                                                    // Set found flag
                }
            }
            if (!found)                                                                            // if contact name is not found 
            {
                printf("Contact not found with name: %s\n", name);
            }
            break;
        case 2:
            val_no(ph_no);                                                                         // Validate phone number                       
            found = 0;
            for (int i = 0; i < addressBook->contactCount; i++)
             {
                if (strcmp(addressBook->contacts[i].phone, ph_no) == 0)                            // Compare phone numbers with numbers in addressbook
                {
                    printf("Contact found:\n");
                    printf("Name: %s\n", addressBook->contacts[i].name);                           // Display contact details if found
                    printf("Phone: %s\n", addressBook->contacts[i].phone);
                    printf("Email: %s\n", addressBook->contacts[i].email);
                    found = 1;                                                                     // Set found flag to indiacte that contact is found.
                }
            }
            if (!found) 
            {
                printf("Contact not found with phone number: %s\n", ph_no);
            }
            break;
        case 3:
            val_email(mail);                                                                        // Validate email
            found = 0;
            for (int i = 0; i < addressBook->contactCount; i++) 
            {
                if (strcmp(addressBook->contacts[i].email, mail) == 0)                                // Compare emails with mail id in the addressbook
                {                                                               
                    printf("Contact found:\n");
                    printf("Name: %s\n", addressBook->contacts[i].name);
                    printf("Phone: %s\n", addressBook->contacts[i].phone);
                    printf("Email: %s\n", addressBook->contacts[i].email);
                    found = 1;                                                                        // Set found flag to indicate mail is matched.
                }
            }
            if (!found) 
            {
                printf("Contact not found with email: %s\n", mail);
            }
            break;
        default:
            printf("Invalid option. Please renter the option to search.\n");                           // if search key is inavlid  
            break;
    }
    }while(search<1 || search>3);                                                                       // Loop until a valid search option is entered
}

/*Editing the contact details by listing it and  edit it by the index*/
void editContact(AddressBook *addressBook)
{   
    int index;
    if (addressBook->contactCount == 0) 
    {
        printf("No contacts available to search.\n");
        return;
    }
    listContacts(addressBook);                                                                              //calling the listcontatct so that user enter the index of contact whic has to be edited
    do
    {
        printf("Enter the index of the contact to edit : ");                                                 // asking the user  to enter the index of the contact to edit
        scanf("%d", &index);
        getchar();                                                                                           // Clear newline
    } while(index < 1 || index > addressBook->contactCount);
    index--;                                                                                                 // Convert to 0 index
    printf("Editing contact %d:\n", index + 1);                                                              

    char newname[20], newphone[20], newemail[100];                                                           // Temporary variables for edited contact details
    int edit;                                                                                              
    do{                      
        printf("Enter the  key to edit: \n1.Name\n2.Phone\n3.Email\n");                                      // asking the user to an option to edit 
        scanf("%d",&edit);
        switch(edit)
        {
            case 1:                                                                                             
                printf("Current Name: %s\n", addressBook->contacts[index].name);                            //dislpaying the current name at the selected index
                val_name(newname);                                                                             // validating the name edited by the user
                strcpy(addressBook->contacts[index].name, newname);                                             // copying the dited name to addressbook strucutre
                break;
            case 2:
                printf("Current Phone: %s\n", addressBook->contacts[index].phone);                            // displaying the current phonenumber at the user selected index
                val_no(newphone);                                                                              // validating the phone number.
                ph_duplicate(addressBook,newphone);                                                           // checking whether the phone number is already exited are not
                strcpy(addressBook->contacts[index].phone, newphone);                                           // copying the edited number to structures
                break;
            case 3:
                printf("Current Email: %s\n", addressBook->contacts[index].email);                                  // displaying the current mail id
                val_email(newemail);                                                                            // validating the edited mail id
                mail_duplicate(addressBook,newemail);                                                           // checking for matching mail id
                strcpy(addressBook->contacts[index].email, newemail);                                           //copying the updated mail id
                break;
            default:
                printf("Invalid option to search");
        }
    }while(edit < 1 || edit >3);                                                                                 //runnig the loop til condtion becomes false
    printf("Contact updated successfully!\n");
}
/*Function for deleting the contact by selecting the index*/
void deleteContact(AddressBook *addressBook)
{
     if (addressBook->contactCount == 0) 
    {
        printf("No contacts available to search.\n");
        return;
    }
    int index;
    listContacts(addressBook);                                                                                    // listing the conatact so user to select the conatct index that has to deleted
    do
    {
        printf("Enter the index of the contact to delete : ");                                                      // selecting the index to delete the conatact details
        scanf("%d", &index);
        getchar();                                                                                                  // Clear newline
    } while(index < 1 || index > addressBook->contactCount);
    index--;
    char conf[10];                                                                                                  // Convert to 0 index
    printf("Are you sure you want to delete contact  index %d ? (yes/no): ", index + 1);                             //asking confirmation from the user to delete the contatc
    scanf("%s", conf);
    getchar();                                                                                                      // Clear newline
    if (strcmp(conf, "yes") != 0)                                           // Confirm deletion
    {
        printf("Deletion cancelled.\n");
        return;
    }
    else
    {
        printf("Deleting contact...\n");
        for (int i = index; i < addressBook->contactCount - 1; i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }
    }
    addressBook->contactCount--;                                            // updating the contact count by reducing by 1.

    printf("Contact deleted successfully!\n");
   
}




/************************************************************************************************************** */
void val_name(char *namearr)
{ 
    int flag =0;
    do
    {
	    int i=0; 
        flag =0;
        printf("Enter the name: ");
        scanf(" %[^\n]",namearr);           //scaning input from the user.
        getchar();
        
        while(namearr[i] !='\0')            //comparing the name to null
        {
            if(namearr[i] >= 'A' && namearr[i] <='Z')
            {
                flag = 0;
            }
            else if(namearr[i] >= 'a' && namearr[i] <='z')
            {
                flag= 0 ;
            }
            else if(namearr[i] == ' ' || namearr[i] =='.')
            {
               flag =0;
            }
            else
            {
                flag = 1;                       //updating flag to 1 to indicate the invalid condition
                break;                          // to terminate the loop if it encounetr any numeric values and special character.
            }
            i++;
        }  
        if(flag)
        {
            printf("Invalid name!!!\n");
        }
    }while(flag);                               // checking the condtion for validating the name.
}
void val_no(char *ph_no)
{
    int flag=0;
    do
    {
        flag =0;
        printf("Enter the number: ");
        scanf(" %[^\n]",ph_no);
        getchar();
        int len = strlen(ph_no);                // to ger the length of the number;
        if(len == 10)                          // checking the length of the number to be 10 digits.  
        {                       
            for(int i=0;i<len;i++)              // runing the loop untill the len
            {
                if(ph_no[i] >= '0' && ph_no[i] <= '9')      // checking the number conatins only digits.
                {
                    flag = 0;
                }
                else
                {
                    flag = 1;                               //updating the flag to indicate the number is invalid,hence contains character or special character.
                    printf("Invalid number!!\n");
                    break;
                }
            }
        }
        else
        {
            flag = 1;                                   //updating the flag to indicate the number is invalid,hence length is not equal to 10.
            printf("Invalid number!!\n");
        }
    }while(flag);
}

void ph_duplicate(AddressBook *addressBook,char *ph_no)
{
    int flag=0;
    for(int i = 0; i < addressBook->contactCount; i++)
        {  
            if (strcmp(addressBook->contacts[i].phone, ph_no) == 0)         // checking the number already exists or not
            {
                printf("Number already exists!!!\n");
                flag = 1;
                break;
            }
        }
    if(flag)
    {                                                                          // if number already exists calling the function to re enter the number.
        val_no(ph_no);
        ph_duplicate(addressBook,ph_no);
    }
}

void val_email(char *mail)
{
    int flag = 0;
    do
    {
        int at_pos = 0;
        flag = 0;
        int at = 0;
        printf("Enter the mail: ");
        scanf(" %[^\n]",mail);
        char needle[20] = ".com";           // intiallzing the needle to .com
        char *ret = strstr(mail,needle);
        if(ret == NULL )                       //checking if needle is present
        {
            flag =1;
            printf("Invalid mail!!\n");
        }
        else                                    //validating other conditions
        {
            int com_pos = ret - mail;
            int len = strlen(mail);
            if(com_pos+4 == len)
            {
                if(mail[0]>= 'a' && mail[0] <='z')  // checking the first character to lowercase alphabet.
                {
                    for(int i=1;mail[i] !='\0';i++)
                    {
                        if(mail[i] == '@')          // cehcking the presence of @
                        {
                            at++;
                            at_pos = i;         //storing the position of @
                        }
                    }
                    if(at == 1)                        // if @ is present at once 
                    {
                        for(int i=0; mail[i] !='\0'; i++)  
                        {
                            if(mail[i] >= 'a' && mail[i] <='z')    //checking for lower case
                            {
                                flag = 0;
                            }
                            else if(mail[i] >= '0' && mail[i] <='9')  // checking for digits
                            {
                                flag = 0;
                            }
                            else if(mail[i] == '@' || mail[i] =='.' || mail[i] == '_')      // checking for spcl chars
                            {
                                flag = 0;
                            }
                            else 
                            {
                                flag = 1;
                                break;
                            }
                        }
                    }
                    else
                    {
                        printf("Invalid mail!!!\n"); 
                        flag = 1;
                    }

                }
                else
                {
                    printf("Invalid mail!!!\n");  
                    flag = 1;
                }
            }
            else 
            {
                flag = 1;
                printf("Invalid mail!!\n");
            }
        }
    }while(flag);
}
void mail_duplicate(AddressBook *addressBook,char *mail)
{
    int flag = 0;
    for(int i = 0; i < addressBook->contactCount; i++)
    {  
            if (strcmp(addressBook->contacts[i].email, mail) == 0)         // checking the number already exists or not
            {
                printf("mail already exists!!\n");
                flag = 1;
                break;
            }
    }if(flag)
    {
        val_email(mail);                                            // if mail already exists calling the function to re enter the mail.
        mail_duplicate(addressBook,mail);
    }
}