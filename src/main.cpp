//main.cpp
//primarily user interface
//#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>


int main(){
	//input variables for satellites
	int numSatellites=0;
	int altitude=0;
	int fovDegrees=0;
	int depth=0;

	std::cout<<"Welcome to the Raytheon satellite coverage optimization program"<<std::endl;
	std::cout<<"---------------------------------------------------------------"<<std::endl<<std::endl;
	
	//get user input---number of satellites
	std::cout<<"Enter the number of satellites (0 to 50) for the simulation as an integer: "<<std::endl;
	while(!(numSatellites>0 && numSatellites<=50)){
		std::cin>> numSatellites;
		if(numSatellites>50 || numSatellites<=0){
			std::cout<<"Invalid input."<<std::endl;
			std::cout<<"Enter the number of satellites (0 to 50) for the simulation as an integer: "<<std::endl;
		}
	}
	
	//get user input---satellite altitude
	std::cout<<"Enter the uniform altitude (meters) of the satellites as an integer: "<<std::endl;
	while(!(altitude>0)){
		std::cin>> altitude;
		if(altitude<=0){
			std::cout<<"Invalid input."<<std::endl;
			std::cout<<"Enter the uniform altitude (meters) of the satellites as an integer: "<<std::endl;
		}
	}

	//get user input---satellite field of view
	std::cout<<"Enter the uniform field of view (degrees) of the satellites as an integer (up to 90 degrees): "<<std::endl;
	while(!(fovDegrees>0 && fovDegrees<=90)){
		std::cin>> fovDegrees;
		if(fovDegrees<=0 || fovDegrees>=90){
			std::cout<<"Invalid input."<<std::endl;
			std::cout<<"Enter the uniform field of view (degrees) of the satellites as an integer: "<<std::endl;
		}
	}


	std::cout<<"Enter the depth of the quadtree as an integer(4-10): "<<std::endl;
	while(!(depth>=4 && depth<=10)){
		std::cin>> depth;
		if(depth<4 || depth>10){
			std::cout<<"Invalid input."<<std::endl;
			std::cout<<"Enter the depth of the quadtree as an integer(4-10): "<<std::endl;
		}
	}
}
