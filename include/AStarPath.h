#pragma once
#include "Graph.h"


// Result returned by A*
struct AStarResult
{
    vector<int> path;        
    vector<int> distances; 
    float totalCost;
};

// Core A* function
AStarResult AStar(const Graph& graph, int start, int end);
