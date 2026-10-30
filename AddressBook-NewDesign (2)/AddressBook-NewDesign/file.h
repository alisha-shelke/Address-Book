/*
 * File: file.h
 * Author: Alisha Shelke
 * Description: Contains declarations for file handling functions.
 */
 
#ifndef FILE_H
#define FILE_H

#include "contact.h"

void saveContactsToFile(AddressBook *addressBook);
void loadContactsFromFile(AddressBook *addressBook);

#endif
