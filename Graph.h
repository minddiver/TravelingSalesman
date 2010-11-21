#pragma once
#define PSEUDO NULL;
#include "Edge.h"
#include "Vertex.h"
//#include "Node.h"

class Graph {
public:
	Graph();
	~Graph();
	//Vertex* getFirstVertex();
	//Node* getTreeRoot();
	// TBD: Vertex per Konstruktor im Graphen erzeugen
	//Vertex* InsVertex(string label);
	//Vertex* InsVertex();
	void InsVertex(Vertex * vertex);
	Edge * InsEdge(Vertex * v1, Vertex * v2, int weight);
	void Prim();

private:
	Vertex* firstVertex;

	//Node* treeRoot;
	//Base* minWeightEdge(Base* vertex);
};

