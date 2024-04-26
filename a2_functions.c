/********* definitions.c ********
    Student Name 	=  Elaine Huang
    Student Number	=  101273300
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "a2_nodes.h"
#include "a2_functions.h"

// Your solution goes here

/*
   Function that creates a new user and adds it to a sorted (ascending order) linked list at
   the proper sorted location. Return the head of the list.
*/
user_t *add_user(user_t *users, const char *username, const char *password)
{
   user_t *new_user = malloc(sizeof(user_t));
   assert(new_user != NULL);
   new_user->next = NULL;
   new_user->friends = NULL;
   new_user->posts = NULL;
   strcpy(new_user->username, username);
   strcpy(new_user->password, password);

   if (users == NULL)
   {
      new_user->next = users;
      return new_user;
   }
   user_t *temp = users;
   while (temp->next != NULL && strcmp(new_user->username, temp->username) > 0)
   {
      temp = temp->next;
   }
   new_user->next = temp->next;
   temp->next = new_user;

   return users;
}
/*
   Function that searches if the user is available in the database
   Return a pointer to the user if found and NULL if not found.
*/
user_t *find_user(user_t *users, const char *username)
{
   assert(users != NULL);
   assert(users->username != NULL);
   while (users != NULL && users->username != NULL && (users->username, username) != 0)
   {
      if (strcmp(users->username, username) == 0)
      {
         return users;
      }
      users = users->next;
   }
   return NULL;
}
/*
   Function that creates a new friend's node.
   Return the newly created node.
*/
friend_t *create_friend(const char *username)
{
   friend_t *friend = malloc(sizeof(friend_t));
   assert(friend != NULL);

   strcpy(friend->username, username);
   return friend;
}

/*
   Function that links a friend to a user. The friend's name should be added into
   a sorted (ascending order) linked list.
*/
void add_friend(user_t *user, const char *friend)
{
   friend_t *added_friend = create_friend(friend);

   if (user->friends == NULL || strcmp(friend, user->friends->username) < 0)
   {
      added_friend->next = user->friends;
      user->friends = added_friend;
   }
   else
   {
      friend_t *current = user->friends;
      for (; current->next != NULL && strcmp(added_friend->username, current->next->username) > 0; current = current->next)
      {
      }
      added_friend->next = current->next;
      current->next = added_friend;
   }
}

/*
   Function that removes a friend from a user's friend list.
   Return true of the friend was deleted and false otherwise.
*/
_Bool delete_friend(user_t *user, char *friend_name)
{
   friend_t *current = user->friends;
   friend_t *previous = NULL;
   while (current != NULL && strcmp(current->username, friend_name) != 0)
   {
      previous = current;
      current = current->next;
   }

   if (current != NULL)
   {
      if (previous != NULL)
      {
         previous->next = current->next;
      }
      else
      {
         user->friends = current->next;
      }
      free(current);
      return true;
   }
   else
   {
      printf("\nInvalid friend's name");

      return false;
   }

   return 0;
}

/*
   Function that creates a new user's post.
   Return the newly created post.
*/
post_t *create_post(const char *text)
{
   post_t *new_post = malloc(sizeof(post_t));
   assert(new_post != NULL);
   strcpy(new_post->content, text);
   new_post->next = NULL;

   return new_post;
}

/*
   Function that adds a post to a user's timeline. New posts should be added following
   the stack convention (LIFO) (i.e., to the beginning of the Posts linked list).
*/
void add_post(user_t *user, const char *text)
{
   post_t *added_post = create_post(text);
   added_post->next = user->posts;
   user->posts = added_post;
}

