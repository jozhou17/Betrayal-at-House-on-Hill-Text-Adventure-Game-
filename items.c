#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "items.h"

/*
   goal: free all items in linked list
   param ITEM *head: a head pointer of struct ITEM defined in items.h
*/
void freeLinkList(ITEM *head)
{
  if (head != NULL )
  {
   printf("\n Free memory for link list and head : %s \n", head->name);
  }

   ITEM *temp;

   while (head != NULL)
   {
      temp = head;
      head = head->next;
      free(temp); 
   }
}

//is list empty
bool isEmpty(ITEM *head)
{
   return head == NULL;
}
// goal: return number of items
int getItemNum(ITEM *head)
{
   int cnt = 0;
   ITEM *cur;

   for (cur = head; cur != NULL; cur = cur->next)
   {
      cnt++;
   }
   return cnt;
}

/*
   goal: remove an item that matches name in parameter
*/
ITEM *removeByName(ITEM *head, char name[])
{
   ITEM *cur = head;
   ITEM *previous = NULL;

   //if list is empty
   if (head == NULL)
   {
      return NULL;
   }
   while (strcmp(cur->name, name) != 0)
   {
      //if tail
      if (cur->next == NULL)
      {
         return NULL;
      }
      else
      {
         // record previous
         previous = cur;
         //go to next
         cur = cur->next;
      }
   }

   // match found
   if (cur == head)
   {
      head = head->next;
   }
   else
   {
      previous->next = cur->next;
   }
   free(cur);
   return head;
}
//goal: insert item into the front of the list
ITEM *insertItem(ITEM *head, char name[], char description[])
{
   //create a link and insert it before the head
   ITEM *cur = (ITEM *)malloc(sizeof(ITEM));
   strcpy(cur->name, name);
   strcpy(cur->description, description);
   cur->next = head;

   //point first to new first node
   head = cur;

   return head;
}

void display(ITEM *head)
{
   ITEM *cur = head;
   printf("\n ---Display item---- \n ");

   //start from the beginning
   while (cur != NULL)
   {
      printf("(%s, %s) ", cur->name, cur->description);
      cur = cur->next;
      printf("\n");
   }
   printf(" --------------");
}

//goal: returns a pointer to a node that matches desired name in parameter
ITEM *get(ITEM *head, char name[])
{
   ITEM *cur = head;

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