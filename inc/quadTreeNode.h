#ifndef QUADTREENODE_H
#define QUADTREENODE_H

#include <cstdlib>
#include <iostream>

#include "satellite.h"

template<class T>
typedef struct{
	T data;
	point p;

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

	node() : data(), point(), parent(), child0(), child1(), child2(), child3() {
		checkMemory();
	}
	node(T dataIn) : data(dataIn), point(), parent(), child0(), child1(), child2(), child3() {
		checkMemory();
	}


	node(T dataIn, point pIn) : data(dataIn), point(pIn), parent(), child0(), child1(), child2(), child3() {
	
	~node(){
		delete child0;
		delete child1;
		delete child2;
		delete child3;
		delete parent;
	}

	node(const node& copy){
		data = copy.data;
		parent = copy.data;
		child0 = copy.child0;
		child1 = copy.child1;
		child2 = copy.child2;
		child3 = copy.child3;
	}

} node;

template<class T>
typedef struct{
	T rad;
	T inc;
	T azu;
} point;


#endif
