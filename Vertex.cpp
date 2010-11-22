#pragma once
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

Base* Vertex::getNext() {
	return (Vertex*)this->getFirstP();
}

void Vertex::setNext(Base* next) {
	this->setFirstP(next);
}

Base* Vertex::getEdge() {
	return this->getFirstP();
}

void Vertex::setEdge(Base *edge) {
	this->setFirstP(edge);
}

