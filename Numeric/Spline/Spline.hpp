/*
 * Spline.hpp
 *
 *  Created on: 16. Dez. 2015
 *      Author: Lukas
 */

#ifndef MATH_NUMERIC_SPLINE_SPLINE_HPP_
#define MATH_NUMERIC_SPLINE_SPLINE_HPP_

#include "../basic/vector.hpp"

template<typename T, uint32_t maxNumSamples>
class Spline_t
{
private:
	ColumnVector_t<T, maxNumSamples> a_;
	ColumnVector_t<T, maxNumSamples> x_;

	ColumnVector_t<T, maxNumSamples - 1> h_;

	ColumnVector_t<T, maxNumSamples> b_;
	ColumnVector_t<T, maxNumSamples> c_;
	ColumnVector_t<T, maxNumSamples> d_;

	void update ()
	{
		Matrix_t<T,maxNumSamples,maxNumSamples> A;
		A.resize(a_.getN(),a_.getN());
		ColumnVector_t<T,maxNumSamples> bI;
		bI.resize(a_.getN(),1);
		for(uint32_t i = 0; i < a_.getN(); i++)
		{
			for(uint32_t j = 0; j < a_.getN(); j++)
			{

				if(i == 0)
					if(i == j)
						A[i][j] = 1;
					else
						A[i][j] = 0;
				else if(i == a_.getN()-1)
					if(i == j)
						A[i][j] = 1;
					else
						A[i][j] = 0;
				else if(j==i-1)
					A[i][j] = h_[i-1];
				else if(j == i+1)
					A[i][j] = h_[i];
				else if(j == i)
					A[i][j] = 2*(h_[i-1]+h_[i]);
				else
					A[i][j] = 0;
			}
			if(i == 0)
				bI[i] = 0;
			else if(i == a_.getN()-1)
				bI[i] = 0;
			else
				bI[i] = 3*((a_[i+1]-a_[i]) / h_[i] - (a_[i]-a_[i-1]) / h_[i-1]);
		}

		c_ = (A.transpose()*A).inverse()*A.transpose()*bI;
		b_.resize(a_.getN()-1,1);
		d_.resize(a_.getN()-1,1);
		for(uint32_t i = 0; i < a_.getN()-1; i++)
		{
			b_[i] = (a_[i+1]-a_[i])/h_[i] - h_[i]*(2*c_[i]+c_[i+1])/3;
			d_[i] = (c_[i+1]-c_[i])/(3*h_[i]);
		}
	}

public:

	template<uint32_t n>
	Spline_t(T (&x)[n], T (&y)[n])
	:a_(y),x_(x)
	{
		h_.resize(n-1,1);
		for(uint32_t i = 0; i < n - 1; i++)
		{
			h_[i] = x[i+1] - x[i];
		}
		update();
	}

	T getY (T x)
	{
		uint32_t i;
		if(x < x_[0])
			return 0;
		if(x > x_[x_.getN()-1])
			return 0;
		else
		{
			for(i = 0; i < x_.getN()-1; i++)
			{
				if(x >= x_[i] && x <= x_[i+1])
				{
					break;
				}
			}
		}

		return a_[i] + (x-x_[i])*(b_[i] + (x-x_[i])*(c_[i]+d_[i]*(x-x_[i])));
	}
};



#endif /* MATH_NUMERIC_SPLINE_SPLINE_HPP_ */
