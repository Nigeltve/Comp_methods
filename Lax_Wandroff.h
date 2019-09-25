#ifndef LAX_WANDROFF_H
#define LAX_WANDROFF_H

#define PI 4*atan(1) // seems that c++ doesnt have a set deffinition... 

#include "Scheme.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <string>
class Lax_Wandroff : public Scheme
{
public:
	/**
	* sets the default values for the Explicit Scheme to zero
	*
	* @param takes no parameters
	* @return returns a instance of the Explicit scheme with all values set to zero.
	*/
	Lax_Wandroff();

	/**
	* sets all the values needed for the class to work
	*
	* @param dx: sets the inital space value
	* @param dt: sets the inital time value
	* @param L: sets the end space value. this is where the simulations ends
	* @param timeStop: sets where in time the simluations should stop
	* @param U: sets the U value in the equations
	*/
	Lax_Wandroff(double dx, double dt, double L, double timeStop, double U);

	/**
	* Prints out all the values that the instance has been set to
	* @param takes no parameters
	* @return returns nothing
	*/
	void printout();

	/**
	* based on the given value of the instance for the Implicit Lax Wandroff scheme.
	* it will return a vector of vectors (a Matrix) so that the user can use it.
	* for further use. with the rows being a single space going through time and
	* a column going through a single instance in time but all points in space.
	*
	* @param takes nothing
	* @return returns a vector of vectors
	*/
	std::vector<std::vector<double>> Theoretical_Sol();
};

#endif