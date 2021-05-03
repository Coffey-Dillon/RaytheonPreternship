#ifndef NODE_H
#define NODE_H

#include "quadTreeNode.h"
#include <cstdlib>		// for NULL
#include <cmath>		// for M_PI

#define EARTH_RADIUS 6372 //km

template<typename T>
class Satellite{
	
	private:
		point position;
		double alt;			// km above Earth
		double view; 		// angle in detector cone, in rad
		double alpha;		// angle in Earth coverage cone (from Earth center)	

	public:

		Satellite() : position(0,0,0), alt(), view(), alpha() { 
			setRadius();
			checkMemory(); 
		}

		Satellite(T incIn, T azuIn, T altIn, T viewIn) : position(0, incIn, azuIn), alt(altIn), view(viewIn), alpha() {
			setRadius();
			setAlpha(); 
			checkMemory();
		}

		Satellite(T altIn, T viewIn) : position(0,0,0), alt(altIn), view(viewIn), alpha() {
			setRadius();
			setAlpha();
			checkMemory();
		} 

		~Satellite() {};


		/* Set Methods */
		/* sets orbit radius for spherical coords */		
		void setRadius() {
			position.rad = alt + EARTH_RADIUS;
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
		T getAzu() const { return position.azu }
		T getInc() const { return position.inc }
		T getRadius() const { return position.rad }

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
	
		

};

#endif
