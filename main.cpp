#include <iostream>

#include <array>
#include <queue>
#include <vector>
#include <memory>
#include <unordered_set>

#include <Node.h>

using namespace std;

int searchBestPath(array<uint8_t,9> const & start_grid, array<uint8_t,9> const & goal_grid)
{
    shared_ptr<Node> start_node (new Node(start_grid));
    shared_ptr<Node> goal_node (new Node(goal_grid));

    unordered_set<shared_ptr<Node>, hashNode, compareNode> explored_nodes;
    priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, priorityNode> queued_nodes;
    vector<shared_ptr<Node>> next_nodes;

    queued_nodes.push(start_node);

    shared_ptr<Node> current_node;

    while(!queued_nodes.empty()) {
        current_node = queued_nodes.top();
        queued_nodes.pop();

        if(current_node->getGrid()==goal_node->getGrid()) {
            return current_node->getPathCost();
        }
        if(!explored_nodes.empty() && explored_nodes.find(current_node)!=explored_nodes.end()) {
            continue;
        }
        if(current_node->getPathCost() >= 40) {
            continue;
        }

        explored_nodes.insert(current_node);

        next_nodes = current_node->successors();
        for(uint8_t i = 0; i < next_nodes.size(); ++i)
        {
            next_nodes[i]->setHeuristic();
            queued_nodes.push(next_nodes[i]);
        }
    }

    return -1;
}

int searchDifferentStates(array<uint8_t,9> const & start_grid, uint8_t distance)
{
    shared_ptr<Node> start_node (new Node(start_grid));
    unordered_set<shared_ptr<Node>, hashNode2, compareNode2> explored_nodes;
    vector<shared_ptr<Node>> solutions;

    priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, priorityNodeBreadthFirst> queued_nodes;
    vector<shared_ptr<Node>> next_nodes;

    queued_nodes.push(start_node);

    shared_ptr<Node> current_node;

    while(!queued_nodes.empty())
    {
        current_node = queued_nodes.top();
        queued_nodes.pop();

        if(explored_nodes.find(current_node)!=explored_nodes.end())
        {
            continue;
        }
        if(current_node->getPathCost() == distance)
        {
            solutions.push_back(current_node);
            continue;
        }

        next_nodes = current_node->successors();
        explored_nodes.insert(current_node);

        for(uint8_t i = 0; i < next_nodes.size(); ++i)
        {
            queued_nodes.push(next_nodes[i]);
        }
    }
    /*
    // RANDOM (NOT EXACTLY) CHECKING TO SEE IF SOME STATES FOUND ARE EXACTLY AT <DISTANCE> STEPS AWAY FROM INITIAL STATE
    for(int i = 0; i < solutions.size(); ++i)
    {
        if(i%500>0) continue;

        int bestPath = searchBestPath(start_grid, solutions[i]->getGrid());
        if(bestPath != distance)
        {
            cout << "Optimal solution: " << bestPath << endl;
            cout << "Grid: " << endl << solutions[i]->getGrid() << endl;
        }
    }*/

    return solutions.size();
}

int main()
{
    cout << "Q1: " << searchBestPath(array<uint8_t,9> { 1,6,4,8,7,0,3,2,5 }, array<uint8_t,9> { 0,1,2,3,4,5,6,7,8 }) << endl;
    // Last answer : 21
    cout << "Q2: " << searchBestPath(array<uint8_t,9> { 8,1,7,4,5,6,2,0,3 }, array<uint8_t,9> { 0,1,2,3,4,5,6,7,8 }) << endl;
    // Last answer : 25
    cout << "Q3: " << searchDifferentStates(array<uint8_t,9> { 0,1,2,3,4,5,6,7,8 }, 27) << endl;
    // Last answer : 11786

    return 0;
}
