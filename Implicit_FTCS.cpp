#include "Implicit_FTCS.h"

Implicit_FTCS::Implicit_FTCS()
{
	this->dt = 0;
	this->dx = 0;
	this->L = 0;
	this->timeStop = 0;
	this->U = 0;
}

Implicit_FTCS::Implicit_FTCS(double dx, double dt, double L, double timeStop, double U) {
	this->dt = dt;				//initialised space steps
	this->dx = dx;				//initialised times steps
	this->L = L;				// initalised length
	this->timeStop = timeStop;	//initialised timestop place
	this->U = U;				//initialised this value
}

void Implicit_FTCS::printout() {
	std::cout << "dx: " << dx << std::endl;
	std::cout << "dt: " << dt << std::endl;
	std::cout << "L: " << L << std::endl;
	std::cout << "stop time: " << timeStop << std::endl;
}

std::vector<std::vector<double>> Implicit_FTCS::Theoretical_Sol()
{
	std::cout << "doing the Implicit FTCS Theoretical Solution!" << std::endl;
	// doing the Thomas Algorithm for solveing tridiagonal Matricies
	// based off this site https://www.quantstart.com/articles/Tridiagonal-Matrix-Solver-via-Thomas-Algorithm

	std::vector<std::vector <double>> total_Vector;


	//need to get the initial vector vertially
	// f(x,0) = 0							when  0  <= x <= 50
	// f(x,0) = 100(sin(pi*((x-50)/60)))	when  50 <= x <= 110
	// f(x,0  = 0							when 110 <= x <= L -> where L is 400

	double x = 0; // keeps track of the spacing between X

	for (int i = 0; i < (L / dx); i++) {
		//mages the initial vector based on resolution what what is given.  
		if (x < 50) {
			//does the first bound given by question
			total_Vector.push_back(std::vector<double> { 0.0 });
			x += dx; //increase by step
		}
		else if ((x >= 50) && (x < 110)) {
			//gives second bound given by question
			double value = 100.0 * (sin(PI * ((x - 50.0) / 60.0)));
			total_Vector.push_back(std::vector<double> {value}); //based on what was given in the question
			x += dx;  //increase by step
		}
		else {
			//gives the rest
			total_Vector.push_back(std::vector<double> { 0.0 });
			x += dx; //increase by step
		}

	}

	// finding coefs, we know what (U*dt/2*dx) is -> a (alpha)
	// coef matrix wants to look like this
	// | 1  a  0  0  0 |
	// |-a  1  a  0  0 |
	// | 0 -a  1  a  0 |
	// | 0  0 -a  1  a |
	// | 0  0  0 -a  1 |

	double alpha = (U*dt) / (2 * dx); // will need this to make the matrix with -alpha and alpha
	std::vector<std::vector<double>> coefMatrix(total_Vector.size(), std::vector<double>(total_Vector.size(),0));
	std::vector<std::vector<double>> coefs_temp(total_Vector.size(), std::vector<double>(total_Vector.size(),0));
	
	//fill coefMatrix with the coefficients from the equation
	for (unsigned int row = 0; row < coefMatrix.size(); row++) {
		for (unsigned int col = 0; col < coefMatrix[row].size(); col++) {
			if ((row == 0) && (col == 0)) {
				//check to see if in first cell and sets the alpha accordingly
				
				coefMatrix[row][col] = 1.0;
				coefMatrix[row][col + 1] = alpha;
			}
			else if ((row == coefMatrix.size() - 1) && (col == coefMatrix[row].size() - 1)) {
				//checks to see if in last cell and sets the alpha accordingly
				coefMatrix[row][col] = 1.0;
				coefMatrix[row][col - 1] = -alpha;
			}
			else {
				if (row == col) {
					// checks to see if in the diagonal line and places the alphas accordingly
					coefMatrix[row][col - 1]= -alpha;
					coefMatrix[row][col] = 1.0;
					coefMatrix[row][col + 1] = alpha;
				}
			}
		}
	}

	//creates the "new" coefficient -> C'
	double bottom; // just help code more reada ble
	double top;
	double t = 0.0;
	int currTimeStep = 0;
	
	
	for (unsigned int i = 0; i < coefs_temp.size(); i++) {
		//i will for ever me on the diagonal so i can access the others easly
		//will be doing operations based on this look at C' and D' https://en.wikipedia.org/wiki/Tridiagonal_matrix_algorithm
		/*
		*        / ci/bi            ; i =1
		* C'  = |
		*        \ ci/bi- ai * C'i-1  ; i = 2,3..n-1
		*/
		coefs_temp[i][i] = 1;
		if (i == coefs_temp.size() - 1) break; // checks to see if if out of bounds ends loop if it is
		
		if (i == 0) {
			//do the C' operations for first value;
			coefs_temp[i][i + 1] = coefMatrix[i][i+1]/ coefMatrix[i][i];
		}
		else {
			//do the rest of the C' values
			bottom = coefMatrix[i][i] - (coefMatrix[i][i - 1] * coefs_temp[i - 1][i]);
			coefs_temp[i][i + 1] = coefMatrix[i][i + 1] / bottom;
		}
	}

	while (t < timeStop) {
		//need to make the "new" values -> D'
		/*
		*       / di/bi      ; i = 1
		* D' = |
		*		\ di- ai * d'i-1 / bi - ai * C'i-1
		*
		*/
		std::vector<std::vector<double>> currTimeVec;
		for (unsigned int i = 0; i < total_Vector.size(); i++) {
		
			if (i == 0) currTimeVec.push_back(std::vector<double>{ total_Vector[i][currTimeStep] / coefMatrix[i][i] });
			else {
				top = total_Vector[i][currTimeStep] - (coefMatrix[i][i - 1] * currTimeVec[i-1][0]);
				bottom = coefMatrix[i][i] - (coefMatrix[i][i-1]* coefs_temp[i-1][i]);
				currTimeVec.push_back(std::vector<double>{top / bottom});
			}
		}


		//finding X
		for (int i = total_Vector.size() - 1; i >= 0; i--) {
			//basically start at the base case and work backwards -> couldnt figure out how to do it recursivly (if i had more time i would be able to)
			//     '-> [x80 x79 x78 ----> x1]
			//since loop starts at idx 79, total_Vector[i] starts adding at bottom of vector, going up till done
			if (i == total_Vector.size() - 1) total_Vector[i].push_back(currTimeVec[i][0]);
			else {
				total_Vector[i].push_back(currTimeVec[i][0] - (coefs_temp[i][i + 1] * total_Vector[i + 1][currTimeStep + 1]));
			}
		}
		currTimeStep++;
		t += dt;
	}
	this->theoretical = total_Vector; //so that the writeToFile function can work
	return total_Vector;
}
