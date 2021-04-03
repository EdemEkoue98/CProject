#include <iostream>
#include <cmath>
#include "CRR_model.h"
#include "EuropeanOptions.h"
#include "MonteCarloMethod.h"
#include"BlackScholes_model.h"
#include "Options.h"
#include "AmericanOptions.h"
#include "EuropeanDigitalOptions.h"
#include "Binlattice.h"



int main()
{   // The option and the parameters which we will use 
	// can directly change it on a put or a call to verify the difference 

	double So = 100, K = 101, T = 10, r = 0.01, sigma = 0.3;

	double u = 0.05;		// Up
	double d = -0.04762;	// Down

	// Instanciates options
	EuropeanOptions euroCall = EuropeanOptions(Options::options::call, K, T, So);// price = 11,05
	AsianOptions Asiancall = AsianOptions(Options::options::call, K, T, So);
	EuropeanOptions euroPut = EuropeanOptions(Options::options::put, K, T, So); // price = 11,05
	EuropeanDigitalOptions euroDigiCall = EuropeanDigitalOptions(Options::options::call, K, T, So);
	EuropeanDigitalOptions euroDigiPut = EuropeanDigitalOptions(Options::options::put, K, T, So);
	AmericanOptions americaCall = AmericanOptions(Options::options::call, K, T, So); // price = 11,05 because we have the s
	AmericanOptions americaPut = AmericanOptions(Options::options::put, K, T, So); // price = 11,05 because we have the s

	//// displays the options payoff
	std::cout << euroCall.payoff() << endl;
	std::cout << euroPut.payoff() << endl;
	std::cout << euroDigiCall.payoff() << endl;
	std::cout << euroDigiPut.payoff() << endl;
	std::cout << americaCall.payoff() << endl;
	std::cout << americaPut.payoff() << endl;

	//// displays about black-scholes methods 

	//
	BlackScholes Bs = BlackScholes(sigma, r, K); // creation of a blaxk scholes model 
	Bs.Pricing(euroCall); // Pricing of a european call

	//// creates a model crr with his parameters 
	CRR crr = CRR(sigma, r, 10);

	//// displays about the crr model 
	std::cout << crr.pricing_crr_European(euroCall, u, d) << endl;
	std::cout << crr.pricing_crr_European(euroPut, u, d) << endl;
	std::cout << crr.pricing_crr_American(americaCall, u, d) << endl;
	std::cout << crr.pricing_crr_American(americaPut, u, d) << endl;

	//// displays about the closedform model 
	std::cout << crr.closedform_European(euroCall, u, d) << endl;   // for applying the closedform model  
	std::cout << crr.closedform_European(euroPut, u, d) << endl;

	//// displays about the BlackSholes closed form model
	std::cout << crr.approximation_Blackscholes_Closed_form_European(euroCall) << endl;
	std::cout << crr.approximation_Blackscholes_Closed_form_European(euroPut) << endl;

	//// displays about the BlackSholes binomial tree model
	std::cout << crr.approximation_blackscholes_Binomial_tree_European(euroCall) << endl;
	std::cout << crr.approximation_blackscholes_Binomial_tree_European(euroPut) << endl;

	MonteCarlo monte = MonteCarlo(sigma, r, 10);

	/*cout << monte.GaussianLaw() << endl;*/ 
	/*cout << monte.MonteCarloPricer_exotic(euroCall) << endl;*/
	for (int i = 0; i < 10; i++)
	{
		cout << monte.Simulation_Monte(Asiancall, 1000) << endl; // even the average is not constant so i print it 
		// ten times to see if the numbers are close
		   /* 23.8668  // i obtain theses numbers and we remark that the price is between 23 and 25
			23.424
			24.0946
			23.8837
			23.5142
			23.3018
			23.8048
			23.4511
			23.1209
			23.1105*/
	}
	//BinLattice<CRR> test();

}