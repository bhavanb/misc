/*
    A C++ Program to generate mazes of a given size using the depth first search algorithm
    https://www.algosome.com/articles/maze-generation-depth-first.html
*/

#include <experimental/random>
#include <iostream>
#include <vector>
using namespace std;
using namespace experimental;

struct pos {
    int x;
    int y;
};
struct cell {
    bool visited = false;
    pos prev = {-1, -1};
};

char *TLC = "┌";
char *HOL = "────";
char *TEM = "┬";
char *LEM = "├";
char *BEM = "┴";
char *BLC = "└";
char *TRC = "┐";
char *REM = "┤";
char *BRC = "┘";
char *VEL = "│";
char *BLS = "    ";
char *SPC = " ";
char *INR = "┼";

const int mazeSize = 16;
cell maze[mazeSize][mazeSize];

void draw_maze(int size);
void depth_first_search(int x, int y);

int main(void) {
    depth_first_search(randint(0, mazeSize - 1), randint(0, mazeSize - 1));
    draw_maze(mazeSize);
    return 0;
}

void depth_first_search(int x, int y) {
    maze[x][y].visited = true;
    vector<pos> neighbours;
    // north
    if (y - 1 >= 0)
        if (!(maze[x][y - 1].visited))
            neighbours.push_back({x, y - 1});
    // south
    if (y + 1 < mazeSize)
        if (!(maze[x][y + 1].visited))
            neighbours.push_back({x, y + 1});
    // east
    if (x + 1 < mazeSize)
        if (!(maze[x + 1][y].visited))
            neighbours.push_back({x + 1, y});
    // west
    if (x - 1 >= 0)
        if (!(maze[x - 1][y].visited))
            neighbours.push_back({x - 1, y});

    if (neighbours.size() == 0) {
        if (maze[x][y].prev.x == -1 || maze[x][y].prev.y == -1) {
            return;
        }
        depth_first_search(maze[x][y].prev.x, maze[x][y].prev.y);
    }

    else {
        int dir = randint(0, (int)neighbours.size() - 1);
        int nx = neighbours[dir].x;
        int ny = neighbours[dir].y;
        maze[nx][ny].prev.x = x;
        maze[nx][ny].prev.y = y;
        neighbours.clear();
        depth_first_search(nx, ny);
    }
}

void draw_maze(int size) {
    if (size == 0)
        return;
    int rows, cols;
    rows = cols = (size * 2) + 1;
    char *grid[rows][cols];

    // top line
    grid[0][0] = TLC;
    for (int i = 1; i < cols - 1; i++) {
        if (i % 2 == 0)
            grid[0][i] = TEM;
        else
            grid[0][i] = HOL;
    }
    grid[0][cols - 1] = TRC;

    for (int i = 1; i < rows; i++) {
        // middle space
        if (i % 2 != 0) {
            for (int j = 0; j < cols; j++) {
                if (j % 2 == 0)
                    grid[i][j] = VEL;
                else
                    grid[i][j] = BLS;
            }
        }

        else {
            // middle line
            if (i < rows - 1) {
                grid[i][0] = LEM;
                for (int j = 1; j < cols; j++) {
                    if (j % 2 != 0)
                        grid[i][j] = HOL;
                    else
                        grid[i][j] = INR;
                }
                grid[i][cols - 1] = REM;
            }
        }
    }

    // bottom line
    grid[rows - 1][0] = BLC;
    for (int i = 1; i < cols - 1; i++) {
        if (i % 2 == 0)
            grid[rows - 1][i] = BEM;
        else
            grid[rows - 1][i] = HOL;
    }
    grid[rows - 1][cols - 1] = BRC;

    // removing walls
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (maze[i][j].prev.x == -1 && maze[i][j].prev.y == -1)
                continue;
            pos g = {(2 * (i + 1)) - 1, (2 * (j + 1)) - 1};
            pos p = {(2 * (maze[i][j].prev.x + 1)) - 1, (2 * (maze[i][j].prev.y + 1)) - 1};

            if (g.x < p.x)
                grid[g.y][g.x + 1] = " ";
            if (p.x < g.x)
                grid[g.y][g.x - 1] = " ";
            if (g.y < p.y)
                grid[g.y + 1][g.x] = "    ";
            if (p.y < g.y)
                grid[g.y - 1][g.x] = "    ";
        }
    }

    // indicating START and END
    grid[1][1] = " ST ";
    grid[cols - 2][rows - 2] = " ED ";
    
    // printing
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
}

/*
Sample Output
┌────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┬────┐
│ ST                │                   │         │              │              │
├    ┼────┼    ┼    ┼    ┼────┼────┼────┼    ┼    ┼    ┼────┼    ┼    ┼    ┼────┤
│    │         │         │                   │    │         │         │         │
├    ┼    ┼────┼────┼    ┼    ┼────┼────┼────┼    ┼    ┼────┼────┼    ┼────┼    ┤
│    │    │              │    │    │              │    │         │    │         │
├    ┼    ┼    ┼────┼────┼    ┼    ┼    ┼────┼────┼    ┼    ┼────┼    ┼    ┼────┤
│    │    │    │         │    │    │    │         │    │         │    │         │
├    ┼    ┼────┼    ┼    ┼    ┼    ┼    ┼────┼    ┼    ┼────┼    ┼────┼────┼    ┤
│    │    │         │         │    │         │              │              │    │
├────┼    ┼    ┼────┼────┼────┼    ┼────┼    ┼────┼────┼────┼────┼────┼    ┼    ┤
│         │                             │                        │         │    │
├    ┼────┼────┼────┼────┼────┼────┼    ┼────┼────┼────┼────┼    ┼    ┼────┼    ┤
│    │         │              │         │                   │         │         │
├    ┼    ┼    ┼    ┼    ┼    ┼    ┼────┼────┼    ┼────┼────┼────┼────┼────┼    ┤
│         │    │    │    │    │              │                             │    │
├────┼────┼    ┼    ┼    ┼────┼────┼────┼    ┼────┼    ┼────┼    ┼────┼    ┼    ┤
│              │    │                   │         │         │    │         │    │
├    ┼────┼    ┼    ┼────┼────┼────┼    ┼────┼    ┼────┼    ┼    ┼────┼    ┼    ┤
│         │    │    │              │         │         │    │         │         │
├────┼    ┼    ┼    ┼    ┼────┼────┼────┼    ┼────┼    ┼────┼    ┼    ┼────┼────┤
│         │    │    │                   │         │         │    │              │
├    ┼────┼────┼    ┼    ┼────┼────┼    ┼────┼    ┼────┼    ┼────┼────┼    ┼    ┤
│                   │         │         │              │              │    │    │
├    ┼────┼────┼────┼────┼    ┼    ┼    ┼    ┼────┼────┼────┼────┼    ┼────┼    ┤
│    │                   │    │    │    │                             │         │
├    ┼    ┼    ┼────┼────┼    ┼    ┼    ┼────┼────┼────┼────┼────┼────┼    ┼    ┤
│    │    │    │              │    │    │                                  │    │
├    ┼    ┼    ┼    ┼────┼────┼    ┼    ┼────┼────┼    ┼    ┼────┼────┼────┼    ┤
│    │    │         │         │    │    │         │    │    │    │              │
├    ┼────┼────┼────┼    ┼    ┼    ┼    ┼    ┼    ┼────┼    ┼    ┼    ┼────┼────┤
│                        │         │         │              │                ED │
└────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┴────┘
*/