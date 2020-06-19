#include <stdio.h>
#include <stdbool.h>

typedef struct item
{
    char name[10];
    char description[80];
    struct item *next;
} ITEM;

void display(ITEM *head);
ITEM *insertItem(ITEM *head, char name[], char description[]);
ITEM *removeByName(ITEM *head, char name[]);
bool isEmpty(ITEM *head);
int getItemNum(ITEM *head);
ITEM * get(ITEM *head, char name[]);
void freeLinkList(ITEM *head);
