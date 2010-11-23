#pragma once

#include "Edge.h"
#include "Vertex.h"


class Graph {
public:
	Graph();
	~Graph();
	void setTreeRoot(Base* newRoot);
	void InsVertex(Vertex * vertex);
	Base * InsEdge(Vertex* v1, Vertex* v2, int weight);
	void Prim();
	void Cycle();

private:
	Base* firstVertex;
	void moveEdge(Base* baseVertex, Base* edge);
	//void moveEdge(Base* baseVertex, Base* lastMarkedEdge, Base* edgeBefore, Base* edge);
	Base* go(Base *vertex);
	Base* treeRoot;
	int weightBetween(Base* v1, Base* v2);
};

