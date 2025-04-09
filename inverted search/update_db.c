#include"main.h"

status update_db(m_node *arr)
{
    char file[30];
    printf("Enter the file name to update the database: ");
    scanf("%s", file);

    FILE *fptr = fopen(file, "r");
    if (fptr == NULL)
    {
        printf("Error: File not found.\n");
        return e_failure;
    }

    char buffer[256];
    while (fscanf(fptr, "%s", buffer) != EOF)
    {
        if (buffer[0] != '#')
        {
            fclose(fptr);
            return e_failure;
        }

        int key = atoi(strtok(&buffer[1], ";"));
        m_node *main_node = malloc(sizeof(m_node));
        if (main_node == NULL)
            return e_failure;

        main_node->file_count = atoi(strtok(NULL, ";"));
        strcpy(main_node->word, strtok(NULL, ";"));
        main_node->m_main_link = NULL;

        s_node *sub_head = NULL;
        for (int i = 0; i < main_node->file_count; i++)
        {
            s_node *sub_node = malloc(sizeof(s_node));
            if (sub_node == NULL)
                return e_failure;

            strcpy(sub_node->file_name, strtok(NULL, ";"));
            sub_node->word_count = atoi(strtok(NULL, ";"));
            sub_node->s_sub_link = sub_head;
            sub_head = sub_node;
        }
        main_node->m_sub_link = sub_head;

        m_node *current = &arr[key];
        if (current->m_main_link == NULL && current->word[0] == '\0')
        {
            arr[key] = *main_node;
        }
        else
        {
            while (current->m_main_link != NULL)
                current = current->m_main_link;

            current->m_main_link = main_node;
        }
    }
    fclose(fptr);
    return e_success;
}
