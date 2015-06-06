#pragma once
#define STRASSEN_PARAMS 8


#include <time.h>
#include <ostream>
#include <iomanip>

class Matrix
{
	friend std::ostream & operator <<(std::ostream& os, Matrix lst);


private:
	int ** a;
	int length;
	Matrix() // empty cunstructor for strassen , only in class
	{

	}

	void copySmallerMatrix(Matrix b , int startI , int startJ)
	{
		int n = b.length;
		for (int x = startI, i = 0; i < n; i++, x++)
			for (int y = startJ , j = 0; j < n; j++, y++)
				a[x][y] = b.a[i][j];
	}
public:

	Matrix(int n, bool random = false , int maxRandom = 20)
	{
		length = n;
		a = new int *[length];
		for (int i = 0; i < length; i++)
			a[i] = new int[length];

		if (random)
			for (int i = 0; i < length; i++)
				for (int j = 0; j < length; j++)
				{
					srand(time(0) + (i + j * 15) + rand() % 50);
					a[i][j] = rand() % maxRandom ;
				}// for j
	}//Matrix

	Matrix(int n, Matrix input , int startI = 0  ,int startJ = 0)
	{
		length = n;
		a = new int *[length];
		for (int i = 0; i < length; i++)
			a[i] = new int[length];


		for (int inputI = startI , i = 0; i < length; i++,inputI++)
			for (int inputJ = startJ , j = 0; j < length; j++,inputJ++)
				a[i][j] = input.a[inputI][inputJ];
	}

	Matrix operator+ (Matrix mat2)
	{
		Matrix temp(length<mat2.length ? length : mat2.length);
		for (int i = 0; i < length; i++)
			for (int j = 0; j < length; j++)
				temp.a[i][j] = a[i][j] + mat2.a[i][j];

		return temp;
	}

	Matrix operator- (Matrix mat2)
	{
		Matrix temp(length<mat2.length ? length : mat2.length);
		for (int i = 0; i < length; i++)
		for (int j = 0; j < length; j++)
			temp.a[i][j] = a[i][j] - mat2.a[i][j];

		return temp;
	}

	Matrix operator* (Matrix mat2)
	{
		Matrix temp(length<mat2.length ? length : mat2.length);
		for (int i = 0; i < length; i++)
			for (int j = 0; j < length; j++)
			{
				temp.a[i][j] = 0;
				for (int k = 0; k < length; k++)
					temp.a[i][j] += (a[i][k] * mat2.a[k][j]);
			}
				
			

		return temp;
	}

	void operator=(const Matrix &b)
	{
		length = b.length;
		a = new int *[length];
		for (int i = 0; i < length; i++)
			a[i] = new int[length];
		for (int i = 0; i < length; i++)
			for (int j = 0; j < length; j++)
				a[i][j] = b.a[i][j];

	}

	static Matrix strassen(Matrix mat1 , Matrix mat2)
	{
		int n = mat1.length;
		if (n <= 2)
			return mat1*mat2;

		Matrix A11(n / 2, mat1, 0 , 0);
		Matrix A21(n / 2, mat1, n/2 , 0);
		Matrix A12(n / 2, mat1, 0, n / 2);
		Matrix A22(n / 2, mat1, n/2, n / 2);


		//For Debug only
		//std::cout << "\nA11:\n" << A11;
		//std::cout << "\nA12:\n" << A12;
		//std::cout << "\nA21:\n" << A21;
		//std::cout << "\nA22:\n" << A22;

		Matrix B11(n / 2, mat2, 0, 0);
		Matrix B21(n / 2, mat2, n / 2, 0);
		Matrix B12(n / 2, mat2, 0, n / 2);
		Matrix B22(n / 2, mat2, n / 2, n / 2);

		Matrix M[STRASSEN_PARAMS];//khoone 0 bedoone estefade

		M[1] = strassen((A11 + A22), (B11 + B22));
		M[2] = strassen( (A21 + A22) , B11);
		M[3] = strassen( A11, (B12-B22) );
		M[4] = strassen( A22 , (B21-B11));
		M[5] = strassen((A11+A12),B22 );
		M[6] = strassen((A21 - A11), (B11 + B12));
		M[7] = strassen((A12 - A22), (B21 + B22));

		Matrix temp1 = M[1] + M[4] - M[5] + M[7];
		Matrix temp2 = M[3] + M[5];
		Matrix temp3 = M[2] + M[4];
		Matrix temp4 = M[1] + M[3] - M[2] + M[6];

		//For Debug only
		//std::cout << "\nTemp1:\n" << temp1;
		//std::cout << "\nTemp2:\n" << temp2;
		//std::cout << "\nTemp3:\n" << temp3;
		//std::cout << "\nTemp4:\n" << temp4;

		Matrix result(n);
		result.copySmallerMatrix(temp1,0,0);
		result.copySmallerMatrix(temp2, 0, n/2);
		result.copySmallerMatrix(temp3, n/2, 0);
		result.copySmallerMatrix(temp4, n/2, n/2);

		return result;

	}

};

std::ostream & operator <<(std::ostream& os, Matrix lst)
{
	for (int i = 0; i < lst.length; i++)
	{
		for (int j = 0; j < lst.length; j++)
		{
			os << std::setw(4) << std::left << lst.a[i][j];
		}
		os << "\n";
	}

	return os;
}