#include <iostream>
#include <random>
#include <ctime>

using namespace std;
int main() {
	const double p[4][2] = { {0.0,0.0},{0.0,1.0},{1.0,0.0},{1.0,1.0} };
	const double d[4] = { 0.0,1.0,1.0,0.0 };
	const double eta = 0.2;  //Wspó³czynnik uczenia
	const double E_max = 0.0003; //maksymalny b³¹d jaki chcemy osi¹gn¹æ
	const int c_max = 500000; // iloœæ kroków uczenia 
	//int many_of_layers = 3;

	//Warstwa wejœciowa
	double x1;
	double x2;

	//Warstwa ukryta
	double y1;
	double y2;

	//Wynik
	double z1;

	srand(time(NULL));
	// Losowanie wag pocz¹tkowych
	double v11 = ((double)rand() / RAND_MAX) * 2 - 1;// *4 - 2;
	double v21 = ((double)rand() / RAND_MAX) * 2 - 1;// *4 - 2;
	double v12 = ((double)rand() / RAND_MAX) * 2 - 1;// *4 - 2;
	double v22 = ((double)rand() / RAND_MAX) * 2 - 1;// *4 - 2;
	double v13 = ((double)rand() / RAND_MAX) * 2 - 1;// *4 - 2;
	double v23 = ((double)rand() / RAND_MAX) * 2 - 1;// *4 - 2;
	double w11 = ((double)rand() / RAND_MAX) * 2 - 1;// *4 - 2;
	double w12 = ((double)rand() / RAND_MAX) * 2 - 1;// *4 - 2;
	double w13 = ((double)rand() / RAND_MAX) * 2 - 1;// *4 - 2;

	double l, E;
	double net11, net12, net21;
	double deltaz1, deltay1, deltay2;

	//uczenie sieci neuronowej
	for (int c = 0; c < c_max; c++) {
		E = 0;
		for (int l = 0; l < 4; l++) {
			//int l = c % 4;
			x1 = p[l][0];
			x2 = p[l][1];
			net11 = x1 * v11 + x2 * v12 + -1.0 * v13;
			net12 = x1 * v21 + x2 * v22 + -1.0 * v23;
			y1 = 1.0 / (1.0 + exp(-net11));
			y2 = 1.0 / (1.0 + exp(-net12));

			net21 = y1 * w11 + y2 * w12 + -1.0 * w13;
			z1 = 1.0 / (1.0 + exp(-net21));

			deltaz1 = (d[l] - z1) * z1 * (1.0 - z1);
			deltay1 = deltaz1 * w11 * (y1 * (1.0 - y1));
			deltay2 = deltaz1 * w12 * (y2 * (1.0 - y2));

			v11 = v11 + eta * deltay1 * x1;
			v21 = v21 + eta * deltay2 * x1;
			v12 = v12 + eta * deltay1 * x2;
			v22 = v22 + eta * deltay2 * x2;
			v13 = v13 - eta * deltay1;
			v23 = v23 - eta * deltay2;
			w11 = w11 + eta * deltaz1 * y1;
			w12 = w12 + eta * deltaz1 * y2;
			w13 = w13 - eta * deltaz1;

			E = E + ((pow(d[l] - z1, 2)) / 2.0);
		}
		//		cout << c << ". " << e << "\n";
		if (E < E_max)break;
	}

	//Testowanie sieci neuronowej
	for (int i = 0; i < 4; i++) {
		x1 = p[i][0];
		x2 = p[i][1];

		net11 = x1 * v11 + x2 * v12 + -1.0 * v13;
		net12 = x1 * v21 + x2 * v22 + -1.0 * v23;
		y1 = 1.0 / (1.0 + exp(-net11));
		y2 = 1.0 / (1.0 + exp(-net12));

		net21 = y1 * w11 + y2 * w12 + -1.0 * w13;
		z1 = 1.0 / (1.0 + exp(-net21));

		cout << x1 << " XOR " << x2 << " = " << z1 << "\n";
	}
	return 0;
}
