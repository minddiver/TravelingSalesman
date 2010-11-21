#pragma once

#include "Node.h"

using namespace std;

Node::Node() {
	this->label = "";
	this->left = PSEUDO;
	this->right = PSEUDO;
}

Node::Node(Vertex* item) {
	Node();
	this->item = item;
}

Node::Node(Vertex* item, Node *left, Node *right) {
	Node(item);
	this->left = left;
	this->right = right;
}
