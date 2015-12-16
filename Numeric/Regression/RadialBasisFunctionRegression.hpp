/*
 * RadialBasisFunctionRegression.hpp
 *
 *  Created on: 07. Dez. 2015
 *      Author: Lukas
 */

#ifndef MATH_NUMERIC_REGRESSION_RADIALBASISFUNCTIONREGRESSION_HPP_
#define MATH_NUMERIC_REGRESSION_RADIALBASISFUNCTIONREGRESSION_HPP_

#include "regression.hpp"
#include <cmath>
template<typename T, uint32_t order, T sigma, uint32_t maxSamples>
class RBFRegression_t : public RegressionBase_t<T, maxSamples>
{
private:
	typedef RegressionBase_t<T, maxSamples> baseType_t;

	ColumnVector_t<T,order> coeffs_;

	virtual void update ()
	{
		uint32_t samples = baseType_t::x_.getN();
		if(samples < 2)
		{
			if(samples<2) throw std::runtime_error("number of samples is not sufficient");
		}
		Matrix_t<T,maxSamples,order> A;
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

	virtual std::ostream& print (std::ostream &stream) const
	{
		stream << coeffs_[0] << " * exp( "  << coeffs_[1] << " * x)";
		return stream;
	}
public:

	template<uint32_t n>
	RBFRegression_t(T(&x)[n],T(&y)[n])
	:baseType_t(x,y),coeffs_()
	{
		update();
	}

	virtual ~RBFRegression_t()
	{

	}

	virtual T getY (T& x) const
	{
		return coeffs_[0] * std::exp(coeffs_[1] * x);
	}
};






#endif /* MATH_NUMERIC_REGRESSION_RADIALBASISFUNCTIONREGRESSION_HPP_ */
