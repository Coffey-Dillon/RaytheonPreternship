#include "../inc/quadTreeNode.h"

#include<iostream>
#include<cstdlib>
#define COUT std::cout
#define ENDL std::endl


int main(){
	
	node<double, double> nodeParent(10);
	node<double, double> nodeChild0(0);
	node<double, double> nodeChild1(1);
	node<double, double> nodeChild2(2);
	node<double, double> nodeChild3(3);

	COUT << "Testing Node: Parent should have value 10 and children0-3" << ENDL;
	
	COUT << "Parent: " << nodeParent.data << ENDL;
	COUT << "Child0: " << nodeChild0.data << ENDL;
	COUT << "Child1: " << nodeChild1.data << ENDL;
	COUT << "Child2: " << nodeChild2.data << ENDL;
	COUT << "Child3: " << nodeChild3.data << ENDL;


	return 0;

}
