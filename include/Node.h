#ifndef NODE_H
#define NODE_H

#include <array>
#include <vector>
#include <memory>

#include <utils.h>

using namespace std;

enum Actions { MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };

class Node
{
    array<uint8_t,9> grid;
    uint8_t blank_cell;
    uint16_t path_cost;
    uint16_t heuristic;
    vector<shared_ptr<Node>> parents_nodes;

    public:

    array<uint8_t,9> getGrid() const;
    uint8_t getBlankCell() const;
    uint16_t getPathCost() const;
    uint16_t getHeuristic() const;
    //vector<shared_ptr<Node>> getParentsNodes() const;

    void setBlankCell();
    void setHeuristic();
    //void setParentsNodes(vector<shared_ptr<Node>> _parents_nodes);

    vector<unique_ptr<Node>> successors() const;

    unique_ptr<Node> moveCell(Actions action) const;

    explicit Node(Node const & n);
    explicit Node(array<uint8_t,9> const & _grid);
    Node(array<uint8_t,9> const & _grid, uint8_t _blank_cell);
    Node(array<uint8_t,9> const & _grid, uint8_t _blank_cell, uint16_t _path_cost);
    Node(array<uint8_t,9> const & _grid, uint8_t _blank_cell, uint16_t _path_cost, uint8_t heuristic, vector<shared_ptr<Node>> _parents_nodes);

    ~Node();
};

struct priorityNodeLowerHeuristic
{
    bool operator()(Node const * n1, Node const * n2) const;
};

struct priorityNodeLowerCost
{
    bool operator()(Node const * n1, Node const * n2) const;
};

struct hashNodeGridOnly
{
    size_t operator()(Node const * node) const;
};

struct hashNodeGridAndCost
{
    size_t operator()(Node const * node) const;
};

struct compareNodeGridOnly
{
    bool operator()(Node const * n1, Node const * n2) const;
};

struct compareNodeGridAndCost
{
    bool operator()(Node const * n1, Node const * n2) const;
};

#endif // NODE_H
