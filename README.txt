When my game begins, the player begins in the starting room which has no items,events, or omens 
as they are initialized to null and false respectively within the init rooms method.  The starting room
as well as all of the rooms in the pile have their neighboring rooms initialized to empty.  Within
this init rooms method, the two omens, two events, and two items are decided.  Rooms each can
have a linked list of items as I created an an insertItem method and a removeByName method
which the rooms can utilize to add or remove items, depending on whether the player takes or
drops items from their inventory.  This action is also achieved through the same insert/remove
method but for the avatar's backpack.Each turn the player has multiple keywords and options they can
choose from the commmand table which I implemented with my init menu method.  This method utilizes
the insertMenu method which inserts a new command into the command table.  When the player inputs
information, I converted it to lower case and for the specific command go, if the player inputs
this they can follow this up with the directions north,east,south,west,down,and up which allows
them to move in that given direction.  If the room has an event, the player's location changes
and connects to the starting room which is executed by my changeLocationEvent.  This method
first checks to see whether the rooms south,east,west,up,down are empty respectively and if they
are, then room then links to the starting room.  The winning condition for the player is if
they have two items in their inventory, omen is marked true, and the player's current location
is the starting room.  This is checked through my checkStatus method which has a boolean
variable called win status that is initially set to false.  Once these conditions are met, this
variable is set to true and the player wins.  The losing condition for the player is if these condition
are not met and the variable remains false.  



Video Link: https://youtu.be/Zs8KhYNLu0c