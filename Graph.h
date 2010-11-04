#pragma once

#include "Edge.h"
#include "Vertex.h"
#include "Node.h"

class Graph {
public:
	Graph();
	~Graph();
	Vertex* getFirstVertex();
	Node* getTreeRoot();
	// TBD: Vertex per Konstruktor im Graphen erzeugen
	Vertex* InsVertex(string label);
	Vertex* InsVertex();
	void InsVertex(Vertex* vertex);
	void InsEdge(Vertex* fromVertex, Vertex* toVertex, int weight);
	void Prim();

private:
	Vertex* firstVertex;
	Vertex* treeRoot;
	Base* minWeightEdge(Base* vertex);
};

