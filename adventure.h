#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

#include "rooms.h"
#include "keyword.h"


typedef struct backpack
{
    char name[20];
    char description[80];
    ITEM *items;
	bool omen;
} BACKPACK;

int getRandomRoom(int low, int high);
bool changeLocationEvent( ROOM startRoom, directionEnum toFromDirection[] );
void freeAllMemory( );
bool checkStatus (BACKPACK avatarBag, roomEnum currentLocation );



