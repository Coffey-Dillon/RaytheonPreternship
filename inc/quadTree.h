#ifndef QUADTREE_H
#define QUADTREE_H

#include <cstdlib>
#include <iostream>

#include "quadTreeNode.h"
#include "satellite.h"


template<class T>
class quadTree{

	private:
		node* head = new node();

		int depth;

	public:	
		quadTree() : head(NULL) {}

		~quadTree(){
			delete head;
		}
		
		void populate(node* parent, depth){
			if(parent == NULL){
				parent = new node;
			}
			if(depth > 0){
				parent->child0 = new node;
				parent->child1 = new node;
				parent->child2 = new node;
				parent->child3 = new node;
			}
			populate(child0, depth-1);
			populate(child1, depth-1);
			populate(child2, depth-1);
			populate(child3, depth-1);
		}

		void populate(Satellite *s){}

		void increaseDepth(){
			depth++;
		}

		void insert(node* n, int child){
		}

		int getCoverage() {}
		
};
#endif
