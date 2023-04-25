#pragma once

#include <stdio.h>
#include <strings.h>
#include <cstring>
#include <vector>
#include <string>
#include <Arduino.h>

#include "Node.h"
#include "config.h"

class Direction {
    private:
        // TODO: import the graph and pos from the constructor
        // int graph[N_NODES][N_NODES];
        // int pos[2][N_NODES];
        int nNodes;
    public:
        Direction();
        char direction(Node *no1, Node *no2);
        const char* mode(Node *intermedio);
        void findEdges(int no1);
        void nodeVector(Node *nodeVec);
        std::vector<std::string> definePath(int *path, int size, Node *nodeVec);
};