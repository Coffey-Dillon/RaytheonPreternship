#ifndef QUADTREE_H
#define QUADTREE_H

#include <cstdlib>
#include <iostream>

#include "quadTreeNode.h"
#include "satellite.h"


template<class T>
class quadTree{

	private:
		node* head;

	public:	
		quadTree() : head() {}
		
		void populate(Satellite s){}

		int getCoverage(){}
		
};
#endif
