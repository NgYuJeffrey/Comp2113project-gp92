#include "snake.h"

#if defined(_WIN32) || defined(_WIN64)
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
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
#endif

void inputstyle() {
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
    while (bor != 'y') {
        cout << "WELCOME TO SNAKE GAME\n[0]: Easy\n[1]: Medium\n[2]: Hard\nSelect Mode: ";
        do { inputstyle(); } while (bor > '2' || bor < '0');
        mode = bor - '0';
        loadScore();
        clearformat();
        cout << "Mode: " << mode << " | High Score: " << highscore << endl;
        cout << "Press WASD to move. Begin? [y/n]";
        do { inputstyle(); } while (bor != 'y' && bor != 'n');
    }

    setboard();
    snakey.push_front(snakelike(head[1], head[0]));
    userput = 'd'; // Initial direction
    dirgate = 0;

    thread navi(abalode);

    while (loopin) {
        inputstyle();
        for (int i = 1; i < 5; i++) {
            if (bor == validput[i] && i % 2 != dirgate) {
                userput = bor;
                dirgate = (i <= 2) ? 1 : 0;
            }
        }
    }

    if (navi.joinable()) navi.join();
    saveScore(snakey.size() - 1);
    cout << "\nFinal Score: " << snakey.size() - 1 << "\nGame Over.\n";
    return 0;
}
