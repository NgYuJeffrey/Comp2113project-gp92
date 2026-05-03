# Comp2113project-gp92

# Text-Based Snake Game (C++)


## Team Members
* **Member 1:** Tianjian Huang - 3036515958
* **Member 2:** NgYu Jeffery - 3036588486

## Application Description
This is a text-based Snake game designed for Linux and Windows. The game features real-time movement, high-score tracking, and three difficulty modes that alter the game's rules.

# The final separated files used for the game are in the separated files branch.

## Features & Coding Requirements
Below is an explanation of how our project satisfies the five core coding requirements:

1. **Generation of Random Events:** - The `pelletdrop()` function utilizes `srand(time(0))` to generate random coordinates for food spawning, ensuring that pellets never overlap with the snake's body or walls.
2. **Data Structures:** - We use a `std::list<snakelike>` to store the snake's segments, allowing for efficient $O(1)$ insertions at the head and deletions at the tail. 
   - A 2D array of `boardstruct` objects represents the game grid.
3. **Dynamic Memory Management:** - The `std::list` container dynamically allocates memory for each new snake segment (node) on the heap as the snake grows.
4. **File Input/Output:** - The game uses `std::ifstream` and `std::ofstream` to manage a `hs_snake.txt` file. It tracks and persists the best scores for Easy, Medium, and Hard modes respectively.
5. **Program Codes in Multiple Files:** - The project is split into `main.cpp` (interface/input), `logic.cpp` (game mechanics), and `snake.h` (shared structures and globals).

## Game Modes (Difficulty Levels)
* **Easy:** Hitting a wall teleports the snake to the opposite side instead.
* **Medium:** Standard gameplay. Hitting walls or the snake body results to death.
* **Hard:** The game speed increases every second time the snake eats a pellet.

## Non-Standard Libraries
* **termios.h / unistd.h:** Used to implement a non-blocking `getch()` function for Linux terminal compatibility, allowing real-time input without pressing 'Enter'.

## Compilation and Execution Instructions
To compile and run the game on the CS Academy server:
1. Open the terminal in the project directory.
2. Run `make` to build the executable.
3. Run `./snake_game` to start.
4. (Optional) Run `make clean` to remove compiled objects.
