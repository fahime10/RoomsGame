# TextAdventureGame
The game is about exploring maps and try to win by completing certain objectives.
The objectives are different for each map, for example, you may need to defeat all enemies first,
or collect a certain number of items, or even reach a specific room.

Be wary of attempting to leave the room while there is an enemy in the current room as the player's,
for it has a likelihood to attack the player and end the session for that map.

## How to win
Depending on the map, there are 3 ways to win.
One way is by defeating all enemies in that map, which can be defeated if the player has all 
required items in their inventory.
Another way is to collect specific items found in the map.
Reaching a specific room can also be a victory condition.

## Extra features
The program can handle errors from user inputting a non-existing map and when using a bad JSON map.
For example, the program will not build the map if there are typos in the fields or
if there are missing fields, then the game will display error reading the file.
The language that the user can use is extended, but not extensive.