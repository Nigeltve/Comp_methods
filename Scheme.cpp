#include "Scheme.h"

Scheme::Scheme(){}
std::vector<std::vector<double>> Scheme::analytical_Sol() 
{	
	std::cout << "doing the analytical solution" << std::endl;

	//need to get the initial vector vertially
	// f(x,0) = 0							when  0  <= x <= 50
	// f(x,0) = 100(sin(pi*((x-50)/60)))	when  50 <= x <= 110
	// f(x,0  = 0							when 110 <= x <= L -> where L is 400

	double x = 0; // keeps track of the spacing between X

	for (int i = 0; i < (L / dx); i++) {
		//makes the initial vector based on resolution what what is given.  
		if (x < 50) {
			//does the first bound given by question
			analytical.push_back(std::vector<double> { 0.0 });
			x += dx; //increase by step
		}
		else if ((x >= 50) && (x < 110)) {
			//gives second bound given by question
			double value = 100.0 * (sin(PI * ((x - 50.0) / 60.0)));
			analytical.push_back(std::vector<double> {value}); //based on what was given in the question
			x += dx;  //increase by step
		}
		else {
			//gives the rest
			analytical.push_back(std::vector<double> { 0.0 });
			x += dx; //increase by step
		}
	}

	double t;
	double value;
	for (t = 0; t < timeStop; t += dt) { // keeps track of where in time the loop is
		x = 0; //keeps track of where space is in the loop
		for (int row = 0; row < analytical.size(); row++) {
			//all boundaries set from the Analytical solutions given
			//once a calculation is done step forward in time. 
			if (x < (50 + 250 * t)) { 
				analytical[row].push_back(0.0);
				x += dx; 
			}
			else if ((x >= 50 + 250 * t) && (x < 110 + 250 * t)) {
				value = 100 * (sin(PI * ((x - 50 + 250 * t) / 60)));
				analytical[row].push_back(value);
				x += dx;
			}
			else {
				analytical[row].push_back(0.0);
				x += dx;
			}
		}
	}

	return analytical; //returns this, so the user can use sit for further use
}

void Scheme::writeToFile(std::string FileName)
{
	//sets up file for Analytical sol
	std::string  anal_name = "results/Analyical_" + FileName + ".csv";
	std::ofstream anal_file(anal_name);

	//sets up a files for Theretical sol
	std::string theory_name = "results/theoretical_" + FileName + ".csv";
	std::ofstream theory_file(theory_name);
	
	try {
		if (analytical.empty() && theoretical.empty()) throw 100; //if both emtpy bring up flag
		else if (!analytical.empty() && theoretical.empty()) {
			//writes a CSV file for the user can use it in other programs.
			//creates the CSV file for the Analytical Scheme
			std::cout << "---Writing Analytical!" << std::endl;

			double t = 0;
			std::string time;
			for (double i = 0; i < analytical[0].size(); i++) {
				//first writes the headers for columns
				time = std::to_string(t);
				anal_file << "dt:" << time;
				if (i == analytical[0].size()-1) {
					anal_file << std::endl;
				}
				else {
					anal_file << ", ";
				}
				t += dt;
			}

			for (int i = 0; i < analytical.size(); i++) {
				//goes through each element and puts into CSV files
				for (int j = 0; j < analytical[i].size(); j++) {
					anal_file << analytical[i][j];
					if (j == analytical[i].size() - 1) {
						//if end of row, make new line
						anal_file << std::endl;
					}
					else {
						//if not end of line, puts a comma.
						anal_file << ", ";
					}
				}
			}
		}
		else if (analytical.empty() && !theoretical.empty()) {
			//writes CSV for theoretical.
			std::cout << "Writing Theoretical!-----" << std::endl;

			double t = 0;
			std::string time;
			for (double i = 0; i < theoretical[0].size(); i++) {
				//writes header for columns 
				time = std::to_string(t); //need to change it to string
				theory_file << "dt:" << time;
				if (i == theoretical[0].size() - 1) {
					theory_file << std::endl; //if row end -> add new line
				}
				else {
					theory_file << ", "; //if not end of row, add comma
				}
				t += dt;
			}

			for (int i = 0; i < theoretical.size(); i++) {
				//goes trhough vlaues
				for (int j = 0; j < theoretical[i].size(); j++) {
					theory_file << theoretical[i][j];
					if (j == theoretical[i].size() - 1) {
						theory_file << std::endl; //if row end -> add new line
					}
					else {
						theory_file << ", ";//if not end of row, add comma
					}
				}
			}
		}
		else if (!analytical.empty() && !theoretical.empty()) {
			std::cout << "------------Writing Both!------------" << std::endl;
			//makes both CSV files.

			double t = 0;
			std::string time;
			for (double i = 0; i < analytical[0].size(); i++) {
				//makes headers for columns
				time = std::to_string(t); //converts to string
				anal_file << "dt:" << time;
				if (i == analytical[0].size() - 1) {
					anal_file << std::endl; //if at end -> add new line
				}
				else {
					anal_file << ", "; // if not -> add comma
				}
				t += dt; //increments 
			}

			for (int i = 0; i < analytical.size(); i++) {
				for (int j = 0; j < analytical[i].size(); j++) {
					anal_file << analytical[i][j];
					if (j == analytical[i].size() - 1) {
						anal_file << std::endl;
					}
					else {
						anal_file << ", ";
					}
				}
			}

			t = 0;

			for (double i = 0; i < theoretical[0].size(); i++) {
				time = std::to_string(t);
				theory_file << "dt:" << time;
				if (i == theoretical[0].size() - 1) {
					theory_file << std::endl;
				}
				else {
					theory_file << ", ";
				}
				t += dt;
			}

			for (int i = 0; i < theoretical.size(); i++) {
				for (int j = 0; j < theoretical[i].size(); j++) {
					theory_file << theoretical[i][j];
					if (j == theoretical[i].size() - 1) {
						theory_file << std::endl;
					}
					else {
						theory_file << ", ";
					}
				}
			}
		}
	}
	catch (int x) {
		//if error thrown, say what the error is, say why, say how to fix it.
		if (x == 100) std::cout << "ERROR 100: Cannot write to files\nYou have not called the Analytical or Theoretical solution Methods.\nPlease do that first." << std::endl;
	}
}