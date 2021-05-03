#ifndef SATELLITE_H
#define SATELLITE_H

#include <iostream>		// for std::*
#include <cstdlib>		// for NULL
#include <cmath>		// for M_PI

#include "quadTreeNode.h"

#define EARTH_RADIUS 6372 //km
#define COUT std::cout
#define ENDL std::endl

template<class T>
class Satellite{
	
	private:
		point<T>* position;
		double alt;			// km above Earth
		double view; 		// angle in detector cone, in rad
		double alpha;		// angle in Earth coverage cone (from Earth center)	

	public:

		Satellite() : position(), alt(), view(), alpha() { 
			position = new point<T>(0,0,0);
			setRadius();
			checkMemory(); 
		}

		Satellite(T incIn, T azuIn, T altIn, T viewIn) : position(0, incIn, azuIn), alt(altIn), view(viewIn), alpha() {
			position = new point<T>(0, incIn, azuIn);
			setRadius();
			setAlpha(); 
			checkMemory();
		}

		Satellite(T altIn, T viewIn) : position(), alt(altIn), view(viewIn), alpha() {
			position = new point<T>(0,0,0);
			setRadius();
			setAlpha();
			checkMemory();
		} 

		~Satellite() {
			delete position;
		};

		void checkMemory(){
			if(this == NULL){
				std::cerr << "Out of Memory: Satellite.h" << std::endl;	
			}
		}

		/* Set Methods */
		/* sets orbit radius for spherical coords */		
		void setRadius() {
			position->rad = alt + EARTH_RADIUS;
		}	

		void setAlt(const T altIn) {
			alt = altIn;
		}

		void setView(const T viewIn) {
			view = viewIn;
		}

		void setAlpha() {
			alpha = asin( (sin(view) / EARTH_RADIUS) * (EARTH_RADIUS + alt)) - view;
		}

		/* Get Methods */
		double getAlpha() const { return alpha; }		
		double getAlt() const { return alt; }
		double getView() const { return view; }
		T getAzu() const { return position->azu; }
		T getInc() const { return position->inc; }
		T getRadius() const { return position->rad; }

		/* radius of FoV cap in km */ 
		double getCapRadius() const {
			return EARTH_RADIUS * sin(alpha);
		}

		/* fraction of spherical earth coverage */
		double getFraction() const {
			return (1 - cos(alpha)) / 2;	
		}

		/* half arch length of FoV cap in km */ 
		double getHalfArchLen() const {
			return (360 / alpha) * (2 * M_PI * EARTH_RADIUS);
		}

		friend std::ostream& operator<<(std::ostream& output, const Satellite<T>& printSat){
			output << "Satellite point: " << printSat->position << ENDL;
			return output;
		} 
};

#endif
