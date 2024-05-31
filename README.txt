Ex03 - Pick Up Sticks Game (using SFML)
====================
file: oop2_ex2-David_Weschler-Ron_Avital.zip

Programmers: Ron Avital
			 David Weschler


Description: 
In this OOP exercise, we developed the game "Pick Up Sticks." 
The game is time-limited, requiring the player to pick up all the sticks 
within a specified duration. If the player manages to pick up all the 
sticks in time, they win; otherwise, they lose when time runs out.
The game was built in a CMake environment and the code was written in C++, using the SFML library. 
The project adheres to object-oriented principles.

Files:

main.cpp: Activates the program
Singleton.h: a singleton class that holds the textures, const variables and enums used in the game
Singleton.cpp: Implementation of the Singleton class
Menu.h: Defines the Menu class
Menu.cpp: Implements the Menu class, incharge of the buttons - 'Start', 'Load', 'Exit'
Button.h: Header file for the Button class, representing interactive buttons in the game's UI.
Button.cpp: Implementation of the Button class.
Game.h: Header file for the Game class, managing the core game mechanics and states.
Game.cpp: Implementation of the Game class
GameInfo.h: Header file for the GameInfo class, storing game-related information such as scores, time and sticks.
GameInfo.cpp: Implementation of the GameInfo class
FileInfo.h: a struct incharge of holding information read from the file
PackOfSticks.h: Header file for the PackOfSticks class, representing the collection of sticks in the game, and incharge of handling them.
PackOfSticks.cpp: Implementation of the PackOfSticks class 
Stick.h: Header file for the Stick class, representing an individual stick in the game.
Stick.cpp: Implementation of the Stick class.
StickDetails.h: a struct incharge of holding the information of an individual stick.
NoFileEx.h: Header file for the NoFileEx class, defining a custom exception for handling missing file errors with graphical feedback using SFML.
NoFileEx.cpp: Implementation of the NoFileEx class.
In Resources: PNG, and TTF files for graphics.

Dominant Data Structures: 
In this program we utilized STL containers and iterators, such as lists, vectors and multiset.
We handled exceptions effectively using invalid_argument, runtime_error and a custom class that inherits from runtime_error.
A singleton class is used to hold textures and fonts in the game.

Notable Algorithms:
Upon pressing a stick, the program finds the stick in O(N) runtime, where N is the number of sticks on the board. 
Checking if a stick can be picked up is done in O(1), and picking up the stick is also O(1) thanks to the use of lists. 
When the hint button is pressed, the program shows the player the pickable sticks in O(K) runtime, where K is the number 
of sticks that can be picked up at that moment.


Design Overview:
The program begins with the 'Menu' class, allowing you to choose between starting a new game or loading 
a previously saved one. Next, we enter the 'Game' class, which manages the core gameplay, including the 
main game loop. The 'PackOfSticks' class is responsible for uploading and downloading game information to 
the file. Each stick in the pack is represented by the 'Stick' class. Additionally, we have a 'Button' class 
that represents buttons, with three in the menu and two more in the game. Textures and fonts are stored in a 
Singleton class for efficiency.

Notes:

Have Fun!