/*
 * matrix.hpp
 *
 *  Created on: 19. Nov. 2015
 *      Author: Lukas
 */

#ifndef NUMERIC_MATRIX_HPP_
#define NUMERIC_MATRIX_HPP_

#include <stdint.h>
#include <string.h>
#include <iostream>
#include <limits>
#include <cmath>



template<bool> struct CompileTimeDimensionError;
template<> struct CompileTimeDimensionError<true> {}; //specialized only for true
#define STATIC_DIMENSION_CHECK(expr)  (CompileTimeDimensionError<(expr) != 0>())


class SingualMatrixException : public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return "Singular Matrix";
	}


};

class DimensionException : public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return "Dimension Check failed";
	}


};


template<typename T, uint32_t max_n, uint32_t max_m>
class Matrix_t
{
private:
	static const uint32_t maxDimension_ = (max_n > max_m ? max_n : max_m);

    Matrix_t<T,maxDimension_,maxDimension_> invert ()
	{

    	Matrix_t<T,maxDimension_,maxDimension_> result(this->n_);
		Matrix_t<T,maxDimension_,maxDimension_> left = *this;
		Line_t swapline;


		uint32_t i;
		for(i = 0; i < this->n_; i++)
		{
			uint32_t j = i;
			// check if actual line has pivot > type epsilon
			while(std::fabs(left[j][i]) < std::numeric_limits<T>::epsilon())
			{
				j++;
				if(j >= left.n_)
				{
					result.resize(0,0);
					return result;
				}
				if(left[j][i] > std::numeric_limits<T>::epsilon())
				{
					swapline = left[j];
					left[j] = left[i];
					left[i] = swapline;

					swapline = result[j];
					result[j] = result[i];
					result[i] = swapline;
				}
			}
			// divide line with pivot
			T pivot = left[i][i];
			for(j = i; j < left.n_; j++)
			{
				left[i][j] /= pivot;
			}
			for(j = 0; j < left.n_; j++)
			{
				result[i][j] /= pivot;
			}
			for(uint32_t k = i+1; k < left.n_; k++)
			{
				T d = left[k][i];
				for(j = i; j < left.n_; j++)
				{
					left[k][j] -= left[i][j]*d;
				}
				for(j = 0; j <= i; j++)
				{
					result[k][j] -= result[i][j]*d;
				}
			}
		}

		for(i = left.n_-1 ; i > 0; i--)
		{
			for(int32_t k = i-1; k >= 0; k--)
			{
				T d = left[k][i];
				left[k][i] = 0;
				for(uint32_t j = 0; j < left.n_; j++)
				{
					result[k][j] -= result[i][j]*d;
				}
			}
		}
		return result;
	}

    Matrix_t<T,max_m, max_n> psuedoInvert ()
	{
    	return ((*this).transpose() * (*this)).invert() * (*this).transpose();
	}

protected:
	class Line_t
	{
	private:
		T data_[max_m];

		uint32_t ml_;

	public:
		Line_t()
		:ml_(0)
		{

		}

		template<uint32_t ml>
		Line_t(const T(&data)[ml])
		:ml_(ml)
		{
			STATIC_DIMENSION_CHECK(ml<=max_m);
			memcpy(data_,data,ml_*sizeof(T));
		}

		virtual ~Line_t()
		{

		}

		void resize(uint32_t newSize)
		{
			if(newSize <= max_m)
				ml_ = newSize;
			else
				throw DimensionException();
		}

	    T& operator[](uint32_t j)
	    {
	    	if(j < ml_)
	    	{
	    		return data_[j];
	    	}

	    	throw DimensionException();
	    }

	    const T& operator[](uint32_t j) const
	    {
	    	if(j < ml_)
	    	{
	    		return data_[j];
	    	}
	    	throw DimensionException();
	    }


	};

	Line_t lines_[max_n];

	uint32_t n_;
	uint32_t m_;

public:


	uint32_t getM() const {
		return m_;
	}

	uint32_t getN() const {
		return n_;
	}

	Matrix_t()
	:n_(0),m_(0)
	{

	}

	template<uint32_t n, uint32_t m>
	Matrix_t (const T (&data)[n][m])
	:n_(n),m_(m)
	{
		STATIC_DIMENSION_CHECK(n<=max_n);
		STATIC_DIMENSION_CHECK(m<=max_m);

		for(int i = 0; i < n; i++)
			lines_[i] = Line_t(data[i]);
	}

	Matrix_t (const uint32_t size)
	:n_(size),m_(size)
	{
		for(uint32_t i = 0; i < size; i++)
		{
			lines_[i].resize(size);
			for(uint32_t j = 0; j < size; j++)
			{
				if(i == j)
				{
					(*this)[i][j] = 1;
				}
				else
				{
					(*this)[i][j] = 0;
				}
			}
		}
	}

	virtual ~Matrix_t()
	{

	}

	void resize (uint32_t new_n, uint32_t new_m)
	{
		if(new_n > max_n || new_m > max_m)
			throw DimensionException();

		this->n_ = new_n;
		this->m_ = new_m;
		for(uint32_t i = 0; i < max_n; i++)
		{
			this->lines_[i].resize(this->m_);
		}
	}


    Line_t& operator[](uint32_t i)
    {
    	if(i < this->n_)
    	{
    		return lines_[i];
    	}

    	throw DimensionException();
    }

    const Line_t& operator[](uint32_t i) const
    {
    	if(i < this->n_)
    	{
    		return lines_[i];
    	}
    	throw DimensionException();
    }


    friend std::ostream& operator<< (std::ostream& stream, const Matrix_t<T,max_n,max_m>& mat)
    {
    	for(uint32_t i = 0; i < mat.n_; i++)
    	{
        	for(uint32_t j = 0; j < mat.m_; j++)
        	{
        		stream << mat[i][j] << " ";
        	}

        	stream << std::endl;
    	}
    	return stream;
    }

