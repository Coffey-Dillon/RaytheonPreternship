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
			head = new node<T, S>();
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
				parent->covered = true;
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
				parent->covered = true;
				parent->child0 = NULL;
				parent->child1 = NULL;
				parent->child2 = NULL;
				parent->child3 = NULL;
			}
		}

		// Populates the quadtree with nodes and creates satellite objects.
		// Use -1 as the depth when initally calling this function. 
		// This indicator prevents recursive calls before an acheivable base case can be established.
		void populate(node<T, S>* parent, Satellite<S>* sat, int dep){
			if(dep < 0){
				int calcDep = (int) ((log(1.0/ sat->getFraction()) / log(4.0)) + 1.0);
				populate(parent, sat, calcDep);
			} else if(dep > 0){
				parent->child0 = new node<T, S>();
				parent->child1 = new node<T, S>();
				parent->child2 = new node<T, S>();
				parent->child3 = new node<T, S>();
				
				parent->child0->parent = parent;
				parent->child1->parent = parent;
				parent->child2->parent = parent;
				parent->child3->parent = parent;

				parent->locate_children();
				
				parent->child0->data = new Satellite<S>(parent->child0->p.inc , parent->child0->p.azu, sat->getRadius(), sat->getView());
				parent->child1->data = new Satellite<S>(parent->child1->p.inc , parent->child1->p.azu, sat->getRadius(), sat->getView());
				parent->child2->data = new Satellite<S>(parent->child2->p.inc , parent->child2->p.azu, sat->getRadius(), sat->getView());
				parent->child3->data = new Satellite<S>(parent->child3->p.inc , parent->child3->p.azu, sat->getRadius(), sat->getView());

				populate(parent->child0, sat, dep-1);
				populate(parent->child1, sat, dep-1);
				populate(parent->child2, sat, dep-1);
				populate(parent->child3, sat, dep-1);
				
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

		// Checks if a node is covered, if so using the level in the quad tree the percent coverage 
		double getCoverage(node<T, S>* curr){
			double coverage = 0.0;
			if(curr->child0 == NULL || curr->covered){
				if(curr->covered){
					return 1.0 / pow(4, curr->lvl);	
				} else{
					return 0.0;
				}	
			} else{
				coverage += getCoverage(curr->child0);
			}
			
			if(curr->child1 == NULL || curr->covered){
				if(curr->covered){		
					return 1.0 / pow(4, curr->lvl);			
				} else{
					return 0.0;
				}
			} else{
				coverage += getCoverage(curr->child1);
			}	
			
			if(curr->child2 == NULL || curr->covered){
				if(curr->covered){
					return 1.0 / pow(4, curr->lvl);			
				} else{
					return 0.0;
				}
			} else{
				coverage += getCoverage(curr->child2);
			}
	
			if(curr->child3 == NULL || curr->covered){
				if(curr->covered){
					return 1.0 / pow(4, curr->lvl);			
				} else{
					return 0.0; 
				}		
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
			node<T, S>* curr1 = printTree.head;
			node<T, S>* curr2 = printTree.head;

			while(curr1 && curr2){
				output << "quadTree print statement child1: \n" << *curr1 << std::endl;
				output << "quadTree print statement child2: \n" << *curr2 << std::endl;
				curr1 = curr1->child1;
				curr2 = curr2->child2;
			}
			output << std::endl;
			return output;
		}
};
#endif
