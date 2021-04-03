#include "CRR_model.h" 

#include <vector>// STL vector templates
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>// standard mathematical library
#include <math.h>
# include <algorithm>
#include "EuropeanOptions.h"
using namespace std;


CRR::CRR(double sigma, double interest, int p)
{
	volatility = sigma;
	interest_rate = interest;
	number_of_iteration = p;
}

double CRR::pricing_crr_European(EuropeanOptions opta, double u, double d)
{
	int n = this->number_of_iteration;
	double K = opta.strike;
	double T = opta.maturity;
	double S = opta.underlying_price;
	double sigma = this->volatility;
	double R = this->interest_rate;
	double alpha = (double)(1 /(double) (1 + R));
	double q = (double)  (R - d) / (double) (u - d);
	double p = (double) 1 - q;
	double U = (double) 1 + u; // U = 1+u 
	double D = (double) (1+d);

	vector<vector<double>> Stocks(n + 1, vector<double>(n + 1, 0));
	vector<vector<double>> Payoffs(n + 1, vector<double>(n + 1, 0));

	// COMPUTE THE STOCKS 
	for (int j = 0; j <= n; j++)
	{
		for (int i = 0; i <= j; i++)
		{
			Stocks[i][j] = S * pow(U,j-i) * pow(D,i);

			/*cout << Stocks[i][j] <<" | " ;*/
		}
		/*cout << "      " << endl;*/
	}

	for (int i = 0; i <= n; i++) // a view on the stocks at node n
	{
		/*cout << Stocks[i][n]<<endl;
		cout << "----------"<<endl;
		cout << " ";*/
	}
	if (opta.verification() == 0) // i.e it is a call option 
	{
		cout << " the option priced here is a call option " << endl;
		for (int j = 0; j <= n; j++)
		{
			/*payoffs of the last node n*/

			Payoffs[j][n] = max(Stocks[j][n] - K, 0.0);

			/*cout << Payoffs[i][n];

			cout << "   " ; */
		}
	}
	if (opta.verification() == 1)
	{
		cout << " the option priced here is a Put option " << endl;
		for (int j = 0; j <= n; j++)
		{
			/*payoffs of the last node n*/

			Payoffs[j][n] = max(-Stocks[j][n] +K, 0.0); // the payoff calculation change 

			/*cout << Payoffs[i][n];

			cout << "   " ; */
		}
	}
	for (int j = n - 1; j >= 0; j--)
	{
		for (int i = 0; i <= j; i++)
		{
			Payoffs[i][j] = (q * Payoffs[i][j+1] + p * Payoffs[i+1][j+1]) * alpha;

			cout << Payoffs[i][j]<<" | ";
		}
		cout << "      " <<endl;
	}

	return Payoffs[0][0];
}

double CRR::closedform_European(EuropeanOptions opta, double u, double d)
{
	int n = this->number_of_iteration;
	double K = opta.strike;
	double T = opta.maturity;
	double S = opta.underlying_price;
	double sigma = this->volatility;
	double R = this->interest_rate;
	double alpha = (double)(1 / (double)(1 + R));
	double q = (double)(R - d) / (double)(u - d);
	double p = (double)(1 - q);
	double U = (double)(1 + u); // U = 1+u 
	double D = (double)(1 + d);

	vector<vector<double>> Stocks(n + 1, vector<double>(n + 1, 0));
	vector<vector<double>> Payoffs(n + 1, vector<double>(n + 1, 0));

	// COMPUTE THE STOCKS 
	for (int j = 0; j <= n; j++)
	{
		for (int i = 0; i <= j; i++)
		{
			Stocks[i][j] = S * pow(U,j-i) * pow(D, i);

			/*cout << Stocks[i][j] << " | ";*/
		}
		/*cout << "      " << endl;*/
	}

	double resultat = 0;
	if (opta.verification() == 0)
	{
		for (int k = 0; k <= n; k++)
		{
			double a = (double)(factorielle(n) / (double)(factorielle(k) * factorielle((double)((double)n - (double)k))));
			double payf = (pow(q, n - k) * pow(p, k)) * (max(Stocks[k][n] - K, 0.0));

			/*cout << payf << endl;*/

			resultat += a * payf;

			/*cout << resultat << endl;*/

		}
	}
	if (opta.verification() == 1) // we price here a put option 
	{
		for (int k = 0; k <= n; k++)
		{
			double a = (double)(factorielle(n) / (double)(factorielle(k) * factorielle((double)((double)n - (double)k))));
			double payf = (pow(q, n - k) * pow(p, k)) * (max(-Stocks[k][n] +K, 0.0));

			/*cout << payf << endl;*/

			resultat += a * payf;

			/*cout << resultat << endl;*/

		} // the payoff is not the same 
	}
	return (double)(resultat)*pow(alpha,n);

}