    // Arithmetic Operators


    Matrix_t<T,max_n,max_m> operator+ (const Matrix_t<T,max_n,max_m>& rhs) const
    {
    	Matrix_t<T,max_n,max_m> result;
    	if(this->n_ != rhs.n_ || this->m_ != rhs.m_)
    		throw DimensionException();
    	result.resize(n_,m_);
    	for(uint32_t i = 0; i < n_; i++)
    	{
    		for(uint32_t j = 0; j < m_; j++)
    		{
    			result[i][j] = (*this)[i][j] + rhs[i][j];
    		}
    	}
    	return result;
    }

    virtual Matrix_t<T,max_n,max_m>& operator+= (const Matrix_t<T,max_n,max_m>& rhs)
	{
    	*this = *this + rhs;
		return *this;
	}

    virtual Matrix_t<T,max_n,max_m> operator+ (const T& rhs) const
    {
    	Matrix_t<T,max_n,max_m> result;

    	result.resize(n_,m_);
    	for(uint32_t i = 0; i < n_; i++)
    	{
    		for(uint32_t j = 0; j < m_; j++)
    		{
    			result[i][j] = (*this)[i][j] + rhs;
    		}
    	}
    	return result;
    }

    virtual Matrix_t<T,max_n,max_m>& operator+= (const T& rhs)
	{
    	*this = *this + rhs;
		return *this;
	}

    virtual Matrix_t<T,max_n,max_m> operator- (const Matrix_t<T,max_n,max_m>& rhs) const
    {
    	Matrix_t<T,max_n,max_m> result;
    	if(this->n_ != rhs.n_ || this->m_ != rhs.m_)
    		throw DimensionException();
    	result.resize(n_,m_);
    	for(uint32_t i = 0; i < n_; i++)
    	{
    		for(uint32_t j = 0; j < m_; j++)
    		{
    			result[i][j] = (*this)[i][j] - rhs[i][j];
    		}
    	}
    	return result;
    }

    virtual Matrix_t<T,max_n,max_m>& operator-= (const Matrix_t<T,max_n,max_m>& rhs)
	{
    	*this = *this - rhs;
		return *this;
	}

    virtual Matrix_t<T,max_n,max_m> operator- (const T& rhs) const
    {
    	Matrix_t<T,max_n,max_m> result;

    	result.resize(n_,m_);
    	for(uint32_t i = 0; i < n_; i++)
    	{
    		for(uint32_t j = 0; j < m_; j++)
    		{
    			result[i][j] = (*this)[i][j] - rhs;
    		}
    	}
    	return result;
    }

    virtual Matrix_t<T,max_n,max_m>& operator-= (const T& rhs)
	{
    	*this = *this - rhs;
		return *this;
	}

    template<uint32_t max_m2>
    Matrix_t<T,max_n,max_m2> operator* (const Matrix_t<T,max_m,max_m2>& rhs) const
    {
    	Matrix_t<T,max_n,max_m2> result;
    	if(getM() != rhs.getN())
    		throw DimensionException();
    	result.resize(getN(),rhs.getM());
    	for(uint32_t i = 0; i < rhs.getM(); i++)
    	{
    		for(uint32_t j = 0; j < getN(); j++)
    		{
    			T sum = 0;
    			for(uint32_t k = 0; k < getM(); k++)
    			{
    				sum += rhs[k][i]*(*this)[j][k];
    			}
    			result[j][i] = sum;
    		}
    	}
    	return result;
    }

    template<uint32_t max_m2>
    Matrix_t<T,max_n,max_m>& operator*= (const Matrix_t<T,max_m,max_m2>& rhs)
	{
    	*this = *this * rhs;
		return *this;
	}

    virtual Matrix_t<T,max_n,max_m> operator* (const T& rhs) const
    {
    	Matrix_t<T,max_n,max_m> result;
    	result.resize(n_,m_);
    	for(uint32_t i = 0; i < n_; i++)
    	{
    		for(uint32_t j = 0; j < m_; j++)
    		{
    			result[i][j] = (*this)[i][j] * rhs;
    		}
    	}
    	return result;
    }

    virtual Matrix_t<T,max_n,max_m>& operator*= (const T& rhs)
	{
    	*this = *this * rhs;
		return *this;
	}

    virtual Matrix_t<T,max_n,max_m> operator/ (const T& rhs) const
    {
    	Matrix_t<T,max_n,max_m> result;
    	result.resize(n_,m_);
    	for(uint32_t i = 0; i < n_; i++)
    	{
    		for(uint32_t j = 0; j < m_; j++)
    		{
    			result[i][j] = (*this)[i][j] / rhs;
    		}
    	}
    	return result;
    }

    virtual Matrix_t<T,max_n,max_m>& operator/= (const T& rhs)
	{
    	*this = *this / rhs;
		return *this;
	}


    Matrix_t<T,max_m,max_n> transpose ()
	{
    	Matrix_t<T,max_m,max_n> result;
    	result.resize(m_,n_);

    	for(uint32_t i = 0; i < n_; i++)
    	{
    		for(uint32_t j = 0; j < m_; j++)
    		{
    			result[j][i] = (*this)[i][j];
    		}
    	}

    	return result;
	}

    Matrix_t<T,max_n,max_m> inverse ()
	{
    	if(max_n == max_m && n_ == m_)
    	{

			Matrix_t<T,max_n,max_m> result = invert();
			if(result.n_ > 0)
				return result;


			return psuedoInvert();

    	}
    	else
    	{
    		return psuedoInvert();
    	}
	}


};


#endif /* NUMERIC_MATRIX_HPP_ */
