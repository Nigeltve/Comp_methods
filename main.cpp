#include "ExplicitUpwind.h"
#include "Implicit_FTCS.h"
#include "Lax_Wandroff.h"
#include "Implicit_Upwind.h"


using namespace std;

int main() {
	
	//-------------------------------------------------------------------//
	//							Anaylitical Solution	                 //
	//-------------------------------------------------------------------//
	
	ExplicitUpwind EU(5.0, 0.02, 400, 0.5, 250);
	vector<vector<double>> Analyical = EU.analytical_Sol();	
	EU.writeToFile("5_02");
	
	ExplicitUpwind EU1(5.0, 0.01, 400, 0.5, 250);
	vector<vector<double>> Analyical1 = EU1.analytical_Sol();
	EU1.writeToFile("5_01");

	ExplicitUpwind EU2(5.0, 0.005, 400, 0.5, 250);
	vector<vector<double>> Analyical2 = EU2.analytical_Sol();
	EU2.writeToFile("5_005");
	
	
	//-------------------------------------------------------------------//
	//				    Explicit UpWind Theoretical Solution	         //
	//-------------------------------------------------------------------//

	ExplicitUpwind EU_T1(5.0, 0.02, 400, 0.5, 250);
	vector<vector<double>> EU_theory = EU_T1.Theoretical_Sol();
	EU_T1.writeToFile("EU_5_02");

	ExplicitUpwind EU_T2(5.0, 0.01, 400, 0.5, 250);
	vector<vector<double>> EU_theory1 = EU_T2.Theoretical_Sol();
	EU_T2.writeToFile("EU_5_01");

	ExplicitUpwind EU_T3(5.0, 0.005, 400, 0.5, 250);
	vector<vector<double>> EU_theor2 = EU_T3.Theoretical_Sol();
	EU_T3.writeToFile("EU_5_005");
	
	//-------------------------------------------------------------------//
	//				     FTCS UpWind Theoretical Solution	             //
	//-------------------------------------------------------------------//
	
	Implicit_FTCS IFTCS(5.0, 0.02, 400, 0.5, 250);
	vector<vector<double>> IFTCS_Theoretical = IFTCS.Theoretical_Sol();
	IFTCS.writeToFile("IFTCS_5_02");

	Implicit_FTCS IFTCS1(5.0, 0.01, 400, 0.5, 250);
	vector<vector<double>> IFTCS_Theoretica1 = IFTCS1.Theoretical_Sol();
	IFTCS1.writeToFile("IFTCS_5_01");

	Implicit_FTCS IFTCS2(5.0, 0.005, 400, 0.5, 250);
	vector<vector<double>> IFTCS_Theoretical2 = IFTCS2.Theoretical_Sol();
	IFTCS2.writeToFile("IFTCS_5_005");
	
	
	
	//-------------------------------------------------------------------//
	//				   Lax Wandroff Theoretical Solution	             //
	//-------------------------------------------------------------------//
	
	Lax_Wandroff Lax(5.0, 0.02, 400, 0.5, 250);
	vector<vector<double>> Lax_Theory = Lax.Theoretical_Sol();
	Lax.writeToFile("LAX_Wandroff_5_02");

	Lax_Wandroff Lax2(5.0, 0.01, 400, 0.5, 250);
	vector<vector<double>> Lax_Theory2 = Lax2.Theoretical_Sol();
	Lax2.writeToFile("LAX_Wandroff_5_01");

	Lax_Wandroff Lax3(5.0, 0.005, 400, 0.5, 250);
	vector<vector<double>> Lax_Theory3 = Lax3.Theoretical_Sol();
	Lax3.writeToFile("LAX_Wandroff_5_005");
	
	
	//-------------------------------------------------------------------//
	//				   Implicit Upwind Theoretical Solution	             //
	//-------------------------------------------------------------------//
	
	Implicit_Upwind IU(5.0, 0.02, 400, 0.5, 250);
	vector<vector<double>> IU_Theory = IU.Theoretical_Sol();
	IU.writeToFile("IU_5_02");

	Implicit_Upwind IU2(5.0, 0.01, 400, 0.5, 250);
	vector<vector<double>> IU_Theory2 = IU2.Theoretical_Sol();
	IU2.writeToFile("IU_5_01");

	Implicit_Upwind IU3(5.0, 0.005, 400, 0.5, 250);
	vector<vector<double>> IU_Theory3 = IU3.Theoretical_Sol();
	IU3.writeToFile("IU_5_005");
	
	
	return 0;
}