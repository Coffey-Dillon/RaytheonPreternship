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

int main(){
	
	quadTree<int, int> *tree = new quadTree<int, int>();
	
	test_00_populate(tree, 1);
	
	return 0;
}



