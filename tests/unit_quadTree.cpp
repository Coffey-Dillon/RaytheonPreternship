#include "../inc/quadTreeNode.h"
#include "../inc/quadTree.h"
#include "../inc/satellite.h"
#include "../inc/macros.h"

#include<iostream>
#include<cstdlib>


// Functions

void test_00_populate(int depth){
	quadTree<double, double> *tree = new quadTree<double, double>();
	node<double, double>* temp = tree->get_head(tree);
	tree->populate(temp, depth);
	COUT << "Populated quadTree: " << ENDL;
	COUT << "Output traverses through child 1 until the bottom is reached."  << ENDL;
	tree->printTree();
}

void test_01_getCoverage(){
	quadTree<Satellite<double>*, double> *test0= new quadTree<Satellite<double>*, double>();
	node<Satellite<double>*, double>* h0 = test0->get_head(test0);
	test0->populate(h0, 4);
	double temp = test0->getCoverage(h0);
	COUT << "Test0 coverage should be 0.0.\nCoverage = " << temp << "\n" << ENDL;
	delete test0;

	quadTree<Satellite<double>*, double> *test1 = new quadTree<Satellite<double>*, double>();
	node<Satellite<double>*, double>* h1 = test1->get_head(test1);
	test1->populate(h1, 4);
	h1->child0->covered = true;
	h1->child1->covered = true;
	h1->child2->covered = true;

	double temp1 = test1->getCoverage(h1);
	COUT << "Test1 coverage should be 0.75\nCoverage = " << temp1 << "\n" << ENDL;
	delete test1;
}

void test_02_populate_with_sat(){
	quadTree<Satellite<double>*, double> *quad = new quadTree<Satellite<double>*, double>(); 
	node<Satellite<double>*, double>* temp = quad->get_head(quad);
	Satellite<double> *sat = new Satellite<double>(1.57, 2.09333, 7372, 0.05);
	quad->populate(temp, sat, -1);
	COUT << "Populated quadTree with stored pointers to Satellite objects: " << ENDL;
	COUT << "Output traverses through child 1 until the bottom is reached."  << ENDL; 
	COUT << *quad << ENDL;
}

void test_03_populate_with_percent(){
	quadTree<Satellite<double>*, double> *quad = new quadTree<Satellite<double>*, double>(); 
	node<Satellite<double>* , double>* temp = quad->get_head(quad);
	Satellite<double> *sat = new Satellite<double>(1.57, 2.09333, 400372, 0.01);
	quad->populate(temp, sat, -1, 0.5);
	double percent = quad->getCoverage(quad->get_head(quad));
	COUT << "Populated quadTree with stored pointers to Satellite objects and covers only up to the target percent." << ENDL;
	COUT << "Output traverses through child 1 until the botttom is reached. " << ENDL;
	COUT << *quad << ENDL;
	COUT << percent << ENDL;
}

void test_05_populate_count(){
	quadTree<Satellite<double>*, double> *quad = new quadTree<Satellite<double>*, double>(); 
	node<Satellite<double>* , double>* temp = quad->get_head(quad);
	Satellite<double> *sat = new Satellite<double>(1.57, 2.09333, 1000, 0.25);
	quad->populate(temp, sat, -1, 100);
	COUT << "\n" << quad->getCoverage(quad->get_head(quad)) << ENDL;
	COUT << *quad << ENDL;
}

int main(){
	
	test_00_populate(4);
	test_01_getCoverage();
	test_02_populate_with_sat();
	test_03_populate_with_percent();
	test_05_populate_count();
	
	return 0;
}


