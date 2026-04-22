#include <iostream> //ioput
#include <chrono> //time
#include <thread> //seperate time
#include <string> //idk
#include <cstring> //idk
#include <stdio.h> //idk
#include <list> //flexable
#include <stdlib.h> //randomness
using namespace std;

#include <fstream> // Part 1: File IO
#if __linux__
#include <termios.h>
#include <unistd.h>
// Custom getch for Linux
char getcha() {
	struct termios oldt, newt;
	char ch;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}
#elif _WIN32 
	#include <conio.h>
#elif _WIN64
	#include <conio.h>
#endif
//enterless input


//if this needs to be submitted
//1. file input and output (highscore for each mode) done
//2. linux compatability (yayyyy)
//3. optimization of snake body presentation (optional)(it'll look better)
//------------------------------
//4. seperation of files (i hate makefile) (save a few days for this)
//5. comments for each section of code
//------------------------------
//6. README
//7. demo vid
char userput=' '; //accepted input
char bor=' '; //input buffer
char validput[5]= {' ','w','a','s','d'}; //input list
int mode=0; //gamemode 0:easy 1:medium 2:hard
char blocks[99]= {' ', '$', '#', 'o','@','.'};//symbols shown
struct boardstruct {
	char display;
	int status; //condition,in,out
};
boardstruct biowaste[21][21];//board
int head[2]= {10,10};//snake head location
struct snakelike {
	int cordx;
	int cordy;

	snakelike(int cordxe, int cordye)
		: cordx(cordxe)
		, cordy(cordye) {
	}
};
list<snakelike> snakey; //snake
string fullboard; //printing buffer, smoother graphics
std::chrono::milliseconds paustime=100ms; //pause time
int dirgate=2; //banned direction (0:updown 1:leftright)
bool loopin=true; // works for some reason and i aint gonna question it

int highscore = 0;
void loadScore() { //load score from file
	string filename = "hs_" + to_string(mode) + ".txt";
	ifstream f(filename);
	if(f >> highscore) f.close();
	else highscore = 0;
}

void saveScore(int current) { //save score into file
	if(current > highscore) {
		string filename = "hs_" + to_string(mode) + ".txt";
		ofstream f(filename);
		f << current;
		f.close();
		cout << "\nNEW HIGH SCORE!";
	}
}

bool deathdetect() { //death detection
	if(mode!=0) {
		return biowaste[head[0]][head[1]].status<=1;
	} else {
		return biowaste[head[0]][head[1]].status<=2;
	}
}

void clearformat() { //this actually still doesnt work on linux because getch
#ifdef _WIN32 
	system("cls");
#elif _WIN64
	system("cls");
#elif __linux__
	system("clear");
#else
	cout<<"imcompatable";
#endif
}

void inputstyle() {
#ifdef _WIN32 
	bor=getch();
#elif _WIN64
	bor=getch();
#elif __linux__
	bor=getcha();
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
	} while (biowaste[pellety][pelletx].status!=0);
	biowaste[pellety][pelletx].status=1;
}

void setboard() { //reset the board
	for(int i=0; i<21; i++) {
		for (int j=0; j<21; j++) {
			if (i*j*(20-i)*(20-j)==0) {
				biowaste[i][j].status=2;
			} else {
				biowaste[i][j].status=0;
			}
		}
	}
	pelletdrop();
}

void shootboard() {
	fullboard = "";
	if (loopin) {
		fullboard+="Score: ";
		fullboard+=to_string(snakey.size() - 1);
		fullboard+="\n";
	}
	for(int i=0; i<21; i++) {
		for (int j=0; j<21; j++) {
				fullboard += blocks[biowaste[i][j].status];
				fullboard += " ";
		}
		fullboard += "\n";
	}
	cout << fullboard;	
}



void abalode() { //timed fuction, detect, update and mkove snake
	while(loopin) {
		this_thread::sleep_for(paustime);
		//clearformat();
		cout<<"\033[H\033[J"; //this is very smooth 
		biowaste[head[0]][head[1]].status=3;
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
		if(biowaste[head[0]][head[1]].status==2 and mode==0) {
			for(int i=0; i<=1; i++) {
				if (head[i]==0) {
					head[i]=19;
				} else if(head[i]==20) {
					head[i]=1;
				}
			}
		}//easy mode loop the border
		if (biowaste[head[0]][head[1]].status==1) {
			pelletdrop();
			if ((snakey.size())%2==1 and mode==2) {
				paustime-=10ms;
			}//hard mode time decrease
		} else {
			biowaste[snakey.back().cordy][snakey.back().cordx].status=0;
			snakey.pop_back();
		}//usual moving
		snakey.push_front(snakelike(head[1],head[0]));
		loopin=deathdetect();
		biowaste[snakey.back().cordy][snakey.back().cordx].status=5;
		biowaste[head[0]][head[1]].status=4;
		shootboard();
	}
	cout<<"Your score is: "<<snakey.size()-1<<"\nPress any button to continue";
	return;
}

int main() {
	//clearformat();
	cout<<"\033[H\033[J";
	while(bor!='y') {
		cout << "WELCOME TO SNAKE GAME\n[0]: Easy (Loop)\n[1]: Medium (Normal)\n[2]: Hard (Fast)\nSelect Mode Number: ";
		do {
			inputstyle();
		} while(bor>'2' or bor<'0');
		mode=bor-'0';
		loadScore();
		//clearformat();
		cout<<"\033[H\033[J";
		cout << "Mode: " << mode << " | High Score: " << highscore << endl;
		cout << "Press WASD to direct the snake's movement\nBegin? [y/n]";
		do {
			inputstyle();
		} while(bor!='y' and bor!='n');
		clearformat();
	}
	thread navi(abalode);
	navi.detach(); //automoves
	setboard();
	snakey.push_front(snakelike(head[1],head[0]));

	while (loopin) {
		inputstyle();
		for (int i=1; i<5; i++) {
			if(bor==validput[i] and i%2!=dirgate) {
				userput=bor;
			}
		}
	} // read user input
	saveScore(snakey.size()-1);
	return 0;
}
