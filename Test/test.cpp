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


int a[3][3] = {{1,2,3},{0,4,7},{0,0,3}};

int b[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};

int main (void)
{
	Ringbuffer_t<int,20> rb;
	std::cout << rb << std::endl;
	rb = b;
	int count = 19;
	while(1)
	{
		std::cout << rb << std::endl;
		rb.push_back(count);
		count++;
	}

}
