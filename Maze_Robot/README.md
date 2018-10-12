# Maze Solving Bot
The bot is designed and programmed to make its way through a maze

The bot must perform the following functions:
1) Walk straight until reaching a dead end
2) Check left and right distances.
3) Move in direction of maximum distances.

**Working Idea:**
* Run both wheel motors in forward direction.
* Stop if distance less than 15mm
* Turn sensor bearing servo right and left and record the ping
* Rotate dc motors to turn the bot to left or right.
* Continue forward motion

**Constraints:**
* The bot, when faced with a dead end, the path with maximum distance must be the correct pathway.
* The bot, shouldn't find a T-point with branching from main path.


**Circuit Diagram:**
![Alt text](/Circuit_Representation.PNG?raw=true "Bot - circuit diagram")
