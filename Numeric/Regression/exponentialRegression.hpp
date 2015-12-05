/*
 * exponentialRegression.hpp
 *
 *  Created on: 05. Dez. 2015
 *      Author: Lukas
 */

#ifndef MATH_NUMERIC_REGRESSION_EXPONENTIALREGRESSION_HPP_
#define MATH_NUMERIC_REGRESSION_EXPONENTIALREGRESSION_HPP_

#include "regression.hpp"
#include <cmath>
template<typename T, uint32_t maxSamples>
class ExponentialRegression_t : public RegressionBase_t<T, maxSamples,ColumnVector_t<T,2> >
{
private:
	typedef RegressionBase_t<T, maxSamples,ColumnVector_t<T,2> > baseType_t;

	ColumnVector_t<T,2> coeffs_;

	virtual void update ()
	{
		uint32_t samples = baseType_t::x_.getN();
		if(samples < 2)
		{
			if(samples<2) throw std::runtime_error("number of samples is not sufficient");
		}
		Matrix_t<T,maxSamples,2> A;
		ColumnVector_t<T,maxSamples> lny;


		A.resize(samples,2);
		lny.resize(samples,1);

		for(uint32_t i = 0; i < samples; i++)
		{
			A[i][0] = 1;
			A[i][1] = baseType_t::x_[i];
			lny[i] = std::log(baseType_t::y_[i]);
		}
		std::cout << "A = \n" << A << std::endl;
		std::cout << "y = \n" << baseType_t::y_ << std::endl;

		coeffs_ = (A.transpose()*A).inverse()*A.transpose()*lny;
		coeffs_[0] = std::exp(coeffs_[0]);

		std::cout << "coeffs_ = \n" << coeffs_ << std::endl;
	}
public:

	template<uint32_t n>
	ExponentialRegression_t(T(&x)[n],T(&y)[n])
	:baseType_t(x,y),coeffs_()
	{
		update();
	}

	virtual const typename baseType_t::coeffType_t& getCoeffs () const
	{
		return coeffs_;
	}

	virtual T getY (T& x) const
	{
		return coeffs_[0] * std::exp(coeffs_[1] * x);
	}
};



#endif /* MATH_NUMERIC_REGRESSION_EXPONENTIALREGRESSION_HPP_ */
