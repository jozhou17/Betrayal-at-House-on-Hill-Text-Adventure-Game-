#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include "adventure.h"



#define ROOM_NUM 7
#define DIR_NUM 6

const int EMPTY_PILE = -1;
const int input_size = 100;

directionEnum to_direction;
directionEnum from_direction;

roomEnum currentLocation = start_room;
COMMAND *menuList = NULL;
ROOM *allRooms = NULL;
BACKPACK avatarBag;

/*
goal: checks win status of player - omen+items+start room = win
param BACKPACK avatarBag: struct defined in adventure.h
param roomEnum currentLocation: enum defined in rooms.h
*/
bool checkStatus(BACKPACK avatarBag, roomEnum currentLocation)
{
	bool winStatus = false;

	if ((avatarBag.omen == true) &&
		(getItemNum(avatarBag.items) == 2) &&
		(currentLocation == start_room))
	{
		winStatus = true;
	}

	return winStatus;
}

/*
 goal: loops through and frees memory in all rooms, player's inventory, and command list
 after the game is copmleted
*/
void freeAllMemory()
{
	for (int i = 0; i < ROOM_NUM; ++i)
	{
		freeLinkList(allRooms[i].items);
	}
	freeLinkList(avatarBag.items);

	freeCommandList(menuList->next);
}
/*
goal: changes the player's room location and connects it to the starting room
after an event occurs
param ROOM startRoom: struct defined in rooms.h
param directionEnum toFromDirection[]: directionEnum defined in rooms.h, links rooms together
*/
bool changeLocationEvent(ROOM startRoom, directionEnum toFromDirection[])
{
	if (startRoom.neighbours[south] == empty)
	{
		toFromDirection[0] = south; //connects start room to south room
		toFromDirection[1] = north; //connects south room to start room
		printf("\nThe NEXT Room will be move to the **SOUTH** of the  starting room due to a **EVENT**\n\n");
		return true;
	}
	else if (startRoom.neighbours[east] == empty)
	{
		toFromDirection[0] = east;
		toFromDirection[1] = west;
		printf("\nThe NEXT Room will be move to the **EAST** of the  starting room due to a **EVENT**\n\n");
		return true;
	}
	else if (startRoom.neighbours[west] == empty)
	{
		toFromDirection[0] = west;
		toFromDirection[1] = east;
		printf("\nThe NEXT Room will be move to the **WEST** of the  starting room due to a **EVENT**\n\n");
		return true;
	}
	else if (startRoom.neighbours[up] == empty)
	{
		toFromDirection[0] = up;
		toFromDirection[1] = down;
		printf("\nThe NEXT Room will be move to the **UP** of the  starting room due to a **EVENT**\n\n");
		return true;
	}
	else if (startRoom.neighbours[down] == empty)
	{
		toFromDirection[0] = down;
		toFromDirection[1] = up;
		printf("\nThe NEXT Room will be move to the **DOWN** of the  starting room due to a **EVENT**\n\n");
		return true;
	}
	if (startRoom.neighbours[north] == empty)
	{
		toFromDirection[0] = north;
		toFromDirection[1] = south;
		printf("\nThe NEXT Room will be move to the **NORTH** of the  starting room due to a **EVENT**\n\n");
		return true;
	}
	else
	{
		return false; // no empty direction is available for starting room
	}
}

/*
 goal: generates a random number to select a room from roompile
 param low: number used to calc random number
 param high: number used to calc random number
*/
int getRandomRoom(int low, int high)
{
	static int roomPile[ROOM_NUM] = {0};
	static int cnt = 0;
	srand(time(0));
	bool NotEmptyFlag = true;

	// The player is already in the starting room , so room 0 should not be in the  room pile
	if (roomPile[0] != 1)
	{
		roomPile[0] = 1;
		++cnt;
	}

	while (NotEmptyFlag)
	{
		int randNum = (rand() % (high - low + 1)) + low;

		if (roomPile[randNum] != 1)
		{
			roomPile[randNum] = 1;
			++cnt;
			return randNum;
		}

		if (cnt == ROOM_NUM) // run out of rooms in pile
		{
			NotEmptyFlag = false;
		}

	} // end while

	return EMPTY_PILE;
}

