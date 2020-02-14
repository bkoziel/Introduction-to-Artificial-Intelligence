#include <iostream>

using namespace std;

int main() {
	const int l_liter = 4;
	const int l_znakow = 35;
	double P[l_liter][l_znakow] = {
		//A
	{-1,1, 1, 1,-1,
	 1,-1,-1,-1, 1,
	 1,-1,-1,-1, 1,
	 1, 1, 1, 1, 1,
	 1,-1,-1,-1, 1,
	 1,-1,-1,-1, 1,
	 1,-1,-1,-1, 1},
	 //C
 {-1, 1, 1, 1, 1,
  1,-1,-1,-1,-1,
  1,-1,-1,-1,-1,
  1,-1,-1,-1,-1,
  1,-1,-1,-1,-1,
  1,-1,-1,-1,-1,
  -1, 1, 1, 1, 1},
  //X
{1,-1,-1,-1, 1,
 1,-1,-1,-1, 1,
-1, 1,-1, 1,-1,
-1,-1, 1,-1,-1,
-1, 1,-1, 1,-1,
 1,-1,-1,-1, 1,
 1,-1,-1,-1, 1},
 //I
{-1, 1, 1, 1,-1,
 -1,-1, 1,-1,-1,
 -1,-1, 1,-1,-1,
 -1,-1, 1,-1,-1,
 -1,-1, 1,-1,-1,
 -1,-1, 1,-1,-1,
 -1, 1, 1, 1,-1} };

	//Znak testowy
	double test[8][l_znakow] = {
		{
		1, 1, 1, 1, 1, // A
		1, -1, -1, -1, 1,
		1, -1, -1, -1, 1,
		1, 1, 1, 1, 1,
		1, -1, -1, -1, 1,
		1, -1, -1, -1, 1,
		1, 1, -1, 1, 1},

	{1, 1, 1, 1, 1,
  -1,-1,1,-1,-1,
  -1,-1,1,-1,-1,
  -1,-1,1,-1,-1,
  -1,-1,1,-1,-1,
  -1,-1,1,-1,-1,
  1, 1, 1, 1, 1},

	{1, 1, 1, 1, 1,
  1,-1,-1,-1,1,
  1,-1,-1,-1,1,
  1,-1,-1,-1,-1,
  1,-1,-1,-1,1,
  1,-1,-1,-1,1,
  1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1,
  1,-1,-1,-1,1,
  1,-1,-1,-1,1,
  1,-1,-1,-1,1,
  1,-1,-1,-1,1,
  1,-1,-1,-1,1,
  1, 1, 1, 1, 1},
		{
		-1, 1, 1, 1, 1, //
		1, -1, 1, -1, 1,
		1, -1, 1, -1, 1,
		1, 1, 1, 1, 1,
		1, -1, -1, -1, 1,
		1, -1, -1, -1, 1,
		1, 1, -1, 1, 1},

	{1, 1, 1, 1, 1,
  1,-1,-1,-1,1,
  1,-1,-1,-1,1,
  1,1,1,1,1,
  1,-1,-1,-1,1,
  1,-1,-1,-1,1,
  1, 1, 1, 1, 1},

	{1, 1, 1, 1, 1,
  -1,1,-1,-1,1,
  -1,-1,1,-1,1,
  -1,-1,1,-1,-1,
  -1,-1,-1,1,1,
  -1,-1,-1,-1,1,
  1, -1, -1, -1, 1},
   {1, 1, 1, 1, 1,
  1,1,1,1,1,
  1,1,1,1,1,
  1,1,1,1,1,
  1,1,1,1,1,
  1,1,1,1,1,
  1, 1, 1, 1, 1},
	};
	//Wyswietlenie znaków	
	for (int k = 0; k < l_liter; k++) {
		for (int i = 0; i < l_znakow; i++) {

			if (P[k][i] == 1) {
				cout << (char)219;
			}
			else {
				cout << (char)176;
			}
			if (i % 5 == 4)
				cout << endl;
		}
		cout << endl;
	}



	//Obliczanie wag
	double w[l_znakow][l_znakow] = { 0 };
	int delta;
	double sum;
	for (int i = 0; i < l_znakow; i++) {
		for (int j = 0; j < l_znakow; j++) {
			if (i == j)
			{
				delta = 1;
			}
			else
			{
				delta = 0;
			}
			sum = 0;
			for (int k = 0; k < l_liter; k++) {
				sum += P[k][i] * P[k][j];
			}

			w[i][j] = (1.0 - delta) * sum;
		}
	}
	/*
	for (int i = 0; i < 35; i++) {
		for (int j = 0; j < 35; j++) {

			cout << w[i][j] << " ";
		}
		cout << endl;
	}
	*/
	cout << endl << "Test" << endl;

	double y[l_znakow];
	double s[l_znakow];

	bool stability = false;

	for (int k = 0; k < 8; k++) {

		cout << "\nWczytano: \n";
		for (int i = 0; i < l_znakow; i++) {

			if (test[k][i] == 1) {
				cout << (char)219;
			}
			else {
				cout << (char)176;
			}

			if (i % 5 == 4)
				cout << endl;
		}
		cout << "Odczytano: \n";
		for (int i = 0; i < l_znakow; i++)
		{
			s[i] = test[k][i];
		}
		stability = false;
		while (!stability) {
			double net[l_znakow] = { 0 };
			for (int i = 0; i < l_znakow; i++) {
				for (int j = 0; j < l_znakow; j++) {
					net[i] += w[i][j] * s[j];
				}
			}
			for (int i = 0; i < l_znakow; i++) {

				if (net[i] > 0) {
					y[i] = 1;
				}
				else if (net[i] == 0) {
					y[i] = s[i];
				}
				else {
					y[i] = -1;
				}
			}
			stability = true;
			for (int i = 0; i < l_znakow; i++) {
				if (y[i] != s[i]) {
					s[i] = y[i];
					stability = false;
				}
			}
			if (!stability) {
				for (int i = 0; i < l_znakow; i++) {
					if (s[i] == 1)
					{
						cout << (char)219;
					}
					else
					{
						cout << (char)176;
					}
					if (i % 5 == 4)
						cout << endl;
				}
				cout << endl;
			}
		}
	}
	return 0;
}