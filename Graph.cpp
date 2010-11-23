#include "Graph.h"

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
Base* Graph::InsEdge(Vertex * v1, Vertex * v2, int weight) {
	
	//Base* lastEdge = v1->getSecondP();
	//Base* newEdge = new Edge(weight);
	//if (lastEdge != PSEUDO) {
	//	newEdge->setSecondP(lastEdge);
	//}
	//newEdge->setFirstP(v2);
	//v1->setSecondP(newEdge);
	//lastEdge = PSEUDO;

	//Base* lastEdge2 = v2->getSecondP();
	//Base * newEdge2 = new Edge(weight);
	//if (lastEdge2 != PSEUDO) {
	//	newEdge2->setSecondP(lastEdge2);
	//}
	//newEdge2->setFirstP(v1);
	//v2->setSecondP(newEdge2);
	//lastEdge2 = PSEUDO;

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
	Base* second = this->firstVertex;
	this->firstVertex = vertex;
	vertex->setFirstP(second);
}


Graph::~Graph() {
	delete this->firstVertex;
}

void Graph::setTreeRoot(Base* newRoot) {
	this->treeRoot = newRoot;
}

void Graph::Prim() {
	Base* p = PSEUDO;
	Base* minEdgeFromHere = PSEUDO;
	Base* minEdge = PSEUDO;
	Base* e = PSEUDO;
	Base* lastMarkedEdgeTmp = PSEUDO;
	Base* lastMarkedEdge = PSEUDO;
	Base* edgeBeforeMinEdgeTmp = PSEUDO;
	Base* edgeBeforeMinEdge = PSEUDO;
	bool unmarkedFound = true;
	
	this->firstVertex->setMarked(true);
	
	while (unmarkedFound) {
		unmarkedFound = false;
		// Kleinste Kante suchen, die den Baum erweitern würde
		p = this->firstVertex;
		minEdge = PSEUDO;		// Korrigiert: reset!
		lastMarkedEdgeTmp = PSEUDO;
		edgeBeforeMinEdgeTmp = PSEUDO;
		lastMarkedEdge = PSEUDO;
		edgeBeforeMinEdge = PSEUDO;
		while (p != PSEUDO) {	// Es wird die komplette Liste durchlaufen
			if (p->isMarked()) {	
				e = p->getSecondP();
				// kleinste Kante suchen
				while (e != PSEUDO) {
					/*	Das kann NICHT der gesuchte Kandidat sein, 
						da nur unter nicht markierten Ecken gesucht wird.
						(==> vorzeitiger Abbruch) */
					if (e->isMarked())
					{
						lastMarkedEdge = e;			// letzte markierte Kante merken
						edgeBeforeMinEdgeTmp = e;
						e = e->getSecondP();		// Vorzeitiger Sprung zum nächsten Kandidaten
						continue;
					}

					// Der 1. Kandidat ist der erst beste
					if (minEdge == PSEUDO) {		
						if (!e->getFirstP()->isMarked()) {			// Kandidat ausgewählt
							lastMarkedEdge = lastMarkedEdgeTmp;			// Letzte markierte Ecke in der Eckenliste speichern
							edgeBeforeMinEdge = edgeBeforeMinEdgeTmp;	// Die Kante vor dem Kandidaten speichern
							minEdge = e;							// den Kandidat speichern
							minEdgeFromHere = p;					// Ausgangsvertex des Kandidaten speichern
						}
					}
					// Sonst vergleichen und wenn kleiner, neue kleinste Ecke setzen
					else {
						if ((!e->getFirstP()->isMarked()) && (((Edge*)e)->getWeight() < (((Edge*)minEdge)->getWeight()))) {
							lastMarkedEdge = lastMarkedEdgeTmp;
							edgeBeforeMinEdge = edgeBeforeMinEdgeTmp;
							minEdge = e;
							minEdgeFromHere = p;
						}
					}
					edgeBeforeMinEdgeTmp = e;
					e = e->getSecondP();
				}
			}
			else {
				unmarkedFound = true;
			}
			p = p->getFirstP();
		}
		
		if(minEdge == PSEUDO)	// extra ueberprfuefung, ob wir den letzten Edge erreicht hatten
			continue;

		moveEdge(minEdgeFromHere, lastMarkedEdge, edgeBeforeMinEdge, minEdge);		// Ans Ende der markierten Kanten einfügen
		//moveEdge(minEdgeFromHere, minEdge);		// Ans Ende der markierten Kanten einfügen
		minEdge->setMarked(true);
		minEdge->getFirstP()->setMarked(true);
		
		// Die umgekehrte Kante auch markieren (Euler-Bedingung)
		e = minEdge->getFirstP()->getSecondP();		// Korrigiert: ->getSecondP(), da bei einer Ecke angefangen werden muss
		lastMarkedEdgeTmp = PSEUDO;
		edgeBeforeMinEdgeTmp = PSEUDO;
		while (e != PSEUDO) {
			if (e->isMarked())
			{
				lastMarkedEdgeTmp = e;
				edgeBeforeMinEdgeTmp = e;
				e = e->getSecondP();
				continue;
			}

			if (e->getFirstP() == minEdgeFromHere) {	
				moveEdge(minEdge->getFirstP(), lastMarkedEdgeTmp, edgeBeforeMinEdgeTmp, e);		// Und richtig einreihen
				//moveEdge(minEdge->getFirstP(), e);		// Und richtig einreihen
				e->setMarked(true);
				break;
			}
			edgeBeforeMinEdgeTmp = e;
			e = e->getSecondP();
		}
		lastMarkedEdgeTmp = PSEUDO;
		edgeBeforeMinEdgeTmp = PSEUDO;
		lastMarkedEdge = PSEUDO;
		edgeBeforeMinEdge = PSEUDO;
	}
}

