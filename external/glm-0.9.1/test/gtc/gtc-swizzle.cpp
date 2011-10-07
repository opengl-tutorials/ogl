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
#include <glm/gtc/swizzle.hpp>

int test_swizzle_vec4_ref_dynamic()
{
	{
		glm::ivec4 A(0, 1, 2, 3);
		glm::ivec4 B(2, 1, 0, 3);
		glm::swizzle(A, glm::Z, glm::Y, glm::X, glm::W) = B;
		assert(A.x == B.x && A.y == B.y && A.z == B.z && A.w == B.w);
	}

	{
		glm::ivec4 A(0, 1, 2, 3);
		glm::ivec3 B(2, 1, 0);
		glm::swizzle(A, glm::Z, glm::Y, glm::X) = B;
		assert(A.x == B.x && A.y == B.y && A.z == B.z);
	}

	{
		glm::ivec4 A(0, 1, 2, 3);
		glm::ivec2 B(2, 1);
		glm::swizzle(A, glm::Z, glm::Y) = B;
		assert(A.x == B.x && A.y == B.y);
	}

	{
		glm::ivec4 A(0, 1, 2, 3);
		int B(2);
		glm::swizzle(A, glm::Z) = B;
		assert(A.x == B);
	}

	return 0;
}

int test_swizzle_vec4_ref_static()
{
	{
		glm::ivec4 A(0, 1, 2, 3);
		glm::ivec4 B(2, 1, 0, 3);
		glm::swizzle<glm::Z, glm::Y, glm::X, glm::W>(A) = B;
		assert(A.x == B.x && A.y == B.y && A.z == B.z && A.w == B.w);
	}

	{
		glm::ivec4 A(0, 1, 2, 3);
		glm::ivec3 B(2, 1, 0);
		glm::swizzle<glm::Z, glm::Y, glm::X>(A) = B;
		assert(A.x == B.x && A.y == B.y && A.z == B.z);
	}

	{
		glm::ivec4 A(0, 1, 2, 3);
		glm::ivec2 B(2, 1);
		glm::swizzle<glm::Z, glm::Y>(A) = B;
		assert(A.x == B.x && A.y == B.y);
	}

	{
		glm::ivec4 A(0, 1, 2, 3);
		int B(2);
		glm::swizzle<glm::Z>(A) = B;
		assert(A.x == B);
	}

	return 0;
}

int test_swizzle_vec4_const_dynamic()
{
	glm::ivec4 A(0, 1, 2, 3);
	glm::ivec4 B = glm::swizzle(A, glm::B, glm::G, glm::R, glm::A);
	assert(glm::all(glm::equal(A, B)));

	glm::ivec3 C = glm::swizzle(A, glm::W, glm::Y, glm::Z);
	assert(glm::all(glm::equal(glm::ivec3(A), C)));

	glm::ivec2 D = glm::swizzle(A, glm::W, glm::X);
	assert(glm::all(glm::equal(glm::ivec2(A), D)));

	int E = glm::swizzle(A, glm::Q);
	assert(E == A.q);

	return 0;
}

int test_swizzle_vec4_const_static()
{
	glm::ivec4 A(0, 1, 2, 3);

	glm::ivec4 B = glm::swizzle<glm::B, glm::G, glm::R, glm::A>(A);
	assert(glm::all(glm::equal(A, B)));

	glm::ivec3 C = glm::swizzle<glm::W, glm::Y, glm::Z>(A);
	assert(glm::all(glm::equal(glm::ivec3(A), C)));

	glm::ivec2 D = glm::swizzle<glm::W, glm::X>(A);
	assert(glm::all(glm::equal(glm::ivec2(A), D)));

	int E = glm::swizzle<glm::Q>(A);
	assert(E == A.q);

	return 0;
}

int main()
{
	int Failed = 0;
	Failed += test_swizzle_vec4_ref_dynamic();
	Failed += test_swizzle_vec4_ref_static();
	Failed += test_swizzle_vec4_const_dynamic();
	Failed += test_swizzle_vec4_const_static();

	return Failed;
}
