#include <unistd.h>
#include <stdio.h>
#include "mini_lib.h"

void delete_element_myfiles_list(MYFILE *file) {
    MYFILES_ELEMENT *current_file = myfiles_list;
    MYFILES_ELEMENT *previous_file;

    // If head node itself holds the key to be deleted
    if (current_file != NULL && current_file->file == file) {
        myfiles_list = current_file->next_file; // Changed head
        mini_free(current_file); // free old head
        return;
    }
 
    // Search for the key to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    while (current_file != NULL && current_file->file != file) {
        previous_file = current_file;
        current_file = current_file->next_file;
    }
 
    // If key was not present in linked list
    if (current_file == NULL)
        return;
 
    // Unlink the node from linked list
    previous_file->next_file = current_file->next_file;
    mini_free(current_file->file);
    mini_free(current_file); // Free memory
}