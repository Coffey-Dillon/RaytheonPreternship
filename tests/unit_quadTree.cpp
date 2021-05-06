#include "../inc/quadTreeNode.h"
#include "../inc/quadTree.h"
#include "../inc/satellite.h"

#include<iostream>
#include<cstdlib>

#define COUT std::cout
#define ENDL std::endl



// Functions
template<class T, class S>
void test_00_populate(quadTree<T, S>* qt, int depth){
	node<T, S>* temp = qt->get_head(qt);
	qt->populate(temp, depth);
	COUT << "Populated quadTree: " << ENDL;
	COUT << *qt << ENDL;
	return;
}


template<class T, class S>
void test_01_getCoverage(quadTree<T, S>* qt){
	node<T, S>* h = qt->get_head(qt);
	double temp = qt->getCoverage(h);
	COUT << "Test coverage should be ~0.25.\nCoverage = " << temp << ENDL;
	COUT << ENDL;
}

template<class T, typename S>
void test_02_populate_with_sat(quadTree<T, S> *qt){
	node<T , S>* temp = qt->get_head(qt);
	Satellite<S> *sat = new Satellite<S>(1.57, 2.09333, 7372, 0.5);
	qt->populate(temp, sat, -1);
	COUT << "Populated quadTree with stored pointers to Satellite objects: " << ENDL;
	COUT << *qt << ENDL;
}

int main(){
	
	quadTree<double, double> *tree = new quadTree<double, double>();
	quadTree<Satellite<double>*, double> *test = new quadTree<Satellite<double>*, double>(); 
	
	test_00_populate(tree, 3);
	test_01_getCoverage(tree);
	test_02_populate_with_sat(test);
	
	return 0;
}


