/*
 * polynomialRegression.hpp
 *
 *  Created on: 25.11.2015
 *      Author: Lukas
 */

#ifndef POLYNOMIALREGRESSION_HPP_
#define POLYNOMIALREGRESSION_HPP_

#include <stdexcept>

#include "regression.hpp"


template<typename T, uint32_t order, uint32_t maxSamples>
class PolynomialRegression_t : public RegressionBase_t<T,maxSamples,ColumnVector_t<T, order+1> >
{
private:

	typedef RegressionBase_t<T,maxSamples,ColumnVector_t<T, order+1> > baseType_t;
	ColumnVector_t<T, order+1> coeffs_;

	virtual void update ()
	{
		uint32_t samples = baseType_t::x_.getN();
		if(samples < order+1)
		{
			if(samples<order+1) throw std::runtime_error("number of samples is not sufficient");
		}
		Matrix_t<T,maxSamples,order+1> A;

		A.resize(samples,order+1);

		for(uint32_t i = 0; i < samples; i++)
		{
			T xs = baseType_t::x_[i];
			T xpow = 1;

			for(uint32_t j = 0; j < order+1; j++)
			{
				A[i][j] = xpow;
				xpow *= xs;
			}
		}
		std::cout << "A = \n" << A << std::endl;
		std::cout << "y = \n" << baseType_t::y_ << std::endl;

		coeffs_ = (A.transpose()*A).inverse()*A.transpose()*baseType_t::y_;

		std::cout << "coeffs_ = \n" << coeffs_ << std::endl;
	}

public:
	template<uint32_t n>
	PolynomialRegression_t(T(&x)[n],T(&y)[n])
	:baseType_t(x,y),coeffs_()
	{
		update();
	}


	PolynomialRegression_t(T* x, T* y, uint32_t n)
	:baseType_t(x,y,n),coeffs_()
	{
		update();
	}


	virtual ~PolynomialRegression_t()
	{

	}

	virtual T getY (T& x) const
	{
		T result = 0;
		T xPow = 1;
		for(uint32_t i = 0; i < order + 1; i++)
		{
			result += coeffs_[i] * xPow;
			xPow *= x;
		}
		return result;
	}


	virtual const typename baseType_t::coeffType_t& getCoeffs () const
	{
		return coeffs_;
	}
};


#endif /* POLYNOMIALREGRESSION_HPP_ */
