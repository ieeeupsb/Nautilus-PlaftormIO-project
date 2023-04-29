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
    Dijkstra dijkstra;

public:
    Scheduler(int startPosition);
    ~Scheduler();
    void setUp(Box *boxes, unsigned int numBoxes);
    std::vector<std::string> getRoute(Box box, Port port);
    std::vector<std::string> getRoute();
    Box getBox();
    Port getAvailablePort();
    Node *getNodeVec();
};

Scheduler::Scheduler(int startPosition)
{
    dijkstra = Dijkstra(N_NODES);
    currentPosition = startPosition;
}

Scheduler::~Scheduler()
{
    free(nodeVec);
}

void Scheduler::setUp(Box *boxes, unsigned int numBoxes)
{
    for (auto deliveryNode : deliveryNodes)
    {
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

std::vector<std::string> Scheduler::getRoute(Box box, Port destPort)
{
    Serial.printf("Porta: %d Occupied: %d\n", destPort.pos, destPort.occupied);

    // TODO: Chose which port to go based on the color
    if(box.color == Color::BLUE) {
        if(destPort.occupied == true)
            for(int i = 0; i < deliveryPorts.size(); i++)
                if(deliveryPorts[i].pos == destPort.pos)
                    deliveryPorts[i].occupied = destPort.occupied;
        
        destPort = getAvailablePort();
        Serial.printf("Porta: %d Occupied: %d\n", destPort.pos, destPort.occupied);
    } else if (box.color == Color::GREEN) {
        if(destPort.occupied == true)
            for(int i = 0; i < deliveryPorts.size(); i++)
                if(deliveryPorts[i].pos == destPort.pos)
                    deliveryPorts[i].occupied = destPort.occupied;

        Serial.printf("Porta: %d Occupied: %d\n", destPort.pos, destPort.occupied);
    }

    if (destPort.occupied == true)
    {
        for (int i = 0; i < deliveryPorts.size(); i++)
        {
            if (deliveryPorts[i].pos == destPort.pos)
                deliveryPorts[i].occupied = destPort.occupied;
        }
        destPort = getAvailablePort();

        Serial.printf("Porta: %d Occupied: %d\n", destPort.pos, destPort.occupied);
    }
    else
    {
        Serial.printf("Porta: %d Occupied: %d\n", destPort.pos, destPort.occupied);
    }

    dijkstra.findPath(graph, currentPosition, destPort.pos);
    auto path = dijkstra.getPathArray();
    int size = dijkstra.getPathSize();
    currentPosition = path[dijkstra.getPathSize() - 1];

    nodeVec = (Node *)calloc(N_NODES, sizeof(Node));
    dir.nodeVector(nodeVec);
    return dir.definePath(path, size, nodeVec);
}

std::vector<std::string> Scheduler::getRoute()
{
    Box box = queue.top();
    queue.pop();

    dijkstra.findPath(graph, currentPosition, box.pos);
    auto path = dijkstra.getPathArray();
    int size = dijkstra.getPathSize();
    currentPosition = path[dijkstra.getPathSize() - 1];

    nodeVec = (Node *)calloc(N_NODES, sizeof(Node));
    dir.nodeVector(nodeVec);
    return dir.definePath(path, size, nodeVec);
}

Box Scheduler::getBox()
{
    return queue.top();
}

Port Scheduler::getAvailablePort()
{
    for (auto port : deliveryPorts)
    {
        if (port.occupied == false)
            return port;
    }
}

Node *Scheduler::getNodeVec()
{
    return nodeVec;
}