#pragma once
#include "Graph.h"
#define PSEUDO NULL;

Graph::Graph() {
	this->firstVertex = PSEUDO;
	//this->treeRoot = PSEUDO;
}

/*	Es muss sichergestellt sein, dass beide Vertices bereits im Graph 
	enthalten sind. Ferner darf die Kante noch nicht existieren. (Performance!)
	Erwartet 2 Referenzen auf die zu verbindenden Ecken (Ecken m�ssen dazu evtl. gesucht werden bzw.
	beim Erstellen des Grpahen gleich eingef�gt werden. Der Graph ist vollst�ndig, d.h. alle 
	Ecken sind miteinander verbunden --> Die Darstellung des Graphen ist nicht optimal!!!
	Zu einer optimalen Darstellung (v.a. wenn man davon ausgehen kann, dass die Gewichte
	in beide Richtungen gleich sind!) Dann kann man ein 2D-statisches Array verwenden, in dem
	alle Eckenpaare vorkommen (Anzahl der Kombinationen bei n Ecken: 
*/
Edge * Graph::InsEdge(Vertex * v1, Vertex * v2, int weight) {
	
	//Base* lastEdge = v1->getSecondP();
	//Base* newEdge = new Edge(weight);
	//if (lastEdge != NULL) {
	//	newEdge->setSecondP(lastEdge);
	//}
	//newEdge->setFirstP(v2);
	//v1->setSecondP(newEdge);
	//lastEdge = NULL;

	//Base* lastEdge2 = v2->getSecondP();
	//Base * newEdge2 = new Edge(weight);
	//if (lastEdge2 != NULL) {
	//	newEdge2->setSecondP(lastEdge2);
	//}
	//newEdge2->setFirstP(v1);
	//v2->setSecondP(newEdge2);
	//lastEdge2 = NULL;

	//return (Edge*)newEdge;

	Edge *NewEdge1 = new Edge(weight);
	NewEdge1->setFirstP(v2);
	
	NewEdge1->setSecondP(v1->getSecondP());
	v1->setSecondP(NewEdge1);


	Edge *NewEdge2 = new Edge(weight);
	NewEdge2->setFirstP(v1);
	
	NewEdge2->setSecondP(v2->getSecondP());
	v2->setSecondP(NewEdge2);

	return NewEdge1;

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
	delete this->firstVertex;
}

void Graph::setTreeRoot(Vertex* newRoot) {
	this->treeRoot = newRoot;
}

void Graph::Prim() {
	Base* p;
	Base* minEdgeFromHere;
	Base* minEdge = NULL;
	Base* e;
	bool unmarkedFound = true;
	
	p = this->firstVertex;
	p->setMarked(true);
	
	while (unmarkedFound) {
		unmarkedFound = false;
		p = this->firstVertex;
		minEdge = NULL;		// Korrigiert: reset!
		while (p != NULL) {
			if (p->isMarked()) {	
				e = p->getSecondP();
				// kleinste Kante suchen
				while (e != NULL) {
					// Erstmal eine beliebige als kleinste annehmen
					if (minEdge == NULL) {
						if (!e->getFirstP()->isMarked()) {
							minEdge = e;
							minEdgeFromHere = p;
						}
					}
					// Vergleichen und wenn kleiner, neue kleinste Ecke setzen
					else {
						if ((!e->getFirstP()->isMarked()) && (((Edge*)e)->getWeight() < ((Edge*)minEdge)->getWeight())) {
							minEdge = e;
							minEdgeFromHere = p;
						}
					}
					e = e->getSecondP();
				}
			}
			else {
				unmarkedFound = true;
			}
			p = p->getFirstP();
		}
		
		if(minEdge == NULL)	// extra ueberprfuefung, ob wir den letzten Edge erreicht hatten
			continue;

		minEdge->setMarked(true);
		moveEdge(minEdgeFromHere, minEdge);		// Ans Ende der markierten Kanten einf�gen
		(minEdge->getFirstP())->setMarked(true);
		
		// Die umgekehrte Kante auch markieren (Euler-Bedingung)
		e = minEdge->getFirstP()->getSecondP();		// Korrigiert: ->getSecondP(), da bei einer Ecke angefangen werden muss
		while (e != NULL) {
			if (e->getFirstP() == minEdgeFromHere) {	
				e->setMarked(true);
				moveEdge(minEdge->getFirstP(), e);		// Und richtig einreihen
				break;
			}
			e = e->getSecondP();
		}
	}
}

//Verschiebt die Kante edge so, dass sie als letzte markierte Kante in der Eckenliste von baseVertex steht
void Graph::moveEdge(Base *baseVertex, Base *edge) {
	Base *last = baseVertex;
	Base *e = last->getSecondP();

	if(last->getSecondP() == edge)	// vielleicht Edge zum Einfuegen, steht schon als erster Element in der Edge-Liste, dann muessen wir nicht tun
	{
		return;
	}

	while (e != NULL && e->isMarked() && ((Edge*)e)->getWeight() < ((Edge*)edge)->getWeight() ) {
		last = e;
		e = e->getSecondP();
	}
	last->setSecondP(edge);

	if (e != NULL)	// falls e ist nicht NULL
		e->setSecondP(edge->getSecondP());	// wir muessen den alten Zeiger von edge speichern
	
	edge->setSecondP(e);
}

void Graph::Cycle() {
	Base* start = this->treeRoot;
	cout << ((Vertex*)start)->getLabel() << "\t\t" << "0 km" << endl;
	Base* last;
	last = go(start);
	cout << ((Vertex*)start)->getLabel() << "\t\t" << weightBetween(last, start) << " km" << endl;
}

Base* Graph::go(Base *vertex) {
	bool isLeave = true;
	Base* leave = NULL;
	Base *next;

	Base *e = vertex->getSecondP();
	
	while (e != NULL && e->isMarked()) {
		if (e->isMarked()) {
			isLeave = false;
			next = e->getFirstP();
			e->setMarked(false);
			if (leave != NULL) {
				// Abstand leave<->dieser berechnen und ausgeben
				cout << ((Vertex*)leave)->getLabel() << "\t\t" << weightBetween(leave, next) << " km" << endl;
				leave = NULL;
			}
			cout << ((Vertex*)next)->getLabel() << "\t\t" << ((Edge*)e)->getWeight() << " km" << endl;		// Ausgabe der n�chsten Stadt
			leave = go(next);
		}
		else {
			break;		// Wenn keine markierten Kanten (mehr), zur�ckkehren, 
		}
		e = e->getSecondP();
	}
	if (isLeave) {
		return vertex;
	}
	else {
		return leave;
	}
}

int Graph::weightBetween(Base* v1, Base* v2) {
	Base* e = v1->getSecondP();
	while (e != NULL) {
		if (e->getFirstP() == v2) {
			return ((Edge*)e)->getWeight();
		}
		e = e->getSecondP();
	}
	return -1;		// sollte nicht passieren
}

