#ifndef QUADTREE_H
#define QUADTREE_H

#include <cstdlib>
#include <iostream>
#include <math.h>

#include "quadTreeNode.h"
#include "satellite.h"

#define earthRad 6370

template<class T, class S>
class quadTree{

	protected:
		node<T, S>* head;

		int depth;

	public:	
		quadTree(){
			head = new node<T, S>();
		}	

		quadTree(int dep) : depth(dep) {
			populate(head, depth);
		}


		~quadTree(){
		//	delete head->child0;
		//	delete head->child1;
		//	delete head->child2;
		//	delete head->child3;
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
				
				parent->child0->parent = parent;
				parent->child1->parent = parent;
				parent->child2->parent = parent;
				parent->child3->parent = parent;

				parent->locate_children();
				
				populate(parent->child0, dep-1);
				populate(parent->child1, dep-1);
				populate(parent->child2, dep-1);
				populate(parent->child3, dep-1);
				
			} else{
				parent->child0 = NULL;
				parent->child1 = NULL;
				parent->child2 = NULL;
				parent->child3 = NULL;
			}
		}
		
		void increaseDepth(){
			depth++;
		}

		void insert(node<T, S>* n, int child){
			
		}

		double getCoverage(node<T, S>* curr){
			double coverage = 0.0;
			if(curr->child0 == NULL || curr->covered){
				return 1.0 / pow(4, curr->lvl);			
			} else{
				coverage += getCoverage(curr->child0);
			}
			
			if(curr->child1 == NULL || curr->covered){
				return 1.0 / pow(4, curr->lvl);			
			} else{
				coverage += getCoverage(curr->child1);
			}	
			
			if(curr->child2 == NULL || curr->covered){
				return 1.0 / pow(4, curr->lvl);			
			} else{
				coverage += getCoverage(curr->child2);
			}
	
			if(curr->child3 == NULL || curr->covered){
				return 1.0 / pow(4, curr->lvl);			
			} else{
				coverage += getCoverage(curr->child3);
			}
			
			return coverage;
		}

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
