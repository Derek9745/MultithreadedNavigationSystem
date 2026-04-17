
#pragma once
#include <vector>
#include <iostream>

// Node.h and Edge.h must be included BEFORE Graph.h

using namespace std;

struct Edge {
	int to;
	float cost;
};


//graph node representation
struct Node {
	int id;
	int x;
	int y;
};




class Graph {
	vector<vector<Edge>> adjList;
	vector<Node>nodeList;


public:
	Graph(const vector<vector<Edge>>& adjList, vector<Node>nodeList) {
		this->adjList = adjList;
		this->nodeList = nodeList;

	}

	const vector<Node>& getNodeList() const {
		return nodeList;
	}

	const vector<vector<Edge>>& getAdjacent() const {
		return adjList;
	}

	void SetNode(int id, int x, int y) {
		if (id >= 0 && id < nodeList.size()) {
			nodeList[id].x = x;
			nodeList[id].y = y;
		}
	}

	void InsertEdge(int from, int to, float cost) {
		adjList[from].push_back({ to, cost });
	}

	//for loop to iterate through the graph and print all the nodes in the graph
	void PrintGraph() {
		for (int i = 0; i < adjList.size(); i++) {
			cout << "vertex: " << i << endl;
			for (int j = 0; j < adjList[i].size(); j++) {
				cout << "neighbor vertex: " << adjList[i][j].to << ", weight: " << adjList[i][j].cost << endl;
			}

		}
	}

};


