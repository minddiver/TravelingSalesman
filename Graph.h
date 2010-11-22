#pragma once

#include "Edge.h"
#include "Vertex.h"


class Graph {
public:
	Graph();
	~Graph();
	void setTreeRoot(Vertex* newRoot);
	void InsVertex(Vertex * vertex);
	Edge * InsEdge(Vertex * v1, Vertex * v2, int weight);
	void Prim();
	void Cycle();

private:
	Vertex* firstVertex;
	void moveEdge(Vertex* baseVertex, Edge* edge);
	Vertex* go(Vertex *vertex);
	Vertex* treeRoot;
	int weightBetween(Base* v1, Base* v2);
};

