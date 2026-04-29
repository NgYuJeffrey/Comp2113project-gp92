#include "snake.h"

// Initialize Global Variables
char userput = ' ';
char bor = ' ';
char validput[5] = {' ', 'w', 'a', 's', 'd'};
int mode = 0;
char blocks[99] = {' ', '$', '#', 'o', '@', '.'};
boardstruct biowaste[21][21];
int head[2] = {10, 10};
list<snakelike> snakey;
string fullboard;
std::chrono::milliseconds paustime = 100ms;
int dirgate = 2;
bool loopin = true;
int highscore[3] = {0,0,0};
string intro[3]= {"The snake will go to the oppositde side of the board when touching the wall instead of dying","Classic game of snake, eat as many pellets as you can and don't bump into the wall or yourself!","The snake moves faster for every second pellet it eats"};

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
			loadScore();
			break;
		}
	}
	f.close();
}


bool deathdetect() {
	if (mode != 0) return biowaste[head[0]][head[1]].status <= 1;
	return biowaste[head[0]][head[1]].status <= 2;
}

void pelletdrop() {
	srand(time(0));
	int px, py;
	do {
		px = (rand() % 19) + 1;
		py = (rand() % 19) + 1;
	} while (biowaste[py][px].status != 0);
	biowaste[py][px].status = 1;
}

void setboard() {
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			biowaste[i][j].status = (i * j * (20 - i) * (20 - j) == 0) ? 2 : 0;
		}
	}
	pelletdrop();
}

void shootboard() {
	fullboard = "";
	if (loopin) {
		fullboard += "Score: " + to_string(snakey.size() - 1) + "\n";
	}
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			fullboard += blocks[biowaste[i][j].status];
			fullboard += " ";
		}
		fullboard += "\n";
	}
	clearformat();
	cout <<fullboard;
}

void abalode() {
	while (loopin) {
		this_thread::sleep_for(paustime);
		biowaste[head[0]][head[1]].status = 3;

		if (userput == 'w') head[0]--;
		else if (userput == 's') head[0]++;
		else if (userput == 'a') head[1]--;
		else if (userput == 'd') head[1]++;

		if (biowaste[head[0]][head[1]].status == 2 && mode == 0) {
			if (head[0] == 0) head[0] = 19;
			else if (head[0] == 20) head[0] = 1;
			if (head[1] == 0) head[1] = 19;
			else if (head[1] == 20) head[1] = 1;
		}

		if (biowaste[head[0]][head[1]].status == 1) {
			pelletdrop();
			if ((snakey.size()) % 2 == 0 && mode == 2 && paustime > 30ms) {
				paustime -= 10ms;
			}
		} else {
			biowaste[snakey.back().cordy][snakey.back().cordx].status = 0;
			snakey.pop_back();
		}

		snakey.push_front(snakelike(head[1], head[0]));
		loopin = deathdetect();
		biowaste[snakey.back().cordy][snakey.back().cordx].status = 5;
		biowaste[head[0]][head[1]].status = 4;
		shootboard();
	}
}

void delscoremenu() {
	clearformat();
	cout<<"Select the score you wish to be deleted\n[0] Easy\n[1] Normal\n[2] Hard\n[3] All\n[4] Quit\n";
	do {
		inputstyle();
	} while(bor>'4' or bor<'0');
	if (bor=='4') {
		clearformat();
		return;
	} else {
		int t=bor-'0';
		cout<<"Are you sure?(y/n)\n";
		do {
			inputstyle();
		} while(bor!='y' and bor!='n');
		if (bor=='y') {
			saveScore(t);
			loadScore();
			bor='n';
			return;
		} else {
			delscoremenu();
			return;
		}
	}
	return;
}

void mainmenu() {
	while (bor != 'y') {
		clearformat();
		cout << "WELCOME TO SNAKE GAME\n[0]: Easy\n[1]: Medium\n[2]: Hard\n[3]: Clear Highscore\nSelect Mode: ";
		do {inputstyle();} while (bor > '3' || bor < '0');
		mode = bor - '0';
		loadScore();
		clearformat();
		if(bor!='3') {
			cout << "Mode: " << mode << " | High Score: " << highscore[mode] << endl<<intro[mode]<<endl;
			cout << "Press WASD to move. Begin? [y/n]";
			do {inputstyle();} while (bor != 'y' && bor != 'n');
		} else {
			delscoremenu();
		}
	}
	return;
}

