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
	bool unmarkedFound = true;
	
	this->firstVertex->setMarked(true);
	
	while (unmarkedFound) {
		unmarkedFound = false;
		p = this->firstVertex;
		minEdge = PSEUDO;		// Korrigiert: reset!
		while (p != PSEUDO) {
			if (p->isMarked()) {	
				e = p->getSecondP();
				// kleinste Kante suchen
				while (e != PSEUDO) {
					// Erstmal eine beliebige als kleinste annehmen
					if (minEdge == PSEUDO) {
						if (!e->getFirstP()->isMarked()) {
							minEdge = e;
							minEdgeFromHere = p;
						}
					}
					// Vergleichen und wenn kleiner, neue kleinste Ecke setzen
					else {
						if ((!e->getFirstP()->isMarked()) && (((Edge*)e)->getWeight() < (((Edge*)minEdge)->getWeight()))) {
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
		
		if(minEdge == PSEUDO)	// extra ueberprfuefung, ob wir den letzten Edge erreicht hatten
			continue;

		moveEdge(minEdgeFromHere, minEdge);		// Ans Ende der markierten Kanten einfügen
		minEdge->setMarked(true);
		minEdge->getFirstP()->setMarked(true);
		
		// Die umgekehrte Kante auch markieren (Euler-Bedingung)
		e = minEdge->getFirstP()->getSecondP();		// Korrigiert: ->getSecondP(), da bei einer Ecke angefangen werden muss
		while (e != PSEUDO) {
			if (e->getFirstP() == minEdgeFromHere) {	
				moveEdge(minEdge->getFirstP(), e);		// Und richtig einreihen
				e->setMarked(true);
				break;
			}
			e = e->getSecondP();
		}
	}
}

//Verschiebt die Kante edge so, dass sie als letzte markierte Kante in der Eckenliste von baseVertex steht
void Graph::moveEdge(Base *baseVertex, Base *edge) {
	//Edge* lastMarkedEdge = (Edge*)baseVertex->getEdge();
	Base* lastMarkedEdge = PSEUDO;
	Base* e = baseVertex->getSecondP();
	Base* beforeEdge;
	
	/*vielleicht Edge zum Einfuegen, steht schon als erster 
	Element in der Edge-Liste, dann muessen wir nicht tun*/
	if(e == edge)	// 
	{
		return;
	}

	while (e != PSEUDO && e->isMarked() && ((Edge*)e)->getWeight() < ((Edge*)edge)->getWeight() ) {
		lastMarkedEdge = e;
		e = e->getSecondP();
	}

	if (lastMarkedEdge == PSEUDO)		// keine markierten Kanten
	{
		// Vorherige suchen
		while (e != PSEUDO)
		{	
			if (e == edge)
				break;
			beforeEdge = e;
			e = e->getSecondP();
		}
		beforeEdge->setSecondP(edge->getSecondP());	// auch wenn PSEUDO
		edge->setSecondP(baseVertex->getSecondP());
		baseVertex->setSecondP(edge);
		return;
	}
	else
	{
		// Vorherige suchen
		e = baseVertex->getSecondP();
		//if (e->getWeight() > edge->getWeight()) 
		//{
		//	// Am Anfang einfügen
		//	return;
		//}
		while (e != PSEUDO)
		{	
			if (e == edge)
				break;
			beforeEdge = e;
			e = e->getSecondP();
		}
		beforeEdge->setSecondP(edge->getSecondP());	// auch wenn PSEUDO
		edge->setSecondP(lastMarkedEdge->getSecondP());
		lastMarkedEdge->setSecondP(edge);
		return;
	}
	
	

	//if (e != PSEUDO)	// falls e ist nicht PSEUDO
	//	e->setSecondP(edge->getSecondP());	// wir muessen den alten Zeiger von edge speichern
	
	if (edge != e)
	{
		lastMarkedEdge->setSecondP(edge);
		edge->setSecondP(e);
	}
}

void Graph::Cycle() {
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
	Base* r;
	Base* re;

	vertex->setMarked(false);

	Base* e = vertex->getSecondP();
	
	while (e != PSEUDO /*&& e->isMarked()*/) {
		if (e->isMarked()) {
			isLeave = false;
			next = e->getFirstP();
			
			e->setMarked(false);		// Fehler: die Rückkante muss auch gelöscht werde, weil sie niemals gegangen wird, ausser es gibt nur 2 Knoten
			// Rückkante löschen
			r = e->getFirstP();
			re = r->getSecondP();
			while (re != PSEUDO) 
			{
				if (re->getFirstP() == vertex)
				{
					re->setMarked(false);
				}
				re = re->getSecondP();
			}
			if (next->isMarked()) {
				if (leave != PSEUDO) {
					// Abstand leave<->dieser berechnen und ausgeben
					cout << ((Vertex*)next)->getLabel() << "\t\t" << weightBetween(leave, next) << " km" << endl;
					leave = PSEUDO;
				}
				else {
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
	cout << "WeightBetween unerwartet terminiert." << endl;
	return -1;		// sollte nicht passieren
}

