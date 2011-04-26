///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-08-17
// Updated : 2009-11-12
// Licence : This source is under MIT License
// File    : glm/core/type_half.inl
///////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright:
// This half implementation is based on OpenEXR which is Copyright (c) 2002, 
// Industrial Light & Magic, a division of Lucas Digital Ltd. LLC
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "_detail.hpp"

namespace glm{
namespace detail
{
	inline float overflow()
	{
		volatile float f = 1e10;

		for(int i = 0; i < 10; ++i)	
			f *= f;             // this will overflow before
								// the for­loop terminates
		return f;
	}

	inline float toFloat32(hdata value)
	{
		int s = (value >> 15) & 0x00000001;
		int e = (value >> 10) & 0x0000001f;
		int m =  value        & 0x000003ff;

		if(e == 0)
		{
			if(m == 0)
			{
				//
				// Plus or minus zero
				//

				detail::uif result;
				result.i = s << 31;
				return result.f;
			}
			else
			{
				//
				// Denormalized number -- renormalize it
				//

				while(!(m & 0x00000400))
				{
					m <<= 1;
					e -=  1;
				}

				e += 1;
				m &= ~0x00000400;
			}
		}
		else if(e == 31)
		{
			if(m == 0)
			{
				//
				// Positive or negative infinity
				//

				uif result;
				result.i = (s << 31) | 0x7f800000;
				return result.f;
			}
			else
			{
				//
				// Nan -- preserve sign and significand bits
				//

				uif result;
				result.i = (s << 31) | 0x7f800000 | (m << 13);
				return result.f;
			}
		}

		//
		// Normalized number
		//

		e = e + (127 - 15);
		m = m << 13;

		//
		// Assemble s, e and m.
		//

		uif Result;
		Result.i = (s << 31) | (e << 23) | m;
		return Result.f;
	}

	inline hdata toFloat16(float const & f)
	{
		uif Entry;
		Entry.f = f;
		int i = Entry.i;

		//
		// Our floating point number, f, is represented by the bit
		// pattern in integer i.  Disassemble that bit pattern into
		// the sign, s, the exponent, e, and the significand, m.
		// Shift s into the position where it will go in in the
		// resulting half number.
		// Adjust e, accounting for the different exponent bias
		// of float and half (127 versus 15).
		//

		register int s =  (i >> 16) & 0x00008000;
		register int e = ((i >> 23) & 0x000000ff) - (127 - 15);
		register int m =   i        & 0x007fffff;

		//
		// Now reassemble s, e and m into a half:
		//

		if(e <= 0)
		{
			if(e < -10)
			{
				//
				// E is less than -10.  The absolute value of f is
				// less than half_MIN (f may be a small normalized
				// float, a denormalized float or a zero).
				//
				// We convert f to a _halfGTX zero.
				//

				return 0;
			}

			//
			// E is between -10 and 0.  F is a normalized float,
			// whose magnitude is less than __half_NRM_MIN.
			//
			// We convert f to a denormalized _halfGTX.
			// 

			m = (m | 0x00800000) >> (1 - e);

			//
			// Round to nearest, round "0.5" up.
			//
			// Rounding may cause the significand to overflow and make
			// our number normalized.  Because of the way a half's bits
			// are laid out, we don't have to treat this case separately;
			// the code below will handle it correctly.
			// 

			if(m & 0x00001000) 
				m += 0x00002000;

			//
			// Assemble the _halfGTX from s, e (zero) and m.
			//

			return hdata(s | (m >> 13));
		}
		else if(e == 0xff - (127 - 15))
		{
			if(m == 0)
			{
				//
				// F is an infinity; convert f to a half
				// infinity with the same sign as f.
				//

				return hdata(s | 0x7c00);
			}
			else
			{
				//
				// F is a NAN; we produce a half NAN that preserves
				// the sign bit and the 10 leftmost bits of the
				// significand of f, with one exception: If the 10
				// leftmost bits are all zero, the NAN would turn 
				// into an infinity, so we have to set at least one
				// bit in the significand.
				//

				m >>= 13;

				return hdata(s | 0x7c00 | m | (m == 0));
			}
		}
		else
		{
			//
			// E is greater than zero.  F is a normalized float.
			// We try to convert f to a normalized half.
			//

			//
			// Round to nearest, round "0.5" up
			//

			if(m &  0x00001000)
			{
				m += 0x00002000;

				if(m & 0x00800000)
				{
					m =  0;     // overflow in significand,
					e += 1;     // adjust exponent
				}
			}

			//
			// Handle exponent overflow
			//

			if (e > 30)
			{
				overflow();        // Cause a hardware floating point overflow;

				return hdata(s | 0x7c00);
				// if this returns, the half becomes an
			}   // infinity with the same sign as f.

			//
			// Assemble the half from s, e and m.
			//

			return hdata(s | (e << 10) | (m >> 13));
		}
	}

	inline thalf::thalf() :
		data(0)
	{}

	inline thalf::thalf(thalf const & s) :
		data(s.data)
	{}

	template <typename U>
	inline thalf::thalf(U const & s) :
		data(toFloat16(float(s)))
	{}

	// Cast
	//inline half::operator float()
	//{
	//	return toFloat();
	//}

	inline thalf::operator float() const 
	{
		return toFloat();
	}

	//inline half::operator double()
	//{
	//	return double(toFloat());
	//}

	//inline half::operator double() const
	//{
	//	return double(toFloat());
	//}

	// Unary updatable operators
	inline thalf& thalf::operator= (thalf const & s)
	{
		data = s.data;
		return *this;
	}

	inline thalf& thalf::operator+=(thalf const & s)
	{
		data = toFloat16(toFloat32(data) + toFloat32(s.data));
		return *this;
	}

	inline thalf& thalf::operator-=(thalf const & s)
	{
		data = toFloat16(toFloat32(data) - toFloat32(s.data));
		return *this;
	}

	inline thalf& thalf::operator*=(thalf const & s)
	{
		data = toFloat16(toFloat32(data) * toFloat32(s.data));		
		return *this;
	}

	inline thalf& thalf::operator/=(thalf const & s)
	{
		data = toFloat16(toFloat32(data) / toFloat32(s.data));
		return *this;
	}

	inline thalf& thalf::operator++()
	{
		float Casted = toFloat32(data);
		data = toFloat16(++Casted);
		return *this;
	}

	inline thalf& thalf::operator--()
	{
		float Casted = toFloat32(data);
		data = toFloat16(--Casted);
		return *this;
	}

	//////////////////////////////////////
	// Binary arithmetic operators

	inline detail::thalf operator+ (detail::thalf const & s1, detail::thalf const & s2)
	{
		return detail::thalf(float(s1) + float(s2));
	}

	inline detail::thalf operator- (detail::thalf const & s1, detail::thalf const & s2)
	{
		return detail::thalf(float(s1) - float(s2));
	}

	inline detail::thalf operator* (detail::thalf const & s1, detail::thalf const & s2)
	{
		return detail::thalf(float(s1) * float(s2));
	}

	inline detail::thalf operator/ (detail::thalf const & s1, detail::thalf const & s2)
	{
		return detail::thalf(float(s1) / float(s2));
	}

	// Unary constant operators
	inline detail::thalf operator- (detail::thalf const & s)
	{
		return detail::thalf(-float(s));
	}

	inline detail::thalf operator-- (detail::thalf const & s, int)
	{
		return detail::thalf(float(s) - 1.0f);
	}

	inline detail::thalf operator++ (detail::thalf const & s, int)
	{
		return detail::thalf(float(s) + 1.0f);
	}

}//namespace detail
}//namespace glm
