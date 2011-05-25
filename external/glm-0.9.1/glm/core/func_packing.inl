///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-03-17
// Updated : 2010-03-17
// Licence : This source is under MIT License
// File    : glm/core/func_packing.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	namespace detail
	{
		
	}//namespace detail

	namespace core{
	namespace function{
	namespace packing
	{
		inline detail::uint32 packUnorm2x16(detail::tvec2<detail::float32> const & v)
		{
			detail::uint16 A((detail::uint16)round(clamp(v.x, 0.0f, 1.0f) * 65535.0f));
			detail::uint16 B((detail::uint16)round(clamp(v.y, 0.0f, 1.0f) * 65535.0f));
			return detail::uint32((B << 16) | A);
		}

		inline detail::uint32 packUnorm4x8(detail::tvec4<detail::float32> const & v)
		{
			 detail::uint8 A((detail::uint8)round(clamp(v.x, 0.0f, 1.0f) * 255.0f));
			 detail::uint8 B((detail::uint8)round(clamp(v.y, 0.0f, 1.0f) * 255.0f));
			 detail::uint8 C((detail::uint8)round(clamp(v.z, 0.0f, 1.0f) * 255.0f));
			 detail::uint8 D((detail::uint8)round(clamp(v.w, 0.0f, 1.0f) * 255.0f));
			 return detail::uint32((D << 24) | (C << 16) | (B << 8) | A);
		}

		inline detail::uint32 packSnorm4x8(detail::tvec4<detail::float32> const & v)
		{
			 detail::uint8 A((detail::uint8)round(clamp(v.x,-1.0f, 1.0f) * 255.0f));
			 detail::uint8 B((detail::uint8)round(clamp(v.y,-1.0f, 1.0f) * 255.0f));
			 detail::uint8 C((detail::uint8)round(clamp(v.z,-1.0f, 1.0f) * 255.0f));
			 detail::uint8 D((detail::uint8)round(clamp(v.w,-1.0f, 1.0f) * 255.0f));
			 return detail::uint32((D << 24) | (C << 16) | (B << 8) | A);
		}

		inline detail::tvec2<detail::float32> unpackUnorm2x16(detail::uint32 const & p)
		{
			detail::uint16 A(detail::uint16(p >> 0));
			detail::uint16 B(detail::uint16(p >> 16));
			return detail::tvec2<detail::float32>(
				A * 1.0f / 65535.0f, 
				B * 1.0f / 65535.0f);
		}

		inline detail::tvec4<detail::float32> unpackUnorm4x8(detail::uint32 const & p)
		{
			detail::uint8 A(detail::uint8(p >> 0));
			detail::uint8 B(detail::uint8(p >> 8));
			detail::uint8 C(detail::uint8(p >> 16));
			detail::uint8 D(detail::uint8(p >> 24));
			return detail::tvec4<detail::float32>(
				A * 1.0f / 255.0f, 
				B * 1.0f / 255.0f,
				C * 1.0f / 255.0f,
				D * 1.0f / 255.0f);
		}

		inline detail::tvec4<detail::float32> unpackSnorm4x8(detail::uint32 const & p)
		{
			detail::uint8 A(detail::uint8(p >> 0));
			detail::uint8 B(detail::uint8(p >> 8));
			detail::uint8 C(detail::uint8(p >> 16));
			detail::uint8 D(detail::uint8(p >> 24));
			return clamp(detail::tvec4<detail::float32>(
				A * 1.0f / 127.0f, 
				B * 1.0f / 127.0f,
				C * 1.0f / 127.0f,
				D * 1.0f / 127.0f), -1.0f, 1.0f);
		}

		inline double packDouble2x32(detail::tvec2<detail::uint32> const & v)
		{
			return *(double*)&v;
		}

		inline detail::tvec2<detail::uint32> unpackDouble2x32(double const & v)
		{
			return *(detail::tvec2<detail::uint32>*)&v;
		}

	}//namespace packing
	}//namespace function
	}//namespace core
}//namespace glm
