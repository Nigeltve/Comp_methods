#include "Lax_Wandroff.h"

Lax_Wandroff::Lax_Wandroff()
{
	//sets all values to 0
	this->dt = 0;
	this->dx = 0;
	this->L = 0;
	this->timeStop = 0;
	this->U = 0;
}

Lax_Wandroff::Lax_Wandroff(double dx, double dt, double L, double timeStop, double U)
{
	this->dt = dt;				//initialised space steps
	this->dx = dx;				//initialised times steps
	this->L = L;				// initalised length
	this->timeStop = timeStop;	//initialised timestop place
	this->U = U;				//initialised this value
}

void Lax_Wandroff::printout()
{
	//prints out everything set
	std::cout << "dx: " << dx << std::endl;
	std::cout << "dt: " << dt << std::endl;
	std::cout << "L: " << L << std::endl;
	std::cout << "stop time: " << timeStop << std::endl;
}

std::vector<std::vector<double>> Lax_Wandroff::Theoretical_Sol()
{

	std::cout << "doing the Lax Wandroff Theoretical Solution!" << std::endl;
	//lax Wandroff has 2 seperate alphas, negative and positive
	double alpha1 = (U * dt) / (2 * dx);   // U^2 * dt12
	double alpha2 = ((U*U)*(dt*dt)) / (2 * (dx*dx)); //sets the second alpha value in scheme

	std::vector<std::vector <double>> totalVect; 

	//need to get the initial vector vertially
	// f(x,0) = 0							when  0  <= x <= 50
	// f(x,0) = 100(sin(pi*((x-50)/60)))	when  50 <= x <= 110
	// f(x,0  = 0							when 110 <= x <= L -> where L is 400

	double x = 0; // keeps track of the spacing between X

	for (int i = 0; i < (L / dx); i++) {
		//mages the initial vector based on resolution what what is given.  
		if (x < 50) {
			//does the first bound given by question
			totalVect.push_back(std::vector<double> { 0.0 });
			x += dx; //increase by step
		}
		else if ((x >= 50) && (x < 110)) {
			//gives second bound given by question
			double value = 100.0 * (sin(PI * ((x - 50.0) / 60.0)));
			totalVect.push_back(std::vector<double> {value}); //based on what was given in the question
			x += dx;  //increase by step
		}
		else {
			//gives the rest
			totalVect.push_back(std::vector<double> { 0.0 });
			x += dx; //increase by step
		}

	}

	//sets values for calculation
	double t;
	double value;
	double bit1;
	double bit2;
	double bit3;
	int current_space = 0;
	for(t = 0; t < timeStop; t+=dt){
		for (int row = 1; row < totalVect.size() - 1; row++) {
			//goes through space
			if (row == 1) totalVect[row - 1].push_back(0.0); // we know that the inital and last spaces are 0
			
			//std::cout << totalVect[row][current_space] << ", " << std::endl;
			bit1 = totalVect[row][current_space]; //first part off the scheme
			bit2 = alpha1 * (totalVect[row + 1][current_space] - totalVect[row - 1][current_space]); //second part o the scheme
			bit3 = alpha2 * (totalVect[row + 1][current_space] + totalVect[row - 1][current_space] - (2 * totalVect[row][current_space])); // third part of the scheme
			value = bit1 - bit2 + bit3; //puts it all together
			 
			totalVect[row].push_back(value); //puts the value into correct row
		
			if (row == totalVect.size() - 2) totalVect[row + 1].push_back(0.0); // if last then put a 0
		}
		current_space++; //moves the current space 1
	}

	this->theoretical = totalVect; //so that the writeToFile function can work
	return totalVect;
}