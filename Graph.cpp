#pragma once
#include "Graph.h"
#define PSEUDO NULL;

Graph::Graph() {
	this->firstVertex = PSEUDO;
	//this->treeRoot = PSEUDO;
}

/*	Es muss sichergestellt sein, dass beide Vertices bereits im Graph 
	enthalten sind. Ferner darf die Kante noch nicht existieren. (Performance!)
	Erwartet 2 Referenzen auf die zu verbindenden Ecken (Ecken müssen dazu evtl. gesucht werden bzw.
	beim Erstellen des Grpahen gleich eingefügt werden. Der Graph ist vollständig, d.h. alle 
	Ecken sind miteinander verbunden --> Die Darstellung des Graphen ist nicht optimal!!!
	Zu einer optimalen Darstellung (v.a. wenn man davon ausgehen kann, dass die Gewichte
	in beide Richtungen gleich sind!) Dann kann man ein 2D-statisches Array verwenden, in dem
	alle Eckenpaare vorkommen (Anzahl der Kombinationen bei n Ecken: 
*/
Edge* Graph::InsEdge(Vertex * v1, Vertex * v2, int weight) {
	Edge* lastEdge = v1->getSecondP();
	Edge* newEdge = new Edge(weight);
	if (lastEdge != NULL) {
		newEdge->setNext(lastEdge);
	}
	newEdge->setTarget(v2);
	v1->setSecondP(newEdge);

	lastEdge = v2->getSecondP();
	Edge* newEdge2 = new Edge(weight);
	if (lastEdge != NULL) {
		newEdge2->setNext(lastEdge);
	}
	newEdge2->setTarget(v1);
	v2->setSecondP(newEdge2);

	return newEdge;
}

void Graph::InsVertex(Vertex * vertex) {
	if (this->firstVertex == NULL)
		this->firstVertex = vertex;
	else {
		Vertex * tmp = this->firstVertex;
		this->firstVertex = vertex;
		vertex->setFirstP(tmp);
	}
}


Graph::~Graph() {
	// TBD: Alle erzeugten Strukturen löschen
}

// TBD: Kodierung der bereits durchlaufenen Kanten/Ecken über ein Bit-Array, wobei eine
// 1 im Array bedeutet, dass die entsprechende Kante/Ecke markiert ist.
//Alter code:
	//// Arrays für Kanten/Ecken anlegen:
	//// Ecken werden nach der Reihenfolge in der Grpahendarstellung kodiert.
	//// Kanten 

	//// Ecken-Array vorbereiten
	//Base* tmpVertex = this->firstVertex;
	//Base* tmpEdge;
	//int vCount = 0;		// Der Zeiger ist bereits auf der 1. Ecke! 

	///*	
	//	vCount gibt den höchsten Exponenten der 2^vCount-Darstellung an.
	//	Eine Ecke -> 1bit -> Darstellung<=1 -> 2^0	(001)
	//	Zwei Ecken -> 2bit -> Darstellung <=2 -> 2^1 (010)
	//	Drei Ecken -> 3bit -> Darstellung <=4 -> 2^2 (100)

	//	Um rauszufinden, ob die Ecke Nr. x (x fängt bei 0 an) markiert ist, reicht ein (markedVertices & 2^x) > 0?.
	//	Bei dieser Darstellung muss der Graph durchlaufen werden, um erst die Nr. der fraglichen Ecke herauszufinden.
	//*/

	///*
	//	Alternative Darstellung: Ein statisches (aber evtl. dynamisch wachsendes) Array mit Zeigern auf die markierten Ecken.
	//	Ein analoges Array für Kanten.
	//	Die Zahl der Kanten in einem vollständigen Graphen ist n(n-1)/2, d.h. es gibt bei 100 Ecken 4950 Kanten.
	//	
	//	Speicherbedarf: 100*size(int) + 4950*size(int) bzw. (n + n(n+1)/2)*size(int) (oder size(long))
	//*/

	//// Anzahl Ecken ermitteln
	//while (tmpVertex->getFirstP != PSEUDO) {
	//	tmpVertex = tmpVertex->getFirstP;
	//	vCount++;
	//}
	//int markedVertices = 2^(vCount+1)

	//Edge* vMinWeight;
	//Edge* vTmpWeight;
	//int iMinWeight = 10000;
	//int iTmpWeight;
	//Node* tmpNode = new Node(this->firstVertex);
	//this->firstVertex->setFlag(true);
	//this->treeRoot = tmpNode;
	//
	//// Kante mit der minimalen Länge für alle markierten Knoten suchen.
	//while (tmpVertex != PSEUDO) {
	//	if (tmpVertex->getFlag() == true) {
	//		vTmpWeight = minWeightEdge(tmpVertex);
	//		iTmpWeight = minWeight->getWeight();
	//		if (iTmpWeight < iMinWeight) {
	//			iMinWeight = iTmpWeight;
	//			vMinWeight = vTmpWeight;
	//		}
	//	}
	//	tmpVertex = tmpVertex->getFirstP();
	//}
	//// Kante der minimalen Länge gefunden. In den Baum einfügen.


