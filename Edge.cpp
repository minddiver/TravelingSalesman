#pragma once
#include "Base.h"
#include "Edge.h"
#include "Vertex.h"

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

Edge* Edge::getNext() {
	return (Edge*)this->getSecondP();
}

void Edge::setNext(Edge* next) {
	this->setSecondP(next);
}

Vertex* Edge::getTarget() {
	return (Vertex*)this->getFirstP();
}

void Edge::setTarget(Vertex* target) {
	this->setFirstP(target);
}