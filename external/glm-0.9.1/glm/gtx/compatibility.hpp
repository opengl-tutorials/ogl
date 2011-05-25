///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2007-01-24
// Updated : 2008-10-24
// Licence : This source is under MIT License
// File    : glm/gtx/compatibility.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
// - GLM_GTC_half_float
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_compatibility
#define glm_gtx_compatibility

// Dependency:
#include "../glm.hpp"  
#include "../gtc/half_float.hpp"

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_compatibility extension included")
#endif

#if(GLM_COMPILER & GLM_COMPILER_VC)
#include <cfloat>
#elif(GLM_COMPILER & GLM_COMPILER_GCC)
#include <cmath>
#endif//GLM_COMPILER

namespace glm
{
	namespace test{
		void main_gtx_compatibility();
	}//namespace test

	namespace gtx{
	//! GLM_GTX_compatibility extension: Provide functions to increase the compatibility with Cg and HLSL languages
	namespace compatibility
	{
		/// \addtogroup gtx_compatibility
		///@{

		template <typename T> inline T lerp(T x, T y, T a){return mix(x, y, a);}																					//!< \brief Returns x * (1.0 - a) + y * a, i.e., the linear blend of x and y using the floating-point value a. The value for a is not restricted to the range [0, 1]. (From GLM_GTX_compatibility)
		template <typename T> inline detail::tvec2<T> lerp(const detail::tvec2<T>& x, const detail::tvec2<T>& y, T a){return mix(x, y, a);}							//!< \brief Returns x * (1.0 - a) + y * a, i.e., the linear blend of x and y using the floating-point value a. The value for a is not restricted to the range [0, 1]. (From GLM_GTX_compatibility)
		template <typename T> inline detail::tvec3<T> lerp(const detail::tvec3<T>& x, const detail::tvec3<T>& y, T a){return mix(x, y, a);}							//!< \brief Returns x * (1.0 - a) + y * a, i.e., the linear blend of x and y using the floating-point value a. The value for a is not restricted to the range [0, 1]. (From GLM_GTX_compatibility)
		template <typename T> inline detail::tvec4<T> lerp(const detail::tvec4<T>& x, const detail::tvec4<T>& y, T a){return mix(x, y, a);}							//!< \brief Returns x * (1.0 - a) + y * a, i.e., the linear blend of x and y using the floating-point value a. The value for a is not restricted to the range [0, 1]. (From GLM_GTX_compatibility)
		template <typename T> inline detail::tvec2<T> lerp(const detail::tvec2<T>& x, const detail::tvec2<T>& y, const detail::tvec2<T>& a){return mix(x, y, a);}	//!< \brief Returns the component-wise result of x * (1.0 - a) + y * a, i.e., the linear blend of x and y using vector a. The value for a is not restricted to the range [0, 1]. (From GLM_GTX_compatibility)
		template <typename T> inline detail::tvec3<T> lerp(const detail::tvec3<T>& x, const detail::tvec3<T>& y, const detail::tvec3<T>& a){return mix(x, y, a);}	//!< \brief Returns the component-wise result of x * (1.0 - a) + y * a, i.e., the linear blend of x and y using vector a. The value for a is not restricted to the range [0, 1]. (From GLM_GTX_compatibility)
		template <typename T> inline detail::tvec4<T> lerp(const detail::tvec4<T>& x, const detail::tvec4<T>& y, const detail::tvec4<T>& a){return mix(x, y, a);}	//!< \brief Returns the component-wise result of x * (1.0 - a) + y * a, i.e., the linear blend of x and y using vector a. The value for a is not restricted to the range [0, 1]. (From GLM_GTX_compatibility)

		template <typename T> inline T saturate(T x){return clamp(x, T(0), T(1));}														//!< \brief Returns clamp(x, 0, 1) for each component in x. (From GLM_GTX_compatibility)
		template <typename T> inline detail::tvec2<T> saturate(const detail::tvec2<T>& x){return clamp(x, T(0), T(1));}					//!< \brief Returns clamp(x, 0, 1) for each component in x. (From GLM_GTX_compatibility)
		template <typename T> inline detail::tvec3<T> saturate(const detail::tvec3<T>& x){return clamp(x, T(0), T(1));}					//!< \brief Returns clamp(x, 0, 1) for each component in x. (From GLM_GTX_compatibility)
		template <typename T> inline detail::tvec4<T> saturate(const detail::tvec4<T>& x){return clamp(x, T(0), T(1));}					//!< \brief Returns clamp(x, 0, 1) for each component in x. (From GLM_GTX_compatibility)

