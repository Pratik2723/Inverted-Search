#include "main.h"

status create_db(f_list *head, m_node *arr)
{
    if (head == NULL || arr == NULL)
    {
        printf("Error: Invalid input to create_db.\n");
        return e_failure;
    }

    f_list *temp = head;
    char word[30];
    int key;

    while (temp != NULL)
    {
        // Open the file
        FILE *fptr = fopen(temp->file_name, "r");
        if (fptr == NULL)
        {
            printf("Error: Unable to open file '%s'.\n", temp->file_name);
            return e_failure;
        }

        // Read words from the file
        while (fscanf(fptr, "%s", word) != EOF)
        {
            // Calculate index for the array (handle alphabetic and non-alphabetic cases)
            key = tolower(word[0]) % 97;

            m_node *main_node = &arr[key];

            if (main_node->m_main_link == NULL && main_node->word[0] == '\0')
            {
                // Initialize the main node for a new word
                main_node->file_count = 1;
                strcpy(main_node->word, word);

                // Create a sub-node
                s_node *sub_node = malloc(sizeof(s_node));
                if (sub_node == NULL)
                {
                    printf("Error: Memory allocation failed.\n");
                    fclose(fptr);
                    return e_failure;
                }

                sub_node->word_count = 1;
                strcpy(sub_node->file_name, temp->file_name);
                sub_node->s_sub_link = NULL;

                main_node->m_sub_link = sub_node;
                main_node->m_main_link = NULL;
            }
            else
            {
                // Traverse the main nodes to find or create a match
                m_node *current = main_node;
                m_node *prev_main = NULL;
                int word_found = 0;

                while (current != NULL)
                {
                    if (strcmp(current->word, word) == 0)
                    {
                        // Word found in main node
                        word_found = 1;

                        // Traverse sub-nodes to update or create a match
                        s_node *sub_current = current->m_sub_link;
                        s_node *sub_prev = NULL;

                        while (sub_current != NULL)
                        {
                            if (strcmp(sub_current->file_name, temp->file_name) == 0)
                            {
                                // File found in sub-node
                                sub_current->word_count++;
                                break;
                            }
                            sub_prev = sub_current;
                            sub_current = sub_current->s_sub_link;
                        }

                        if (sub_current == NULL)
                        {
                            // Create a new sub-node
                            s_node *new_sub_node = malloc(sizeof(s_node));
                            if (new_sub_node == NULL)
                            {
                                printf("Error: Memory allocation failed.\n");
                                fclose(fptr);
                                return e_failure;
                            }

                            new_sub_node->word_count = 1;
                            strcpy(new_sub_node->file_name, temp->file_name);
                            new_sub_node->s_sub_link = NULL;

                            current->file_count++;
                            sub_prev->s_sub_link = new_sub_node;
                        }
                        break;
                    }

                    prev_main = current;
                    current = current->m_main_link;
                }

                if (!word_found)
                {
                    // Create a new main node
                    m_node *new_main_node = malloc(sizeof(m_node));
                    if (new_main_node == NULL)
                    {
                        printf("Error: Memory allocation failed.\n");
                        fclose(fptr);
                        return e_failure;
                    }

                    // Create a new sub-node
                    s_node *new_sub_node = malloc(sizeof(s_node));
                    if (new_sub_node == NULL)
                    {
                        printf("Error: Memory allocation failed.\n");
                        fclose(fptr);
                        return e_failure;
                    }

                    // Initialize main node
                    new_main_node->file_count = 1;
                    strcpy(new_main_node->word, word);
                    new_main_node->m_sub_link = new_sub_node;
                    new_main_node->m_main_link = NULL;

                    // Initialize sub-node
                    new_sub_node->word_count = 1;
                    strcpy(new_sub_node->file_name, temp->file_name);
                    new_sub_node->s_sub_link = NULL;

                    prev_main->m_main_link = new_main_node;
                }
            }
        }

        fclose(fptr);
        temp = temp->next;
    }
    return e_success;
}
