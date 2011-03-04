///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-08-31
// Updated : 2008-08-31
// Licence : This source is under MIT License
// File    : test/core/type_vec4.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <glm/glm.hpp>
#include <glm/gtc/half_float.hpp>

template <int Value>
struct mask
{
	enum{value = Value};
};

enum comp
{
	X,
	Y,
	Z,
	W
};

//template<comp X, comp Y, comp Z, comp W>
//__m128 swizzle(glm::vec4 const & v)
//{
//	__m128 Src = _mm_set_ps(v.w, v.z, v.y, v.x);
//	return _mm_shuffle_ps(Src, Src, mask<(int(W) << 6) | (int(Z) << 4) | (int(Y) << 2) | (int(X) << 0)>::value);
//}

bool test_hvec4()
{
	glm::hvec4 const A = glm::hvec4(0, 1, 2, 3);
	//glm::hvec4 B = glm::swizzle<glm::X, glm::Y, glm::Z, glm::W>(A);

	//glm::vec4 B = glm::detail::tvec##(glm::vec4::_size)<float>();

	return true;
}

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
	test_hvec4();

	//__m128 DataA = swizzle<X, Y, Z, W>(glm::vec4(1.0f, 2.0f, 3.0f, 4.0f));
	//__m128 DataB = swizzle<W, Z, Y, X>(glm::vec4(1.0f, 2.0f, 3.0f, 4.0f));

	bool Result = true;

	Result = Result && test_operators();
	Result = Result && test_hvec4();
	
	assert(Result);
	return Result;

	return 0;
}

