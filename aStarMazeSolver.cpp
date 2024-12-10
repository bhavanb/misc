/*
    A C++ implementation of the A* pathfinding algorithm to solve a maze
    https://en.wikipedia.org/wiki/A*_search_algorithm
*/

#include <algorithm>
#include <forward_list>
#include <fstream>
#include <iostream>
#include <vector>

class Node {
public:
    std::pair<int, int> pos;
    bool traversable;
    int gCost = 0;
    int hCost = 0;
    int fCost() {
        return gCost + hCost;
    }
    Node *parent;

    int distanceFrom(Node *b) {
        return abs(pos.first - b->pos.first) + abs(pos.second - b->pos.second);
    }

    bool isIn(std::forward_list<Node *> container) {
        for (auto &&i : container)
            if (i->pos == this->pos)
                return true;
        return false;
    }

    bool operator==(const Node &b) const {
        return (pos == b.pos);
    }
};

const int size = 33;
Node grid[size][size];

void readMaze();
std::vector<Node *> getNeighbours(Node *node);
void aStar(std::pair<int, int> startPos, std::pair<int, int> targetPos);
std::forward_list<Node *> getPath(Node *startNode, Node *targetNode);
void drawPath(std::forward_list<Node *> path);

int main(void) {
    readMaze();
    aStar({1, 1}, {size - 2, size - 2});
    return 0;
}

void readMaze() {
    std::ifstream mazefile;
    std::string line;
    mazefile.open("maze");
    int lc = 0;
    while (getline(mazefile, line)) {
        for (int i = 0, j = 0; i < line.length(); i += 2, j++) {
            if (line[i] == 'H') {
                grid[lc][j] = {{lc, j}, false};
                std::cout<<"██";
            } else {
                grid[lc][j] = {{lc, j}, true};
                std::cout<<"  ";
            }
        }
        lc++;
        std::cout<<std::endl;
    }

    mazefile.close();
}

void aStar(std::pair<int, int> startPos, std::pair<int, int> targetPos) {
    Node *startNode = &grid[startPos.first][startPos.second];
    Node *targetNode = &grid[targetPos.first][targetPos.second];
    std::forward_list<Node *> openSet;   // list of nodes to be evaluated
    std::forward_list<Node *> closedSet; // list of nodes already evaluated

    openSet.push_front(startNode);
    while (!openSet.empty()) {
        Node *currentNode = openSet.front();
        for (Node *node : openSet)
            if (node->fCost() < currentNode->fCost() || (node->fCost() == currentNode->fCost() && node->hCost < currentNode->hCost))
                currentNode = node;

        openSet.remove(currentNode);
        closedSet.push_front(currentNode);

        if (currentNode == targetNode) {
            drawPath(getPath(startNode, currentNode));
            return;
        }

        for (Node *neighbour : getNeighbours(currentNode)) {
            if (!neighbour->traversable || neighbour->isIn(closedSet))
                continue;
            int newMovementCost = currentNode->gCost + currentNode->distanceFrom(neighbour);
            if (newMovementCost < neighbour->gCost || !(neighbour->isIn(openSet))) {
                neighbour->gCost = newMovementCost;
                neighbour->hCost = neighbour->distanceFrom(targetNode);
                neighbour->parent = currentNode;
                if (!(neighbour->isIn(openSet)))
                    openSet.push_front(neighbour);
            }
        }
    }
}

std::vector<Node *> getNeighbours(Node *node) {
    std::vector<Node *> neighbours;
    // north
    if (node->pos.second - 1 >= 0)
        neighbours.push_back(&grid[node->pos.first][node->pos.second - 1]);
    // south
    if (node->pos.second + 1 >= 0)
        neighbours.push_back(&grid[node->pos.first][node->pos.second + 1]);
    // east
    if (node->pos.first + 1 < size)
        neighbours.push_back(&grid[node->pos.first + 1][node->pos.second]);
    // west
    if (node->pos.first - 1 < size)
        neighbours.push_back(&grid[node->pos.first - 1][node->pos.second]);

    return neighbours;
}

std::forward_list<Node *> getPath(Node *startNode, Node *targetNode) {
    std::forward_list<Node *> path;
    Node *currentNode = targetNode;
    while (!(*currentNode == *startNode)) {
        path.push_front(currentNode);
        currentNode = currentNode->parent;
    }
    return path;
}

void drawPath(std::forward_list<Node *> path) {
    std::cout<<"Found path!"<<std::endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (grid[i][j].traversable)
                if (grid[i][j].isIn(path))
                    std::cout << "▒▒";
                else
                    std::cout << "  ";
            else
                std::cout << "██";
        }
        std::cout << std::endl;
    }
}


