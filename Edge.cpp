#pragma once

#include "Base.h"
#include "Edge.h"

Edge::Edge() {
	this->weight = 0;
}

Edge::Edge(int weight) {
	this->weight = weight;
}

int Edge::getWeight() {
	return this->weight;
}

void Edge::setWeight(int weight) {
	this->weight = weight;
}