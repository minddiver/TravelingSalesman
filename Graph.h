#pragma once

#include "Edge.h"
#include "Vertex.h"


class Graph {
public:
	Graph();
	Graph(Graph* toCopy);								//implement W	DONE! (to be tested)
	~Graph();
	void InsVertex(string label);						//implement J
	void InsEdge(string v1, string v2, int weight);		//implement J
	Base* getFirstVertex();	
	void setTreeRoot(string label);						//implement J
	void Prim();
	void Cycle();
	Graph* copy();										//implement W	DONE! (to be tested)
	Graph operator=(Graph other);						//implement W

private:
	Base* firstVertex;
	void InsEdge(Vertex* v1, Vertex* v2, int weight);		//change private	
	void InsVertex(Vertex * vertex);						//change private
	void setTreeRoot(Base* newRoot);						//change private
	void moveEdge(Base* baseVertex, Base* lastMarkedEdge, Base* edgeBefore, Base* edge);
	Vertex* findVertex(string label);		//implement	J
	Base* go(Base *vertex);
	Base* treeRoot;
	int weightBetween(Base* v1, Base* v2);
};

