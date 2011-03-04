///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2009-05-07
// Updated : 2009-05-07
// Licence : This source is under MIT License
// File    : glm/gtx/simd_vec4.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
// - intrinsic
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_gtx_simd_mat4
#define glm_gtx_simd_mat4

// Dependency:
#include "../glm.hpp"

#if(GLM_ARCH & GLM_ARCH_SSE2)
#	include "../core/intrinsic_matrix.hpp"
#	include "../gtx/simd_vec4.hpp"
#else
#	error "GLM: GLM_GTX_simd_mat4 requires compiler support of SSE2 through intrinsics"
#endif

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_GTX_simd_mat4 extension included")
#endif

namespace glm
{
	namespace detail
	{
		/// 4x4 Matrix implemented using SIMD SEE intrinsics.
		/// \ingroup gtx_simd_mat4
		GLM_ALIGNED_STRUCT(16) fmat4x4SIMD
		{
			enum ctor{null};

			typedef float value_type;
			typedef fvec4SIMD col_type;
			typedef fvec4SIMD row_type;
			typedef std::size_t size_type;
			static size_type value_size();
			static size_type col_size();
			static size_type row_size();
			static bool is_matrix();

			fvec4SIMD Data[4];

			//////////////////////////////////////
			// Constructors

			fmat4x4SIMD();
			explicit fmat4x4SIMD(float const & s);
			explicit fmat4x4SIMD(
				float const & x0, float const & y0, float const & z0, float const & w0,
				float const & x1, float const & y1, float const & z1, float const & w1,
				float const & x2, float const & y2, float const & z2, float const & w2,
				float const & x3, float const & y3, float const & z3, float const & w3);
			explicit fmat4x4SIMD(
				fvec4SIMD const & v0,
				fvec4SIMD const & v1,
				fvec4SIMD const & v2,
				fvec4SIMD const & v3);
			explicit fmat4x4SIMD(
				tmat4x4<float> const & m);

			// Conversions
			//template <typename U> 
			//explicit tmat4x4(tmat4x4<U> const & m);

			//explicit tmat4x4(tmat2x2<T> const & x);
			//explicit tmat4x4(tmat3x3<T> const & x);
			//explicit tmat4x4(tmat2x3<T> const & x);
			//explicit tmat4x4(tmat3x2<T> const & x);
			//explicit tmat4x4(tmat2x4<T> const & x);
			//explicit tmat4x4(tmat4x2<T> const & x);
			//explicit tmat4x4(tmat3x4<T> const & x);
			//explicit tmat4x4(tmat4x3<T> const & x);

			// Accesses
			fvec4SIMD & operator[](size_type i);
			fvec4SIMD const & operator[](size_type i) const;

			// Unary updatable operators
			fmat4x4SIMD & operator= (fmat4x4SIMD const & m);
			fmat4x4SIMD & operator+= (float const & s);
			fmat4x4SIMD & operator+= (fmat4x4SIMD const & m);
			fmat4x4SIMD & operator-= (float const & s);
			fmat4x4SIMD & operator-= (fmat4x4SIMD const & m);
			fmat4x4SIMD & operator*= (float const & s);
			fmat4x4SIMD & operator*= (fmat4x4SIMD const & m);
			fmat4x4SIMD & operator/= (float const & s);
			fmat4x4SIMD & operator/= (fmat4x4SIMD const & m);
			fmat4x4SIMD & operator++ ();
			fmat4x4SIMD & operator-- ();
		};

		// Binary operators
		fmat4x4SIMD operator+ (fmat4x4SIMD const & m, float const & s);
		fmat4x4SIMD operator+ (float const & s, fmat4x4SIMD const & m);
		fmat4x4SIMD operator+ (fmat4x4SIMD const & m1, fmat4x4SIMD const & m2);
	    
		fmat4x4SIMD operator- (fmat4x4SIMD const & m, float const & s);
		fmat4x4SIMD operator- (float const & s, fmat4x4SIMD const & m);
		fmat4x4SIMD operator- (fmat4x4SIMD const & m1, fmat4x4SIMD const & m2);

		fmat4x4SIMD operator* (fmat4x4SIMD const & m, float const & s);
		fmat4x4SIMD operator* (float const & s, fmat4x4SIMD const & m);

		fvec4SIMD operator* (fmat4x4SIMD const & m, fvec4SIMD const & v);
		fvec4SIMD operator* (fvec4SIMD const & v, fmat4x4SIMD const & m);

		fmat4x4SIMD operator* (fmat4x4SIMD const & m1, fmat4x4SIMD const & m2);

		fmat4x4SIMD operator/ (fmat4x4SIMD const & m, float const & s);
		fmat4x4SIMD operator/ (float const & s, fmat4x4SIMD const & m);

		fvec4SIMD operator/ (fmat4x4SIMD const & m, fvec4SIMD const & v);
		fvec4SIMD operator/ (fvec4SIMD const & v, fmat4x4SIMD const & m);

		fmat4x4SIMD operator/ (fmat4x4SIMD const & m1, fmat4x4SIMD const & m2);

		// Unary constant operators
		fmat4x4SIMD const operator-  (fmat4x4SIMD const & m);
		fmat4x4SIMD const operator-- (fmat4x4SIMD const & m, int);
		fmat4x4SIMD const operator++ (fmat4x4SIMD const & m, int);

	}//namespace detail

	namespace gtx{
	//! GLM_GTX_simd_mat4 extension: SIMD implementation of mat4 type.
	namespace simd_mat4
	{
		typedef detail::fmat4x4SIMD simdMat4;

		/// \addtogroup gtx_simd_mat4
		///@{

		//! Convert a simdMat4 to a mat4.
		//! (From GLM_GTX_simd_mat4 extension)
		detail::tmat4x4<float> mat4_cast(
			detail::fmat4x4SIMD const & x);

		//! Multiply matrix x by matrix y component-wise, i.e.,
		//! result[i][j] is the scalar product of x[i][j] and y[i][j].
		//! (From GLM_GTX_simd_mat4 extension).
		detail::fmat4x4SIMD matrixCompMult(
			detail::fmat4x4SIMD const & x,
			detail::fmat4x4SIMD const & y);

		//! Treats the first parameter c as a column vector
		//! and the second parameter r as a row vector
		//! and does a linear algebraic matrix multiply c * r.
		//! (From GLM_GTX_simd_mat4 extension).
		detail::fmat4x4SIMD outerProduct(
			detail::fvec4SIMD const & c,
			detail::fvec4SIMD const & r);

		//! Returns the transposed matrix of x
		//! (From GLM_GTX_simd_mat4 extension).
		detail::fmat4x4SIMD transpose(
			detail::fmat4x4SIMD const & x);

		//! Return the determinant of a mat4 matrix.
		//! (From GLM_GTX_simd_mat4 extension).
		float determinant(
			detail::fmat4x4SIMD const & m);

		//! Return the inverse of a mat4 matrix.
		//! (From GLM_GTX_simd_mat4 extension).
		detail::fmat4x4SIMD inverse(
			detail::fmat4x4SIMD const & m);

		///@}

	}//namespace simd_mat4
	}//namespace gtx
}//namespace glm

#include "simd_mat4.inl"

namespace glm{using namespace gtx::simd_mat4;}

#endif//glm_gtx_simd_mat4
