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
		int numSats;

	public:	
		quadTree() : depth(0), numSats(0){
			head = new node<T, S>();
		}	

		quadTree(int dep) : depth(dep), numSats(0) {
			head = new node<T, S>();
			populate(head, depth);
		}

		~quadTree(){
			delete head;
		}
		
		node<T, S>* get_head(quadTree<T, S>* qt){
			return qt->head;
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

		// inserts satellite objects into the children of a given node
		void addSats(node<T, S>* p, Satellite<S>* s){
			p->child0->data = new Satellite<S>(p->child0->p.inc , p->child0->p.azu, s->getRadius(), s->getView());
			p->child1->data = new Satellite<S>(p->child1->p.inc , p->child1->p.azu, s->getRadius(), s->getView());	
			p->child2->data = new Satellite<S>(p->child2->p.inc , p->child2->p.azu, s->getRadius(), s->getView());
			p->child3->data = new Satellite<S>(p->child3->p.inc , p->child3->p.azu, s->getRadius(), s->getView());
			numSats += 4;
		}
		
		// Places the satellite at the node pointed to and updates satellite location vector
		void insert(node<T, S>* n, Satellite<S> *sat){
			n->data = new Satellite<S>(n->p.inc , n->p.azu, sat->getRadius(), sat->getView());
			numSats += 1;
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
					addSats(parent, sat);	
				}

				populate(parent->child0, sat, dep-1);
				populate(parent->child1, sat, dep-1);
				populate(parent->child2, sat, dep-1);
				populate(parent->child3, sat, dep-1);
				
			} else{
				parent->covered = true;
				parent->setCoverage();
				parent->child0 = NULL;
				parent->child1 = NULL;
				parent->child2 = NULL;
				parent->child3 = NULL;
			}			
		}
		
		void populate(node<T, S>* parent, Satellite<S>* sat, int dep, int satcount){
			if(dep < 0){
				int calcDep = (int) ((log(1.0/ sat->getFraction()) / log(4.0)) + 1.0);
				populate(parent, sat, calcDep, satcount);
			} else if(dep > 0){
				
				increaseDepth(parent);
				
				populate(parent->child0, sat, dep-1, satcount);
				populate(parent->child1, sat, dep-1, satcount);
				populate(parent->child2, sat, dep-1, satcount);
				populate(parent->child3, sat, dep-1, satcount);
				
			} else{
				if(satcount >= numSats){
					insert(parent, sat);			
				} else {
					parent->data = NULL;
				}
				if(parent->data != NULL){
					parent->covered = true;
					parent->setCoverage();
				} else{
					parent->covered = false;
				}
				parent->child0 = NULL;
				parent->child1 = NULL;
				parent->child2 = NULL;
				parent->child3 = NULL;
			}			
		}


		// Populates the quadtree with nodes and creates satellite objects
		// Gives coverage of at least the percent entered 
		// Equally distributes satellites throughout the globe 
		// Case statement is used to determine which children are proritized when determining coverage of a given node.
		void populate(node<T, S>* parent, Satellite<S>* sat, int dep, double percent){
			if(dep < 0){
				int calcDep = (int) ((log(1.0/ (sat->getFraction() * (1 + percent))) / log(4.0)) + 1.0);
				depth = calcDep;
				if(percent >= 1){
					populate(parent, sat, calcDep);
				} else{
					populate(parent, sat, calcDep, percent);
				}
			} else if(dep > 0){				

				increaseDepth(parent);
				populate(parent->child0, sat, dep-1, percent);
				populate(parent->child1, sat, dep-1, percent);
				populate(parent->child2, sat, dep-1, percent);
				populate(parent->child3, sat, dep-1, percent);

			} else{
				double temp = 0;
				fillCovered(parent, sat, percent, temp, 0);
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
						insert(parent->child0, sat);
						temp = currPercent + ctopPercent;
						fillCovered(parent->child1, sat, targetPercent, temp, 1);
						fillCovered(parent->child2, sat, targetPercent, temp, 2);
						fillCovered(parent->child3, sat, targetPercent, temp, 3);
						break;
					case 1:
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

		// Updates the coverage of parent nodes to true if all children are covered
		void updateCoverage(node<T, S>* n){
			if(n == NULL || n->covered){
				return;	
			}

			if(n->child0 != NULL && !n->child0->covered){
				updateCoverage(n->child0);
			} else if(n->child1 != NULL && !n->child1->covered){
				updateCoverage(n->child1);
			} else if(n->child2 != NULL && !n->child2->covered){
				updateCoverage(n->child2);
			} else if(n->child3 != NULL && !n->child3->covered){
				updateCoverage(n->child3);
			} else{
				n->covered = true;
				updateCoverage(n->parent);
				return;
			}
		}


		// Implements the updateCoverage for the entire quadTree
		void setCovered(){
			updateCoverage(head);
		}


		int getNumSats(){
			return numSats;
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

		node<T, S>* findNextNode(node<T, S>* n, double lat, double log){
			lat += (2 * M_PI);
			log += (2 * M_PI);
			double dist0 = n->child0 != NULL ? sqrt(pow((n->child0->p.inc - lat), 2) + pow((n->child0->p.azu - log), 2)) : 100;
			double dist1 = n->child1 != NULL ? sqrt(pow((n->child1->p.inc - lat), 2) + pow((n->child1->p.azu - log), 2)) : 100;
			double dist2 = n->child2 != NULL ? sqrt(pow((n->child2->p.inc - lat), 2) + pow((n->child2->p.azu - log), 2)) : 100;
			double dist3 = n->child3 != NULL ? sqrt(pow((n->child3->p.inc - lat), 2) + pow((n->child3->p.azu - log), 2)) : 100;
			int flag = 0;	
			flag = dist0 < dist1 ? 0 : 1;
			flag = dist1 < dist2 ? 1 : 2;
			flag = dist2 < dist3 ? 2 : 3;
			
			switch(flag){
				case 0:
					return n->child0;
				case 1:
					return n->child1;
				case 2:
					return n->child2;
				case 3:
					return n->child3;
			}
			return NULL;
		}

		// Traverses the quad tree to a specific location to check if the location is covered
		bool locationStatus(double lat, double log){
			node<T, S>* curr = head;
			double rlat = lat / RAD_DEGREES;
			double rlog = log / RAD_DEGREES;
			while(true){
				if(curr!= NULL && curr->covered){
					return true;			
				}else if(curr == NULL){
					return false;
				}else {
					curr = findNextNode(curr, rlat, rlog);
				}
			}
		}
 

		// Assignment operator
		quadTree<T, S>& operator=(const quadTree<T, S>& rhs){
			if(this != &rhs){
				this->head = rhs->head;			
			}
		}

		// Prints all nodes using recursion.
		void printChildren(node<T, S>* curr){
			if(curr == NULL){
				return;			
			}

			COUT << *curr << ENDL;
			printChildren(curr->child0);
			printChildren(curr->child1);
			printChildren(curr->child2);
			printChildren(curr->child3);
		}

		// implements the printChildren method for the entire tree
		void printTree(){
			printChildren(head);
		}
		
		friend std::ostream& operator<<(std::ostream& output, const quadTree<T, S>& printTree){
			node<T, S>* curr1 = printTree.head;

			while(curr1){
				output << "quadTree print statement child1: \n" << *curr1 << std::endl;
				curr1 = curr1->child1;
			}
			return output;
		}
};
#endif