/*
   Function that removes a post from a user's list of posts.
   Return true if the post was deleted and false otherwise.
*/
_Bool delete_post(user_t *user, int number)
{
   post_t *to_del = user->posts;
   int count = 0;
   if (number == 1)
   {
      user->posts = to_del->next;
      free(to_del);
      printf("\nPost %d was deleted successfully!", number);
      return true;
   }
   while (to_del != NULL && count < number - 2)
   {
      to_del = to_del->next;
      count++;
   }

   if (to_del == NULL || to_del->next == NULL)
   {
      printf("\nInvalid post's number");
      return false;
   }
   post_t *temp = to_del->next->next;
   free(to_del->next);
   to_del->next = temp;
   printf("\nPost %d was deleted successfully!", number);
   return true;

   return 0;
}

/*
   Function that  displays a specific user's posts
*/
void display_user_posts(user_t *user)
{
   unsigned short int counter = 1;

   post_t *user_posts = user->posts;
   if (user_posts == NULL)
   {
      printf("\nNo posts available for %s.", user->username);
   }
   else
   {
      for (; user_posts != NULL; user_posts = user_posts->next)
      {
         printf("\n%i- %s: %s", counter, user->username, user_posts->content);
         counter++;
      }
   }
}

/*
   Function that displays a specific user's friends
*/
void display_user_friends(user_t *user)
{
   unsigned short int counter = 1;
   friend_t *user_friends = user->friends;
   if (user_friends == NULL)
   {
      printf("\nNo friends available for %s.", user->username);
   }
   while (user_friends != NULL)
   {
      printf("\n%d- %s", counter, user_friends->username);
      user_friends = user_friends->next;
      counter++;
   }
}
/*
   Function that displays all the posts of 2 users at a time from the database.
   After displaying 2 users' posts, it prompts if you want to display
   posts of the next 2 users.
   If there are no more post or the user types “n” or “N”, the function returns.
*/
void display_all_posts(user_t *users)
{
   unsigned short int counter = 0;
   char choice;

   user_t *user = users;
   while (user != NULL)
   {
      if (counter < 2)
      {
         display_user_posts(user);
         user = user->next;
         counter++;
      }
      else
      {
         printf("\nDo you want to display next 2 users posts? (Y/N): ");
         scanf(" %c", &choice);
         if (choice == 'Y' || choice == 'y')
         {
            counter = 0;
            printf("\n");
         }
         else if (choice == 'N' || choice == 'n')
         {
            break;
         }
         else
         {
            printf("\nInvalid input. Please try again.");
         }
      }
   }
}

/*
   Fucntion that free all users from the database before quitting the application.
*/
void teardown(user_t *users)
{
   user_t *del;
   for (; users != NULL; users = users->next)
   {
      del = users;
      free(del);
   }
}

/*
   Function that prints the main menu with a list of options for the user to choose from
*/
void print_menu()
{
   printf("\n***********************************************************\n                      MAIN MENU:\n***********************************************************");
   printf("\n1. Register a new User\n2. Manage a user's profile (change password)\n3. Manage a user's posts (display/add/remove)\n4. Manage a user's friends (display/add/remove)\n5. Display All posts\n6. Exit");
   printf("\n\nEnter your choice: ");
}

/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
   user_t *users = NULL;
   char buffer[500];
   fgets(buffer, sizeof(buffer), file); // Read and discard the header line
   int count = 0;
   for (int i = 0; i < num_users; i++)
   {
      fgets(buffer, sizeof(buffer), file);
      buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

      char *token = strtok(buffer, ",");
      char *token2 = strtok(NULL, ",");
      users = add_user(users, token, token2);
      char *username = token;

      token = strtok(NULL, ",");

      user_t *current_user = users;
      for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
         ;

      while (token != NULL && strcmp(token, ",") != 0 && count < 3)
      {
         if (strcmp(token, " ") != 0)
         {
            add_friend(current_user, token);
         }
         token = strtok(NULL, ",");
         count++;
      }
      count = 0;

      // token = strtok(NULL, ",");
      while (token != NULL && strcmp(token, ",") != 0)
      {
         add_post(current_user, token);
         token = strtok(NULL, ",");
      }
   }
   return users;
}
