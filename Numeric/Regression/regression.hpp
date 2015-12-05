/*
 * regression.hpp
 *
 *  Created on: 05. Dez. 2015
 *      Author: Lukas
 */

#ifndef MATH_NUMERIC_REGRESSION_REGRESSION_HPP_
#define MATH_NUMERIC_REGRESSION_REGRESSION_HPP_

#include <stdint.h>
#include "../basic/vector.hpp"


template<typename T, uint32_t maxSamples, typename CoeffType>
class RegressionBase_t
{
public:
	typedef CoeffType coeffType_t;

protected:
	ColumnVector_t<T, maxSamples> x_;
	ColumnVector_t<T, maxSamples> y_;

	virtual void update () = 0;
public:

	template<uint32_t n>
	RegressionBase_t(T (&x)[n], T (&y)[n])
	:x_(x),y_(y)
	{

	}

	RegressionBase_t(T* x, T* y, uint32_t n)
	:x_(),y_()
	{
		x_.resize(n,1);
		y_.resize(n,1);
		for(uint32_t i = 0; i < n; i++)
		{
			x_[i] = x[i];
			y_[i] = y[i];
		}
	}


	virtual ~RegressionBase_t()
	{

	}

	virtual const CoeffType& getCoeffs () const = 0;

	virtual T getY (T& x) const = 0;
};



#endif /* MATH_NUMERIC_REGRESSION_REGRESSION_HPP_ */
