#include <iostream>
#include "Matrix.h"
using namespace std;


int main()
{
	const int n = 8;//tavani az 2
	Matrix a(n, true,5);
	Matrix b(n, true,5);

	cout <<"A:\n"<< a << "\nB:\n" << b;

	//Test Adding Matrix
	cout << "\nA+B=\n" << a + b;
	cout << "\nA-B=\n" << a - b;

	//Test Multiply Matrix
	cout << "\nA*B=   (Standard way)\n" << a * b;


	cout << "\nA*B=   (Straseen way)\n" << Matrix::strassen(a,b);

	cin.ignore();
	cin.get();
	return 0;
}