void Graph::Prim() {
	/*Die Typen von Vars wieder angepasst. So lässt sich das noch schöner Casten und vor allem muss nicht
	mehr bei jeder Überprüfung auf minimale Länge gecastet werden.*/
	Vertex * p;
	Vertex * minEdgeFromHere;
	Edge * minEdge = NULL;
	Edge * e;
	bool unmarkedFound = true;
	
	p = this->firstVertex;
	p->setMarked(true);
	
	while (unmarkedFound) {
		unmarkedFound = false;
		p = this->firstVertex;
		/*Korrigiert: hier sollte minEdge am Anfang von jedem Durchlauf auf NULL gesetzt werden, sonst
		ist da noch der Wert vom letzten Durchlauf gespeichert. Wenn beim nächsten Durchlauf eine
		Kante gefunden werden müsste, die wieder die gleiche Länge hat wie die minimale aus dem letzten
		Durchlauf, würde der Algorithmus sonst versagen.*/
		minEdge = NULL;		
		while (p != NULL) {
			if (p->isMarked()) {	
				e = (Edge*)p->getSecondP();
				while (e != NULL) {
					if (minEdge == NULL) {
						if (!e->getFirstP()->isMarked()) {
							minEdge = e;
							minEdgeFromHere = p;
						}
					}
					else {
						if ((!e->getFirstP()->isMarked()) && (e->getWeight() < (minEdge->getWeight()))) {
							minEdge = e;
							minEdgeFromHere = p;
						}
					}
					e = (Edge*)e->getSecondP();
				}
			}
			else {
				unmarkedFound = true;
			}
			p = (Vertex*)p->getFirstP();
		}
		minEdge->setMarked(true);
		minEdge->getFirstP()->setMarked(true);
		
		/*Korrigiert: ->getSecondP() dazugenommen. Der Durchlauf sollte bei einer Kante starten und nicht bei
		der Ecke selbst, sonst würde im ungünstigen Fall die nächste Ecke markiert. (Eigentlich wieder nicht) */
		e = minEdge->getFirstP()->getSecondP();
		while (e != NULL) {
			if (e->getFirstP() == minEdgeFromHere) {
				e->setMarked(true);
			}
			e = e->getSecondP();
		}
	}

	//TODO: Liste durchlaufen, 
	// nicht markierte Ecken suchen, 
	// minimale Kante zu einer nicht markierten Ecke bestimmen
	// v = firstV;
	// While v->getFirst != NULL (solange nicht das Ende erreicht)
	// if (! m->isMarked)
	// Kantenliste durchlaufen, alle Gewichte zu den nicht markierten Ecken vergleichen, Minimum bestimmen

	

}

/*	Findet zu einem Knoten die Kante mit der minimalen Länge.
	Rückgabewert: Kante mit der minimalen Länge.
*/
//Base* Graph::minWeightEdge(Base *vertex) {
//	Base* tmpEdge;
//	Base* minWeight = PSEUDO;
//	int tmpWeight;
//
//	tmpEdge = vertex;
//	while (tmpEdge != PSEUDO) {
//		tmpEdge = tmpEdge->getSecondP;
//		tmpWeight = ((Edge*)tmpEdge)->getWeight();
//		if (tmpWeight < ((Edge*)minWeight)->getWeight()) {
//			minWeight = tmpEdge;
//		}
//	}
//	minWeight->setFlag(true);
//	return minWeight;
//}
