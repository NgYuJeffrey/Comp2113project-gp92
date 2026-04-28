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
//------------------------------
//4. seperation of files (i hate makefile) (save a few days for this)
//5. comments for each section of code
//------------------------------
//6. README
//7. demo vid
char userput=' '; //accepted input
char bor=' '; //input buffer
char validput[5]= {' ','w','a','s','d'}; //input list
int mode=7; //gamemode 0:easy 1:medium 2:hard
char blocks[10]= {' ', '$', '#', 'o','@','.'};//symbols shown
struct boardstruct {
	char display;
	int status; //condition
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
bool loopin=true; //decision buffer
string intro[3]= {"The snake will go to the oppositde side of the board when touching the wall instead of dying","Classic game of snake, eat as many pellets as you can and don't bump into the wall or yourself!","The snake moves faster for every second pellet it eats"};

int highscore[3] = {0,0,0};
void saveScore(int mode) { //save score into file
	string filename = "hs_snake.txt";
	ofstream f(filename);
	for(int i=0; i<3; i++) {
		if((i-mode)*(3-mode)==0) {
			f<<"0\n";
		} else {
			f<<highscore[i]<<"\n";
		}
	}
	f.close();
}

void loadScore() { //load score from file
	string filename = "hs_snake.txt";
	ifstream f(filename);
	string topscore;
	int i=0;
	while(getline(f,topscore)) {
		if (topscore!="") {
			highscore[i]=stoi(topscore);
			i++;
		} else {
			f.close();
			saveScore(3);
			cout<<"bruh";
			loadScore();
			break;
		}

	}

	f.close();
}

bool deathdetect() { //death detection
	if(mode!=0) {
		return biowaste[head[0]][head[1]].status<=1;
	} else {
		return biowaste[head[0]][head[1]].status<=2;
	}
}

void inputstyle() {//stylized input for different version of operating system
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

void delscoremenu() {
	cout<<"\033[H\033[J";
	cout<<"Select the score you wish to be deleted\n[0] Easy\n[1] Normal\n[2] Hard\n[3] All\n[4] Quit\n";
	do {
		inputstyle();
	} while(bor>'4' or bor<'0');
	if (bor=='4') {
		return;
	} else {
		int t=bor-'0';
		cout<<"Are you sure?(y/n)\n";
		do {
			inputstyle();
		} while(bor!='y' and bor!='n');
		if (bor=='y'){
			saveScore(t);
			loadScore();
		} else{
			delscoremenu();
			return;
		}
	}
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
	cout<<"\033[H\033[J";
	loadScore();
	while(bor!='y' or mode==3) {
		cout << "WELCOME TO SNAKE GAME\n[0]: Easy (Loop)\n[1]: Medium (Normal)\n[2]: Hard (Fast)\n[3]: Clear Highscore\nSelect Mode Number: ";
		do {
			inputstyle();
		} while(bor>'3' or bor<'0');
		mode=bor-'0';
		cout<<"\033[H\033[J";
		if (mode==3) {
			delscoremenu();
		} else {
			cout << "Mode: " << mode << " | High Score: " << highscore[mode] << endl<<intro[mode]<<endl;
			cout << "Press WASD to direct the snake's movement\nBegin? [y/n]\n";
			do {
				inputstyle();
			} while(bor!='y' and bor!='n');
		}

		cout<<"\033[H\033[J";
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
	if (snakey.size()-1>highscore[mode]) {
		highscore[mode]=snakey.size()-1;
		saveScore(4);
		cout << "\nNEW HIGH SCORE!";
	}
	return 0;
}
