#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "keyword.h"

//goal: traverses through command list and frees all nodes
void freeCommandList(COMMAND *head)
{
	if ( head != NULL)
    {
	 printf("\n Free memory for command list %s \n", head->name);
	}
	COMMAND *temp;
	
	while ( head != NULL)
	{
		temp = head;
		head = head-> next;
		free(temp);
	}
}
/*
   goal: insert a new command into the menu
   param COMMAND *head: pointer to a COMMAND struct
   param name: name of command to be inserted
   param description: description of command to be inserted 
*/
COMMAND *insertMenu(COMMAND *head, char name[], char description[])
{
   //create a link and insert it before the head
   COMMAND *cur = (COMMAND *)malloc(sizeof(COMMAND));
   strcpy(cur->name, name);
   strcpy(cur->description, description);
   cur->next = head;

   //point first to new first node
   head = cur;
   return head;
}

//goal: traverse through list of COMMANDS and return true/false depending on whether
//a given name is in the list
bool find(COMMAND *head, char name[])
{
   COMMAND *cur = head;

   if (head == NULL)
   {
      return false;
   }

   while (strcmp(cur->name, name) != 0)
   {
      if (cur->next == NULL)
      {
         return false;
      }
      else
      {
         cur = cur->next;
      }
   }

   return true;
}
// creates list of commands 
COMMAND *init_menu()
{
   COMMAND *list = NULL;
   list = insertMenu(list, "go",        " go direction from curent location");
   list = insertMenu(list, "exit",      " quit the game");
   list = insertMenu(list, "take",      " where ITEM is the name of an item in a room");
   list = insertMenu(list, "drop",      " where ITEM is the name of an item in the avatar’s inventory");
   list = insertMenu(list, "look",      " display the rooms in each direction and the items in the room");
   list = insertMenu(list, "inventory", " display items in  the avatar’s inventory ");
   list = insertMenu(list, "help",      " display menu");
   list = insertMenu(list, "add",       " add new command to menu");
   list = insertMenu(list, "search",    " search if command exist in menu");

   return list;
}


void showMenu(COMMAND *head)
{
   COMMAND *cur = head;
   printf("\n-----------------Display menu----------------\n");

   while (cur != NULL)
   {
      printf("(%s  ) ", cur->name);
      cur = cur->next;
      printf("\n");
   }
   printf("--------------------------------------------------\n");
}

//goal: traverses through COMMAND list and returns a node if it matches 
// name in parameter
COMMAND * search(COMMAND *head, char name[])
{
   COMMAND *cur = head;

   if (head == NULL)
   {
      return NULL;
   }

   while (strcmp(cur->name, name) != 0)
   {
      if (cur->next == NULL)
      {
         return NULL;
      }
      else
      {
         cur = cur->next;
      }
   }

   return cur;
}

