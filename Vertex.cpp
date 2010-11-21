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
	//if (this->label != NULL)
	//	delete this->label;
}

string Vertex::getLabel() {
	return this->label;
}

void Vertex::setLabel(string label) {
	this->label = label;
}