		template <typename T> inline T atan2(T x, T y){return atan(x, y);}																//!< \brief Arc tangent. Returns an angle whose tangent is y/x. The signs of x and y are used to determine what quadrant the angle is in. The range of values returned by this function is [-PI, PI]. Results are undefined if x and y are both 0. (From GLM_GTX_compatibility)
		template <typename T> inline detail::tvec2<T> atan2(const detail::tvec2<T>& x, const detail::tvec2<T>& y){return atan(x, y);}	//!< \brief Arc tangent. Returns an angle whose tangent is y/x. The signs of x and y are used to determine what quadrant the angle is in. The range of values returned by this function is [-PI, PI]. Results are undefined if x and y are both 0. (From GLM_GTX_compatibility)
		template <typename T> inline detail::tvec3<T> atan2(const detail::tvec3<T>& x, const detail::tvec3<T>& y){return atan(x, y);}	//!< \brief Arc tangent. Returns an angle whose tangent is y/x. The signs of x and y are used to determine what quadrant the angle is in. The range of values returned by this function is [-PI, PI]. Results are undefined if x and y are both 0. (From GLM_GTX_compatibility)
		template <typename T> inline detail::tvec4<T> atan2(const detail::tvec4<T>& x, const detail::tvec4<T>& y){return atan(x, y);}	//!< \brief Arc tangent. Returns an angle whose tangent is y/x. The signs of x and y are used to determine what quadrant the angle is in. The range of values returned by this function is [-PI, PI]. Results are undefined if x and y are both 0. (From GLM_GTX_compatibility)

		template <typename genType> bool isfinite(genType const & x);											//!< \brief Test whether or not a scalar or each vector component is a finite value. (From GLM_GTX_compatibility)
		template <typename valType> detail::tvec2<bool> isfinite(const detail::tvec2<valType>& x);				//!< \brief Test whether or not a scalar or each vector component is a finite value. (From GLM_GTX_compatibility)
		template <typename valType> detail::tvec3<bool> isfinite(const detail::tvec3<valType>& x);				//!< \brief Test whether or not a scalar or each vector component is a finite value. (From GLM_GTX_compatibility)
		template <typename valType> detail::tvec4<bool> isfinite(const detail::tvec4<valType>& x);				//!< \brief Test whether or not a scalar or each vector component is a finite value. (From GLM_GTX_compatibility)

		template <typename genType> bool isinf(genType const & x);														//!< \brief Determines whether the given floating-point value is infinite. (From GLM_GTX_compatibility extension) 
		template <typename genType> detail::tvec2<bool> isinf(const detail::tvec2<genType>& x);					//!< \brief Determines whether the given floating-point value is infinite. (From GLM_GTX_compatibility extension) 
		template <typename genType> detail::tvec3<bool> isinf(const detail::tvec3<genType>& x);					//!< \brief Determines whether the given floating-point value is infinite. (From GLM_GTX_compatibility extension) 
		template <typename genType> detail::tvec4<bool> isinf(const detail::tvec4<genType>& x);					//!< \brief Determines whether the given floating-point value is infinite. (From GLM_GTX_compatibility extension) 

		template <typename genType> bool isnan(genType const & x);														//!< \brief Checks given floating-point value for not a number (NAN) (From GLM_GTX_compatibility extension)
		template <typename genType> detail::tvec2<bool> isnan(const detail::tvec2<genType>& x);					//!< \brief Checks given floating-point value for not a number (NAN) (From GLM_GTX_compatibility extension)
		template <typename genType> detail::tvec3<bool> isnan(const detail::tvec3<genType>& x);					//!< \brief Checks given floating-point value for not a number (NAN) (From GLM_GTX_compatibility extension)
		template <typename genType> detail::tvec4<bool> isnan(const detail::tvec4<genType>& x);					//!< \brief Checks given floating-point value for not a number (NAN) (From GLM_GTX_compatibility extension)

