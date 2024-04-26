/********* main.c ********
    Student Name 	=   Elaine Huang
    Student Number	=   101273300
*/

// Includes go here
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a2_nodes.h"
#include "a2_functions.h"

int main()
{
    /******** DONT MODIFY THIS PART OF THE CODE ********/
    /* THIS CODE WILL LOAD THE DATABASE OF USERS FROM THE FILE
       AND GENERATE THE STARTING LINKED LIST.
    */
    FILE *csv_file = fopen("user_details.csv", "r"); // details
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);

    fclose(csv_file);
    /******** DONT MODIFY THIS PART OF THE CODE ********/

    /* IMPORTANT: You must use the users linked list created in the code above.
                  Any new users should be added to that linked list.
    */

    // Your solution goes here
    user_t *new_user = users;
    char username[20];
    char password[15];
    char text[150];
    unsigned short int choice;
    unsigned short int post_choice;
    unsigned short int counter;
    do
    {
    
    print_menu();
    scanf("%i", &choice);

    
    
    while (choice > 0 || choice <= 6)
    {
        if (choice == 1)
        {
            printf("\nEnter a username: ");
            scanf("%s", &username);
            printf("\nEnter an upto 15 characters password: ");
            scanf("%s", &password);
            add_user(users, username, password);
            printf("\n**** User Added! ****");
        }
        else if (choice == 2)
        {
            printf("\nEnter username to update their password: ");
            scanf("%s", &username);
            new_user = find_user(users, username);
            if (new_user != NULL)
            {
                printf("\nEnter a new password that is upto 15 characters: ");
                scanf("%s", &password);
                strcpy(new_user->password, password);
                printf("\n**** Password changed! ****\n");
            }
            else
            {
                printf("\n------------------------------------------------\n                      User not found\n------------------------------------------------");
            }
        }
        else if (choice == 3)
        {
            printf("\nEnter username to manage their posts: ");
            scanf("%s", &username);
            new_user = find_user(users, username);
            printf("\n------------------------------------------------");
            printf("                %s's posts", new_user->username);
            display_user_posts(new_user);
            if (new_user != NULL)
            {
                do
                {
                    printf("\n------------------------------------------------\n\n1. Add a new user post\n2. Remove a users post\n3. Return to main menu\n\nYour choice: ");

                    scanf("%i", &choice);
                    switch (choice)
                    {
                    case 1:
                        printf("\nEnter your post content: ");
                        scanf(" %[^\n]s", text);
                        add_post(new_user, text);
                        printf("\nPost added to your profile.");
                        printf("\n------------------------------------------------");
                        printf("                %s's posts", new_user->username);
                        printf("\n------------------------------------------------");
                        display_user_posts(new_user);

                        break;
                    case 2:
                        printf("\nWhich post you want to delete?");
                        scanf("%i", &post_choice);
                        delete_post(new_user, post_choice);
                        display_user_posts(new_user);

                        break;
                    case 3:
                        break;

                    default:
                        printf("\nInvalid choice. Please try again.");
                        break;
                    }
                } while (choice != 3);
            }
            else
            {
                printf("\n\n------------------------------------------------\n                      User not found\n------------------------------------------------");
            }
        }
        else if (choice == 4)
        {
            printf("\nEnter username to manage their friends: ");
            scanf("%s", &username);
            new_user = find_user(users, username);
            if (new_user != NULL)
            {
                do
                {
                    counter = 1;
                    printf("\n------------------------------------------------");
                    printf("                %s's friends", new_user->username);
                    printf("\n------------------------------------------------\n\n1. Display all user's friends\n2. Add a new friend\n3. Delete a friend\n4. Return to main menu\n\nYour choice: ");

                    scanf("%i", &choice);
                    switch (choice)
                    {
                    case 1:
                        printf("\nList of %s's friends: ", new_user->username);
                        display_user_friends(new_user);
                        break;
                    case 2:
                        printf("\nEnter a new friends' name: ");
                        scanf("%s", &username);
                        add_friend(new_user, username);
                        printf("\nFriend added to the list.");
                        break;
                    case 3:
                        printf("\nList of %s's friends: ", new_user->username);
                        display_user_friends(new_user);
                        printf("\n\nEnter a friend's name to delete: ");
                        scanf("%s", username);
                        delete_friend(new_user, username);
                        for (friend_t *temp = new_user->friends; temp != NULL; temp = temp->next, counter++)
                        {
                        }
                        printf("\nList of %s's friends: ", new_user->username);
                        display_user_friends(new_user);
                        break;
                    case 4:
                        break;

                    default:
                        printf("\nInvalid choice. Please try again.");
                        break;
                    }
                } while (choice != 4);
            }
            else
            {
                printf("\n\n------------------------------------------------\n                      User not found\n------------------------------------------------");
            }
        }
        else if (choice == 5)
        {
            display_all_posts(users);
            break;
        }
        else if (choice == 6)
        {
            printf("\n*******************************************\n     Thank you for using Text-Based Facebook\n                               Goodbye!\n*******************************************");
            teardown(users);
        }
        else{
            printf("\nInvalid choice. Please try again.");
        }

        print_menu();
        scanf("%i", &choice);

        
    }}
    while (choice > 0 || choice <= 6);
        
            print_menu();
            scanf("%i", &choice);
        
}