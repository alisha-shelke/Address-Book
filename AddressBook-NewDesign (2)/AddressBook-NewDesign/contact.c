/*
 * File: contact.c
 * Author: Alisha Shelke
 * Description: Implements contact creation, searching, editing,
 * deletion, listing, and validation.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria
    
    int choice;
    printf("Choose sorting criteria:\n1. sort by Name\n2. sort by phone Number\n3. sort by Email\n");
    scanf("%d", &choice);
    switch(choice)
    {
        case 1:
        {
            for(int i = 0; i < addressBook->contactCount - 1; i++)
            {
                for(int j = i + 1; j < addressBook->contactCount; j ++)
                {
                   if(strcmp(addressBook->contacts[i].name, addressBook->contacts[j].name) > 0)
                   {
                    Contact temp = addressBook->contacts[i];
                    addressBook->contacts[i] = addressBook->contacts[j];
                    addressBook->contacts[j] = temp;
                   }
                }
            }
            break;
        }
        case 2:
        {
            for(int i = 0; i < addressBook->contactCount - 1; i++)
            {
                 for(int j = i + 1; j < addressBook->contactCount; j ++)
                 {
                     if(strcmp(addressBook->contacts[i].phone, addressBook->contacts[j].phone) > 0)
                     {
                        Contact temp = addressBook->contacts[i];
                        addressBook->contacts[i] = addressBook->contacts[j];
                        addressBook->contacts[j] = temp;
                     }
                 }
            }
            break;
        }
        case 3:
        {
            for(int i = 0; i < addressBook->contactCount - 1; i++)
            {
                for(int j = i + 1; j < addressBook->contactCount; j ++)
                {
                    if(strcmp(addressBook->contacts[i].email,addressBook->contacts[j].email) > 0)
                    {
                        Contact temp = addressBook->contacts[i];
                        addressBook->contacts[i] = addressBook->contacts[j];
                        addressBook->contacts[j] = temp;
                    }
                }
            }
            break;
        }
        default:
               printf("Invalid choice!\n");
               break;
    }
    for(int i = 0; i < addressBook->contactCount; i ++)
    {
        printf("Contact %d: Name: %s, Phone: %s, Email: %s\n", i + 1,
                                                               addressBook->contacts[i].name,
                                                               addressBook->contacts[i].phone,
                                                               addressBook->contacts[i].email);
    }

}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    do
    {
         printf("Enter the name : ");
         scanf(" %[^\n]",addressBook->contacts[addressBook->contactCount].name);
    } while (valid_name(addressBook -> contacts[addressBook->contactCount].name) == 0);
    
    do
    {
        printf("Enter the phone no : ");
        scanf(" %s",addressBook->contacts[addressBook->contactCount].phone);
    } while (valid_phone( addressBook, addressBook -> contacts[addressBook->contactCount].phone) == 0);
    
    do
    {
         printf("Enter the email id : ");
         scanf(" %s",addressBook->contacts[addressBook->contactCount].email);
    } while (valid_email(addressBook, addressBook -> contacts[addressBook->contactCount].email) == 0);
    
   
    addressBook->contactCount++;
}

int searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int choice = 0;
    printf("1. Search by name.\n2. Search by phone\n3. Search ny email.\nEnter the choice : ");
    scanf("%d", &choice);
    switch (choice)
    {
        case 1:
              char name[50];
              printf("Enter the name : ");
              scanf(" %[^\n]", name);
              for(int i = 0; i < addressBook->contactCount; i++)
              {
                  if(strcmp(name, addressBook->contacts[i].name) == 0)
                  {
                    printf("Name: %s, Phone: %s, Email: %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    return i; // return the index
                  }
              }
              break;
        case 2:
              char phone[50];
              printf("Enter the phone number : ");
              scanf("%s", phone);
              for(int i = 0; i < addressBook->contactCount; i++)
              {
                  if(strcmp(phone, addressBook->contacts[i].phone) == 0)
                  {
                    printf("Name: %s, Phone: %s, Email: %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    return i;// return the index
                  }
              }
              break;
        case 3:
              char email[50];
              printf("Enter the email : ");
              scanf("%s", email);
              for(int i = 0; i < addressBook->contactCount; i++)
              {
                  if(strcmp(email, addressBook->contacts[i].email) == 0)
                  {
                    printf("Name: %s, Phone: %s, Email: %s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    return i;// return the index
                  }
              }
              break;
            default:
              break;

    }
    return -1;
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int ret = searchContact(addressBook);
    if(ret == -1)
    {
        printf("Contact not found\n");
        return ;
    }
    printf("1. Edit name\n2. Edit phone\n3. Edit mail id.\nEnter the choice : ");
    int choice = 0;
    scanf("%d", &choice);
    switch (choice)
    {
        case 1:
        {
            char name[50];
            do
            {
            printf("Enter the name : ");
            scanf(" %[^\n]", name);
            } 
            //validate the name -> 1 -> valid name
                            //-> 0 -> not a valid name
            while(valid_name(name) == 0);               
            strcpy(addressBook->contacts[ret].name, name);
            break;
        }
         case 2:
        {
            char phone[20];
            
            do
            {
               printf("Enter the phone number : ");
                scanf(" %[^\n]", phone);
            } while (valid_phone(addressBook, phone) == 0);
            
            strcpy(addressBook->contacts[ret].phone, phone);
            break;
        }
         case 3:
        {
            char email[50];
            do
            {
                 printf("Enter the email id  : ");
                 scanf(" %[^\n]", email);
            } while (valid_email(addressBook, email) == 0);
            
            strcpy(addressBook->contacts[ret].email, email);
            break;
        }
        default:
              printf("Invalid choice\n");
              break;
    }

    printf("Name: %s, Phone: %s, Email: %s\n", addressBook->contacts[ret].name, addressBook->contacts[ret].phone, addressBook->contacts[ret].email);
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int ret = searchContact(addressBook);
    for(int i = ret; i < addressBook->contactCount; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }
    addressBook->contactCount--;
}
int valid_name(char *name)
{
   int i = 0;
   while(name[i] != '\0')
   {
    if(!((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z')|| (name[i] == ' ')))
    {
        return 0;
    }
    i++;
   }
   return 1;
}
int valid_phone(AddressBook *addressBook, char *phone)
{
   int i = 0;
   while(phone[i] != '\0')
   {
    if(phone[i] < '0' || phone[i] > '9')
    {
        return 0;
    }
    i++;
   }
   if(i != 10)
   {
    return 0;
   }
   for(int j = 0; j < addressBook-> contactCount; j++)
   {
    if(strcmp(phone, addressBook->contacts[j].phone) == 0)
    {
        return 0;
    }
   }
   return 1;
}
int valid_email(AddressBook *addressBook, char *email)
{
   int at = 0;

for(int i = 0; email[i] != '\0'; i++)
{
    if(email[i] == '@')
    {
        at++;
    }
}

if(at != 1)
{
    return 0;
}

if(strstr(email, ".com") == NULL)
{
    return 0;
}

for(int i = 0; i < addressBook->contactCount; i++)
{
    if(strcmp(email, addressBook->contacts[i].email) == 0)
    {
        return 0;
    }
}

return 1;
}