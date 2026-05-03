#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <list>
#include <fstream>
#include <vector>

using namespace std;
using namespace std::chrono_literals;

// Structures
struct boardstruct {
    char display;
    int status; 
};

struct snakelike {
    int cordx;
    int cordy;
    snakelike(int cordxe, int cordye) : cordx(cordxe), cordy(cordye) {}
};

// Global Variable Declarations
extern char userput;
extern char bor;
extern char validput[5];
extern int mode;
extern char blocks[99];
extern boardstruct biowaste[21][21];
extern int head[2];
extern list<snakelike> snakey;
extern string fullboard;
extern std::chrono::milliseconds paustime;
extern int dirgate;
extern bool loopin;
extern int highscore[3];
extern string intro[3];
extern int score;

// Function Prototypes
void loadScore();
void saveScore(int mode);
bool deathdetect();
void clearformat();
void inputstyle();
void pelletdrop();
void setboard();
void shootboard();
void abalode();
void mainmenu();
void delscoremenu();
char getcha(); // Linux specific input

#endif
