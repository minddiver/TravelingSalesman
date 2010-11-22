#pragma once

#include "Base.h"
#include "Vertex.h"

class Edge : public Base {
public:
	Edge();
	Edge(int weight);
	int getWeight();
	void setWeight(int weight);
	Edge* getNext();
	void setNext(Edge* next);
	Base* getTarget();
	void setTarget(Base* target);

private:
	int weight;
};