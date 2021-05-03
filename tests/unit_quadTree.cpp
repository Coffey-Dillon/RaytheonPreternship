#include "../inc/quadTreeNode.h"
#include "../inc/quadTree.h"

#include<iostream>
#include<cstdlib>

#define COUT std::cout
#define ENDL std::endl

template<class T, class S>
void test_00_populate(quadTree<T, S>* qt, int depth){
	node<T, S>* temp = qt->get_head(qt);
	qt->populate(temp, depth);
	COUT << *qt << ENDL;
	return;
}

template<class T, class S>
void test_01_getCoverage(quadTree<T, S>* qt){
	node<T, S>* h = qt->get_head(qt);
	double temp = qt->getCoverage(h);
	COUT << "Test coverage should be ~1.00.\nCoverage = " << temp << ENDL;
}

int main(){
	
	quadTree<double, double> *tree = new quadTree<double, double>();
	
	test_00_populate(tree, 5);
	test_01_getCoverage(tree);
	
	return 0;
}


