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
#include "../Numeric/Spline/Spline.hpp"

int a[3][3] = {{1,2,3},{0,4,7},{0,0,3}};

int b[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};


#include <random>

int main (void)
{

////	for(int j = 3; j < 25; j++)
////	{
////		double x[j];
////		double y[j];
////
////		for(int i = 0; i < j; i++)
////		{
////			x[i] = i;
////			y[i] = i*i;
////		}
////		PolynomialRegression_t<double,2,30> poly(x,y,j);
////		for(double i = -10; i < 10; i+=0.1)
////		{
////			std::cout << i << "\t" << poly.getY(i) << std::endl;
////		}
////	}
//
//    std::random_device rd;
//    std::mt19937 gen(rd());
//	std::normal_distribution<> d(0,0.1);
//	double x[20];
//	double y[20];
//	for(int i = 0; i < 20; i++)
//	{
//		x[i] = i;
//		y[i] = 1+0.3*(1 - std::exp(-0.03*i));//+d(gen);//(((rand()*1.0)/RAND_MAX)-0.5)*0.2;
//		std::cout << i << "\t" << y[i] << std::endl;
//	}
//
//
//
//
//
//	ExponentialRegression_t<double,30> expo(x,y);
//	PolynomialRegression_t<double,19,30> poly(x,y);
////	ExponentialSpecialRegression_t<double,30> expSpec(x,y);
//
//	std::cout << expo << std::endl;
//	std::cout << poly << std::endl;
////	for(double i = -10; i < 20; i+=0.5)
////	{
////		std::cout << i << "\t" << expo.getY(i) << std::endl;
////	}
//
//

	double x[10];
	double y[10];

	for(int i = 0; i < 10; i++)
	{
		x[i] = i;
		y[i] = 2+3*i+i*i;
	}
	Spline_t<double,20> spline(x,y);
	for(double i = 0; i < 10; i+=0.2)
	{
		std::cout << i << "\t" << spline.getY(i) << std::endl;
	}

}
