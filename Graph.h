#pragma once

#include "Edge.h"
#include "Vertex.h"


class Graph {
public:
	Graph();
	Graph(Graph* toCopy);					//implement
	~Graph();
	void InsVertex(string label);			//implement
	void InsEdge(string v1, string v2);		//implement
	Base* getFirstVertex();					//implement
	void setTreeRoot(string label);			//implement
	void Prim();
	void Cycle();
	Graph* copy();							//implement

private:
	Base* firstVertex;
	void InsEdge(Vertex* v1, Vertex* v2, int weight);		//change private	
	void InsVertex(Vertex * vertex);						//change private
	void setTreeRoot(Base* newRoot);						//change private
	void moveEdge(Base* baseVertex, Base* lastMarkedEdge, Base* edgeBefore, Base* edge);
	Base* go(Base *vertex);
	Base* treeRoot;
	int weightBetween(Base* v1, Base* v2);
};

