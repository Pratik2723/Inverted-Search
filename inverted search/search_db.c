#include"main.h"

status search_db(m_node *arr)
{
    char word[30];
    printf("Enter the word you want to search: ");
    scanf("%s", word);

    int key = tolower(word[0]) % 97;
    if (key < 0 || key > 25)
        key = 26;

    m_node *current = &arr[key];
    if (current->m_main_link == NULL && strcmp(current->word, word) != 0)
        return DATA_NOT_FOUND;

    while (current != NULL)
    {
        if (strcmp(current->word, word) == 0)
        {
            printf("The word '%s' is present in %d files:\n", word, current->file_count);
            s_node *sub_current = current->m_sub_link;
            while (sub_current != NULL)
            {
                printf(" - %s: %d times\n", sub_current->file_name, sub_current->word_count);
                sub_current = sub_current->s_sub_link;
            }
            return e_success;
        }
        current = current->m_main_link;
    }
    return DATA_NOT_FOUND;
}
