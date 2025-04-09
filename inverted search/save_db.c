#include"main.h"

status save_db(m_node *arr)
{
    char file[30], choice;
    printf("Enter the file name to save the database: ");
    scanf("%s", file);

    FILE *fptr = fopen(file, "w");
    if (fptr == NULL)
        return e_failure;

    for (int key = 0; key < 27; key++)
    {
        m_node *current = &arr[key];
        if (current->m_main_link == NULL && current->word[0] == '\0') // Skip uninitialized entries
            continue;

        while (current != NULL)
        {
            fprintf(fptr, "#%d;%s;%d;#", key, current->word, current->file_count);
            s_node *sub_current = current->m_sub_link;
            while (sub_current != NULL)
            {
                fprintf(fptr, "%s;%d;", sub_current->file_name, sub_current->word_count);
                sub_current = sub_current->s_sub_link;
            }
            fprintf(fptr, "\n");
            current = current->m_main_link;
        }
    }
    fclose(fptr);
    return e_success;
}
