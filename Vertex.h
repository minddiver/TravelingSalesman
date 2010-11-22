#pragma once

#include "Base.h"
#include "Edge.h"

class Vertex : public Base {
public:
	Vertex();
	~Vertex();
	Vertex(string label);
	string getLabel();
	void setLabel(string label);
	Vertex* getNext();
	void setNext(Vertex* next);
	Base* getEdge();
	void setEdge(Base* edge);

private:
	string label;
};