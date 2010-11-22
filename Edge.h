#pragma once
//#include "Base.h"
#include "Vertex.h"

#define PSEUDO NULL;
using namespace std;

class Edge : public Base {
public:
	Edge();
	Edge(int weight);
	int getWeight();
	void setWeight(int weight);
	Edge* getNext();
	void setNext(Edge* next);
	Vertex* getTarget();
	void setTarget(Vertex* target);

private:
	int weight;
};