/*
 * test.cpp
 *
 *  Created on: 25.11.2015
 *      Author: Lukas
 */


#include <iostream>
#include <windows.h>

#include "../Numeric/basic/matrix.hpp"
#include "../Numeric/basic/vector.hpp"
#include "../Numeric/basic/scalar.hpp"


#include "../Numeric/util/RingBuffer.hpp"


#include "../Numeric/Regression/polynomialRegression.hpp"
#include "../Numeric/Regression/exponentialRegression.hpp"

int a[3][3] = {{1,2,3},{0,4,7},{0,0,3}};

int b[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};




int main (void)
{

//	for(int j = 3; j < 25; j++)
//	{
//		double x[j];
//		double y[j];
//
//		for(int i = 0; i < j; i++)
//		{
//			x[i] = i;
//			y[i] = i*i;
//		}
//		PolynomialRegression_t<double,2,30> poly(x,y,j);
//		for(double i = -10; i < 10; i+=0.1)
//		{
//			std::cout << i << "\t" << poly.getY(i) << std::endl;
//		}
//	}

	double x[20];
	double y[20];
	for(int i = 0; i < 20; i++)
	{
		x[i] = i;
		y[i] = 0.3*std::exp(-0.03*i);
	}



	ExponentialRegression_t<double,30> expo(x,y);


	for(double i = -10; i < 10; i+=0.1)
	{
		std::cout << i << "\t" << expo.getY(i) << std::endl;
	}




}
