#include "Node.h"

#include <array>
#include <iostream>

using namespace std;

array<uint8_t,9> Node::getGrid() const
{
    return array<uint8_t,9>(grid);
}

uint8_t Node::getBlankCell() const
{
    return blank_cell;
}

uint16_t Node::getPathCost() const
{
    return path_cost;
}

uint16_t Node::getHeuristic() const
{
    return heuristic;
}
/*
vector<shared_ptr<Node>> Node::getParentsNodes() const
{
    return vector<shared_ptr<Node>>(parents_nodes);
}
*/
void Node::setBlankCell()
{
    for(uint8_t i = 0; i < 9; ++i)
    {
        if(grid[i]==0)
        {
            blank_cell = i;
            return;
        }
    }
}

void Node::setHeuristic()
{
    uint8_t h = 0;
    uint8_t deltaX;
    uint8_t deltaY;

    for(uint8_t i = 0; i < blank_cell; ++i)
    {
        deltaX=abs(i%3-grid[i]%3);
        deltaY=abs(i/3-grid[i]/3);
        //cout << "X:" << deltaX << " ; Y:" << deltaY << endl;
        h += deltaX+deltaY;
    }
    for(uint8_t i = blank_cell+1; i < 9; ++i)
    {
        deltaX=abs(i%3-grid[i]%3);
        deltaY=abs(i/3-grid[i]/3);
        //cout << "X:" << deltaX << " ; Y:" << deltaY << endl;
        h += deltaX+deltaY;
    }

    uint8_t const g = path_cost;
/*
    cout << "Path_cost: " << g << endl;
    cout << "H cost: " << h << endl;
*/
    heuristic = h+g;
}
/*
void Node::setParentsNodes(vector<shared_ptr<Node>> _parents_nodes)
{
    parents_nodes = _parents_nodes;
}*/

vector<unique_ptr<Node>> Node::successors() const
{
    vector<unique_ptr<Node>> next_nodes;

    uint8_t const col=blank_cell%3;
    uint8_t const row=blank_cell/3;

    if(col>0) next_nodes.push_back(moveCell(Actions::MOVE_RIGHT));
    if(col<2) next_nodes.push_back(moveCell(Actions::MOVE_LEFT));
    if(row>0) next_nodes.push_back(moveCell(Actions::MOVE_DOWN));
    if(row<2) next_nodes.push_back(moveCell(Actions::MOVE_UP));

    return next_nodes;
}

unique_ptr<Node> Node::moveCell(Actions action) const
{
    array<uint8_t,9> initial_grid = grid;
    array<uint8_t,9> new_grid = grid;
    uint8_t new_blank_cell, moved_cell;

    switch(action)
    {
        case MOVE_RIGHT:
            moved_cell = blank_cell-1;
            break;
        case MOVE_LEFT:
            moved_cell = blank_cell+1;
            break;
        case MOVE_UP:
            moved_cell = blank_cell+3;
            break;
        case MOVE_DOWN:
            moved_cell = blank_cell-3;
            break;
    };

    new_grid[blank_cell]=new_grid[moved_cell];
    new_grid[moved_cell]=0;
    new_blank_cell=moved_cell;

    unique_ptr<Node> new_node(new Node(new_grid, new_blank_cell, path_cost+1));

    if(new_grid == initial_grid) cout << "ERREUR" << endl;

    return new_node;
}

Node::Node(Node const & n)
: Node(n.grid, n.blank_cell, n.path_cost, n.heuristic, n.parents_nodes)
{
    //cout << "node copy constructor" << endl;
}
Node::Node(array<uint8_t,9> const & _grid)
: grid(_grid), path_cost(0), heuristic(0), parents_nodes(vector<shared_ptr<Node>>(0))
{
    //cout << "node constructor 1" << endl;
    setBlankCell();
}
Node::Node(array<uint8_t,9> const & _grid, uint8_t _blank_cell)
: Node(_grid, _blank_cell, 0)
{
    //cout << "node constructor 2" << endl;
}
Node::Node(array<uint8_t,9> const & _grid, uint8_t _blank_cell, uint16_t _path_cost)
: Node(_grid, _blank_cell, _path_cost, 0, vector<shared_ptr<Node>>(0))
{
    //cout << "node constructor 3" << endl;
}
Node::Node(array<uint8_t,9> const & _grid, uint8_t _blank_cell, uint16_t _path_cost, uint8_t heuristic, vector<shared_ptr<Node>> _parents_nodes)
: grid(_grid), blank_cell(_blank_cell), path_cost(_path_cost), heuristic(0), parents_nodes(_parents_nodes)
{
    //cout << "node constructor 3" << endl;
}

Node::~Node()
{
    //cout << "node destructor" << endl;
}

bool priorityNodeLowerHeuristic::operator()(Node const * const n1, Node const * const n2) const
{
    return (n1->getHeuristic() >= n2->getHeuristic()); // prioritize low path cost
}

bool priorityNodeLowerCost::operator()(Node const * n1, Node const * n2) const
{
    return (n1->getPathCost() >= n2->getPathCost());
}

size_t hashNodeGridOnly::operator()(Node const * node) const
{
    size_t value = 0;
    array<uint8_t,9> grid = node->getGrid();

    for(int i = 0; i < 9; ++i)
    {
        value ^= grid[i] << (3*i);
    }

    return value;
}

size_t hashNodeGridAndCost::operator()(Node const * node) const
{
    size_t value = 0;
    array<uint8_t,9> grid = node->getGrid();

    for(int i = 0; i < 9; ++i)
    {
        value ^= grid[i] << (3*i);
    }

    value ^= node->getPathCost();

    return value;
}

bool compareNodeGridOnly::operator()(Node const * n1, Node const * n2) const
{
    array<uint8_t,9> const grid1 = n1->getGrid();
    array<uint8_t,9> const grid2 = n2->getGrid();

    for(int i = 0; i < 9; ++i)
    {
        if(grid1[i]!=grid2[i]) return false;
    }

    return true;
}

bool compareNodeGridAndCost::operator()(Node const * n1, Node const * n2) const
{
    array<uint8_t,9> const grid1 = n1->getGrid();
    array<uint8_t,9> const grid2 = n2->getGrid();

    for(int i = 0; i < 9; ++i)
    {
        if(grid1[i]!=grid2[i]) return false;
    }

    if (n1->getPathCost() != n2->getPathCost()) return false;

    return true;
}
