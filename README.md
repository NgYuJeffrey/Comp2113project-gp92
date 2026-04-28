# Comp2113project-gp92

Text-Based Snake (HKU COMP2113 Project)
Team Members
Name: [Your Name]

UID: [Your UID]

GitHub Username: [Your Username]

Application Description
This is a real-time, terminal-based Snake game implemented in C++. The game features a multi-threaded architecture that allows the snake to move independently while the user provides input via "enterless" key presses. It includes three distinct difficulty modes, high-score persistence, and smooth terminal rendering using ANSI escape codes.

Game Features
Easy Mode (0): Borderless gameplay. The snake loops through walls and reappears on the opposite side.

Medium Mode (1): Traditional gameplay. Hitting walls results in an immediate game over.

Hard Mode (2): Acceleration mode. The game speed increases significantly every time the snake eats a pellet.

High Score System: Scores are saved to separate files based on the chosen difficulty mode.

Smooth Graphics: Uses \033[H\033[J buffer clearing to prevent screen flickering in the Linux terminal.

Coding Requirements Mapping
This project satisfies the five core coding requirements as follows:

Generation of Random Events: * Found in logic.cpp: The pelletdrop() function uses srand(time(0)) and a do-while loop to randomly spawn food only on empty tiles.

Data Structures for Storing Data: * Found in snake.h: We use a std::list<snakelike> to store snake segments for efficient head/tail manipulation and a 2D array of boardstruct for the game grid.

Dynamic Memory Management: * The std::list container dynamically allocates memory on the heap for every new snakelike node added when the snake eats a pellet.

File Input/Output: * Found in logic.cpp: Functions loadScore() and saveScore() use ifstream and ofstream to read/write persistent high scores to files like hs_0.txt.

Program Codes in Multiple Files: * The project is split into main.cpp (input/menu), logic.cpp (gameplay mechanics), and snake.h (definitions), compiled via a Makefile.

Non-Standard Libraries
<termios.h> & <unistd.h>: Used in the getcha() function to disable canonical mode in the Linux terminal. This allows the game to detect W, A, S, D keys instantly without the user having to press Enter.

<thread>: Used to separate the movement logic (abalode) from the input listener, enabling real-time gameplay.

Compilation and Execution Instructions
To Compile: Navigate to the project directory and run:

Bash
make
To Run: Execute the generated binary:

Bash
./snake_game
To Reset:
To remove object files and the executable:

Bash
make clean
