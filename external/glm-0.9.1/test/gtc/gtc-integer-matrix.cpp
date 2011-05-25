///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-09-16
// Updated : 2010-09-16
// Licence : This source is under MIT licence
// File    : test/gtx/simd-mat4.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#define GLM_MESSAGES
#include <glm/glm.hpp>
#include <glm/gtc/matrix_integer.hpp>

int test_int_matrix()
{
	{
		glm::mediump_uint A(0);
	}

	return 0;
}

int main()
{
	int Failed = 0;
	Failed += test_int_matrix();

	return Failed;
}
