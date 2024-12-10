/*
    A C++ Program to generate mazes of a given size using recursive back-tracking
    https://weblog.jamisbuck.org/2010/12/27/maze-generation-recursive-backtracking
*/

#include <experimental/random>
#include <iostream>
#include <vector>
using namespace std;
using namespace experimental;

const int height = 33, width = 33;
int maze[height][width];

void generateMaze();
void recursion(int r, int c);
void setmaze(int maze[height][width], int val);
void drawMaze();

int main(void) {
    generateMaze();
    drawMaze();
    return 0;
}

void generateMaze() {

    // Initialize
    setmaze(maze, 1);

    // r for row, c for column
    // Generate random r
    int r = randint(0, height - 1);
    while (r % 2 == 0) {
        r = randint(0, height - 1);
    }
    // Generate random c
    int c = randint(0, width - 1);
    while (c % 2 == 0) {
        c = randint(0, width - 1);
    }
    // Starting cell
    maze[r][c] = 0;

    // 　Allocate the maze with recursive method
    recursion(r, c);
}

void recursion(int r, int c) {
    // 4 random directions
    int randDirs[6];
    for (int i = 0; i < 6; i++)
        randDirs[i] = randint(1, 4);
    // Examine each direction
    for (int i = 0; i < 8; i++) {

        switch (randDirs[i]) {
        case 1: // 　Whether 2 cells up is out or not
            if (r - 2 <= 0)
                continue;
            if (maze[r - 2][c] != 0) {
                maze[r - 2][c] = 0;
                maze[r - 1][c] = 0;
                recursion(r - 2, c);
            }
            break;
        case 2: // Whether 2 cells to the right is out or not
            if (c + 2 >= width - 1)
                continue;
            if (maze[r][c + 2] != 0) {
                maze[r][c + 2] = 0;
                maze[r][c + 1] = 0;
                recursion(r, c + 2);
            }
            break;
        case 3: // Whether 2 cells down is out or not
            if (r + 2 >= height - 1)
                continue;
            if (maze[r + 2][c] != 0) {
                maze[r + 2][c] = 0;
                maze[r + 1][c] = 0;
                recursion(r + 2, c);
            }
            break;
        case 4: // Whether 2 cells to the left is out or not
            if (c - 2 <= 0)
                continue;
            if (maze[r][c - 2] != 0) {
                maze[r][c - 2] = 0;
                maze[r][c - 1] = 0;
                recursion(r, c - 2);
            }
            break;
        }
    }
}

void setmaze(int maze[height][width], int val) {
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            maze[i][j] = val;
}

void drawMaze() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            if (maze[i][j] == 0)
                cout << "  ";
            else
                cout << "HH";
        }
        cout << endl;
    }
}

/*
Sample Output:

HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
HH      HH  HH                      HH              HH          HH
HHHHHH  HH  HH  HHHHHHHHHHHHHHHHHH  HHHHHH  HHHHHH  HH  HHHHHH  HH
HH          HH  HH              HH      HH  HH      HH  HH      HH
HH  HHHHHHHHHH  HH  HH  HHHHHHHHHHHHHH  HH  HHHHHHHHHH  HH  HHHHHH
HH              HH  HH      HH      HH  HH              HH      HH
HHHHHHHHHH  HH  HH  HHHHHH  HH  HH  HH  HHHHHHHHHHHHHHHHHHHHHH  HH
HH      HH  HH  HH      HH  HH  HH  HH              HH          HH
HH  HH  HHHHHH  HHHHHH  HH  HH  HH  HHHHHHHHHHHHHH  HH  HHHHHH  HH
HH  HH      HH  HH      HH      HH                      HH      HH
HH  HH  HH  HH  HH  HH  HH  HHHHHHHHHH  HHHHHHHHHHHHHHHHHHHHHHHHHH
HH  HH  HH  HH  HH  HH  HH  HH      HH  HH              HH      HH
HH  HHHHHH  HH  HH  HHHHHHHHHH  HH  HHHHHH  HHHHHHHHHH  HHHHHH  HH
HH  HH      HH  HH  HH      HH  HH  HH      HH      HH  HH      HH
HH  HH  HH  HH  HHHHHH  HH  HH  HH  HH  HHHHHH  HHHHHH  HH  HH  HH
HH  HH  HH      HH      HH      HH  HH  HH                  HH  HH
HH  HHHHHH  HHHHHH  HHHHHHHHHHHHHH  HH  HHHHHHHHHHHHHHHHHH  HHHHHH
HH      HH      HH  HH      HH      HH              HH  HH  HH  HH
HHHHHH  HHHHHH  HH  HHHHHH  HH  HHHHHHHHHHHHHHHHHHHHHH  HH  HH  HH
HH      HH      HH          HH          HH              HH  HH  HH
HH  HHHHHH  HH  HHHHHH  HHHHHHHHHHHHHH  HHHHHHHHHHHHHH  HH  HH  HH
HH  HH      HH      HH  HH      HH      HH              HH  HH  HH
HH  HHHHHHHHHH  HHHHHH  HH  HHHHHH  HHHHHH  HH  HHHHHH  HH  HH  HH
HH          HH  HH      HH      HH          HH  HH      HH      HH
HH  HHHHHH  HHHHHH  HHHHHHHHHH  HHHHHHHHHHHHHH  HH  HH  HH  HHHHHH
HH      HH      HH          HH      HH          HH  HH  HH      HH
HHHHHH  HHHHHH  HHHHHHHHHH  HH  HHHHHH  HHHHHHHHHH  HHHHHHHHHH  HH
HH  HH  HH  HH      HH      HH      HH          HH  HH          HH
HH  HH  HH  HH  HHHHHH  HHHHHHHHHH  HHHHHHHHHH  HHHHHH  HHHHHHHHHH
HH          HH      HH      HH              HH  HH          HH  HH
HH  HHHHHHHHHHHHHH  HHHHHH  HH  HHHHHH  HHHHHH  HH  HHHHHH  HH  HH
HH              HH              HH          HH      HH          HH
HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH
*/