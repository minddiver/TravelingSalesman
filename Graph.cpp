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

// TBD: Kodierung der bereits durchlaufenen Kanten/Ecken über ein Bit-Array, wobei eine
// 1 im Array bedeutet, dass die entsprechende Kante/Ecke markiert ist.
void Graph::Prim() {
	// Arrays für Kanten/Ecken anlegen:
	// Ecken werden nach der Reihenfolge in der Grpahendarstellung kodiert.
	// Kanten 

	// Ecken-Array vorbereiten
	Base* tmpVertex = this->firstVertex;
	Base* tmpEdge;
	int vCount = 0;		// Der Zeiger ist bereits auf der 1. Ecke! 

	/*	
		vCount gibt den höchsten Exponenten der 2^vCount-Darstellung an.
		Eine Ecke -> 1bit -> Darstellung<=1 -> 2^0	(001)
		Zwei Ecken -> 2bit -> Darstellung <=2 -> 2^1 (010)
		Drei Ecken -> 3bit -> Darstellung <=4 -> 2^2 (100)

		Um rauszufinden, ob die Ecke Nr. x (x fängt bei 0 an) markiert ist, reicht ein (markedVertices & 2^x) > 0?.
		Bei dieser Darstellung muss der Graph durchlaufen werden, um erst die Nr. der fraglichen Ecke herauszufinden.
	*/

	/*
		Alternative Darstellung: Ein statisches (aber evtl. dynamisch wachsendes) Array mit Zeigern auf die markierten Ecken.
		Ein analoges Array für Kanten.
		Die Zahl der Kanten in einem vollständigen Graphen ist n(n-1)/2, d.h. es gibt bei 100 Ecken 4950 Kanten.
		
		Speicherbedarf: 100*size(int) + 4950*size(int) bzw. (n + n(n+1)/2)*size(int) (oder size(long))
	*/

	// Anzahl Ecken ermitteln
	while (tmpVertex->getFirstP != PSEUDO) {
		tmpVertex = tmpVertex->getFirstP;
		vCount++;
	}
	int markedVertices = 2^(vCount+1)

	Edge* vMinWeight;
	Edge* vTmpWeight;
	int iMinWeight = 10000;
	int iTmpWeight;
	Node* tmpNode = new Node(this->firstVertex);
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
Base* Graph::minWeightEdge(Base *vertex) {
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
