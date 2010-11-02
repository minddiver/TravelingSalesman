#pragma once
#include "Graph.h"

Graph::Graph() {
	this->firstVertex = PSEUDO;
	this->treeRoot = PSEUDO;
}

void Graph::InsEdge(Vertex *fromVertex, Vertex *toVertex) {

}

void Graph::InsVertex(Vertex *vertex) {

}

Vertex* Graph::getFirstVertex() {
	return this->firstVertex;
}

Vertex* Graph::getTreeRoot() {
	return this->treeRoot;
}

Graph::~Graph() {

}