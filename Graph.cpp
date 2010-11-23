#include "Graph.h"

Graph::Graph() {
	this->firstVertex = PSEUDO;
	this->treeRoot = PSEUDO;
}

Graph::Graph(Graph* toCopy)
{
	// Zun�chst die Ecken kopieren
	Base* v = toCopy->getFirstVertex();
	if (v == PSEUDO)				// Abbruch, da leer
		return;
	Base* lastLocal = ((Vertex*)v)->copy();
	this->firstVertex = lastLocal;
	v = v->getFirstP();
	while (v != PSEUDO) 
	{
		lastLocal->setFirstP(((Vertex*)v)->copy());
		lastLocal = lastLocal->getFirstP();
		v = v->getFirstP();
	}
	// Ecken kopiert, jetzt die Kanten kopieren
	v = toCopy->getFirstVertex();
	Base* w = this->getFirstVertex();
	Base* x = PSEUDO;
	Base* y = PSEUDO;
	Base* e = PSEUDO;
	lastLocal = PSEUDO;
	while (v != PSEUDO)
	{
		e = v->getSecondP();
		if (e != PSEUDO)
		{
			w->setSecondP(((Edge*)e)->copy());
			lastLocal = w->getSecondP();
			e = e->getSecondP();
			while (e != PSEUDO)
			{
				lastLocal->setSecondP(((Edge*)e)->copy());
				lastLocal = lastLocal->getSecondP();
				// Die Zielecke muss gefunden werden
				x = this->getFirstVertex();
				y = toCopy->getFirstVertex();
				while (y != PSEUDO)
				{
					if (y == e->getFirstP())
						break;
					x = x->getFirstP();
					y = y->getFirstP();
				}
				// Zielecke gefunden
#ifdef DEBUG_LEVEL 
				if (DEBUG_LEVEL > 0)
				{
					if (x == PSEUDO)
					{
						cout << "Die Zielecke wurde �berraschend nicht gefunden." << endl;
					}
				}
#endif
				lastLocal->setFirstP(x);
				e = e->getSecondP();
			}
		}
		v = v->getFirstP();
		w = w->getFirstP();
	}
}

void Graph::InsVertex(string label)
{
	// Sicherstellen dass dieses Vertex noch nicht eingefuegt war
	if(this->findVertex(label) == PSEUDO)
	{
		Vertex * toBeInserted = new Vertex(label);
		this->InsVertex(toBeInserted);
	}
}


void Graph::InsEdge(string v1, string v2, int weight)
{
	Vertex * startVertex = this->findVertex( v1 );
	Vertex * endVertex = this->findVertex( v2 );

	if(startVertex != PSEUDO && endVertex != PSEUDO && weight > 0)
		this->InsEdge(startVertex, endVertex, weight);
	else
		cout << "!!! Edge was not created! Make sure that you added Vertexes and that the weight is > 0." << endl;

}


Vertex* Graph::findVertex(string label)
{
	Base * iterator = this->firstVertex;
	if(iterator != PSEUDO)
	{
		while(iterator->getFirstP() != PSEUDO)
		{
			if(((Vertex*)iterator)->getLabel() == label)
				return (Vertex*)iterator;

			iterator = iterator->getFirstP();
		}
	}
	return PSEUDO;
}
	

Graph::~Graph() {
	Vertex* v = (Vertex*)this->firstVertex;
	Edge* e = PSEUDO;
	Edge* nextE = e;
	Vertex* nextV = PSEUDO;

	while (v != PSEUDO) 
	{
		nextV = (Vertex*)v->getFirstP();
		
		Edge* e = (Edge*)v->getSecondP();
		while (e != PSEUDO) 
		{
			nextE = (Edge*)e->getSecondP();
			delete e;
		}
		delete v;
	}
}

Base* Graph::getFirstVertex()
{
	return this->firstVertex;
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
void Graph::InsEdge(Vertex * v1, Vertex * v2, int weight) {
	Edge *NewEdge1 = new Edge(weight);
	NewEdge1->setFirstP(v2);
	
	NewEdge1->setSecondP(v1->getSecondP());
	v1->setSecondP(NewEdge1);


	Edge *NewEdge2 = new Edge(weight);
	NewEdge2->setFirstP(v1);
	
	NewEdge2->setSecondP(v2->getSecondP());
	v2->setSecondP(NewEdge2);

	return;

}

void Graph::InsVertex(Vertex * vertex) {
	Base* second = this->firstVertex;
	this->firstVertex = vertex;
	vertex->setFirstP(second);
}

void Graph::setTreeRoot(string label)
{
	Vertex * newRoot = this->findVertex(label);

	if(newRoot != PSEUDO)
		this->setTreeRoot(newRoot);
	else
		cout << "!!! The Vertex could not be found! Tree root was not set." << endl;
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
		// Kleinste Kante suchen, die den Baum erweitern w�rde
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
						e = e->getSecondP();		// Vorzeitiger Sprung zum n�chsten Kandidaten
						continue;
					}

					// Der 1. Kandidat ist der erst beste
					if (minEdge == PSEUDO) {		
						if (!e->getFirstP()->isMarked()) {			// Kandidat ausgew�hlt
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

		moveEdge(minEdgeFromHere, lastMarkedEdge, edgeBeforeMinEdge, minEdge);		// Ans Ende der markierten Kanten einf�gen
		//moveEdge(minEdgeFromHere, minEdge);		// Ans Ende der markierten Kanten einf�gen
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
	// Wenn es schon vorne eingereiht ist, zur�ckkehren
	if (edgeBefore == PSEUDO)
		return;
	// Wenn es noch keine markierten gibt
	if (lastMarkedEdge == PSEUDO) 
	{
		edgeBefore->setSecondP(edge->getSecondP());
		edge->setSecondP(baseVertex->getSecondP());
		baseVertex->setSecondP(edge);
	}
	// hinter der letzten Anh�ngen, damit die Reihenfolge stimmt
	else
	{
		edgeBefore->setSecondP(edge->getSecondP());
		edge->setSecondP(lastMarkedEdge->getSecondP());
		lastMarkedEdge->setSecondP(edge);
	}
}


void Graph::Cycle() {
	 /*Wenn Prim schon mal aufgerufen wurde, kann Cycle beliebig oft aufgerufen werden,
	 vorausgesetzt die Startbedingungen sind erf�llt.
	 Die Startbedingungen sind zum einen die Menge an markierten Kanten, die den
	 MST aufspannen, zum anderen die Ecken selbst. Da go() am Anfang alle Ecken des MST 
	 als markiert erwartet und dann die Markierungen entfernt, 
	 m�ssen (alle) Ecken markiert werden. Man kann davon ausgehen, 
	 dass alle Ecken des Graphen auch zum MST geh�ren, sonst w�re es kein MST!
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
					// Abstand leave<->n�chster berechnen und ausgeben
					cout << ((Vertex*)next)->getLabel() << "\t\t" << weightBetween(leave, next) << " km" << endl;
					leave = PSEUDO;
				}
				else {
					// Abstand dieser<->n�chster berechnen und ausgeben
					cout << ((Vertex*)next)->getLabel() << "\t\t" << ((Edge*)e)->getWeight() << " km" << endl;		// Ausgabe der n�chsten Stadt
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

Graph* Graph::copy() {
	return new Graph(this);
}

Graph Graph::operator =(Graph other)
{
	// TODO
}