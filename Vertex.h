#pragma once

#include "Edge.h"
#include "Base.h"
#define PSEUDO NULL;
using namespace std;

class Vertex : public Base {
public:
	Vertex();
	~Vertex();
	Vertex(char* label);
	char * getLabel();
	void setLabel(char * label);
	Vertex* getNext();
	void setNext(Vertex* next);
	Edge* getEdge();
	void setEdge(Edge* edge);

private:
	char * label;
};