		typedef bool						bool1;			//!< \brief boolean type with 1 component. (From GLM_GTX_compatibility extension)
		typedef detail::tvec2<bool>			bool2;			//!< \brief boolean type with 2 components. (From GLM_GTX_compatibility extension)
		typedef detail::tvec3<bool>			bool3;			//!< \brief boolean type with 3 components. (From GLM_GTX_compatibility extension)
		typedef detail::tvec4<bool>			bool4;			//!< \brief boolean type with 4 components. (From GLM_GTX_compatibility extension)

		typedef bool						bool1x1;		//!< \brief boolean matrix with 1 x 1 component. (From GLM_GTX_compatibility extension)
		typedef detail::tmat2x2<bool>		bool2x2;		//!< \brief boolean matrix with 2 x 2 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat2x3<bool>		bool2x3;		//!< \brief boolean matrix with 2 x 3 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat2x4<bool>		bool2x4;		//!< \brief boolean matrix with 2 x 4 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat3x2<bool>		bool3x2;		//!< \brief boolean matrix with 3 x 2 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat3x3<bool>		bool3x3;		//!< \brief boolean matrix with 3 x 3 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat3x4<bool>		bool3x4;		//!< \brief boolean matrix with 3 x 4 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat4x2<bool>		bool4x2;		//!< \brief boolean matrix with 4 x 2 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat4x3<bool>		bool4x3;		//!< \brief boolean matrix with 4 x 3 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat4x4<bool>		bool4x4;		//!< \brief boolean matrix with 4 x 4 components. (From GLM_GTX_compatibility extension)

		typedef int							int1;			//!< \brief integer vector with 1 component. (From GLM_GTX_compatibility extension)
		typedef detail::tvec2<int>			int2;			//!< \brief integer vector with 2 components. (From GLM_GTX_compatibility extension)
		typedef detail::tvec3<int>			int3;			//!< \brief integer vector with 3 components. (From GLM_GTX_compatibility extension)
		typedef detail::tvec4<int>			int4;			//!< \brief integer vector with 4 components. (From GLM_GTX_compatibility extension)

		typedef int							int1x1;			//!< \brief integer matrix with 1 component. (From GLM_GTX_compatibility extension)
		typedef detail::tmat2x2<int>		int2x2;			//!< \brief integer matrix with 2 x 2 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat2x3<int>		int2x3;			//!< \brief integer matrix with 2 x 3 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat2x4<int>		int2x4;			//!< \brief integer matrix with 2 x 4 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat3x2<int>		int3x2;			//!< \brief integer matrix with 3 x 2 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat3x3<int>		int3x3;			//!< \brief integer matrix with 3 x 3 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat3x4<int>		int3x4;			//!< \brief integer matrix with 3 x 4 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat4x2<int>		int4x2;			//!< \brief integer matrix with 4 x 2 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat4x3<int>		int4x3;			//!< \brief integer matrix with 4 x 3 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat4x4<int>		int4x4;			//!< \brief integer matrix with 4 x 4 components. (From GLM_GTX_compatibility extension)

		typedef gtc::half_float::half						half1;			//!< \brief half-precision floating-point vector with 1 component. (From GLM_GTX_compatibility extension)
		typedef detail::tvec2<gtc::half_float::half>		half2;			//!< \brief half-precision floating-point vector with 2 components. (From GLM_GTX_compatibility extension)
		typedef detail::tvec3<gtc::half_float::half>		half3;			//!< \brief half-precision floating-point vector with 2 components. (From GLM_GTX_compatibility extension)
		typedef detail::tvec4<gtc::half_float::half>		half4;			//!< \brief half-precision floating-point vector with 2 components. (From GLM_GTX_compatibility extension)

		typedef gtc::half_float::half						half1x1;		//!< \brief half-precision floating-point matrix with 1 component. (From GLM_GTX_compatibility extension)
		typedef detail::tmat2x2<gtc::half_float::half>		half2x2;		//!< \brief half-precision floating-point matrix with 2 x 2 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat2x3<gtc::half_float::half>		half2x3;		//!< \brief half-precision floating-point matrix with 2 x 3 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat2x4<gtc::half_float::half>		half2x4;		//!< \brief half-precision floating-point matrix with 2 x 4 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat3x2<gtc::half_float::half>		half3x2;		//!< \brief half-precision floating-point matrix with 3 x 2 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat3x3<gtc::half_float::half>		half3x3;		//!< \brief half-precision floating-point matrix with 3 x 3 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat3x4<gtc::half_float::half>		half3x4;		//!< \brief half-precision floating-point matrix with 3 x 3 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat4x2<gtc::half_float::half>		half4x2;		//!< \brief half-precision floating-point matrix with 4 x 2 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat4x3<gtc::half_float::half>		half4x3;		//!< \brief half-precision floating-point matrix with 4 x 3 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat4x4<gtc::half_float::half>		half4x4;		//!< \brief half-precision floating-point matrix with 4 x 4 components. (From GLM_GTX_compatibility extension)

