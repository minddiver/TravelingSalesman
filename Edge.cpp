#pragma once

#include "Base.h"
#include "Edge.h"
using namespace std;

Edge::Edge() {
	this->weight = 0;
}

int Edge::getWeight() {
	return this->weight;
}