
#include <vector>
#include <queue>
#include <utility>
#include <iostream>
#include <climits>
#include "AStarPath.h"

using namespace std;

//method for calculating distance between nodes
float Heuristic(const Node& a, const Node& b) {
	return abs(a.x - b.x) + abs(a.y - b.y);
}


//priority queue node for A*
struct AStarNode {
	int id;
	float g;//cost so far
	float f;//g + heuristic distance

	bool operator>(const AStarNode& other) const {
		return f > other.f;
	}
};



AStarResult AStar(Graph& graph, int startID, int destID) {
	priority_queue<AStarNode, vector<AStarNode>, greater<>> pq;

	int n = graph.getNodeList().size();

	vector<float> costSoFar(n, INT_MAX);//intital cost goes to infinity
	vector<int> prevNode(n, -1);//a list of the previous nodes taversed from


	costSoFar[startID] = 0;//holds current computed cost value

	pq.push({
	  startID,
	  0.0f,
	  Heuristic(graph.getNodeList()[startID],graph.getNodeList()[destID])
		});


	while (!pq.empty()) {        //while the priority queue is not empty
		AStarNode top = pq.top();//take the first node
		pq.pop();				 //and remove that node with smallest distance from the queue

		int u = top.id;          //and temporarily store its ID

		if (u == destID) break;  //if we have reached the destination node, stop

		if (top.g > costSoFar[top.id]) {
			continue;
		}

		//explore all adjacent neighbors of current vertex
		for (int i = 0; i < graph.getAdjacent()[u].size(); i++) {
			Edge edge = graph.getAdjacent()[u][i];
			float newCost = costSoFar[u] + edge.cost;

			//calculate if adjaxent neighbor vertex has less cost 
			if (newCost < costSoFar[edge.to]) {
				costSoFar[edge.to] = newCost;
				prevNode[edge.to] = u;

				float h = Heuristic(graph.getNodeList()[edge.to],
					graph.getNodeList()[destID]);
				pq.push({ edge.to, newCost, newCost + h });
			}
		}
	}

	AStarResult result;
	result.path = ReconstructPath(startID, destID, prevNode);
	result.distances = costSoFar;   // if you actually want full cost map
	result.totalCost = costSoFar[destID];

	return result;
};


//creating a step by step recreation of the path taken, for futue implementation of logging
vector<int> ReconstructPath(int start, int end, const vector<int>& prevNode) {
	vector<int> path;

	for (int at = end; at != -1; at = prevNode[at]) {
		path.push_back(at);
	}

	reverse(path.begin(), path.end());

	// Optional: check if path is valid
	if (path[0] != start) return {};

	return path;
}


