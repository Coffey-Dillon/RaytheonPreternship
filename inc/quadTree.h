#ifndef QUADTREE_H
#define QUADTREE_H

#include <cstdlib>
#include <iostream>

#include "quadTreeNode.h"
#include "satellite.h"

#define earthRad 6370

template<class T, class S>
class quadTree{

	protected:
		node<T, S>* head;

		int depth;

	public:	
		quadTree() : head(NULL), depth(1) {
			head = new node<T, S>;
		}

		quadTree(int dep) : head(NULL), depth(dep) {
			head = new node<T, S>;
			populate(head, depth);
		}


		~quadTree(){
			delete head->child0;
			delete head->child1;
			delete head->child2;
			delete head->child3;
			delete head;
		}
		
		node<T, S>* get_head(quadTree<T, S>* qt){
			return qt->head;
		}

		void populate(node<T, S>* parent, int dep){
			if(dep > 0){
				parent->child0 = new node<T, S>();
				parent->child1 = new node<T, S>();
				parent->child2 = new node<T, S>();
				parent->child3 = new node<T, S>();
				populate(parent->child0, dep-1);
				populate(parent->child1, dep-1);
				populate(parent->child2, dep-1);
				populate(parent->child3, dep-1);
			} else{
				parent->child0 = NULL;
				parent->child1 = NULL;
				parent->child2 = NULL;
				parent->child3 = NULL;
				return;
			}
		}
		
		void increaseDepth(){
			depth++;
		}

		void insert(node<T, S>* n, int child){
			
		}

		void getCoverage() {}

		// Assignment operator
		quadTree<T, S>& operator=(const quadTree<T, S>& rhs){
			if(this != &rhs){
				this->head = rhs->head;			
			}
		}
		
		//TODO finish print operator for whole tree
		friend std::ostream& operator<<(std::ostream& output, const quadTree<T, S>& printTree){
			node<T, S>* curr = printTree.head;
			while(curr){
				output << "quadTree print statement: " << *curr << std::endl;
				curr = curr->child1;
			}
			return output;
		}
};
#endif
