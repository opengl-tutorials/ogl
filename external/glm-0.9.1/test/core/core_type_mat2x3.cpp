///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-08-31
// Updated : 2008-08-31
// Licence : This source is under MIT License
// File    : test/core/type_mat2x3.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <glm/glm.hpp>

static bool test_operators()
{
	glm::mat2x3 m(1.0f);
	glm::vec2 u(1.0f);
	glm::vec3 v(1.0f);
	float x = 1.0f;
	glm::vec3 a = m * u;
	glm::vec2 b = v * m;
	glm::mat2x3 n = x / m;
	glm::mat2x3 o = m / x;
	glm::mat2x3 p = x * m;
	glm::mat2x3 q = m * x;
	bool R = m != q;
	bool S = m == m;

	return true;
}

int main()
{
	bool Result = true;

	Result = Result && test_operators();

	assert(Result);
	return Result;
}
