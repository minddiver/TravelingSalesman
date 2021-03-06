#pragma once
#include "Graph.h"
#include <stdio.h>
#include <vector>
using namespace std;

int main() {
	Graph * grrr = new Graph();
	
	// automatische Erzeugung des Graphen
	
	//Vertex* v1 = new Vertex("A");
	//Vertex* v2 = new Vertex("B");
	//Vertex* v3 = new Vertex("C");
	//Vertex* v4 = new Vertex("D");
	//Vertex* v5 = new Vertex("E");
	//Vertex* v6 = new Vertex("F");
	//grrr->InsVertex(v1);
	//grrr->InsVertex(v2);
	//grrr->InsVertex(v3);
	//grrr->InsVertex(v4);
	//grrr->InsVertex(v5);
	//grrr->InsVertex(v6);
	//Base* e1 = grrr->InsEdge(v1, v2, 60);
	//Base* e2 = grrr->InsEdge(v1, v3, 50);
	//grrr->InsEdge(v1, v4, 63);
	//grrr->InsEdge(v1, v5, 57);
	//grrr->InsEdge(v1, v6, 84);
	//Base* e3 = grrr->InsEdge(v2, v3, 32);
	//grrr->InsEdge(v2, v4, 103);
	//grrr->InsEdge(v2, v5, 56);
	//grrr->InsEdge(v2, v6, 83);
	//grrr->InsEdge(v3, v4, 84);	
	//grrr->InsEdge(v3, v5, 75);
	//grrr->InsEdge(v3, v6, 53);
	//grrr->InsEdge(v4, v5, 120);
	//grrr->InsEdge(v4, v6, 61);
	//grrr->InsEdge(v5, v6, 126);
	//grrr->Prim();
	//grrr->setTreeRoot(v5);
	//grrr->Cycle();

	//
	//// wait before close trick
	//int aa;
	//cin >> aa;
	//return 0;
	
/***********************************************************************/
	// manuelle Erzeugung

	vector<Vertex*> * vertexes = new vector<Vertex*>();
	int opt = 0;
	int newRootId = 0;
	int tempWeight = 0;
	bool primCalled = false;

	int entriesTotal = 0;
	int entriesCounter = 0;

	Vertex * tempV;
	string vertexName;
	string tempName;


	cout << "Welcome to the Traveling Salesman Problem Solver!" << endl;
	while (true){
		cout << endl << "Here is a list of things you can do: " << endl;
		cout << "1. Add a new Vertex (with a name)" << endl;
		cout << "2. Add egdes (with weights) to all Vertexes" << endl;
		cout << "3. Create a spanning tree. [call prim() function]" << endl;
		cout << "4. Print a Tree structure (NLR)." << endl;
		cout << "5. Exit" << endl << "Please enter your choice: ";
		cin >> opt;

		switch (opt){
			case 1:
				cout << "Enter the name for this Vertex: ";
				cin >> vertexName;
				getline(cin, tempName);
				vertexName.append(tempName);
				
				tempV = new Vertex(vertexName);
				vertexes->push_back(tempV);
				grrr->InsVertex(tempV);
				cout << endl << ">> New Vertex is inserted successfully." << endl;
				
				// to always have an updated structure
				primCalled = false;
				break;
			case 2:
				cout << "We need create edges between all the vertexes and specify weights. Lets start." << endl;
				cout << "Here's a list of Vertexes for a reference" << endl;

				for (unsigned int i = 0; i < vertexes->size(); i++)
				{
					cout << i+1 << ": " << vertexes->at(i)->getLabel() << endl;
				}

				entriesTotal = ((vertexes->size()-1)*vertexes->size())/2;
				entriesCounter = 1;
				cout << "Total entries: " << entriesTotal << endl;

				for(unsigned int i = 0; i < vertexes->size(); i++)
				{
					for(unsigned int j = 0; j < vertexes->size(); j++)
					{
						// we only need to add each pair once
						if(i < j)
						{
							cout << "(" << entriesCounter << "/" << entriesTotal << ")  Weight for:  Vertex" <<
								i+1 << " ( " << vertexes->at(i)->getLabel() << " ) and Vertex" <<
								j+1 << " ( " << vertexes->at(j)->getLabel() << " ): ";
							cin >> tempWeight;
							
							grrr->InsEdge(vertexes->at(i), vertexes->at(j), tempWeight);
							entriesCounter++;
						}// otherwise skip
					}
				}

				cout << "Tada!" << endl;
				// to always have an updated structure
				primCalled = false;
				break;
			case 3:
				cout << "Calling Prim() function..." << endl;
				grrr->Prim();

				// OK. User called Prim()
				primCalled = true;
				cout << "Prim() was called successfully. Spanning Tree is constructed." << endl;
				break;
			case 4:
				if (primCalled)
				{
					// print all vertexes
					cout << "Here's a list of Vertexes for a reference" << endl << endl;
					for (unsigned int i = 0; i < vertexes->size(); i++)
					{
						cout << i+1 << ": " << vertexes->at(i)->getLabel() << endl;
					}
					cout << "Choose the root of the tree: ";
					cin >> newRootId;

					// make sure thaat the index is inside of vector
					if((unsigned int)newRootId - 1 < vertexes->size() || newRootId - 1 >= 0)
					{
						cout << "Calling Cycle() function..." << endl;
						grrr->setTreeRoot( vertexes->at(newRootId-1) );
						grrr->Cycle();
						cout << endl << "Cycle() called successfully." << endl;
					}
					else
					{
						cout << "Sorry, this Vertex-ID is not in the list." << endl;
					}
				}
				else
				{
					cout << ">Please call Prim() before calling this Function" << endl;
				}
				break;
			case 5:
				return 0;
			default:
				cout << endl << ">> Sorry, can't understand your command. Try again. To exit choose 5" << endl;
				break;
		}
	}

/******************************************************************************************************/
	
	return 0;
}
