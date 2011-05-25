///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-08-31
// Updated : 2008-08-31
// Licence : This source is under MIT License
// File    : test/core/type_mat4x4.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#define GLM_MESSAGES
#include <glm/glm.hpp>
#include <cstdio>

void print(glm::dmat4 const & Mat0)
{
	printf("mat4(\n");
	printf("\tvec4(%2.3f, %2.3f, %2.3f, %2.3f)\n", Mat0[0][0], Mat0[0][1], Mat0[0][2], Mat0[0][3]);
	printf("\tvec4(%2.3f, %2.3f, %2.3f, %2.3f)\n", Mat0[1][0], Mat0[1][1], Mat0[1][2], Mat0[1][3]);
	printf("\tvec4(%2.3f, %2.3f, %2.3f, %2.3f)\n", Mat0[2][0], Mat0[2][1], Mat0[2][2], Mat0[2][3]);
	printf("\tvec4(%2.3f, %2.3f, %2.3f, %2.3f))\n\n", Mat0[3][0], Mat0[3][1], Mat0[3][2], Mat0[3][3]);
}

bool test_mat4x4()
{
	glm::dmat4 Mat0(
		glm::dvec4(0.6f, 0.2f, 0.3f, 0.4f), 
		glm::dvec4(0.2f, 0.7f, 0.5f, 0.3f), 
		glm::dvec4(0.3f, 0.5f, 0.7f, 0.2f), 
		glm::dvec4(0.4f, 0.3f, 0.2f, 0.6f));
	glm::dmat4 Inv0 = glm::inverse(Mat0);
	glm::dmat4 Res0 = Mat0 * Inv0;

	print(Mat0);
	print(Inv0);
	print(Res0);

	return true;
}

static bool test_operators()
{
	glm::mat4x4 m(1.0f);
	glm::vec4 u(1.0f);
	glm::vec4 v(1.0f);
	float x = 1.0f;
	glm::vec4 a = m * u;
	glm::vec4 b = v * m;
	glm::mat4x4 n = x / m;
	glm::mat4x4 o = m / x;
	glm::mat4x4 p = x * m;
	glm::mat4x4 q = m * x;
	bool R = m != q;
	bool S = m == m;

	return true;
}

int main()
{
	bool Result = true;

	Result = Result && test_mat4x4();
	Result = Result && test_operators();
	
	assert(Result);
	return Result;
}
