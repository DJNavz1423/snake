#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

// 40 by 20 boundary
const int width = 40;
const int height = 20;

// ulo sa bitin
int x, y;

// coordinates sa food
int fruitX, fruitY;

// score
int score;

// snake tail coordinates
int tailX[100], tailY[100];

// snake tail lenfg
int nTail;

// snake direction
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;

//check if game is over
bool gameOver;

void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw() {
    system("cls");  // Clear console

    // Draw the top boundary
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    // Draw the game board
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "#";  // Left boundary

            if (i == y && j == x)
                cout << "O";  // Snake head
            else if (i == fruitY && j == fruitX)
                cout << "F";  // Fruit
            else {
                bool printTail = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        printTail = true;
                    }
                }
                if (!printTail) cout << " ";
            }

            if (j == width - 1) cout << "#";  // Right boundary
        }
        cout << endl;
    }

    // Draw the bottom boundary
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    // Display the score
    cout << "Score: " << score << endl;
}

void Input() {
    if (_kbhit()) {  // keyboard
        switch (_getch()) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic() {
    // Update the tail position
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Move the snake head
    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }

    // Check for collision with boundaries
    if (x >= width) x = 0;
    else if (x < 0) x = width - 1;
    if (y >= height) y = 0;
    else if (y < 0) y = height - 1;

    // Check for collision with tail
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    // Check if snake ate the fruit
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}


int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(200);  // Slow down the game
    }
    return 0;
}
