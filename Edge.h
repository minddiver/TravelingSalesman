#pragma once
#include "Base.h"

using namespace std;

class Edge : public Base {
public:
	Edge();
	Edge(int weight);
	int getWeight();
	void setWeight(int weight);

private:
	int weight;
};