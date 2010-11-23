#pragma once

#include "Base.h"

class Edge : public Base {
public:
	Edge();
	Edge(Edge* toCopy);
	Edge(int weight);
	~Edge();
	int getWeight();
	void setWeight(int weight);
	Edge* copy();

private:
	int weight;
};