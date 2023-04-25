#pragma once

#include <stdlib.h>
#include <vector>
#include <iostream>
#include "config.h"

class Dijkstra{
    private:
        unsigned int numNodes;
        unsigned int pathSize;
        int* pathArray;
        float* acumWeight;
        bool* wasVisited; 
        std::vector<int> toWeight;
        std::vector<int> toVisit;

    public:
        Dijkstra(unsigned int numNodes) {
            this->numNodes = numNodes;
            this->pathSize = 0;
            this->pathArray = NULL;
            this->acumWeight = (float*)calloc(numNodes, sizeof(float));
            this->wasVisited = (bool*)calloc(numNodes, sizeof(bool));
            
            for (unsigned int i = 0; i < this->numNodes; i++) {
                acumWeight[i] = -1.0F;
                wasVisited[i] = false;
            }

            this->toVisit.clear();
            this->toWeight.clear();
        }

        ~Dijkstra() {
            this->toVisit.clear();
            this->toWeight.clear();
            free(this->acumWeight);
            free(this->wasVisited);
            free(this->pathArray);
        }

        bool isInToVisit(int node) {
            for (int i = 0; i < toVisit.size(); i++) {
                if (toVisit.at(i) == node) return true;
            }

            return false;
        }

        void setAsVisited(int node) {
            this->wasVisited[node] = true;
            this->toVisit.erase(this->toVisit.begin());
        }

        int* findPath(const int graph[N_NODES][N_NODES], int origin, int destination) {
            int visiting = origin;
            this->acumWeight[origin] = 0;
            toVisit.push_back(origin);

            //printWasVisited();
            //printAccumWeight();
            while(!this->toVisit.empty()) {
                for(int i = 0; i < this->numNodes; i++) {
                    if(graph[visiting][i] > 0) {
                        this->toWeight.push_back(i);
                        //printVectorContents(toWeight);
                        if(!isInToVisit(i) && !wasVisited[i])
                            this->toVisit.push_back(i);
                    }
                }

                while(!this->toWeight.empty()) {
                    int weighting = toWeight.at(0);
                    
                    float sourceAccum = this->acumWeight[visiting];
                    float targetAccum = this->acumWeight[weighting];
                    float distance = graph[visiting][weighting];
                    
                    if(sourceAccum + distance < targetAccum || targetAccum == -1) {
                        this->acumWeight[weighting] = sourceAccum + distance;
                    }

                    this->toWeight.erase(this->toWeight.begin());
                }

                setAsVisited(visiting); //already removes from toVisit
                if(!toVisit.empty()) visiting = toVisit.at(0);
                //printWasVisited();
                //printAccumWeight();
            }

            pathArray = (int*)malloc(sizeof(int));
            pathArray[0] = destination;
            //pathArray[3] = destination;
            pathSize++;
            int minAcumulatedNode;
            int now = destination;
            while(pathArray[pathSize-1] != origin){
                int min = INT32_MAX;
                for(int i = 0; i < numNodes; i++){
                    if(graph[now][i] != 0){
                        if(acumWeight[i] < min){
                            minAcumulatedNode = i;
                            //std::cout << i << ": ";
                            min = acumWeight[i];
                            //std::cout << min << "\n";
                        }
                    } 
                }
                pathSize++;
                pathArray = (int*)realloc(pathArray, pathSize*sizeof(int));
                pathArray[pathSize-1] = minAcumulatedNode;
                //pathArray[0] = minAcumulatedNode;
                now = minAcumulatedNode;
            } 

            int flipping;
            for(int i = 0; i < pathSize/2 ; i++){
                flipping = pathArray[pathSize -1 - i];
                pathArray[pathSize -1 -i] = pathArray[i];
                pathArray[i] = flipping;
            }
            return pathArray;
        }
        
        void printVectorContents(std::vector<int> vector){
            for(int i = 0 ; i < vector.size(); i++){
                std::cout << i << ": " << vector.at(i) << "\n";
            }
            std::cout << "________________________\n";
        }

        void printWasVisited(){
            std::cout << "was visited : |";
            for(int i = 0; i < numNodes; i++){
                std::cout << i << "  ";
            }
            std::cout << "|\n";
            std::cout << "              |";
            for(int i = 0; i < numNodes; i++){
                std::cout << wasVisited[i] << "  ";
            }
            std::cout << "|\n\n";
        }

        void printAccumWeight(){
            std::cout << "AccumWeight : |";
            for(int i = 0; i < numNodes; i++){
                std::cout << i << "  ";
            }
            std::cout << "|\n";
            std::cout << "              |";
            for(int i = 0; i < numNodes; i++){
                std::cout << acumWeight[i] << "  ";
            }
            std::cout << "|\n\n";
        }

        int getPathSize(){
            return this->pathSize;
        }

        int* getPathArray(){
            return this->pathArray;
        }

    
};
//TODO resetar os pesos - praticamente copiar o que ta oconstructor
//TODO sincar infos de nó com sua posicão x y