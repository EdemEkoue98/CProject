#pragma once
#pragma once
#include <iostream>
#define _USE_MATH_DEFINES
# include<list>
#include <cmath>
#include <vector>

template<typename Type> class BinLattice
{

private:
	int N;
	vector<vector<Type>> Lattice;

public :
	BinLattice() {}

	void SetN(int N)
	{
		this->N = N;
		Lattice.resize(N + 1);
		for (int n = 0; n <= N; n++)
			Lattice[n].resize(n + 1);
	}

	void SetNode(int n, int i, double x)
	{
		Lattice[n][i] = x;
	}

	Type GetNode(int n, int i) const
	{
		return Lattice[n][i];
	}

	void BinDisplay() const
	{
		for (int n = 0; n <= N; n++)
		{
			for (int i = 0; i <= n; i++)
				cout << GetNode(n, i) << " ";
		}
		cout << endl;
	}
};


