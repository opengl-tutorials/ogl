///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-08-17
// Updated : 2010-02-17
// Licence : This source is under MIT License
// File    : glm/core/type_half.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_core_type_half
#define glm_core_type_half

#include <cstdlib>

namespace glm
{
	namespace test
	{
		bool main_type_half();

	}//namespace test

	namespace detail
	{
		typedef short hdata;

		float toFloat32(hdata value);
		hdata toFloat16(float const & value);

		///16-bit floating point type.
		/// \ingroup gtc_half_float
		class thalf
		{
		public: 
			// Constructors
			thalf();
			thalf(thalf const & s);
			
			template <typename U>
			explicit thalf(U const & s);

			// Cast
			//operator float();
			operator float() const;
			//operator double();
			//operator double() const;

			// Unary updatable operators
			thalf& operator= (thalf const & s);
			thalf& operator+=(thalf const & s);
			thalf& operator-=(thalf const & s);
			thalf& operator*=(thalf const & s);
			thalf& operator/=(thalf const & s);
			thalf& operator++();
			thalf& operator--();
	
			float toFloat() const{return toFloat32(data);}

			hdata _data() const{return data;}

		private:
			hdata data;
		};

		thalf operator+ (thalf const & s1, thalf const & s2);

		thalf operator- (thalf const & s1, thalf const & s2);

		thalf operator* (thalf const & s1, thalf const & s2);

		thalf operator/ (thalf const & s1, thalf const & s2);

		// Unary constant operators
		thalf operator- (thalf const & s);

		thalf operator-- (thalf const & s, int);

		thalf operator++ (thalf const & s, int);

	}//namespace detail


}//namespace glm

#include "type_half.inl"

#endif//glm_core_type_half
