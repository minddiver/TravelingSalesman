#pragma once
#include "Graph.h"

int main() {
	Graph * grrr = new Graph();
	Vertex * v1 = new Vertex("Bla1");
	Vertex * v2 = new Vertex("Bla2");
	Vertex * v3 = new Vertex("Bla3");
	grrr->InsVertex(v1);
	grrr->InsVertex(v2);
	grrr->InsVertex(v3);
	Edge * e1 = grrr->InsEdge(v1,v2,1);
	Edge * e2 = grrr->InsEdge(v1,v3,2);
	Edge * e3 = grrr->InsEdge(v2,v3,3);
	grrr->Prim();
	return 0;
}