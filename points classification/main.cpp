#include <iostream>
#include <cmath>
#include <random>
#include <time.h>
#include <windows.h>
#include <cstdlib>

using namespace std;

HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

enum color {
	red = 12,
	blue = 9,
	navy_blue = 1,
	green = 10,
	yellow = 14
};

int f_progowa(double x);
int f_liniowa(double x);
int f_sigmoidalna(double x);

int main() {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 2;
	cfi.dwFontSize.Y = 2;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	double W[5] = { 0.0 }; //wagi po³¹czeñ
	srand(time(NULL));
	double x[3];
	for (int l = 0; l < 2; l++) {

		for (double N = 0.0; N < 2; N++) {

			for (int i = 0; i < 5; ++i)
			{
				W[i] = double(rand()) / RAND_MAX * 10.0 - 5;
			}

			for (int f = 0; f < 3; f++) {

				for (double a = -5; a <= 5; a += 0.1) {
					for (double b = -5; b <= 5; b += 0.1) {
						x[0] = N;
						x[1] = a;
						x[2] = b;

						double suma = (double)x[1] * W[1] + x[2] * W[2] + x[0] * W[0];
						if (l == 1) {
							if (f == 2) {
								suma = (1.0 / (1.0 + exp(-suma))) * W[3] + x[0] * W[4];
							}
							else {
								suma *= W[3] + x[0] * W[4];
							}
						}
						int result;
						switch (f) {
						case 0: result = f_progowa(suma); break;
						case 1: result = f_liniowa(suma); break;
						case 2: result = f_sigmoidalna(suma); break;
						}

						if ((a > -0.01 && a < 0.01) || (b > -0.01 && b < 0.01)) {
							SetConsoleTextAttribute(hOut, 15);
							cout << (char)219;
						}
						else {
							SetConsoleTextAttribute(hOut, result);
							cout << (char)219;
						}

					}
					cout << endl;
				}
				cout << endl << endl << endl;
			}
		}
	}
	return 0;
}

int f_progowa(double x) {

	if (x >= 0) {
		return red;
	}
	else {
		return blue;
	}
}
int f_liniowa(double x) {

	if (x < -2) {
		return navy_blue;
	}
	else if (x <= 2) {
		return green;
	}
	else {
		return red;
	}
}

int f_sigmoidalna(double x) {

	double temp = 1.0 / (1.0 + exp(-x));

	if (temp >= 0 && temp < 0.25) {
		return yellow;
	}
	else if (temp >= 0.25 && temp < 0.5) {
		return blue;
	}
	else if (temp >= 0.5 && temp < 0.75) {
		return green;
	}
	else if (temp >= 0.75 && temp <= 1) {
		return red;
	}
}
