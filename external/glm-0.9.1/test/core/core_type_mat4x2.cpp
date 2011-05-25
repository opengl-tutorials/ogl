///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-08-31
// Updated : 2008-08-31
// Licence : This source is under MIT License
// File    : test/core/type_mat4x2.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <glm/glm.hpp>

static bool test_operators()
{
	glm::mat4x2 m(1.0f);
	glm::vec4 u(1.0f);
	glm::vec2 v(1.0f);
	float x = 1.0f;
	glm::vec2 a = m * u;
	glm::vec4 b = v * m;
	glm::mat4x2 n = x / m;
	glm::mat4x2 o = m / x;
	glm::mat4x2 p = x * m;
	glm::mat4x2 q = m * x;
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