double CRR::approximation_blackscholes_Binomial_tree_European(EuropeanOptions opta)
{
	int n = this->number_of_iteration;
	double K = opta.strike;
	double T = opta.maturity;
	double S = opta.underlying_price;
	double sigma = this->volatility;
	double r = this->interest_rate;

	double h = (double)(T/n);
	cout <<" h = "<< h << endl;
	double U = (double)(exp((r + (pow(sigma, 2) / 2)) * h + sigma * pow(h,0.5)) );
	cout <<" U = "<< U << endl;
	double D = (double)(exp((r + (pow(sigma, 2) / 2)) * h - sigma * pow(h,0.5)));
	cout << " D = " << D << endl;
	double R = exp(r * h);
	/*cout << " R = " << R << endl;*/
	double alpha = (double)(1 /R);
	double q = (double)(R - D) / (double)(U - D);
	/*cout << " q = " << q << endl;*/
	double p = (double)1 - q;

	vector<vector<double>> Stocks(n + 1, vector<double>(n + 1, 0));
	vector<vector<double>> Payoffs(n + 1, vector<double>(n + 1, 0));

	// COMPUTE THE STOCKS 
	for (int j = 0; j <= n; j++)
	{
		for (int i = 0; i <= j; i++)
		{
			Stocks[i][j] = S * pow(U, j - i) * pow(D, i);

			/*cout << Stocks[i][j] <<" | " ;*/
		}
		/*cout << "      " << endl;*/
	}

	for (int i = 0; i <= n; i++) // a view on the stocks at node n
	{
		/*cout << Stocks[i][n]<<endl;
		cout << "----------"<<endl;
		cout << " ";*/
	}
	if (opta.verification() == 0) // i.e it is a call option 
	{
		cout << " the option priced here is a call option " << endl;
		for (int j = 0; j <= n; j++)
		{
			/*payoffs of the last node n*/

			Payoffs[j][n] = max(Stocks[j][n] - K, 0.0);

			/*cout << Payoffs[i][n];

			cout << "   " ; */
		}
	}
	if (opta.verification() == 1)
	{
		cout << " the option priced here is a Put option " << endl;
		for (int j = 0; j <= n; j++)
		{
			/*payoffs of the last node n*/

			Payoffs[j][n] = max(-Stocks[j][n] + K, 0.0); // the payoff calculation change 

			/*cout << Payoffs[i][n];

			cout << "   " ; */
		}
	}
	for (int j = n - 1; j >= 0; j--)
	{
		for (int i = 0; i <= j; i++)
		{
			Payoffs[i][j] = (q * Payoffs[i][j + 1] + p * Payoffs[i + 1][j + 1]) * alpha;

			/*cout << Payoffs[i][j] << " | ";*/
		}
		/*cout << "      " << endl;*/
	}

	return Payoffs[0][0];
	

}

