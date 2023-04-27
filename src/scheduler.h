#include <vector>
#include <string>
#include <queue>

#include "Dijkstra.h"
#include "direction.h"
#include "util.h"
#include "config.h"
#include "Node.h"

class Scheduler
{
private:
    Direction dir;
    std::priority_queue<Box, std::vector<Box>, boxComparision> queue;
    std::vector<Port> deliveryPorts;
    int currentPosition;
    Node *nodeVec;
public:
    Scheduler(int startPosition);
    ~Scheduler();
    void setUp(Box *boxes, unsigned int numBoxes);
    std::vector<std::string> getRoute(Box box, Port port);
    std::vector<std::string> getRoute();
    Box getBox();
    Port getAvailablePort();
    Node* getNodeVec();
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


    for (size_t i = 0; i < numBoxes; i++)
    {   
        queue.push(boxes[i]);
    }
    

}

std::vector<std::string> Scheduler::getRoute(Box box, Port destPort) {
    Dijkstra dijkstra = Dijkstra(N_NODES);
    
    Serial.println();
    Serial.printf("Porta ");
    Serial.print(destPort.pos);
    Serial.printf(".occupied = ");
    Serial.println(destPort.occupied);
    // TODO: Chose which port to go based on the color
    if(destPort.occupied == true){
        for(int i = 0; i<deliveryPorts.size(); i++){
            if (deliveryPorts[i].pos == destPort.pos)
                deliveryPorts[i].occupied = destPort.occupied; 
        }
        destPort = getAvailablePort();

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
        
    auto path = dijkstra.getPathArray();
    currentPosition = path[dijkstra.getPathSize() - 1];
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
      
    return dirVec;
}

std::vector<std::string> Scheduler::getRoute() {
    Dijkstra dijkstra = Dijkstra(N_NODES);
    
    Box box = queue.top();
    queue.pop();

    // If box is waiting then we need to pick it up
    dijkstra.findPath(graph, currentPosition, box.pos);
        
    auto path = dijkstra.getPathArray();
    currentPosition = path[dijkstra.getPathSize() - 1];

    nodeVec = (Node *)calloc(N_NODES, sizeof(Node));
    dir.nodeVector(nodeVec);

    int size = dijkstra.getPathSize();
    std::vector<std::string> dirVec = dir.definePath(path, size, nodeVec);
      
    return dirVec;
}

Box Scheduler::getBox() {
    return queue.top();
}

Port Scheduler::getAvailablePort() {
    for (auto port: deliveryPorts) {
        if (port.occupied == false)
            return port;
    }
}

Node* Scheduler::getNodeVec() {
    return nodeVec;
}