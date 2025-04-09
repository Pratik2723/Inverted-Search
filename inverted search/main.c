/*
Name : Pratik Jadhav
Batch : 24021G

*/
#include "main.h"


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Error: Insufficient arguments\nUsage: ./a.out file1.txt file2.txt ...\n");
        return 1;
    }

    f_list *head = NULL;
    m_node arr[28] = {0};

    if (read_and_validate(argc, argv, &head) == e_failure)
    {
        printf("Error: Failed to read and validate files\n");
        return 1;
    }

    int choice, created = 0;
    char proceed;
    do
    {
        printf("\n1. Create Database\n2. Display Database\n3. Search Database\n4. Save Database\n5. Update Database\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (created)
            {
                printf("Error: Database already created. Use update or restart the program.\n");
                break;
            }
            if (create_db(head, arr) == e_success)
            {
                printf("Database created successfully.\n");
                created = 1;
            }
            else
                printf("Error: Failed to create database.\n");
            break;
        case 2:
            display_db(arr);
            break;
        case 3:
            if (search_db(arr) == DATA_NOT_FOUND)
                printf("Word not found in database.\n");
            break;
        case 4:
            if (save_db(arr) == e_success)
                printf("Database saved successfully.\n");
            else
                printf("Error: Failed to save database.\n");
            break;
        case 5:
            if (update_db(arr) == e_success)
                printf("Database updated successfully.\n");
            else
                printf("Error: Failed to update database.\n");
            break;
        case 6:
            printf("Exiting the program.\n");
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }

        printf("Do you want to continue? (y/n): ");
        scanf(" %c", &proceed);
    } while (proceed == 'y' || proceed == 'Y');

    return 0;
}
