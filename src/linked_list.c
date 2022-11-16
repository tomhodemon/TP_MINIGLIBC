#include <locale.h>
#include "mini_lib.h"

void delete_element_myfiles_list(MYFILE *file) {
    MYFILES_ELEMENT *current_file = myfiles_list;
    MYFILES_ELEMENT *previous_file;

    if (current_file != NULL && current_file->file == file) {
        myfiles_list = current_file->next_file; // Changed head
        mini_free(current_file->file);
        if(current_file->file->ind_read != -1) mini_free(current_file->file->buffer_read);
        if(current_file->file->ind_write != -1) mini_free(current_file->file->buffer_write);
        mini_free(current_file);
        return;
    }
     while (current_file != NULL && current_file->file != file) {
        previous_file = current_file;
        current_file = current_file->next_file;
    }
 
    if (current_file == NULL)
        return;
 
    previous_file->next_file = current_file->next_file;
    mini_free(current_file->file);
    if(current_file->file->ind_read != -1) mini_free(current_file->file->buffer_read);
    if(current_file->file->ind_write != -1) mini_free(current_file->file->buffer_write);
    mini_free(current_file);
}