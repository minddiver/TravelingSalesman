#pragma once
#include "Base.h"
#include "Vertex.h"

Vertex::Vertex() {
	this->label = string("");
}

Vertex::Vertex(string label) {
	this->label = label;
}

Vertex::~Vertex() {
	delete &this->label;
}

string Vertex::getLabel() {
	return this->label;
}

void Vertex::setLabel(string label) {
	this->label = label;
}

Vertex* Vertex::getNext() {
	return (Vertex*)this->getFirstP();
}

void Vertex::setNext(Vertex* next) {
	this->setFirstP(next);
}

Edge* Vertex::getEdge() {
	return (Edge*)this->getFirstP();
}

void Vertex::setEdge(Edge *edge) {
	this->setFirstP(edge);
}

