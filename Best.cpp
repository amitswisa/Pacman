#include "Best.h"
#include <queue>
#include <utility>

Position Best::move(Board* board, Ghost* ghost, Position& pacmanPos, vector<Ghost>& ghosts) {
    Position toReturn;
    int bestRoad = INT_MAX;

    int x = ghost->getPosition().getXPosition();
    int y = ghost->getPosition().getYPosition();

    vector<Position> goodPaths;
    // choose the best option of moving next.
    for (int i = 0;i < 4;i++) {
        Position temp(x + dx[i], y + dy[i]);
        // check validation of next move and replace if shortest move.
        if (isValid(board, temp) && pathToPacman[x + dx[i]][y + dy[i]] <= bestRoad)
        {
            if (pathToPacman[x + dx[i]][y + dy[i]] < bestRoad)
                goodPaths.clear();

            if (!isPositionOnGhosts(temp, ghost, ghosts)) {
                bestRoad = pathToPacman[x + dx[i]][y + dy[i]];
                toReturn.setPosition(x + dx[i], y + dy[i]);
                goodPaths.push_back(toReturn);
            }
        }
    }

    if (goodPaths.size() == 1)
        return goodPaths[0];

    // if next move is not defined, choose random to avoid exception.
    if (goodPaths.size() == 0 || bestRoad == 0 || isPositionOnGhosts(toReturn, ghost, ghosts))
    {
        do {
            goodPaths.clear();
            int random = (rand() % (4));
            toReturn.setPosition(x + dx[random], y + dy[random]);
            goodPaths.push_back(toReturn);
        } while (!isValid(board, toReturn));
    }

    int randomPathSelect = (rand() % (goodPaths.size()));
    return goodPaths[randomPathSelect];
}

void Best::fixPathArray(Board& board, Position& pacmanPos, vector<Ghost>& ghosts) {

    // reset isVisited array
    for (int i = 0;i < rowSize;i++) {
        for (int j = 0;j < colSize;j++) {
            this->isVisited[i][j] = false;
            this->pathToPacman[i][j] = 0;
        }
    }

    queue<pair<int, int>> q;
    q.push(make_pair(pacmanPos.getXPosition(), pacmanPos.getYPosition()));
    isVisited[pacmanPos.getXPosition()][pacmanPos.getYPosition()] = true;
    while (!q.empty()) {

        pair<int, int> temp = q.front();
        q.pop();

        for (int i = 0;i < 4;i++) {
            Position tempPos(temp.first+dx[i], temp.second+dy[i]);
            if (isValid(&board, tempPos) && isVisited[temp.first + dx[i]][temp.second + dy[i]] == false) {
                q.push(make_pair(temp.first + dx[i], temp.second + dy[i]));
                isVisited[temp.first + dx[i]][temp.second + dy[i]] = true;
                pathToPacman[temp.first + dx[i]][temp.second + dy[i]] = pathToPacman[temp.first][temp.second] + 1;
            }
        }

    }

}

void Best::setBFSarray(int _rowSize, int _colSize) {
    if (pathToPacman != NULL)
    {
        // reset BFS array
        for (int i = 0;i < this->rowSize;i++) {
            delete[] isVisited[i];
            delete[] pathToPacman[i];
        }
        delete[] isVisited;
        delete[] pathToPacman;
    }
    // allocating BFS new arrays and init them.
    pathToPacman = new int* [_colSize];
    isVisited = new bool* [_colSize];
    for (int i = 0;i < _colSize;i++) {
        pathToPacman[i] = new int[_rowSize];
        isVisited[i] = new bool[_rowSize];
        for (int j = 0;j < _rowSize;j++) {
            pathToPacman[i][j] = 0;
            isVisited[i][j] = false;
        }
    }

    rowSize = _colSize;
    colSize = _rowSize;

}