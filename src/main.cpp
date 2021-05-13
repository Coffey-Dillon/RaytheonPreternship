/* Raytheon Preternship
 * main.cpp
 * Command line User Interface
 */

#include "../inc/macros.h"
#include "../inc/quadTree.h"
#include "../inc/satellite.h"

// Functions for getting user input

double getAltitude(){
	double temp = -1;
	while(temp < 0){
		if(temp != -1){
			COUT << "Please enter a positive value for altitude." << ENDL;		
		}
		COUT << "Enter altitude of satellites in kilometes above the surface of earth: ";
		CIN >> temp;
	}
	COUT << "\n";
	return temp;
}

double getFieldOfView(){
	double temp = -1;
	while(temp < 0 && temp < 2 * M_PI){
		if(temp != -1){
			COUT << "Please enter valid field of view." << ENDL;		
		}
		COUT << "Enter a field of view for the satellites in radians: ";
		CIN >> temp;
	}
	COUT << "\n";
	return temp;
}

double getCoveragePerSat(){
	double temp = -1;
	while(temp < 0 || temp > 0.5){
		if(temp != -1){
			COUT << "Please enter a value larger than 0.0  and less than 0.5." << ENDL;		
		}
		COUT << "Enter intended coverage of each satellite as a percentage: ";
		CIN >> temp;
	}
	COUT << "\n";
	return temp;
}

double getPercent(){
	double temp = 1.1;
	while(temp > 1.0){
		if((temp < 0 || temp > 1) && temp != 1.1){
			COUT << "Please enter a value between 0.0 and 1.0." << ENDL;		
		}
		COUT << "Enter the target percent coverage of the consellation: ";
		CIN >> temp;
	}
	COUT << "\n";
	return temp;
}

int getNumSats(){
	int temp = -1;
	while(temp < 0){
		if(temp != -1){
			COUT << "Please enter a value above 0." << ENDL;		
		}
		COUT << "Enter the planned number of satellites in the consellation: ";
		CIN >> temp;
	}
	COUT << "\n";
	return temp;
}

double getlatitude(){
	double temp = -100;
	while(temp < -90 || temp > 90){
		if(temp != -1){
			COUT << "Please enter a value between -90 and 90 degrees." << ENDL;
		}
		COUT << "Enter latitude: ";
		CIN >> temp;
	}
	COUT << "\n";
	return temp;
}

double getlongitude(){
	double temp = -100;
	while(temp < -90 || temp > 90){
		if(temp != -1){
			COUT << "Please enter a value between -90 and 90 degrees." << ENDL;
		}
		COUT << "Enter longitude: ";
		CIN >> temp;
	}
	COUT << "\n";
	return temp;
}



template<class T, typename S>
void interact(quadTree<T, S>* qt){
	char userIn = 'c';
	int inter;
	while(userIn != 'q' && userIn > 39){
		COUT << "\nChoose an interaction:\n" 
			 << "\t1: Check total coverage.\n"
			 << "\t2: Check total number of Satellites\n"
			 << "\t3: Check coverage at a specific latitude and longitude.\n"
			 << "\t4: Add additional satellites\n"
			 << "\t5: Remove satellites\nInput: ";
		CIN >> inter;

		switch(inter){
			case 1:
				COUT << "Total coverage: " << qt->getCoverage(qt->get_head(qt)) << ENDL;
				break;
			case 2:
				COUT << "Total number of satellites: " << qt->getNumSats() << ENDL;
				break;
			case 3:{
				double lat = getlatitude();	
				double log = getlongitude();
				bool out = qt->locationStatus(lat, log) ? true : false;
				COUT << "Latitude, Longitude (" << lat << ", " << log << ") is "; 
				if(out){
					COUT << "covered. " << ENDL;
				} else {
					COUT << "not covered." << ENDL;
				}
				break;

			}
		}

		COUT << "Press 'c' to continue or 'q' to quit.\nInput: ";
		CIN >> userIn;
	}
}


int main(){
	
	int func;

	// Variable set to default values
	double altitude = 1000;
	double fieldOfView = 0.05;
	double percent = 1.0;
	int numSats;
	
	std::system("clear");
	COUT << "------------------------------------------------------------------------------------------------\n\n";
	COUT << "\tRaytheon Preternship satellite constellation program: \n\n" 
		 << "This program models a satellite constellation around earth using user input parameters.\n" 
		 << "Select a use case then enter the prompted values. The program will generate a model of \n"
		 << "earth and place satellites in a constellation based on the given parameters.\n"
		 << ENDL;
	
	char excmd = 'c';
	while(excmd == 'c'){
		COUT << "\nEnter value to be determined: " << ENDL;
		COUT << "\t1: Number of Satellites from coverage, altitude, and FOV\n\t2: Expected Coverage from number of Satellites, altitude, and FOV \n\t3: Custom constellation model\nInput:  ";
		CIN >> func;

		switch(func){
			case 1: {
				altitude = getAltitude();
				fieldOfView = getFieldOfView();
				percent = getPercent();
				quadTree<Satellite<double>*, double> *quad = new quadTree<Satellite<double>*, double>();
				Satellite<double>* sat = new Satellite<double>(1.57, 2.09333, altitude, fieldOfView);
				quad->populate(quad->get_head(quad), sat, -1, percent);
				numSats = quad->getNumSats(); 
				COUT << "The Number of Satellites needed is: " << numSats << ENDL;
				delete quad;
				break;
			}
			case 2: {
				altitude = getAltitude();
				fieldOfView = getFieldOfView();
				numSats = getNumSats();
				quadTree<Satellite<double>*, double> *quad = new quadTree<Satellite<double>*, double>();
				Satellite<double>* sat = new Satellite<double>(1.57, 2.09333, altitude, fieldOfView);
				quad->populate(quad->get_head(quad), sat, -1, numSats);
				percent = quad->getCoverage(quad->get_head(quad)); 
				COUT << "The total constellation coverage is: " << percent << ENDL;
				delete quad;
				break;
			}
			case 3: {
				std::system("clear");
				int userIn;
				COUT << "Welcome to custom constellation creation mode. Build a constellation using either\n"
					 << "a specified number of Satellites or a specified coverage.\n\n"
			  	 	 << "\tBuild by: \n" 
				 	 << "\t 1: Number of Satellites\n"
				 	 << "\t 2: Target coverage\nInput: ";
				CIN >> userIn;
				altitude = getAltitude();
				fieldOfView = getFieldOfView();
				quadTree<Satellite<double>*, double> *quad = new quadTree<Satellite<double>*, double>();
				Satellite<double>* sat = new Satellite<double>(1.57, 2.09333, altitude, fieldOfView);
			
				if(userIn == 1){
					numSats = getNumSats();
					quad->populate(quad->get_head(quad), sat, -1, numSats);
				} else{
					percent = getPercent();
					quad->populate(quad->get_head(quad), sat, -1, percent);
				}
				interact(quad);
				break;
			}

			default:
				break;
		}
		
		COUT << "Press 'c' to continue.\nInput: ";
		CIN >> excmd;
	}

	return 0;	
}