		typedef float						float1;			//!< \brief single-precision floating-point vector with 1 component. (From GLM_GTX_compatibility extension)
		typedef detail::tvec2<float>		float2;			//!< \brief single-precision floating-point vector with 2 components. (From GLM_GTX_compatibility extension)
		typedef detail::tvec3<float>		float3;			//!< \brief single-precision floating-point vector with 3 components. (From GLM_GTX_compatibility extension)
		typedef detail::tvec4<float>		float4;			//!< \brief single-precision floating-point vector with 4 components. (From GLM_GTX_compatibility extension)

		typedef float						float1x1;		//!< \brief single-precision floating-point matrix with 1 component. (From GLM_GTX_compatibility extension)
		typedef detail::tmat2x2<float>		float2x2;		//!< \brief single-precision floating-point matrix with 2 x 2 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat2x3<float>		float2x3;		//!< \brief single-precision floating-point matrix with 2 x 3 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat2x4<float>		float2x4;		//!< \brief single-precision floating-point matrix with 2 x 4 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat3x2<float>		float3x2;		//!< \brief single-precision floating-point matrix with 3 x 2 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat3x3<float>		float3x3;		//!< \brief single-precision floating-point matrix with 3 x 3 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat3x4<float>		float3x4;		//!< \brief single-precision floating-point matrix with 3 x 4 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat4x2<float>		float4x2;		//!< \brief single-precision floating-point matrix with 4 x 2 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat4x3<float>		float4x3;		//!< \brief single-precision floating-point matrix with 4 x 3 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat4x4<float>		float4x4;		//!< \brief single-precision floating-point matrix with 4 x 4 components. (From GLM_GTX_compatibility extension)

		typedef double						double1;		//!< \brief double-precision floating-point vector with 1 component. (From GLM_GTX_compatibility extension)
		typedef detail::tvec2<double>		double2;		//!< \brief double-precision floating-point vector with 2 components. (From GLM_GTX_compatibility extension)
		typedef detail::tvec3<double>		double3;		//!< \brief double-precision floating-point vector with 3 components. (From GLM_GTX_compatibility extension)
		typedef detail::tvec4<double>		double4;		//!< \brief double-precision floating-point vector with 4 components. (From GLM_GTX_compatibility extension)

		typedef double						double1x1;		//!< \brief double-precision floating-point matrix with 1 component. (From GLM_GTX_compatibility extension)
		typedef detail::tmat2x2<double>		double2x2;		//!< \brief double-precision floating-point matrix with 2 x 2 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat2x3<double>		double2x3;		//!< \brief double-precision floating-point matrix with 2 x 3 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat2x4<double>		double2x4;		//!< \brief double-precision floating-point matrix with 2 x 4 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat3x2<double>		double3x2;		//!< \brief double-precision floating-point matrix with 3 x 2 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat3x3<double>		double3x3;		//!< \brief double-precision floating-point matrix with 3 x 3 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat3x4<double>		double3x4;		//!< \brief double-precision floating-point matrix with 3 x 4 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat4x2<double>		double4x2;		//!< \brief double-precision floating-point matrix with 4 x 2 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat4x3<double>		double4x3;		//!< \brief double-precision floating-point matrix with 4 x 3 components. (From GLM_GTX_compatibility extension)
		typedef detail::tmat4x4<double>		double4x4;		//!< \brief double-precision floating-point matrix with 4 x 4 components. (From GLM_GTX_compatibility extension)

		///@}

	}//namespace compatibility
	}//namespace gtx
}//namespace glm

#include "compatibility.inl"

namespace glm{using namespace gtx::compatibility;}

#endif//glm_gtx_compatibility










