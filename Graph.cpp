#pragma once
#include "Graph.h"
//#define PSEUDO NULL;

Graph::Graph() {
	this->firstVertex = NULL;
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
	NewEdge1->setTarget(v2);
	
	NewEdge1->setNext((Edge*)v1->getEdge());
	v1->setEdge(NewEdge1);


	Edge *NewEdge2 = new Edge(weight);
	NewEdge2->setTarget(v1);
	
	NewEdge2->setNext((Edge*)v2->getEdge());
	v2->setEdge(NewEdge2);

	return NewEdge1;

}

void Graph::InsVertex(Vertex * vertex) {
	Vertex* second = this->firstVertex;
	this->firstVertex = vertex;
	vertex->setNext(second);
	/*if (this->firstVertex == NULL)
		this->firstVertex = vertex;
	else {
		Vertex * tmp = this->firstVertex;
		this->firstVertex = vertex;
		vertex->setNext(tmp);
	}*/
}


Graph::~Graph() {
	delete this->firstVertex;
}

void Graph::setTreeRoot(Vertex* newRoot) {
	this->treeRoot = newRoot;
}

void Graph::Prim() {
	Vertex* p = NULL;
	Vertex* minEdgeFromHere = NULL;
	Edge* minEdge = NULL;
	Edge* e = NULL;
	bool unmarkedFound = true;
	
	this->firstVertex->setMarked(true);
	
	while (unmarkedFound) {
		unmarkedFound = false;
		p = this->firstVertex;
		minEdge = NULL;		// Korrigiert: reset!
		while (p != NULL) {
			if (p->isMarked()) {	
				e = (Edge*)p->getEdge();
				// kleinste Kante suchen
				while (e != NULL) {
					// Erstmal eine beliebige als kleinste annehmen
					if (minEdge == NULL) {
						if (!e->getTarget()->isMarked()) {
							minEdge = e;
							minEdgeFromHere = p;
						}
					}
					// Vergleichen und wenn kleiner, neue kleinste Ecke setzen
					else {
						if ((!e->getTarget()->isMarked()) && (e->getWeight() < (minEdge->getWeight()))) {
							minEdge = e;
							minEdgeFromHere = p;
						}
					}
					e = e->getNext();
				}
			}
			else {
				unmarkedFound = true;
			}
			p = p->getNext();
		}
		
		if(minEdge == NULL)	// extra ueberprfuefung, ob wir den letzten Edge erreicht hatten
			continue;

		moveEdge(minEdgeFromHere, minEdge);		// Ans Ende der markierten Kanten einfügen
		minEdge->setMarked(true);
		minEdge->getTarget()->setMarked(true);
		
		// Die umgekehrte Kante auch markieren (Euler-Bedingung)
		e = (Edge*)((Vertex*)minEdge->getTarget())->getEdge();		// Korrigiert: ->getSecondP(), da bei einer Ecke angefangen werden muss
		while (e != NULL) {
			if (e->getTarget() == minEdgeFromHere) {	
				moveEdge((Vertex*)minEdge->getTarget(), e);		// Und richtig einreihen
				e->setMarked(true);
				break;
			}
			e = e->getNext();
		}
	}
}

//Verschiebt die Kante edge so, dass sie als letzte markierte Kante in der Eckenliste von baseVertex steht
void Graph::moveEdge(Vertex *baseVertex, Edge *edge) {
	//Edge* lastMarked = (Edge*)baseVertex->getEdge();
	Edge* lastMarked = NULL;
	Edge *e = (Edge*)baseVertex->getEdge();
	Edge* beforeEdge;
	
	/*vielleicht Edge zum Einfuegen, steht schon als erster 
	Element in der Edge-Liste, dann muessen wir nicht tun*/
	if(e == edge)	// 
	{
		return;
	}

	while (e != NULL && e->isMarked() && e->getWeight() < ((Edge*)edge)->getWeight() ) {
		lastMarked = e;
		e = (Edge*)e->getNext();
	}

	if (lastMarked == NULL)		// keine markierten Kanten
	{
		// Vorherige suchen
		while (e != NULL)
		{	
			if (e == edge)
				break;
			beforeEdge = e;
			e = e->getNext();
		}
		beforeEdge->setNext(edge->getNext());	// auch wenn NULL
		edge->setNext((Edge*)baseVertex->getEdge());
		baseVertex->setEdge(edge);
		return;
	}
	else
	{
		// Vorherige suchen
		e = (Edge*)baseVertex->getEdge();
		//if (e->getWeight() > edge->getWeight()) 
		//{
		//	// Am Anfang einfügen
		//	return;
		//}
		while (e != NULL)
		{	
			if (e == edge)
				break;
			beforeEdge = e;
			e = e->getNext();
		}
		beforeEdge->setNext(edge->getNext());	// auch wenn NULL
		edge->setNext(lastMarked->getNext());
		lastMarked->setNext(edge);
		return;
	}
	
	

	//if (e != NULL)	// falls e ist nicht NULL
	//	e->setSecondP(edge->getSecondP());	// wir muessen den alten Zeiger von edge speichern
	
	if (edge != e)
	{
		lastMarked->setSecondP(edge);
		edge->setSecondP(e);
	}
}

void Graph::Cycle() {
	Vertex* start = this->treeRoot;
	cout << ((Vertex*)start)->getLabel() << "\t\t" << "0 km" << endl;
	Vertex* last;
	last = go(start);
	cout << ((Vertex*)start)->getLabel() << "\t\t" << weightBetween(last, start) << " km" << endl;
}

Vertex* Graph::go(Vertex* vertex) {
	bool isLeave = true;
	Vertex* leave = NULL;
	Vertex *next;
	Vertex* r;
	Edge* re;

	vertex->setMarked(false);

	Edge *e = (Edge*)vertex->getEdge();
	
	while (e != NULL /*&& e->isMarked()*/) {
		if (e->isMarked()) {
			isLeave = false;
			next = (Vertex*)e->getTarget();
			
			e->setMarked(false);		// Fehler: die Rückkante muss auch gelöscht werde, weil sie niemals gegangen wird, ausser es gibt nur 2 Knoten
			// Rückkante löschen
			r = (Vertex*)e->getTarget();
			re = (Edge*)r->getEdge();
			while (re != NULL) 
			{
				if ((Vertex*)re->getTarget() == vertex)
				{
					re->setMarked(false);
				}
				re = re->getNext();
			}
			if (next->isMarked()) {
				if (leave != NULL) {
					// Abstand leave<->dieser berechnen und ausgeben
					cout << ((Vertex*)next)->getLabel() << "\t\t" << weightBetween(leave, next) << " km" << endl;
					leave = NULL;
				}
				else {
					cout << ((Vertex*)next)->getLabel() << "\t\t" << e->getWeight() << " km" << endl;		// Ausgabe der nächsten Stadt
				}
				leave = go(next);
				
			}
		}
		e = e->getNext();
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

