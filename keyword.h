#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct command  {
    char name[10];
    char description[80];
    struct command *next;
} COMMAND;

COMMAND * search(COMMAND *head, char name[]);
COMMAND* insertMenu(COMMAND *head, char name[], char description[]);
bool find(COMMAND *head, char name[]);
COMMAND* init_menu(  );
void showMenu(COMMAND *head);
void freeCommandList(COMMAND *head);



