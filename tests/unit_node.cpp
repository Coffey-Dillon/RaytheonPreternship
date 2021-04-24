#include "../inc/quadTreeNode.h"

#include<iostream>
#include<cstdlib>
#define COUT std::cout
#define ENDL std::endl


int main(){
	
	node<int, int> nodeParent(10);
	node<int, int> nodeChild0(0);
	node<int, int> nodeChild1(1);
	node<int, int> nodeChild2(2);
	node<int, int> nodeChild3(3);

	COUT << "Testing Node: Parent should have value 10 and children0-3" << ENDL;
	
	COUT << "Parent: " << nodeParent.data << ENDL;
	COUT << "Child0: " << nodeChild0.data << ENDL;
	COUT << "Child1: " << nodeChild1.data << ENDL;
	COUT << "Child2: " << nodeChild2.data << ENDL;
	COUT << "Child3: " << nodeChild3.data << ENDL;


	return 0;

}
