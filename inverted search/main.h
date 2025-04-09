#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Status codes
typedef enum
{
    e_success,
    e_failure,
    DATA_NOT_FOUND
} status;

// Structure for file list
typedef struct file_list
{
    char file_name[50];
    struct file_list *next;
} f_list;

// Sub-node structure
typedef struct sub_node
{
    char file_name[50];
    int word_count;
    struct sub_node *s_sub_link;
} s_node;

// Main-node structure
typedef struct main_node
{
    char word[30];
    int file_count;
    struct main_node *m_main_link;
    struct sub_node *m_sub_link;
} m_node;

// Function prototypes
status read_and_validate(int argc, char *argv[], f_list **head);
status create_db(f_list *head, m_node *arr);
status display_db(m_node *arr);
status search_db(m_node *arr);
status save_db(m_node *arr);
status update_db(m_node *arr);
status open_files(char *file_name);

#endif // MAIN_H