void Graph::moveEdge(Base* baseVertex, Base* lastMarkedEdge, Base* edgeBefore, Base* edge) {
	// Wenn es schon vorne eingereiht ist, zurückkehren
	if (edgeBefore == PSEUDO)
		return;
	// Wenn es noch keine markierten gibt
	if (lastMarkedEdge == PSEUDO) 
	{
		edgeBefore->setSecondP(edge->getSecondP());
		edge->setSecondP(baseVertex->getSecondP());
		baseVertex->setSecondP(edge);
	}
	// hinter der letzten Anhängen, damit die Reihenfolge stimmt
	else
	{
		edgeBefore->setSecondP(edge->getSecondP());
		edge->setSecondP(lastMarkedEdge->getSecondP());
		lastMarkedEdge->setSecondP(edge);
	}
}

//Verschiebt die Kante edge so, dass sie als letzte markierte Kante in der Eckenliste von baseVertex steht
//void Graph::moveEdge(Base *baseVertex, Base *edge) {
//	Base* lastMarkedEdge = PSEUDO;
//	Base* e = baseVertex->getSecondP();
//	Base* beforeEdge;
//	
//	/*vielleicht Edge zum Einfuegen, steht schon als erster 
//	Element in der Edge-Liste, dann muessen wir nicht tun*/
//	if(e == edge)	// 
//	{
//		return;
//	}
//
//	while (e != PSEUDO && e->isMarked() && ((Edge*)e)->getWeight() < ((Edge*)edge)->getWeight() ) {
//		lastMarkedEdge = e;
//		e = e->getSecondP();
//	}
//
//	if (lastMarkedEdge == PSEUDO)		// keine markierten Kanten
//	{
//		// Vorherige suchen
//		while (e != PSEUDO)
//		{	
//			if (e == edge)
//				break;
//			beforeEdge = e;
//			e = e->getSecondP();
//		}
//		beforeEdge->setSecondP(edge->getSecondP());	// auch wenn PSEUDO
//		edge->setSecondP(baseVertex->getSecondP());
//		baseVertex->setSecondP(edge);
//		return;
//	}
//	else
//	{
//		// Vorherige suchen
//		e = baseVertex->getSecondP();
//		while (e != PSEUDO)
//		{	
//			if (e == edge)
//				break;
//			beforeEdge = e;
//			e = e->getSecondP();
//		}
//		beforeEdge->setSecondP(edge->getSecondP());	// auch wenn PSEUDO
//		edge->setSecondP(lastMarkedEdge->getSecondP());
//		lastMarkedEdge->setSecondP(edge);
//		return;
//	}
//	
//	if (edge != e)
//	{
//		lastMarkedEdge->setSecondP(edge);
//		edge->setSecondP(e);
//	}
//}

void Graph::Cycle() {
	 /*Wenn Prim schon mal aufgerufen wurde, kann Cycle beliebig oft aufgerufen werden,
	 vorausgesetzt die Startbedingungen sind erfüllt.
	 Die Startbedingungen sind zum einen die Menge an markierten Kanten, die den
	 MST aufspannen, zum anderen die Ecken selbst. Da go() am Anfang alle Ecken des MST 
	 als markiert erwartet und dann die Markierungen entfernt, 
	 müssen (alle) Ecken markiert werden. Man kann davon ausgehen, 
	 dass alle Ecken des Graphen auch zum MST gehören, sonst wäre es kein MST!
	 Kanten bleiben nach dem Lauf markiert.*/
	Base* tmp = this->firstVertex;
	while (tmp != PSEUDO)
	{
		tmp->setMarked(true);
		tmp = tmp->getFirstP();
	}
	
	// Durchlauf starten
	Base* start = this->treeRoot;
	cout << ((Vertex*)start)->getLabel() << "\t\t" << "0 km" << endl;
	Base* last;
	last = go(start);
	cout << ((Vertex*)start)->getLabel() << "\t\t" << weightBetween(last, start) << " km" << endl;
}

Base* Graph::go(Base* vertex) {
	bool isLeave = true;
	Base* leave = PSEUDO;
	Base *next;
	Base* e = vertex->getSecondP();

	if (DEBUG_LEVEL > 0)
		cout << "Gone to " << ((Vertex*)vertex)->getLabel() << endl;

	vertex->setMarked(false);	// Ecke als besucht markieren

	while (e != PSEUDO) {
		if (e->isMarked()) {
			next = e->getFirstP();
			if (next->isMarked()) {
				isLeave = false;
				if (leave != PSEUDO) {
					// Abstand leave<->nächster berechnen und ausgeben
					cout << ((Vertex*)next)->getLabel() << "\t\t" << weightBetween(leave, next) << " km" << endl;
					leave = PSEUDO;
				}
				else {
					// Abstand dieser<->nächster berechnen und ausgeben
					cout << ((Vertex*)next)->getLabel() << "\t\t" << ((Edge*)e)->getWeight() << " km" << endl;		// Ausgabe der nächsten Stadt
				}
				leave = go(next);
			}
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
	while (e != PSEUDO) {
		if (e->getFirstP() == v2) {
			return ((Edge*)e)->getWeight();
		}
		e = e->getSecondP();
	}
	if (DEBUG_LEVEL > 0)
		cout << "WeightBetween terminierte unerwartet." << endl;
	return -1;		// sollte nicht passieren
}

