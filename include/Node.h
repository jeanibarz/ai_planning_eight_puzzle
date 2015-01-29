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
    vector<shared_ptr<Node>> getParentsNodes() const;

    void setBlankCell();
    void setHeuristic();
    void setParentsNodes(vector<shared_ptr<Node>> _parents_nodes);

    vector<shared_ptr<Node>> successors() const;

    shared_ptr<Node> moveCell(Actions action) const;

    Node(Node const & n);
    Node(array<uint8_t,9> const & _grid);
    Node(array<uint8_t,9> const &  _grid, uint8_t _blank_cell);
    Node(array<uint8_t,9> const & _grid, uint8_t _blank_cell, uint16_t _path_cost);
    Node(array<uint8_t,9> const & _grid, uint8_t _blank_cell, uint16_t _path_cost, uint8_t heuristic, vector<shared_ptr<Node>> _parents_nodes);

    ~Node();
};

struct priorityNode
{
    bool operator()(shared_ptr<Node const> const n1, shared_ptr<Node const> const n2) const;
};

struct priorityNodeBreadthFirst
{
    bool operator()(shared_ptr<Node const> const n1, shared_ptr<Node const> const n2) const;
};

struct hashNode
{
    size_t operator()(shared_ptr<Node const> const node) const;
};

struct hashNode2
{
    size_t operator()(shared_ptr<Node const> const node) const;
};

struct compareNode
{
    bool operator()(shared_ptr<Node const> const n1, shared_ptr<Node const> const n2) const;
};

struct compareNode2
{
    bool operator()(shared_ptr<Node const> const n1, shared_ptr<Node const> const n2) const;
};

#endif // NODE_H