int main()
{
	directionEnum toFromDirection[2];
	char input[input_size];
	char lowerCase[input_size];
	int toRoomNum;
	bool exit_flag = false;
	avatarBag.omen = false;

	allRooms = init_rooms();
	menuList = init_menu(menuList);
	showMenu(menuList);

	while (!exit_flag)
	{
		printf("\nEnter input : ");
		fgets(input, sizeof(input), stdin);

		for (int i = 0; input[i]; i++)
		{
			lowerCase[i] = tolower(input[i]);
		}

		char *firstWord = strtok(lowerCase, " \n");
		char *secondWord = strtok(NULL, " \n"); // uses same input again

		// if invalid go back to start of while loop
		if (search(menuList, firstWord) == NULL)
		{
			printf("\nYour input is invalid! Please follow the menu list below ");
			showMenu(menuList);
			continue; // skip the rest of the function and return to beginning of while loop
		}
		else
		{
			printf("firstword : %s, secondword : %s ", firstWord, secondWord);

			if (strcmp(firstWord, "look") == 0)
			{
				printf("\n --------------------your current room information : --------------------------\n");
				show(&allRooms[currentLocation]);
			}
			else if (strcmp(firstWord, "go") == 0)
			{
				if (strcmp(secondWord, "north") == 0)
				{
					to_direction = north;
					from_direction = south;
				}

				else if (strcmp(secondWord, "east") == 0)
				{
					to_direction = east;
					from_direction = west;
				}
				else if (strcmp(secondWord, "west") == 0)
				{
					to_direction = west;
					from_direction = east;
				}

				else if (strcmp(secondWord, "up") == 0)
				{
					to_direction = up;
					from_direction = down;
				}

				else if (strcmp(secondWord, "down") == 0)
				{
					to_direction = down;
					from_direction = up;
				}
				else
				{
					printf("\nYour input direction is invalid \n");
					continue;
				}

				printf("\n ------------------------your current room information : --------------------------\n");
				show(&allRooms[currentLocation]);

				// The current room's north is empty, it means it need to get a random from room pile
				if (allRooms[currentLocation].neighbours[to_direction] == empty)
				{
					toRoomNum = getRandomRoom(0, 6);
					if (toRoomNum != EMPTY_PILE) // move to new room only if room pile is not empty
					{
						// if the new room has a *event' and there is available direction in the starting room
						// The && operator can short circuit if the first condition is false, it will not execute the function checking
						if ((allRooms[toRoomNum].event == true) &&
							(changeLocationEvent(allRooms[start_room], toFromDirection)))
						{
							//  link "start room " to the room selected from random room pile
							allRooms[start_room].neighbours[toFromDirection[0]] = toRoomNum;
							allRooms[toRoomNum].neighbours[toFromDirection[1]] = start_room;
						}
						else
						{
							// link "current room"  to the room selected from random room pile
							allRooms[currentLocation].neighbours[to_direction] = toRoomNum;
							allRooms[toRoomNum].neighbours[from_direction] = currentLocation;
						}

						printf("\n**********************************your new room information : ****************************\n");
						show(&allRooms[toRoomNum]);

						// reset event to false for this new room, so it will not be trigger room relocation again
						allRooms[toRoomNum].event = false;

						// if the current room has omen
						if (allRooms[toRoomNum].omen == true)
						{ // set avatarBag.omen to true to record one of the winning condition
							avatarBag.omen = true;
							// reset the new room 's omen to false, so it will not be used again.
							allRooms[toRoomNum].omen = false;
						}

						// change current loacation to the new room
						currentLocation = toRoomNum;
					} //if (toRoomNum != EMPTY_PILE)

					else
					{
						printf("\nThe random room pile is empty, you have lost the game!\n");
						exit_flag = true;
					}

				} // if (allRooms[currentLocation].neighbours[to_direction] == empty)

				else // if Not empty, means it is already been visited
				{
					// Just change the current location to this visited room
					currentLocation = allRooms[currentLocation].neighbours[to_direction];
					printf("\n ******************Your new room information***********************\n");
					printf("\nYou have visited this room before !\n");
					show(&allRooms[currentLocation]);
				}
			} //if (strcmp(firstWord, "go") == 0)

			else if (strcmp(firstWord, "exit") == 0)
			{
				printf("\nGame over !\n");
				exit_flag = true;
			}

			else if (strcmp(firstWord, "help") == 0)
			{
				printf("\n Menu list : \n");
				showMenu(menuList);
			}

			else if (strcmp(firstWord, "take") == 0)
			{ // take an item from current room
				ITEM *item = get(allRooms[currentLocation].items, secondWord);
				if (item != NULL)
				{
					printf("\nThe item that you want to take : %s \n", item->name);
					// if item in room  matches user input add it to inventory
					avatarBag.items = insertItem(avatarBag.items, item->name, item->description);

					// remove the same item from curent room
					printf("\nRemoved thi	s item from current room : %s \n", item->name);

					//** Assign the linklist head to allRooms[currentLocation].items
					allRooms[currentLocation].items = removeByName(allRooms[currentLocation].items, item->name);

					printf("\nRoom item list after removal :\n");
					show(&allRooms[currentLocation]);

					printf("\nCurrent avatarBag inventory list :\n");
					display(avatarBag.items);
				}
				else
				{
					printf("\nThe item that you want to take is not in the current room : %s \n", secondWord);
				}
			} //else if (strcmp(firstWord, "take") == 0)

			else if (strcmp(firstWord, "inventory") == 0)
			{
				printf("\n\n Avatar inventory list : \n");
				display(avatarBag.items);
			}

			else if (strcmp(firstWord, "add") == 0)
			{
				menuList = insertMenu(menuList, secondWord, " a new command just added");
				showMenu(menuList);
			}

			else if (strcmp(firstWord, "search") == 0)
			{
				COMMAND *result = search(menuList, secondWord);
				printf("\nSearch result :  \n");
				printf("\nname : %s , description : %s \n", result->name, result->description);
			}
			else if (strcmp(firstWord, "drop") == 0)
			{
				ITEM *avatarItem = get(avatarBag.items, secondWord);
				// check if the item that will drop is in the inventory or not
				if (avatarItem != NULL)
				{
					printf("\nThe item that you want to drop from avatr inventory : %s \n", avatarItem->name);
					// if item in inventory  matches user input add it to "CURRENT ROOM"
					allRooms[currentLocation].items = insertItem(allRooms[currentLocation].items, avatarItem->name, avatarItem->description);

					//remove the same item from inventory
					printf("\nRemoved this item from inventoyr: %s \n", avatarItem->name);
					// assign linklist head to avatarBag.items
					avatarBag.items = removeByName(avatarBag.items, avatarItem->name);

					printf("\nCurrent room item list after drop item from inventory :\n");
					show(&allRooms[currentLocation]);

					printf("\nCurrent avatarBag inventory list :\n");
					display(avatarBag.items);
				}
				else
				{
					printf("\nThe item that you want to drop is not in the current inventory : %s \n", secondWord);
				}
			} //else if drop

		} // end else after check menu

		// Check if the player has won or not
		if (checkStatus(avatarBag, currentLocation))
		{
			printf("\nThe player has won the Game !!!! \n");
			exit_flag = true;
		}

	} // end while

	// Free all memory from all the data sturcture when it is not longer needed by the appliacation.
	freeAllMemory();
}
