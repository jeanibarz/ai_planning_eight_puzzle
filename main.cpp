#include <iostream>

#include <array>
#include <queue>
#include <vector>
#include <memory>
#include <unordered_set>
#include <unordered_map>

#include <Node.h>

using namespace std;

int searchBestPath(array<uint8_t,9> const & start_grid, array<uint8_t,9> const & goal_grid)
{
    unique_ptr<Node const> start_node (new Node(start_grid));
    unique_ptr<Node const> goal_node (new Node(goal_grid));

    vector<unique_ptr<Node const>> nodes_manager;
    unordered_set<Node const *, hashNodeGridAndCost, compareNodeGridAndCost> explored_nodes;
    priority_queue<Node const *, vector<Node const *>, priorityNodeLowerHeuristic> queued_nodes;

    queued_nodes.push(start_node.get());

    Node const * current_node;
    vector<unique_ptr<Node>> next_nodes;

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

        next_nodes = current_node->successors(); // gets nodes ownership
        for(uint8_t i = 0; i < next_nodes.size(); ++i)
        {
            next_nodes[i]->setHeuristic();
            queued_nodes.push(next_nodes[i].get());
            nodes_manager.emplace_back(move(next_nodes[i]));
        }
    }

    return -1;
}

int searchDifferentStates(array<uint8_t,9> const & start_grid, uint8_t const distance)
{
    unique_ptr<Node const> start_node(new Node(start_grid));

    vector<unique_ptr<Node const>> nodes_manager;
    unordered_set<Node const *, hashNodeGridOnly, compareNodeGridOnly> explored_nodes;
    priority_queue<Node const *, vector<Node const *>, priorityNodeLowerCost> queued_nodes;
    vector<Node const *> solutions;

    queued_nodes.push(start_node.get());
    nodes_manager.emplace_back(move(start_node));

    Node const * current_node;
    vector<unique_ptr<Node>> next_nodes;

    while(!queued_nodes.empty())
    {
        current_node = queued_nodes.top();
        queued_nodes.pop();

        if(explored_nodes.find(current_node)!=explored_nodes.end())
        {
            continue;
        }

        explored_nodes.insert(current_node);

        if(current_node->getPathCost() == distance)
        {
            solutions.emplace_back(current_node);
            continue;
        }

        next_nodes = current_node->successors();

        for(uint8_t i = 0; i < next_nodes.size(); ++i)
        {
            if(explored_nodes.find(next_nodes[i].get())!=explored_nodes.end()) continue;

            queued_nodes.push(next_nodes[i].get());
            unique_ptr<Node> my_node = move(next_nodes[i]);
            nodes_manager.emplace_back(move(my_node));
        }
    }

    cout << "Nodes:" << nodes_manager.size() << endl;

    return solutions.size();
}

int main()
{
    cout << "Q1: " << searchBestPath(array<uint8_t,9> { 1,6,4,8,7,0,3,2,5 }, array<uint8_t,9> { 0,1,2,3,4,5,6,7,8 }) << endl;
    // Last answer : 21
    cout << "Q2: " << searchBestPath(array<uint8_t,9> { 8,1,7,4,5,6,2,0,3 }, array<uint8_t,9> { 0,1,2,3,4,5,6,7,8 }) << endl;
    // Last answer : 25
    cout << "Q3: " << searchDifferentStates(array<uint8_t,9> { 0,1,2,3,4,5,6,7,8 }, 27) << endl;
    // Last answer : 6274

    return 0;
}
