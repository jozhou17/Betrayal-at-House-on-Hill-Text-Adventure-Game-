#include <stdio.h>
#include <string.h>
#include "rooms.h"


// goal: initializes all rooms individually and sets the room's neighbors to empty 
ROOM *init_rooms()
{
	allRoom[0].key = start_room;
	strcpy(allRoom[0].name, "start room");
	strcpy(allRoom[0].description, "This is the start room");
	allRoom[0].items = NULL;
	allRoom[0].event = false;
	allRoom[0].omen = false;

	allRoom[1].key = one;
	strcpy(allRoom[1].name, "room one");
	strcpy(allRoom[1].description, "This is the room one");
	allRoom[1].items = NULL;
	allRoom[1].items = insertItem(allRoom[1].items, "key", "this is public key");
	allRoom[1].event = false;
	allRoom[1].omen = false;

	allRoom[2].key = two;
	strcpy(allRoom[2].name, "room two");
	strcpy(allRoom[2].description, "This is the room two");
	allRoom[2].items = NULL;
	allRoom[2].items = insertItem(allRoom[2].items, "pc", "this is pc");
	allRoom[2].event = false;
	allRoom[2].omen = false;

	allRoom[3].key = three;
	strcpy(allRoom[3].name, "room three");
	strcpy(allRoom[3].description, "This is the room three");
	allRoom[3].items = NULL;
	allRoom[3].event = true;
	allRoom[3].omen = false;

	allRoom[4].key = four;
	strcpy(allRoom[4].name, "room four");
	strcpy(allRoom[4].description, "This is the  room four");
	allRoom[4].items = NULL;
	allRoom[4].event = true;
	allRoom[4].omen = false;

	allRoom[5].key = five;
	strcpy(allRoom[5].name, "room five");
	strcpy(allRoom[5].description, "This is the room five");
	allRoom[5].items = NULL;
	allRoom[5].event = false;
	allRoom[5].omen = true;

	allRoom[6].key = six;
	strcpy(allRoom[6].name, "room six");
	strcpy(allRoom[6].description, "this is the room six");
	allRoom[6].items = NULL;
	allRoom[6].event = false;
	allRoom[6].omen = true;

	for (int i = 0; i < 7; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			allRoom[i].neighbours[j] = empty;
		}
	}

	return allRoom;
}

//prints room information so player can see what rooms are north,east,west,etc of them
void show(ROOM *room)
{
	printf("\n room name : %s,   %s ", room->name, room->description);

	display(room->items);

	printf("\n current room neighbor info :  \n");

	for (int i = 0; i < 6; ++i)
	{
		switch (i)
		{
		case 0:
			printf("  north :  ");
			break;

		case 1:
			printf(" south :  ");
			break;

		case 2:
			printf(" east  :  ");
			break;

		case 3:
			printf(" west  :  ");
			break;

		case 4:
			printf(" up    :  ");
			break;

		case 5:
			printf(" down  :  ");
			break;

		default:
			printf(" \n ");
			break;
		}

		switch (room->neighbours[i])
		{
		case 0:
			printf("start_room \n ");
			break;

		case 1:
			printf("room one \n ");
			break;

		case 2:
			printf("room two \n ");
			break;

		case 3:
			printf("room three \n ");
			break;

		case 4:
			printf("room four \n ");
			break;

		case 5:
			printf("room five \n ");
			break;

		case 6:
			printf("room six \n ");
			break;

		default:
			printf("empty \n ");
			break;
		}

	} // end for

	printf("\n%s ",   (room->event == true ? "The event is TRUE ! " : "The event is false "));
	printf("\n%s \n", (room->omen == true ?  "The omen is TRUE ! " : "The omen is false "));
}
