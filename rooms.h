#include <stdio.h>
#include "items.h"

typedef enum
{
    north,
    south,
    east,
    west,
    up,
    down
} directionEnum;

typedef enum
{   empty = -1,
    start_room = 0,
    one,
    two,
    three,
    four,
    five,
    six
} roomEnum;

typedef struct room
{
    roomEnum key;
    char name[20];
    char description[80];
    ITEM *items;
    roomEnum neighbours[6];
    bool event;
    bool omen;
     
} ROOM;

ROOM *init_rooms();
void show(ROOM *room);
ROOM allRoom[7];
