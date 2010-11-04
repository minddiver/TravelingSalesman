#pragma once
#include "Graph.h"

Graph::Graph() {
	this->firstVertex = PSEUDO;
	this->treeRoot = PSEUDO;
}

/*	Es muss sichergestellt sein, dass beide Vertices bereits im Graph 
	enthalten sind. Ferner darf die Kante noch nicht existieren.
*/
void Graph::InsEdge(Vertex *v1, Vertex *v2, int weight) {
	Edge* lastEdge = v1->getSecondP();
	Edge* newEdge = new Edge(weight);
	if (lastEdge != PSEUDO) {
		newEdge->setSecondP(lastEdge);
	}
	newEdge->setFirstP(v2);
	v1->setSecondP(newEdge);

	lastEdge = v2->getSecondP();
	newEdge = new Edge(weight);
	if (lastEdge != PSEUDO) {
		newEdge->setSecondP(lastEdge);
	}
	newEdge->setFirstP(v1);
	v2->setSecondP(newEdge);
}

void Graph::InsVertex(Vertex *vertex) {
	Vertex* v;
	v = this->getFirstVertex();
	vertex->setFirstP(v);
	this->firstVertex = vertex;
}

Vertex* Graph::InsVertex(string label) {
	Vertex* newVertex = new Vertex();
	newVertex->setLabel(label);
	InsVertex(newVertex);
	return newVertex;	
}

Vertex* Graph::InsVertex() {
	Vertex* newVertex = new Vertex();
	InsVertex(newVertex);
	return newVertex;
}

Vertex* Graph::getFirstVertex() {
	return this->firstVertex;
}

Node* Graph::getTreeRoot() {
	return this->treeRoot;
}

Graph::~Graph() {
	// TBD: Alle erzeugten Strukturen löschen
}

void Graph::Prim() {
	Edge* vMinWeight;
	Edge* vTmpWeight;
	int iMinWeight = 10000;
	int iTmpWeight;
	Node* tmpNode = new Node(this->firstVertex);
	Base* tmpVertex = this->firstVertex;
	Base* tmpEdge;
	this->firstVertex->setFlag(true);
	this->treeRoot = tmpNode;
	
	// Kante mit der minimalen Länge für alle markierten Knoten suchen.
	while (tmpVertex != PSEUDO) {
		if (tmpVertex->getFlag() == true) {
			vTmpWeight = minWeightEdge(tmpVertex);
			iTmpWeight = minWeight->getWeight();
			if (iTmpWeight < iMinWeight) {
				iMinWeight = iTmpWeight;
				vMinWeight = vTmpWeight;
			}
		}
		tmpVertex = tmpVertex->getFirstP();
	}
	// Kante der minimalen Länge gefunden. In den Baum einfügen.


}

/*	Findet zu einem Knoten die Kante mit der minimalen Länge.
	Rückgabewert: Kante mit der minimalen Länge.
*/
Base* Graph::minWeightVertex(Base *vertex) {
	Base* tmpEdge;
	Base* minWeight = PSEUDO;
	int tmpWeight;

	tmpEdge = vertex;
	while (tmpEdge != PSEUDO) {
		tmpEdge = tmpEdge->getSecondP;
		tmpWeight = ((Edge*)tmpEdge)->getWeight();
		if (tmpWeight < ((Edge*)minWeight)->getWeight()) {
			minWeight = tmpEdge;
		}
	}
	minWeight->setFlag(true);
	return minWeight;
}
