#include "snake.h"

#if defined(_WIN32) || defined(_WIN64)
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
    char getcha() { // custom getch() function for linux
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
#endif

void inputstyle() { // picking getch() function based on operation system | input: operation system | output: compatable getch() function
#if defined(_WIN32) || defined(_WIN64)
    bor = getch();
#else
    bor = getcha();
#endif
}

void clearformat() {
    cout << "\033[2J\033[H";
}

int main() {
    clearformat();
    mainmenu();
    setboard();
    snakey.push_front(snakelike(head[1], head[0]));
    userput = 'd'; // Initial direction
    dirgate = 0;

    thread navi(abalode);

    while (loopin) { // grab valid user input | input: user input | output: valid user input
        inputstyle();
        for (int i = 1; i < 5; i++) {
            if (bor == validput[i] && i % 2 != dirgate) {
                userput = bor;
                dirgate = i%2;
            }
        }
    }

    if (navi.joinable()) navi.join();
    cout << "\nFinal Score: " << snakey.size() - 1 << "\nGame Over.\n";
    if (snakey.size()-highscore[mode]>1) {
		highscore[mode]=snakey.size()-1;
		saveScore(4);
		cout << "\nNEW HIGH SCORE!";
	}
    
    return 0;
}
