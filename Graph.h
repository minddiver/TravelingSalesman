#pragma once

#include "Edge.h"
#include "Vertex.h"

class Graph {
public:
	Graph();
	~Graph();
	Vertex* getFirstVertex();
	Vertex* getTreeRoot();
	void InsVertex(Vertex* vertex);
	void InsEdge(Vertex* fromVertex, Vertex* toVertex);

private:
	Vertex* firstVertex;
	Vertex* treeRoot;
};

