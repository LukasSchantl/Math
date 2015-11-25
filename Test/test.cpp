/*
 * test.cpp
 *
 *  Created on: 25.11.2015
 *      Author: Lukas
 */


#include <iostream>

#include "../Numeric/basic/matrix.hpp"
#include "../Numeric/basic/vector.hpp"

#include "../Numeric/util/RingBuffer.hpp"



int main (void)
{
	Ringbuffer_t<int,20> rb;

	rb.clear();
	int count = 0;
	while(1)
	{
		while(rb.size() != 17)
		{
			rb.push_back(count);
			count++;
		}
		while(!rb.empty())
		{
			std::cout << rb.front() << " = " << rb[0] <<  std::endl;
			rb.pop_front();
		}
	}

}
