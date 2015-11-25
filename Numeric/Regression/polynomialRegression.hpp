/*
 * polynomialRegression.hpp
 *
 *  Created on: 25.11.2015
 *      Author: Lukas
 */

#ifndef POLYNOMIALREGRESSION_HPP_
#define POLYNOMIALREGRESSION_HPP_

#include <stdint.h>

template<typename T, uint32_t maxSamples>
class PolynomialRegression_t
{
private:
	T x_[maxSamples];
	T y_[maxSamples];

public:
	template<uint32_t n>
	PolynomialRegression_t(T(&x)[n],T(&y)[n])
	{
		static_assert(n<=maxSamples, "Input array does not fit in memory");

		memcpy(x_,x[0],sizeof(T)*n);
		memcpy(y_,y[1],sizeof(T)*n);
	}
};


#endif /* POLYNOMIALREGRESSION_HPP_ */
