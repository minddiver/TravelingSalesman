#pragma once
#include "Base.h"
#include "Vertex.h"

Vertex::Vertex() {
	this->label = NULL;
}

Vertex::Vertex(char * label) {
	this->label = label;
}

Vertex::~Vertex() {
	if (this->label != NULL)
		delete this->label;
}

char * Vertex::getLabel() {
	return this->label;
}

void Vertex::setLabel(char * label) {
	this->label = label;
}

