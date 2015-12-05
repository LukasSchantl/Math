/*
 * vector.hpp
 *
 *  Created on: 19. Nov. 2015
 *      Author: Lukas
 */

#ifndef NUMERIC_VECTOR_HPP_
#define NUMERIC_VECTOR_HPP_

#include "matrix.hpp"

template<typename T, uint32_t max_n>
class ColumnVector_t : public Matrix_t<T,max_n,1>
{
public:
	ColumnVector_t()
	:Matrix_t<T,max_n,1>()
	{

	}

	template<uint32_t n>
	ColumnVector_t(const T (&data)[n])
	:Matrix_t<T,max_n,1>()
	{
		STATIC_DIMENSION_CHECK(n<=max_n);
		this->resize(n,1);
		for(uint32_t i = 0; i < n; i++)
		{
			(*((Matrix_t<T,max_n,1>*)this))[i][0] = data[i];
		}
	}

	virtual ~ColumnVector_t()
	{

	}



	T& operator[](uint32_t i) throw(DimensionException)
	{
		if(i < this->n_)
		{
			return (*((Matrix_t<T,max_n,1>*)this))[i][0];
		}
		throw DimensionException();
	}

	const T& operator[](uint32_t i) const throw(DimensionException)
	{
		if(i < this->n_)
		{
			return (*((Matrix_t<T,max_n,1>*)this))[i][0];
		}
		throw DimensionException();
	}

	operator Matrix_t<T,max_n,1>() const
	{
		return (*(Matrix_t<T,max_n,1>(this)));
	}

	operator Matrix_t<T,max_n,1>&() const
	{
		return (*(Matrix_t<T,max_n,1>(this)));
	}


	ColumnVector_t<T,max_n>& operator= (const Matrix_t<T,max_n,1>& rhs)
	{
		(*(Matrix_t<T,max_n,1>*)this) = rhs;
		return *this;
	}

};


template<typename T, uint32_t max_m>
class LineVector_t : public Matrix_t<T,1,max_m>
{
public:
	LineVector_t()
	:Matrix_t<T,1,max_m>()
	{

	}

	template<uint32_t m>
	LineVector_t(const T (&data)[m])
	:Matrix_t<T,1,max_m>()
	{
		STATIC_DIMENSION_CHECK(m<=max_m);
		this->resize(1,m);
		for(uint32_t i = 0; i < m; i++)
		{
			(*((Matrix_t<T,1,max_m>*)this))[0][i] = data[i];
		}
	}

	virtual ~LineVector_t()
	{

	}

	T& operator[](uint32_t j) throw(DimensionException)
	{
		if(j < this->m_)
		{
			return (*((Matrix_t<T,1,max_m>*)this))[0][j];
		}
		throw DimensionException();
	}

	const T& operator[](uint32_t j) const throw(DimensionException)
	{
		if(j < this->m_)
		{
			return (*((Matrix_t<T,1,max_m>*)this))[0][j];
		}
		throw DimensionException();
	}

	operator Matrix_t<T,1,max_m>() const
	{
		return (*(Matrix_t<T,1,max_m>(this)));
	}

	operator Matrix_t<T,1,max_m>&() const
	{
		return (*(Matrix_t<T,1,max_m>(this)));
	}


	LineVector_t<T,max_m>& operator= (const Matrix_t<T,1,max_m>& rhs)
	{
		(*(Matrix_t<T,1,max_m>*)this) = rhs;
		return *this;
	}

};

#endif /* NUMERIC_VECTOR_HPP_ */
