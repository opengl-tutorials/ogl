///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2012 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2012-09-19
// Updated : 2012-09-19
// Licence : This source is under MIT licence
// File    : test/gtc/constants.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

int main()
{
	int Error(0);

	float MinHalf = 0.0f;
	while (glm::half(MinHalf) == glm::half(0.0f))
		MinHalf += std::numeric_limits<float>::epsilon();

	return Error;
}
