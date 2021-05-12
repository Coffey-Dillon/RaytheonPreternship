#ifndef QUADTREE_H
#define QUADTREE_H

#include "macros.h"
#include "quadTreeNode.h"
#include "satellite.h"

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
			delete head;
		}
		
		node<T, S>* get_head(quadTree<T, S>* qt){
			return qt->head;
		}
		
		// Populates the quadtree with node up to a given depth
		// Either manually used to create an empty tree or called by the quad tree constructor
		// 	Recursive traversal of the quad tree, at each level creates 4 nodes then calls populate on each
		// 	of the new nodes.
		// 	Once the nodes have been created and linked to the parent locate_children() sets the point struct in each node
		void populate(node<T, S>* parent, int dep){
			if(dep > 0){
				increaseDepth(parent);
			} else{
				parent->child0 = NULL;
				parent->child1 = NULL;
				parent->child2 = NULL;
				parent->child3 = NULL;
			}
		}

		// Populates the quadtree with nodes and creates satellite objects.
		// Give full coverage of the planet
		// Use -1 as the depth when initally calling this function. 
		// This indicator prevents recursive calls before an acheivable base case can be established.
		void populate(node<T, S>* parent, Satellite<S>* sat, int dep){
			if(dep < 0){
				int calcDep = (int) ((log(1.0/ sat->getFraction()) / log(4.0)) + 1.0);
				populate(parent, sat, calcDep);
			} else if(dep > 0){
				
				increaseDepth(parent);
				
				if(dep == 1){
					parent->child0->data = new Satellite<S>(parent->child0->p.inc , parent->child0->p.azu, sat->getRadius(), sat->getView());
					parent->child1->data = new Satellite<S>(parent->child1->p.inc , parent->child1->p.azu, sat->getRadius(), sat->getView());
					parent->child2->data = new Satellite<S>(parent->child2->p.inc , parent->child2->p.azu, sat->getRadius(), sat->getView());
					parent->child3->data = new Satellite<S>(parent->child3->p.inc , parent->child3->p.azu, sat->getRadius(), sat->getView());
				}

				populate(parent->child0, sat, dep-1);
				populate(parent->child1, sat, dep-1);
				populate(parent->child2, sat, dep-1);
				populate(parent->child3, sat, dep-1);
				
			} else{
				parent->covered = true;
				parent->child0 = NULL;
				parent->child1 = NULL;
				parent->child2 = NULL;
				parent->child3 = NULL;
			}			
		}

		// Populates the quadtree with nodes and creates satellite objects
		// Gives coverage of at least the percent entered 
		// Equally distributes satellites
		//TODO uncover area not seen by satellite by increasing depth and mapping to coverage
		void populate(node<T, S>* parent, Satellite<S>* sat, int dep, double percent){
			if(dep < 0){
				int calcDep = (int) ((log(1.0/ (sat->getFraction() * (1 + percent))) / log(4.0)) + 1.0);
				depth = calcDep;
				populate(parent, sat, calcDep, percent);
			} else if(dep > 0){				

				increaseDepth(parent);
				populate(parent->child0, sat, dep-1, percent);
				populate(parent->child1, sat, dep-1, percent);
				populate(parent->child2, sat, dep-1, percent);
				populate(parent->child3, sat, dep-1, percent);

			} else{
				double temp = 0;
				fillCovered(parent, sat, percent, temp, 0);
				condense(parent);
				// parent->child0 = NULL;
				//parent->child1 = NULL;
				//parent->child2 = NULL;
				//parent->child3 = NULL;
			}			
		}

		void fillCovered(node<T, S>* parent, Satellite<S>* sat, double targetPercent, double currPercent, int childNum){
			if(targetPercent/2 <= currPercent){
				return; 
			}

			increaseDepth(parent);
			double needed = targetPercent - currPercent;
			double topLevel = 1.0 / pow(4, depth);
			double childPercent = 1.0 / pow(4, parent->child0->lvl);
			double ctopPercent = (childPercent / topLevel);
			double temp;

			if(targetPercent < 0.25){
				depth++;
				fillCovered(parent->child0, sat, targetPercent / 0.25, currPercent, 0);
			} else{
				switch(childNum){
					case 0:	
						parent->child0->covered = true;
						temp = currPercent + ctopPercent;
						fillCovered(parent->child1, sat, targetPercent, temp, 1);
						fillCovered(parent->child2, sat, targetPercent, temp, 2);
						fillCovered(parent->child3, sat, targetPercent, temp, 3);
						break;
					case 1:
						//increaseDepth(parent);
						if(needed/3 >= (3 * ctopPercent)){
							parent->child2->covered = true;			
							parent->child3->covered = true;
							parent->child0->covered = true;
							temp = currPercent + 3 * ctopPercent;
							fillCovered(parent->child1, sat, targetPercent, temp, 1);
						} else if(needed/3 >= (2 * ctopPercent)){
							parent->child2->covered = true;
							parent->child3->covered = true;
							temp = currPercent + 2 * ctopPercent;
							fillCovered(parent->child0, sat, targetPercent, temp, 1);
						} else{
							fillCovered(parent->child2, sat, targetPercent, currPercent, 2);
							fillCovered(parent->child3, sat, targetPercent, currPercent, 3);
						}
						break;
					
					case 2:
						//increaseDepth(parent);
						if(needed/3 >= (3 * ctopPercent)){
							parent->child1->covered = true;			
							parent->child3->covered = true;
							parent->child0->covered = true;
							temp = currPercent + 3 * ctopPercent;
							fillCovered(parent->child2, sat, targetPercent, temp, 2);
						} else if(needed/3 >= (2 * ctopPercent)){
							parent->child1->covered = true;
							parent->child3->covered = true;
							temp = currPercent + 2 * ctopPercent;
							fillCovered(parent->child0, sat, targetPercent, temp, 2);
						} else{
							fillCovered(parent->child1, sat, targetPercent, currPercent, 1);
							fillCovered(parent->child3, sat, targetPercent, currPercent, 3);
						}
						break;
					
					case 3:
						//increaseDepth(parent);
						if(needed/3 >= (3) * ctopPercent){
							parent->child1->covered = true;			
							parent->child2->covered = true;
							parent->child0->covered = true;
						 	temp = currPercent + 3 * ctopPercent;
							fillCovered(parent->child3, sat, targetPercent, temp, 3);
						} else if(needed/3 >= (2 * ctopPercent)){
							parent->child1->covered = true;
							parent->child2->covered = true;
							temp = currPercent + 2 * ctopPercent;
							fillCovered(parent->child0, sat, targetPercent, temp, 3);
						} else{
							fillCovered(parent->child1, sat, targetPercent, currPercent, 1);
							fillCovered(parent->child2, sat, targetPercent, currPercent, 2);
						}
						break;
				}

			}

		}

		// Creates a copy of the satellite object passed to the function and places it at the node
		void insert_new(node<T, S>* n, Satellite<S>* sat){
			Satellite<S>* newSat = sat;
			n->data = newSat;
		}

		// Places the satellite at the node pointed to
		void insert(node<T, S>* n, Satellite<S> *sat){
			n->data = sat;
		}

		// Traverses to the first covered node, then deletes all children below the fully covered node
		// 	as the coverage status is indicated by the parent so children are redundant. 
		// TODO write unit test for this method
		void condense(node<T, S>* n){
			if(n == NULL){
				return;
			}

			if(n->covered){
				delete n->child0;
				delete n->child1;
				delete n->child2;
				delete n->child3;
				n->child0 = NULL;
				n->child1 = NULL;
				n->child2 = NULL;
				n->child3 = NULL;
			} else{
				condense(n->child0);
				condense(n->child1);
				condense(n->child2);
				condense(n->child3);
			}
		}

		// Checks if a node is covered, if so using the level in the quad tree the percent coverage 
		//  is determined and added to the total. 
		double getCoverage(node<T, S>* curr){
			double coverage = 0.0;
			if(curr == NULL){
				return 0.0;
			} else if(curr->covered) {
				return 1.0 / pow(4, curr->lvl);	
			}else{
				coverage += getCoverage(curr->child0);
			}
			
			if(curr == NULL){
				return 0.0;
			} else if(curr->covered) {
				return 1.0 / pow(4, curr->lvl);	
			}else{
				coverage += getCoverage(curr->child1);
			}
			
			if(curr == NULL){
				return 0.0;
			} else if(curr->covered) {
				return 1.0 / pow(4, curr->lvl);	
			}else{
				coverage += getCoverage(curr->child2);
			}
			
			if(curr == NULL){
				return 0.0;
			} else if(curr->covered) {
				return 1.0 / pow(4, curr->lvl);	
			}else{
				coverage += getCoverage(curr->child3);
			}

			return coverage;
		}

		// Creates another level of nodes below the node passed to this function
		// Allocates and locates child nodes
		void increaseDepth(node<T,S>* curr){
			curr->child0 = new node<T, S>();
			curr->child1 = new node<T, S>();
			curr->child2 = new node<T, S>();
			curr->child3 = new node<T, S>();
				
			curr->child0->parent = curr;
			curr->child1->parent = curr;
			curr->child2->parent = curr;
			curr->child3->parent = curr;
			curr->locate_children();				
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

			while(curr1){
				output << "quadTree print statement child1: \n" << *curr1 << std::endl;
				curr1 = curr1->child1;
			}
			output << std::endl;
			return output;
		}
};
#endif
