#include "../inc/quadTreeNode.h"

#include<iostream>
#include<cstdlib>
#define COUT std::cout
#define ENDL std::endl

template<class T, class S>
void test_00_locate_children(node<T, S>* node){
	point<S> *tp = new point<S>(0.0, 0.0, 0.0);
	node->p = tp;
	node->locate_children();
}


int main(){
	
	node<double, double>* nodeParent = new node<double, double>(10);
	node<double, double>* nodeChild0 = new node<double, double>(0);
	node<double, double>* nodeChild1 = new node<double, double>(1);
	node<double, double>* nodeChild2 = new node<double, double>(2);
	node<double, double>* nodeChild3 = new node<double, double>(3);

	COUT << "Testing Node: Parent should have value 10 and children0-3" << ENDL;
	
	COUT << "Parent: " << nodeParent->data << ENDL;
	COUT << "Child0: " << nodeChild0->data << ENDL;
	COUT << "Child1: " << nodeChild1->data << ENDL;
	COUT << "Child2: " << nodeChild2->data << ENDL;
	COUT << "Child3: " << nodeChild3->data << ENDL;

	// Assigns manually created child nodes to parent node
	nodeParent->child0  = nodeChild0;
	nodeParent->child1  = nodeChild1;
	nodeParent->child2  = nodeChild2;
	nodeParent->child3  = nodeChild3;


	test_00_locate_children(nodeParent);
	COUT << "Parent point: " << nodeParent->p << ENDL;
	COUT << "Child0 point: " << nodeChild0->p << ENDL;
	COUT << "Child1 point: " << nodeChild1->p << ENDL;
	COUT << "Child2 point: " << nodeChild2->p << ENDL;
	COUT << "Child3 point: " << nodeChild3->p << ENDL;
	return 0;

}
