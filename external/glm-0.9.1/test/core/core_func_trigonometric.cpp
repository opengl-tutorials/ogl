///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2011-01-15
// Updated : 2011-01-15
// Licence : This source is under MIT licence
// File    : test/gtx/simd-mat4.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <glm/glm.hpp>

int test_static_assert()
{
	//glm::lessThan(glm::mat4(0), glm::mat4(4));

	return 0;
}

int test_lessThan_vec2()
{
	glm::bvec2 O = glm::bvec2(true, false);

	glm::bvec2 A = glm::lessThan(glm::vec2(0, 6), glm::vec2(4, 2));
	assert(glm::all(glm::equal(O, A)));

	glm::bvec2 B = glm::lessThan(glm::ivec2(0, 6), glm::ivec2(4, 2));
	assert(glm::all(glm::equal(O, B)));

	glm::bvec2 C = glm::lessThan(glm::uvec2(0, 6), glm::uvec2(4, 2));
	assert(glm::all(glm::equal(O, C)));

	return 0;
}

int test_lessThan_vec3()
{
	glm::bvec3 O = glm::bvec3(true, true, false);

	glm::bvec3 A = glm::lessThan(glm::vec3(0, 1, 6), glm::vec3(4, 5, 2));
	assert(glm::all(glm::equal(O, A)));

	glm::bvec3 B = glm::lessThan(glm::ivec3(0, 1, 6), glm::ivec3(4, 5, 2));
	assert(glm::all(glm::equal(O, B)));

	glm::bvec3 C = glm::lessThan(glm::uvec3(0, 1, 6), glm::uvec3(4, 5, 2));
	assert(glm::all(glm::equal(O, C)));

	return 0;
}

int test_lessThan_vec4()
{
	glm::bvec4 O = glm::bvec4(true, true, false, false);

	glm::bvec4 A = glm::lessThan(glm::vec4(0, 1, 6, 7), glm::vec4(4, 5, 2, 3));
	assert(glm::all(glm::equal(O, A)));

	glm::bvec4 B = glm::lessThan(glm::ivec4(0, 1, 6, 7), glm::ivec4(4, 5, 2, 3));
	assert(glm::all(glm::equal(O, B)));

	glm::bvec4 C = glm::lessThan(glm::uvec4(0, 1, 6, 7), glm::uvec4(4, 5, 2, 3));
	assert(glm::all(glm::equal(O, C)));

	return 0;
}

int test_greaterThanEqual_vec2()
{
	glm::bvec2 O = glm::bvec2(false, true);

	glm::bvec2 A = glm::greaterThanEqual(glm::vec2(0, 6), glm::vec2(4, 2));
	assert(glm::all(glm::equal(O, A)));

	glm::bvec2 B = glm::greaterThanEqual(glm::ivec2(0, 6), glm::ivec2(4, 2));
	assert(glm::all(glm::equal(O, B)));

	glm::bvec2 C = glm::greaterThanEqual(glm::uvec2(0, 6), glm::uvec2(4, 2));
	assert(glm::all(glm::equal(O, C)));

	return 0;
}

int test_greaterThanEqual_vec3()
{
	glm::bvec3 O = glm::bvec3(false, false, true);

	glm::bvec3 A = glm::greaterThanEqual(glm::vec3(0, 1, 6), glm::vec3(4, 5, 2));
	assert(glm::all(glm::equal(O, A)));

	glm::bvec3 B = glm::greaterThanEqual(glm::ivec3(0, 1, 6), glm::ivec3(4, 5, 2));
	assert(glm::all(glm::equal(O, B)));

	glm::bvec3 C = glm::greaterThanEqual(glm::uvec3(0, 1, 6), glm::uvec3(4, 5, 2));
	assert(glm::all(glm::equal(O, C)));

	return 0;
}

int test_greaterThanEqual_vec4()
{
	glm::bvec4 O = glm::bvec4(false, false, true, true);

	glm::bvec4 A = glm::greaterThanEqual(glm::vec4(0, 1, 6, 7), glm::vec4(4, 5, 2, 3));
	assert(glm::all(glm::equal(O, A)));

	glm::bvec4 B = glm::greaterThanEqual(glm::ivec4(0, 1, 6, 7), glm::ivec4(4, 5, 2, 3));
	assert(glm::all(glm::equal(O, B)));

	glm::bvec4 C = glm::greaterThanEqual(glm::uvec4(0, 1, 6, 7), glm::uvec4(4, 5, 2, 3));
	assert(glm::all(glm::equal(O, C)));

	return 0;
}

int test_all()
{
	assert(glm::all(glm::bvec2(true, true)));
	assert(!glm::all(glm::bvec2(true, false)));
	assert(!glm::all(glm::bvec2(false, false)));

	assert(glm::all(glm::bvec3(true, true, true)));
	assert(!glm::all(glm::bvec3(true, false, true)));
	assert(!glm::all(glm::bvec3(false, false, false)));

	assert(glm::all(glm::bvec4(true, true, true, true)));
	assert(!glm::all(glm::bvec4(true, false, true, false)));
	assert(!glm::all(glm::bvec4(false, false, false, false)));

	return 0;
}


int main()
{
	int Failed = 0;
	Failed += test_static_assert();
	Failed += test_lessThan_vec2();
	Failed += test_lessThan_vec3();
	Failed += test_lessThan_vec4();
	Failed += test_greaterThanEqual_vec2();
	Failed += test_greaterThanEqual_vec3();
	Failed += test_greaterThanEqual_vec4();
	Failed += test_all();

	return Failed;
}

