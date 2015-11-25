/*
 * RingBuffer.hpp
 *
 *  Created on: 25.11.2015
 *      Author: Lukas
 */

#ifndef RINGBUFFER_HPP_
#define RINGBUFFER_HPP_


#include <stdint.h>

template<typename T, size_t maxSize>
class Ringbuffer_t
{
private:
	T data_[maxSize];

	size_t inPtr_;
	size_t outPtr_;

public:

	Ringbuffer_t()
	:inPtr_(0), outPtr_(0)
	{

	}


	void push_back(T sample)
	{
		data_[inPtr_] = sample;
		inPtr_++;
		inPtr_ = inPtr_ % maxSize;
		if(inPtr_ == outPtr_)
		{
			outPtr_++;
			outPtr_ = outPtr_ % maxSize;
		}
	}

	void pop_front()
	{
		if(inPtr_ != outPtr_)
		{
			outPtr_++;
			outPtr_ = outPtr_ % maxSize;
		}
	}

	T front () const
	{
		return data_[outPtr_];
	}

	T back () const
	{
		return data_[(inPtr_-1)%maxSize];
	}

	bool empty () const
	{
		return(inPtr_ == outPtr_);
	}

	size_t size () const
	{
		if(outPtr_ < inPtr_)
		{
			return inPtr_ - outPtr_ + 1;
		}
		else if(outPtr_ > inPtr_)
		{
			return maxSize - outPtr_ + inPtr_ + 1;
		}
		else
		{
			return 0;
		}
	}

	size_t max_size () const
	{
		return maxSize;
	}

	const T& operator[] (size_t idx) const
	{
		if(idx >= size())
		{
			return data_[0];
		}
		return data_[(outPtr_+idx)%maxSize];
	}

	void clear ()
	{
		inPtr_ = 0;
		outPtr_ = 0;
	}
};

#endif /* RINGBUFFER_HPP_ */
