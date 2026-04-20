#include <iostream> //ioput
#include <chrono> //time
#include <thread> //seperate time
#include <string> //idk
#include <cstring> //idk
#include <conio.h> //enterless input
#include <stdio.h> //idk
#include <list> //flexable
#include <stdlib.h> //randomness
using namespace std;

//if this needs to be submitted
//1. file input and output (highscore for each mode)
//2. menu (should be fine)
// -----------------------------
//3. difficulty setting (easy:wall looping / hard:accleration) done
//4. linux compatability (fuckkkkk)
//4.5. optimization of snake body presentation (optional)(it'll look better)
//------------------------------
//5. seperation of files (i hate makefile) (save a few days for this)
//6. comments for each section of code
char userput=' '; //accepted input
char bor=' '; //input buffer
char validput[5]= {' ','w','a','s','d'}; //input list
int mode=0; //gamemode 0:easy 1:medium 2:hard
char blocks[99]= {' ','$','X','O','T'};//symbols shown
struct boardstruct {
	char display;
	int status[3]; //condition,in,out
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
bool loopin=true; // im going to be so fr this detection is subpar


bool deathdetect() { //death detection
	if(mode!=0) {
		return biowaste[head[0]][head[1]].status[0]<=1;
	} else {
		return biowaste[head[0]][head[1]].status[0]<=2;
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

void inputstyle(){
#ifdef _WIN32 || _WIN64
	bor=getch();
#elif __linux__
	cin>>bor;
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
	biowaste[pellety][pelletx].status[0]=1;
}

void setboard() { //reset the board
	for(int i=0; i<21; i++) {
		for (int j=0; j<21; j++) {
			if (i*j*(20-i)*(20-j)==0) {
				biowaste[i][j].status[0]=2;
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
	cout<<fullboard<<head[0]<<head[1];
}



void abalode() { //timed fuction, detect, update and mkove snake
	while(loopin) {
		this_thread::sleep_for(paustime);
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
		if(biowaste[head[0]][head[1]].status[0]==2 and mode==0) {
			for(int i=0; i<=1; i++) {
				if (head[i]==0) {
					head[i]=19;
				} else if(head[i]==20) {
					head[i]=1;
				}
			}
		} 
		if (biowaste[head[0]][head[1]].status[0]==1) {
			pelletdrop();
			if ((snakey.size())%2==1 and mode==2) {
				paustime-=10ms;
			}
		} else {
			biowaste[snakey.back().cordy][snakey.back().cordx].status[0]=0;
			snakey.pop_back();
		}
		snakey.push_front(snakelike(head[1],head[0]));
		loopin=deathdetect();
		biowaste[head[0]][head[1]].status[0]=3;
		shootboard();
	}
	cout<<"Your score is: "<<snakey.size()-1<<"\nPress any button to continue";
	return;
}

int main() {
	//input file here
	cout<<"ready for snake game? (wasd to turn snake)"; //menu here
	inputstyle();
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
	//output file here
	return 0;
}
