#include "main.h"

status read_and_validate(int argc, char *argv[], f_list **head)
{
    if (argc < 2)
    {
        printf("Error: No files provided as input.\n");
        return e_failure;
    }

    for (int i = 1; i < argc; i++)
    {
        // Check if the file is valid
        if (open_files(argv[i]) == e_success)
        {
            // Create a new node for the valid file
            f_list *new_node = malloc(sizeof(f_list));
            if (new_node == NULL)
            {
                printf("Error: Memory allocation failed for file node.\n");
                return e_failure;
            }

            // Initialize the new node
            strcpy(new_node->file_name, argv[i]);
            new_node->next = NULL;

            if (*head == NULL)
            {
                // Add the first file to the list
                *head = new_node;
            }
            else
            {
                // Traverse the list to check for duplicates and append
                f_list *temp = *head;
                f_list *prev = NULL;
                int is_duplicate = 0;

                while (temp != NULL)
                {
                    if (strcmp(temp->file_name, argv[i]) == 0)
                    {
                        printf("Error: Duplicate file '%s' detected. Skipping.\n", argv[i]);
                        free(new_node);
                        is_duplicate = 1;
                        break;
                    }
                    prev = temp;
                    temp = temp->next;
                }

                if (!is_duplicate)
                {
                    prev->next = new_node;
                }
            }
        }
    }

    if (*head == NULL)
    {
        printf("Error: No valid files provided.\n");
        return e_failure;
    }

    printf("All valid files have been successfully validated and stored.\n");
    return e_success;
}


status open_files(char *file_name)
{
    // Attempt to open the file
    FILE *fptr = fopen(file_name, "r");
    if (fptr == NULL)
    {
        printf("Error: File '%s' does not exist or cannot be opened.\n", file_name);
        return e_failure;
    }

    // Check for .txt extension
    if (strstr(file_name, ".txt") == NULL || strcmp(strstr(file_name, ".txt"), ".txt") != 0)
    {
        printf("Error: File '%s' does not have a valid .txt extension.\n", file_name);
        fclose(fptr);
        return e_failure;
    }

    // Check if the file is empty
    fseek(fptr, 0, SEEK_END);
    if (ftell(fptr) == 0)
    {
        printf("Error: File '%s' is empty.\n", file_name);
        fclose(fptr);
        return e_failure;
    }

    // Close the file and return success
    fclose(fptr);
    return e_success;
}
