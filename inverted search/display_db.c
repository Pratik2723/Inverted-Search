#include"main.h"


status display_db(m_node *arr)
{
    printf("%s\t%s\t  %s\t%s\t%s\n", "Index", "Word", "Filecount", "Files Name", "Wordcount");
    for (int key = 0; key < 27; key++) // Iterate over each index
    {
        m_node *current = &arr[key];
        if (current->m_main_link == NULL && current->word[0] == '\0') // Skip uninitialized entries
            continue;

        while (current != NULL)
        {
            printf("[%d]\t%s\t\t%d\t", key, current->word, current->file_count);
            s_node *sub_current = current->m_sub_link;
            while (sub_current != NULL)
            {
                printf("%s -> %d\t", sub_current->file_name, sub_current->word_count);
                sub_current = sub_current->s_sub_link;
            }
            printf("\n");
            current = current->m_main_link;
        }
    }
    return e_success;
}
