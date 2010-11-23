#pragma once

#include "Base.h"
#include "Vertex.h"

class Edge : public Base {
public:
	Edge();
	Edge(int weight);
	int getWeight();
	void setWeight(int weight);
	//Base* getNext();
	//void setNext(Base* next);
	//Base* getTarget();
	//void setTarget(Base* target);

private:
	int weight;
};