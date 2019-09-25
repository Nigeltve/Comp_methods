#include "ExplicitUpwind.h"


ExplicitUpwind::ExplicitUpwind()
{
	
	this->dt = 0;
	this->dx = 0;
	this->L = 0;
	this->timeStop = 0;
	this->U = 0;
	
}

ExplicitUpwind::ExplicitUpwind(double dx, double dt, double L, double timeStop, double U) {
	
	this->dt = dt;				//initialised space steps
	this->dx = dx;				//initialised times steps
	this->L = L;				// initalised length
	this->timeStop = timeStop;	//initialised timestop place
	this->U = U;				//initialised this value
}

void ExplicitUpwind::printout() {
	
	std::cout << "dx: " << dx << std::endl;
	std::cout << "dt: " << dt << std::endl;
	std::cout << "L: " << L << std::endl;
	std::cout << "stop time: " << timeStop <<std::endl;
}

std::vector<std::vector<double>> ExplicitUpwind::Theoretical_Sol() {
	std::cout << "doing Theoretical Solution" << std::endl;
	//need to get the initial vector vertially
	// f(x,0) = 0							when  0  <= x <= 50
	// f(x,0) = 100(sin(pi*((x-50)/60)))	when  50 <= x <= 110
	// f(x,0  = 0							when 110 <= x <= L -> where L is 400

	double x = 0; // keeps track of the spacing between X

	for (int i = 0; i < (L / dx); i++) {
		//mages the initial vector based on resolution what what is given.  
		if (x < 50) {
			//does the first bound given by question
			theoretical.push_back(std::vector<double> { 0.0 });
			x += dx; //increase by step
		}
		else if ((x >= 50) && (x < 110)) {
			//gives second bound given by question
			double value = 100.0 * (sin(PI * ((x - 50.0) / 60.0)));
			theoretical.push_back(std::vector<double> {value}); //based on what was given in the question
			x += dx;  //increase by step
		}
		else {
			//gives the rest
			theoretical.push_back(std::vector<double> { 0.0 });
			x += dx; //increase by step
		}

	}

	double t; // need this to know wher the time starts
	double value; // just a place holder for storing into vector. makes it easier to read
	double alpha = (U*dt) / dx; // since this is constant, no need to recalculate this.
	int current_space = 0; // keeps track of the current space
	
	for (t = 0; t < timeStop; t += dt) {
		//goes through all points in space
		for (int row = 1; row < theoretical.size(); row++) {
			// goes through all the points in space as set by the inital vectors
			if (row == 1) theoretical[row - 1].push_back(0.0); //get the 0th index
			value = theoretical[row][current_space] - (alpha * (theoretical[row][current_space] - theoretical[row - 1][current_space]));
			//std::cout << value << std::endl;
			theoretical[row].push_back(value); //puts value in right vector
		}
		current_space++; // increase the space
	}

	return theoretical; //returns this so user can use it for further use.
}
