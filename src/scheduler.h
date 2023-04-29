#include <vector>
#include <string>
#include <queue>

#include "Dijkstra.h"
#include "direction.h"
#include "util.h"
#include "config.h"
#include "Node.h"
#include "robot.h"

robot_t bot;

class Scheduler
{
private:
    Direction dir;
    std::vector<Port> deliveryPorts;
    std::vector<Port> deliveryNodesB;
    std::vector<Port> deliveryNodesA;
    int currentPosition;
    Node *nodeVec;
    int *path; 
    int pathSize;
public:
    Scheduler(int startPosition);
    ~Scheduler();
    void setUp(Box *boxes, unsigned int numBoxes);
    std::priority_queue<Box, std::vector<Box>, boxComparision> queue;
    std::vector<std::string> getRoute(Box box, Port port);
    std::vector<std::string> getRoute();
    Box getBox();
    Port getAvailablePort(Box currentBox);
    Node* getNodeVec();
    int * getPath();
    int getPathSize();
    int flag = 0;
};

Scheduler::Scheduler(int startPosition) {
    currentPosition = startPosition;
}

Scheduler::~Scheduler() {
    free(nodeVec);
}

void Scheduler::setUp(Box *boxes, unsigned int numBoxes) {
    for (auto deliveryNode : deliveryNodes) {
        Port port;
        port.pos = deliveryNode;
        port.occupied = false;
        deliveryPorts.push_back(port);        
    }

    for (auto deliveryNodeA : processNodesA) {
        Port port1;
        port1.pos = deliveryNodeA;
        port1.occupied = false;
        deliveryNodesA.push_back(port1);        
    }
    
    for (auto deliveryNodeB : processNodesB) {
        Port port2;
        port2.pos = deliveryNodeB;
        port2.occupied = false;
        deliveryNodesB.push_back(port2);        
    }


    for (size_t i = 0; i < numBoxes; i++)
    {   
        queue.push(boxes[i]);
    }
    

}

std::vector<std::string> Scheduler::getRoute(Box box, Port destPort) {
    Dijkstra dijkstra = Dijkstra(N_NODES);
    
    // TODO: Chose which port to go based on the color
    if(destPort.occupied == true){
        if(box.color == BLUE){
            for(int i = 0; i<deliveryPorts.size(); i++){
                if (deliveryPorts[i].pos == destPort.pos)
                    deliveryPorts[i].occupied = destPort.occupied; 
            }
        }

        if(box.color == RED){   
            for(int i = 0; i<deliveryNodesA.size(); i++){
                if (deliveryNodesA[i].pos == destPort.pos)
                    deliveryNodesA[i].occupied = destPort.occupied; 
            }
        }
            
        if(box.color == GREEN){
            for(int i = 0; i<deliveryNodesB.size(); i++){
                if (deliveryNodesB[i].pos == destPort.pos)
                    deliveryNodesB[i].occupied = destPort.occupied; 
            }
        }
        destPort = getAvailablePort(box);

        Serial.println();
        Serial.printf("Porta ");
        Serial.print(destPort.pos);
        Serial.printf(".occupied = ");
        Serial.println(destPort.occupied);
    }
    else {
        Serial.println();
        Serial.printf("Porta ");
        Serial.print(destPort.pos);
        Serial.printf(".occupied = ");
        Serial.println(destPort.occupied);
    }

    // Serial.printf("No de destino: ");
    // Serial.println(destPort.pos);
    // If box is waiting then we need to pick it up
    dijkstra.findPath(graph, currentPosition, destPort.pos);
        
    path = dijkstra.getPathArray();
    currentPosition = path[dijkstra.getPathSize() - 1];
    pathSize = dijkstra.getPathSize();
    // Serial.printf("Minimun Path is: [ ");
    // int a= dijkstra.getPathSize();
    // for(int i = 0; i < a; i++){
    //     Serial.print(path[i]);
    //     Serial.printf(" ");
    // }
    // Serial.println("]");

    nodeVec = (Node *)calloc(N_NODES, sizeof(Node));
    dir.nodeVector(nodeVec);

    int size = dijkstra.getPathSize();
    std::vector<std::string> dirVec = dir.definePath(path, size, nodeVec);

    if (box.color != BLUE) {
        Box newBox;
        if (box.color == GREEN) newBox.color = BLUE;

        else if (box.color == RED) newBox.color = GREEN;
        
        newBox.num = box.num;
        newBox.pos = currentPosition+1;
        // Serial.print(F(" BoxPos: "));
        // serial_print_format(box.pos, 4);
        newBox.status = WAINTING;

        queue.push(newBox);
    }
      
    return dirVec;
}

std::vector<std::string> Scheduler::getRoute() {
    Dijkstra dijkstra = Dijkstra(N_NODES);

    if(queue.empty()){
        //flag = 1;
        Serial.print("FILA -= VAZIA =- BRO");
    }
    
    Box box = queue.top();
    queue.pop();

    // If box is waiting then we need to pick it up
    dijkstra.findPath(graph, currentPosition, box.pos);
        
    path = dijkstra.getPathArray();
    currentPosition = path[dijkstra.getPathSize() - 1];

    nodeVec = (Node *)calloc(N_NODES, sizeof(Node));
    dir.nodeVector(nodeVec);

    int size = dijkstra.getPathSize();
    pathSize = dijkstra.getPathSize();
    std::vector<std::string> dirVec = dir.definePath(path, size, nodeVec);
      
    return dirVec;
}

Box Scheduler::getBox() {
    return queue.top();
}

// Port Scheduler::getAvailablePort() {
//     for (auto port: deliveryPorts) {
//         if (port.occupied == false)
//             return port;
//     }
// }

Port Scheduler::getAvailablePort(Box currentBox) {
    
    if(currentBox.color == BLUE){
        for (Port port: deliveryPorts) {
            if (port.occupied == false)
                return port;
        }
    } else if(currentBox.color == GREEN){
        for (Port port1: deliveryNodesB) {
            if (port1.occupied == false)
                return port1;
        }
    } else if(currentBox.color == RED){
        for (Port port2: deliveryNodesA) {
            if (port2.occupied == false)
                return port2;
        }
    }
}

Node* Scheduler::getNodeVec() {
    return nodeVec;
}

int * Scheduler::getPath() {
    return path;
}

int Scheduler::getPathSize(){
    return pathSize;
}