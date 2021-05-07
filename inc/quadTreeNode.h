#ifndef QUADTREENODE_H
#define QUADTREENODE_H


//Globals
//TODO make a macros.h file with globals, libraries, and define statements
double earthRad = 6370;
double pi = 3.14;


template<typename T>
struct point{
	T rad;
	T inc;
	T azu;

	point<T>() {}
	point<T>(T radius, T inclination, T azumith) : rad(radius), inc(inclination), azu(azumith) {}

	// Assignment operator
	point<T>* operator=(point<T>* assign){
		this->rad = assign->rad;
		this->inc = assign->inc;
		this->azu = assign->azu;

		return assign;
	}

	friend std::ostream& operator<<(std::ostream& output, const point<T>& printData){
		output << "radius: " << printData.rad << ", inclination: " << printData.inc << ", azimuth: " << printData.azu;
		return output;
	}
};


template<typename T, typename S>
struct node{
	T data;
	point<S> p;
	int lvl;				//depth in the quadTree that the node lies on. inital 4 children nodes are lvl 1
	bool covered;
	
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

	node(): data(), lvl(1), parent(NULL), child0(NULL), child1(NULL), child2(NULL), child3(NULL) {
		checkMemory();
		p = new point<S>();
	}
	
	node(T dataIn) : data(dataIn), lvl(1), parent(NULL), child0(NULL), child1(NULL), child2(NULL), child3(NULL) {
		checkMemory();
		p = new point<S>();
	}

	node(T dataIn, point<S> pIn) : data(dataIn), lvl(1), parent(NULL), point<S>(pIn), parent(NULL), child0(NULL), child1(NULL), child2(NULL), child3(NULL) {
		checkMemory();
	}
	
	~node(){
		delete child0;
		delete child1;
		delete child2;
		delete child3;
		delete p;
	}

	node(const node& copy){
		data = copy.data;
		parent = copy.data;
		child0 = copy.child0;
		child1 = copy.child1;
		child2 = copy.child2;
		child3 = copy.child3;
	}
	
	// Determines the values to be stored in the point struct of each node.
	// Uses the point object help by the current node to determine the point object values 
	//  for the children of the node.
	bool locate_children(){
		if(p.rad == 0){
			child0->p.inc = 0;
			child0->p.azu = 0;
			child0->p.rad = earthRad;
			child0->lvl = 1;

			child1->p.inc = pi / 2;
			child1->p.azu = 2 * pi / 3;
			child1->p.rad = earthRad;
			child1->lvl = 1;

				
			child2->p.inc = pi / 2;
			child2->p.azu = 4 * pi / 3;
			child2->p.rad = earthRad;
			child2->lvl = 1;


			child3->p.inc = pi / 2;
			child3->p.azu = 6 * pi / 3;
			child3->p.rad = earthRad;
			child3->lvl = 1;

		} else{
			child0->lvl = lvl + 1;
			child0->p = p;
				
			child1->lvl = lvl + 1;
			child1->p.inc = p.inc - (2 * pi / (3 * lvl))/4;
			child1->p.azu = p.azu - (2 * pi / (3 * lvl))/4;
			child1->p.rad = earthRad;
				
			child2->lvl = lvl + 1;
			child2->p.inc = p.inc + (2 * pi / (3 * lvl))/4;
			child2->p.azu = p.azu;
			child2->p.rad = earthRad;
				
			child3->lvl = lvl + 1;
			child3->p.inc = p.inc - (2 * pi / (3 * lvl))/4;
			child3->p.azu = p.azu + (2 * pi / (3 * lvl))/4;
			child3->p.rad = earthRad;
		}
		return true;
	}

	// Assignment operator
	node& operator=(const node& assign){
		if(this != assign){
			this->data = assign.data;
			this->p = assign.p;
			this->parent = assign.parent;
			this->child0 = assign.child0;
			this->child1 = assign.child1;
			this->child2 = assign.child2;
			this->child3 = assign.child3;
		}
	}
	node* operator=(const node* assign){
		if(this != assign){
			this->data = assign.data;
			this->p = assign->p;
			this->parent = assign->parent;
			this->child0 = assign->child0;
			this->child1 = assign->child1;
			this->child2 = assign->child2;
			this->child3 = assign->child3;
		}
	}

	// Friend method to print node
	friend std::ostream& operator<<(std::ostream& output, const node<T, S>& printNode){
		output << "Node data: " << printNode.data << std::endl;
		output << "Node point: " << printNode.p << std::endl;
		return output;
	}
};


#endif
