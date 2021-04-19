#ifndef QUADTREE_H
#define QUADTREE_H

#include <cstdlib>
#include <iostream>

#include "quadTreeNode.h"
#include "satellite.h"


template<class T>
class quadTree{

	private:
		struct node{
			T data;
			
			node* parent;
			node* child0;
			node* child1;
			node* child2;
			node* child3;

			void checkMemory(){
				if(this == NULL){
					std::cerr << "Out of Memory" << std::endl;
				}
			}

			node() : data(), parent(), child0(), child1(), child2(), child3() {
				checkMemory();
			}

			node(T dataIn) : data(dataIn), parent(), child0(), child1(), child2(), child3() {
			checkMemory();
			}

			~node(){
				delete child0;
				delete child1;
				delete child2;
				delete child3;
			}

			node(const node& copy){
				data = copy.data;
				parent = copy.parent;
				child0 = copy.child0;
				child1 = copy.child1;
				child2 = copy.child2;
				child3 = copy.child3;
			}
		}

		node* head;
	
	public:
		


		
};
#endif
