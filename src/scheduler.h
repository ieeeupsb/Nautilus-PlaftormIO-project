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
    Dijkstra dijkstra = Dijkstra(N_NODES);
    Direction dir;
    std::priority_queue<Box, std::vector<Box>, boxComparision> queue;
    std::vector<Port> deliveryPorts;
    Port getAvailablePort();
public:
    Scheduler(Box* boxes, unsigned int numBoxes);
    ~Scheduler();
    std::vector<std::string> getRoute(int source, Box box);
    std::vector<std::string> getRoute(int source);
    Box getBox();
};

Scheduler::Scheduler(Box* boxes, unsigned int numBoxes) {
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

Scheduler::~Scheduler()
{
}

std::vector<std::string> Scheduler::getRoute(int source, Box box) {

    // TODO: Chose which port to go based on the color
    Port destPort = getAvailablePort();

    // If box is waiting then we need to pick it up
    dijkstra.findPath(graph, source, destPort.pos);
        
    auto path = dijkstra.getPathArray();

    Node *nodeVec = (Node *)calloc(N_NODES, sizeof(Node));
    dir.nodeVector(nodeVec);

    int size = dijkstra.getPathSize();
    std::vector<std::string> dirVec = dir.definePath(path, size, nodeVec);
      
    return dirVec;
}

std::vector<std::string> Scheduler::getRoute(int source) {
    Box box = queue.top();
    queue.pop();

    // If box is waiting then we need to pick it up
    dijkstra.findPath(graph, source, box.pos);
        
    auto path = dijkstra.getPathArray();

    Node *nodeVec = (Node *)calloc(N_NODES, sizeof(Node));
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