#include <iostream> //ioput
#include <chrono> //time
#include <thread> //seperate time
#include <string> //idk
#include <cstring> //idk
#include <conio.h> //enterless input
#include <stdio.h> //idk
#include <list> //flexable
#include <stdlib.h> //randomness
#include <curses.h> //more linux compatibility stuff
using namespace std;

//if this needs to be submitted
//1. file input and output (highscore for each mode)
//2. menu (should be fine)
// -----------------------------
//3. difficulty setting (easy:wall looping / hard:accleration)
//4. linux compatability (fuckkkkk)
//4.5. optimization of snake body presentation (optional)(it'll look better)
//------------------------------
//5. seperation of files (i hate makefile) (save a few days for this)
//6. comments for each section of code
char userput=' '; //accepted input
char bor=' '; //input buffer
char validput[5]= {' ','w','a','s','d'}; //input list
int q=0; //uhh
char blocks[99]= {' ','X','$','O','T'};//symbols shown
struct boardstruct {
	char display;
	int status[3]; //condition,in,out
};
boardstruct biowaste[21][21];//board
int head[2]= {11,11};//snake head location
struct snakelike {
	int cordx;
	int cordy;

	snakelike(int cordxe, int cordye)
		: cordx(cordxe)
		, cordy(cordye) {
	}
};
list<snakelike> snakey;
string fullboard;
int dirgate=2; //ban direction (0:updown 1:leftright)
bool loopin=true; // im going to be so fr this detection is subpar

bool deathdetect() { //dead
	if(biowaste[head[0]][head[1]].status[0]%2==1) { //needs adjustment for easy mode check
		return 0;
	} else {
		return 1;
	}
}

void clearformat() { //this actually still doesnt work on linux because getch
#ifdef _WIN32 || _WIN64
	system("cls");
#elif __linux__
	system("clear");
#else
	cout<<"imcompatable";
#endif
}


void pelletdrop() { // spawn pellet on blank space
	srand(time(0));
	int pelletx,pellety;
	do {
		pelletx=(rand() % 19)+1;
		pellety=(rand() % 19)+1;
	} while (biowaste[pellety][pelletx].status[0]!=0);
	biowaste[pellety][pelletx].status[0]=2;
} 

void setboard() { //reset the board
	for(int i=0; i<21; i++) {
		for (int j=0; j<21; j++) {
			if (i*j*(20-i)*(20-j)==0) {
				biowaste[i][j].status[0]=1;
			} else {
				biowaste[i][j].status[0]=0;
			}
		}
	}
	pelletdrop();
}

void shootboard() { // print the board
	fullboard="";
	for(int i=0; i<21; i++) {
		for (int j=0; j<21; j++) {
			fullboard+=blocks[biowaste[i][j].status[0]];
			fullboard+=" ";
		}
		fullboard+="\n";
	}
	cout<<fullboard<<snakey.size();
}



void abalode() { //timed fuction, detect, update and mkove snake
	while(loopin) {
		this_thread::sleep_for(100ms); // hardmode speed implant
		clearformat();
		if (userput=='w') {
			head[0]--;
			dirgate=1;
		} else if (userput=='s') {
			head[0]++;
			dirgate=1;
		} else if (userput=='a') {
			head[1]--;
			dirgate=0;
		} else if (userput=='d') {
			head[1]++;
			dirgate=0;
		} //i am sure there is a better way for this
		if (biowaste[head[0]][head[1]].status[0]==2) {
			pelletdrop();
		} else {
			biowaste[snakey.back().cordy][snakey.back().cordx].status[0]=0;
			snakey.pop_back();
		}
		snakey.push_front(snakelike(head[1],head[0]));
		loopin=deathdetect();
		biowaste[head[0]][head[1]].status[0]=3;
		shootboard();
	}
	return;
}

int main() {
	cout<<"ready for snake game? (wasd to turn snake)"; //update menu and read file here
	bor=getch();
	thread navi(abalode);
	navi.detach(); //automoves
	setboard();
	snakey.push_front(snakelike(head[1],head[0]));

	while (loopin) {
		bor=getch();
		for (int i=1; i<5; i++) {
			if(bor==validput[i] and i%2!=dirgate) {
				userput=bor;
			}
		}
	} // read input
	return 0; //file output

}