double CRR::approximation_Blackscholes_Closed_form_European(EuropeanOptions opta)
{
	int n = this->number_of_iteration;
	double K = opta.strike;
	double T = opta.maturity;
	double S = opta.underlying_price;
	double sigma = this->volatility;
	double r = this->interest_rate;

	double h = (double)(T / n);
	cout << " h = " << h << endl;
	double U = (double)(exp((r + (pow(sigma, 2) / 2)) * h + sigma * pow(h, 0.5)));
	cout << " U = " << U << endl;
	double D = (double)(exp((r + (pow(sigma, 2) / 2)) * h - sigma * pow(h, 0.5)));
	cout << " D = " << D << endl;
	double R = exp(r * h);
	/*cout << " R = " << R << endl;*/
	double alpha = (double)(1 / R);
	double q = (double)(R - D) / (double)(U - D);
	/*cout << " q = " << q << endl;*/
	double p = (double)1 - q;

	vector<vector<double>> Stocks(n + 1, vector<double>(n + 1, 0));
	vector<vector<double>> Payoffs(n + 1, vector<double>(n + 1, 0));
	
	for (int j = 0; j <= n; j++)
	{
		for (int i = 0; i <= j; i++)
		{
			Stocks[i][j] = S * pow(U, j - i) * pow(D, i);

			/*cout << Stocks[i][j] << " | ";*/
		}
		/*cout << "      " << endl;*/
	}

	double resultat = 0;
	if (opta.verification() == 0)
	{
		for (int k = 0; k <= n; k++)
		{
			double a = (double)(factorielle(n) / (double)(factorielle(k) * factorielle((double)((double)n - (double)k))));
			double payf = (pow(q, n - k) * pow(p, k)) * (max(Stocks[k][n] - K, 0.0));

			/*cout << payf << endl;*/

			resultat += a * payf;

			/*cout << resultat << endl;*/

		}
	}
	if (opta.verification() == 1) // we price here a put option 
	{
		for (int k = 0; k <= n; k++)
		{
			double a = (double)(factorielle(n) / (double)(factorielle(k) * factorielle((double)((double)n - (double)k))));
			double payf = (pow(q, n - k) * pow(p, k)) * (max(-Stocks[k][n] + K, 0.0));

			/*cout << payf << endl;*/

			resultat += a * payf;

			/*cout << resultat << endl;*/

		} // the payoff is not the same 
	}
	
	return (double)(resultat)*pow(alpha, n);


}


double payoff()
{
	return 1;
}


double CRR::pricing_crr_American(AmericanOptions opta, double u, double d)
{
	// parameters of the methods
	int n = this->number_of_iteration;
	double K = opta.strike;
	double T = opta.maturity;
	double S = opta.underlying_price;
	double sigma = this->volatility;
	double R = this->interest_rate;
	double alpha = (double)(1 / (double)(1 + R));
	double q = (double)(R - d) / (double)(u - d);
	double p = (double)1 - q;
	double U = (double)1 + u; // U = 1+u 
	double D = (double)(1 + d);
	vector<vector<double>> Stocks(n + 1, vector<double>(n + 1, 0));
	vector<vector<double>> Payoffs(n + 1, vector<double>(n + 1, 0));

	// COMPUTE THE STOCKS the S[I][J]
	for (int j = 0; j <= n; j++)
	{
		for (int i = 0; i <= j; i++)
		{
			Stocks[i][j] = S * pow(U, j - i) * pow(D, i);

			/*cout << Stocks[i][j] <<" | " ;*/
		}
		/*cout << "      " << endl;*/
	}

	//for (int i = 0; i <= n; i++) // a view on the stocks at node n
	//{
	//	/*cout << Stocks[i][n]<<endl;
	//	cout << "----------"<<endl;
	//	cout << " ";*/
	//}
	if (opta.verificationA() == 0) // i.e if it is a call option 
	{
		cout << " the option priced here is a call option " << endl;
		for (int j = 0; j <= n; j++)
		{
			/*payoffs of the last node n*/

			Payoffs[j][n] = max(Stocks[j][n] - K, 0.0);

			/*cout << Payoffs[j][n];

			cout << "   " ; */
		}
	}
	if (opta.verificationA() == 1)
	{
		cout << " the option priced here is a Put option " << endl;
		for (int j = 0; j <= n; j++)
		{
			/*payoffs of the last node n*/

			Payoffs[j][n] = max(-Stocks[j][n] + K, 0.0); // the payoff calculation change 

			/*cout << Payoffs[j][n];

			cout << "   " ; */
		}
	}
	for (int j = n - 1; j >= 0; j--)
	{
		for (int i = 0; i <= j; i++)
		{
			
			Payoffs[i][j] = max((q * Payoffs[i][j + 1] + p * Payoffs[i + 1][j + 1]) * alpha,Payoffs[i][j]);

			cout << Payoffs[i][j] << " | ";
		}
		cout << "      " << endl;
	}

	return Payoffs[0][0];
}


double CRR::factorielle(double p)
{
	double res = 1;

	if (p == 0)
	{
		return res;
	}
	else
	{
		return p * factorielle(p - 1);
	}


}
