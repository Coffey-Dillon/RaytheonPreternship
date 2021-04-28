#ifndef QUADTREENODE_H
#define QUADTREENODE_H

#include <cstdlib>
#include <iostream>

#include "satellite.h"

template<typename T>
struct point{
	T rad;
	T inc;
	T azu;

	point<T>(){}
};


template<typename T, typename S>
struct node{
	T data;
	point<S> p;

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

	node() : data(), parent(NULL), child0(NULL), child1(NULL), child2(NULL), child3(NULL) {
		checkMemory();
	}
	node(T dataIn) : data(dataIn), parent(NULL), child0(NULL), child1(NULL), child2(NULL), child3(NULL) {
		checkMemory();
	}

	node(T dataIn, point<S> pIn) : data(dataIn), point<S>(pIn), parent(NULL), child0(NULL), child1(NULL), child2(NULL), child3(NULL) {
		checkMemory();
	}
	
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





};


#endif
