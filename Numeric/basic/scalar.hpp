/*
 * scalar.hpp
 *
 *  Created on: 04. Dez. 2015
 *      Author: Lukas
 */

#ifndef MATH_NUMERIC_BASIC_SCALAR_HPP_
#define MATH_NUMERIC_BASIC_SCALAR_HPP_


template<typename T>
T powerDescreteFast (T base, uint32_t exponent)
{
	T result = 1;
	while(exponent)
	{
		if(exponent&0x1)
			result *= base;
		base *= base;
		exponent = exponent >> 1;
	}
	return result;
}


#endif /* MATH_NUMERIC_BASIC_SCALAR_HPP_ */
