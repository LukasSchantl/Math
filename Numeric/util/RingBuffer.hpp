/*
 * RingBuffer.hpp
 *
 *  Created on: 25.11.2015
 *      Author: Lukas
 */

#ifndef RINGBUFFER_HPP_
#define RINGBUFFER_HPP_

#include <type_traits>
#include <stdint.h>


template<typename T, size_t maxSize>
class Ringbuffer_t
{
private:
	T data_[maxSize];

	size_t inPtr_;
	size_t outPtr_;
	bool empty_;

public:

	Ringbuffer_t()
	:inPtr_(0), outPtr_(0), empty_(true)
	{

	}

	template<size_t size>
	Ringbuffer_t(T (&data)[size])
	:inPtr_(0), outPtr_(0), empty_(true)
	{
		*this = data;
	}

	void push_back(T sample)
	{

		if(!empty_ && inPtr_ == outPtr_)
		{
			outPtr_++;
			outPtr_ = outPtr_ % maxSize;
		}

		data_[inPtr_] = sample;
		inPtr_++;
		inPtr_ = inPtr_ % maxSize;
		empty_ = false;
	}

	void pop_front()
	{
		if(!empty_)
		{
			outPtr_++;
			outPtr_ = outPtr_ % maxSize;
			if(inPtr_ == outPtr_)
				empty_ = true;
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
		return empty_;
	}

	size_t size () const
	{
		if(empty_)
			return 0;

		if(outPtr_ < inPtr_)
		{
			return inPtr_ - outPtr_;
		}
		else if(outPtr_ > inPtr_)
		{
			return maxSize - outPtr_ + inPtr_;
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
		empty_ = true;
	}

	template<size_t size>
	Ringbuffer_t<T,maxSize>& operator= (const T(&data)[size])
	{
		static_assert(size<=maxSize,"Array to big");
		clear();
		memcpy(data_,data,sizeof(T)*size);
		inPtr_ = size % maxSize;
		empty_ = (size == 0);
		return *this;
	}

	friend std::ostream& operator<< (std::ostream& stream, const Ringbuffer_t<T,maxSize>& rb)
	{
		stream << "Size: " << rb.size() << std::endl;
		for(uint32_t i = 0; i < maxSize; i++)
		{
			if((rb.outPtr_ + i)%maxSize < rb.inPtr_)
				stream << i << "\t" << rb.data_[i];
			else
				stream << i << "\t" << "invalid";
			if(i == rb.inPtr_)
				stream << "\t<-- insert position";
			if(i == rb.outPtr_)
				stream << "\t<-- front";
			if(i == (rb.inPtr_-1)%maxSize)
				stream << "\t<-- back";
			stream << std::endl;
		}
		return stream;
	}
};



#endif /* RINGBUFFER_HPP_ */
