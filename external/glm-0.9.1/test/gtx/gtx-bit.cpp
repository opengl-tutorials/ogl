///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-09-16
// Updated : 2010-09-16
// Licence : This source is under MIT licence
// File    : test/gtx/bit.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <glm/glm.hpp>
#include <glm/gtx/number_precision.hpp>
#include <glm/gtx/bit.hpp>
#include <iostream>

enum result
{
	SUCCESS,
	FAIL,
	ASSERT,
	STATIC_ASSERT
};

namespace extractField
{
	template <typename genType, typename sizeType>
	struct type
	{
		genType		Value;
		sizeType	BitFirst;
		sizeType	BitCount;
		genType		Return;
		result		Result;
	};

	typedef type<glm::uint64, glm::uint> typeU64;

	typeU64 const Data64[] =
	{
		{0xffffffffffffffff, 8, 0, 0x0000000000000000, SUCCESS},
		{0x0000000000000000, 0,64, 0x0000000000000000, SUCCESS},
		{0xffffffffffffffff, 0,64, 0xffffffffffffffff, SUCCESS},
		{0x0f0f0f0f0f0f0f0f, 0,64, 0x0f0f0f0f0f0f0f0f, SUCCESS},
		{0x0000000000000000, 8, 0, 0x0000000000000000, SUCCESS},
		{0x8000000000000000,63, 1, 0x0000000000000001, SUCCESS},
		{0x7fffffffffffffff,63, 1, 0x0000000000000000, SUCCESS},
		{0x0000000000000300, 8, 8, 0x0000000000000003, SUCCESS},
		{0x000000000000ff00, 8, 8, 0x00000000000000ff, SUCCESS},
		{0xfffffffffffffff0, 0, 5, 0x0000000000000010, SUCCESS},
		{0x00000000000000ff, 1, 3, 0x0000000000000007, SUCCESS},
		{0x00000000000000ff, 0, 3, 0x0000000000000007, SUCCESS},
		{0x0000000000000000, 0, 2, 0x0000000000000000, SUCCESS},
		{0xffffffffffffffff, 0, 8, 0x00000000000000ff, SUCCESS},
		{0xffffffff00000000,32,32, 0x00000000ffffffff, SUCCESS},
		{0xfffffffffffffff0, 0, 8, 0x0000000000000000, FAIL},
		{0xffffffffffffffff,32,32, 0x0000000000000000, FAIL},
		//{0xffffffffffffffff,64, 1, 0x0000000000000000, ASSERT}, // Throw an assert 
		//{0xffffffffffffffff, 0,65, 0x0000000000000000, ASSERT}, // Throw an assert 
		//{0xffffffffffffffff,33,32, 0x0000000000000000, ASSERT}, // Throw an assert 
	};

	int test()
	{
		glm::uint32 count = sizeof(Data64) / sizeof(typeU64);
		
		for(glm::uint32 i = 0; i < count; ++i)
		{
			glm::uint64 Return = glm::extractField(
				Data64[i].Value, 
				Data64[i].BitFirst, 
				Data64[i].BitCount);
			
			bool Compare = Data64[i].Return == Return;
			
			if(Data64[i].Result == SUCCESS && Compare)
				continue;
			else if(Data64[i].Result == FAIL && !Compare)
				continue;
			
			std::cout << "glm::extractfield test fail on test " << i << std::endl;
			return 1;
		}
		
		return 0;
	}
}//extractField

namespace bitRevert
{
	template <typename genType>
	struct type
	{
		genType		Value;
		genType		Return;
		result		Result;
	};

	typedef type<glm::uint64> typeU64;

	typeU64 const Data64[] =
	{
		{0xffffffffffffffff, 0xffffffffffffffff, SUCCESS},
		{0x0000000000000000, 0x0000000000000000, SUCCESS},
		{0xf000000000000000, 0x000000000000000f, SUCCESS},
	};

	int test()
	{
		glm::uint32 count = sizeof(Data64) / sizeof(typeU64);
		
		for(glm::uint32 i = 0; i < count; ++i)
		{
			glm::uint64 Return = glm::bitRevert(
				Data64[i].Value);
			
			bool Compare = Data64[i].Return == Return;
			
			if(Data64[i].Result == SUCCESS && Compare)
				continue;
			else if(Data64[i].Result == FAIL && !Compare)
				continue;
			
			std::cout << "glm::extractfield test fail on test " << i << std::endl;
			return 1;
		}
		
		return 0;
	}
}//bitRevert

int main()
{
	::extractField::test();
	::bitRevert::test();
}