/*
Sample Output:
██████████████████████████████████████████████████████████████████
██                  ██      ██              ██          ██      ██
██  ██████  ██████  ██  ██  ██████  ██  ██  ██████████  ██████  ██
██  ██      ██      ██  ██  ██      ██  ██                      ██
██████  ██████  ██████  ██  ██  ██████████  ██████████████████  ██
██      ██              ██      ██      ██  ██              ██  ██
██  ██████████████████████████████  ██  ██████  ██████████  ██████
██                                  ██      ██          ██      ██
██████████  ██████████████████████████████  ██████  ██████████  ██
██  ██  ██  ██  ██                  ██  ██      ██      ██      ██
██  ██  ██  ██  ██  ██████████████  ██  ██  ██████████  ██  ██  ██
██      ██      ██      ██      ██      ██              ██  ██  ██
██  ██  ██████  ██  ██████████  ██████  ██████████████████  ██  ██
██  ██      ██  ██      ██          ██          ██      ██  ██  ██
██████████  ██  ██████  ██████  ██████████████  ██████  ██  ██████
██          ██          ██      ██      ██      ██      ██      ██
██  ██████  ██████████████████  ██  ██  ██  ██████  ██████████  ██
██      ██  ██          ██      ██  ██  ██  ██      ██      ██  ██
██  ██  ██████  ██  ██████████  ██  ██  ██  ██  ██████  ██  ██  ██
██  ██  ██      ██              ██  ██          ██      ██  ██  ██
██  ██  ██  ██████████████████  ██  ██  ██████████  ██████  ██  ██
██  ██  ██                  ██      ██  ██  ██      ██  ██  ██  ██
██  ██  ██████████████████  ██████████  ██  ██  ██████  ██  ██  ██
██  ██  ██              ██  ██      ██      ██      ██          ██
██  ██  ██████████  ██  ██  ██  ██  ██  ██████████  ██  ██████████
██  ██      ██      ██  ██  ██  ██  ██  ██          ██  ██      ██
██████  ██  ██  ██████  ██  ██  ██  ██████  ██████████████  ██  ██
██      ██  ██  ██  ██  ██  ██  ██          ██              ██  ██
██  ██  ██  ██  ██  ██  ██  ██  ██████████████  ██████████████  ██
██  ██  ██          ██      ██          ██      ██  ██          ██
██████  ██████████  ██████████████████  ██  ██████  ██  ██████  ██
██              ██                  ██              ██      ██  ██
██████████████████████████████████████████████████████████████████
Found path!
██████████████████████████████████████████████████████████████████
██  ▒▒▒▒▒▒▒▒        ██      ██              ██          ██      ██
██  ██████▒▒██████  ██  ██  ██████  ██  ██  ██████████  ██████  ██
██  ██▒▒▒▒▒▒██      ██  ██  ██      ██  ██                      ██
██████▒▒██████  ██████  ██  ██  ██████████  ██████████████████  ██
██▒▒▒▒▒▒██              ██      ██▒▒▒▒▒▒██  ██▒▒▒▒▒▒▒▒▒▒▒▒▒▒██  ██
██▒▒██████████████████████████████▒▒██▒▒██████▒▒██████████▒▒██████
██▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒██▒▒▒▒▒▒██▒▒▒▒▒▒    ██▒▒▒▒▒▒██
██████████  ██████████████████████████████▒▒██████▒▒██████████▒▒██
██  ██  ██  ██  ██                  ██  ██▒▒    ██▒▒▒▒▒▒██▒▒▒▒▒▒██
██  ██  ██  ██  ██  ██████████████  ██  ██▒▒██████████▒▒██▒▒██  ██
██      ██      ██      ██      ██      ██▒▒▒▒▒▒▒▒▒▒▒▒▒▒██▒▒██  ██
██  ██  ██████  ██  ██████████  ██████  ██████████████████▒▒██  ██
██  ██      ██  ██      ██          ██          ██      ██▒▒██  ██
██████████  ██  ██████  ██████  ██████████████  ██████  ██▒▒██████
██          ██          ██      ██      ██      ██      ██▒▒▒▒▒▒██
██  ██████  ██████████████████  ██  ██  ██  ██████  ██████████▒▒██
██      ██  ██          ██      ██  ██  ██  ██      ██▒▒▒▒▒▒██▒▒██
██  ██  ██████  ██  ██████████  ██  ██  ██  ██  ██████▒▒██▒▒██▒▒██
██  ██  ██      ██              ██  ██          ██▒▒▒▒▒▒██▒▒██▒▒██
██  ██  ██  ██████████████████  ██  ██  ██████████▒▒██████▒▒██▒▒██
██  ██  ██                  ██      ██  ██  ██▒▒▒▒▒▒██  ██▒▒██▒▒██
██  ██  ██████████████████  ██████████  ██  ██▒▒██████  ██▒▒██▒▒██
██  ██  ██              ██  ██▒▒▒▒▒▒██      ██▒▒▒▒▒▒██    ▒▒▒▒▒▒██
██  ██  ██████████  ██  ██  ██▒▒██▒▒██  ██████████▒▒██  ██████████
██  ██      ██      ██  ██  ██▒▒██▒▒██  ██▒▒▒▒▒▒▒▒▒▒██  ██▒▒▒▒▒▒██
██████  ██  ██  ██████  ██  ██▒▒██▒▒██████▒▒██████████████▒▒██▒▒██
██      ██  ██  ██  ██  ██  ██▒▒██▒▒▒▒▒▒▒▒▒▒██▒▒▒▒▒▒▒▒▒▒▒▒▒▒██▒▒██
██  ██  ██  ██  ██  ██  ██  ██▒▒██████████████▒▒██████████████▒▒██
██  ██  ██          ██      ██▒▒▒▒▒▒▒▒▒▒██▒▒▒▒▒▒██  ██        ▒▒██
██████  ██████████  ██████████████████▒▒██▒▒██████  ██  ██████▒▒██
██              ██                  ██▒▒▒▒▒▒        ██      ██▒▒██
██████████████████████████████████████████████████████████████████

*/