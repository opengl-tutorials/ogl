///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-08-31
// Updated : 2008-08-31
// Licence : This source is under MIT License
// File    : test/core/type_vec1.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <glm/glm.hpp>

static bool test_operators()
{
	glm::vec4 A(1.0f);
	glm::vec4 B(1.0f);
	bool R = A != B;
	bool S = A == B;

	return true;
}

int main()
{
	bool Result = true;

	Result = Result && test_operators();
	
	assert(Result);
	return Result;
}
