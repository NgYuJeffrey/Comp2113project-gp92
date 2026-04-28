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
int highscore = 0;

void loadScore() {
    string filename = "hs_" + to_string(mode) + ".txt";
    ifstream f(filename);
    if (f >> highscore) f.close();
    else highscore = 0;
}

void saveScore(int current) {
    if (current > highscore) {
        string filename = "hs_" + to_string(mode) + ".txt";
        ofstream f(filename);
        f << current;
        f.close();
        cout << "\nNEW HIGH SCORE!";
    }
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
    cout << "\033[H" << fullboard; // Smoother draw
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
            if ((snakey.size()) % 2 == 1 && mode == 2 && paustime > 30ms) {
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
