#pragma once

#define PSEUDO NULL;

#include <string>

using namespace std;

class Node {
public:
	Node();
	Node(Vertex* item);
	Node(Vertex* item, Node* left, Node* right);
	Node* getLeft();
	Node* getRight();
	void setLeft(Node* node);
	void setRight(Node* node);
	Vertex* getItem();
	void setItem(Vertex* item);
private:	
	Vertex* item;
	Node* left;
	Node* right;
}
