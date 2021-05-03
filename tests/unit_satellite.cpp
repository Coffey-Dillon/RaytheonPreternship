#include "../inc/satellite.h"
#include <iostream>
#include <cstdlib>

#define COUT std::cout
#define ENDL std::endl

int main() {
	
	
	Satellite<T> sat1;
	
	COUT << "Satellite attributes:" << ENDL;
	COUT << "postition radius: " << sat1.getRadius << ENDL;
	COUT << "azumithal ang: " << sat1.getAzu << ENDL; 
	COUT << "inclination: " << sat1.getInc << ENDL;
	COUT << "altitude: " << sat1.getAlt << ENDL;
	COUT << "central Earth ang: " << sat1.getAlpha << ENDL;
	COUT << "view: " << sat1.getView << ENDL;
	COUT << "cap radius: " << sat1.getCapRadius<< ENDL;
	COUT << "half arch len: " << sat1.getHalfArchLen << ENDL;
	COUT << "coverage fraction: " << sat1.getFraction << ENDL;

	return 0;
}
