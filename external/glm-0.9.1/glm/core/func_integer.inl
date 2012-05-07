///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2010-03-17
// Updated : 2010-03-31
// Licence : This source is under MIT License
// File    : glm/core/func_integer.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm
{
	namespace detail
	{
		
	}//namespace detail

	namespace core{
	namespace function{
	namespace integer
	{
		// uaddCarry
		template <typename genUType>
		inline genUType uaddCarry
		(
			genUType const & x, 
			genUType const & y, 
			genUType & Carry
		)
		{
			detail::highp_uint_t Value64 = detail::highp_uint_t(x) + detail::highp_uint_t(y);
			genUType Result = genUType(Value64 % (detail::highp_uint_t(1) << detail::highp_uint_t(32)));
			Carry = (Value64 % (detail::highp_uint_t(1) << detail::highp_uint_t(32))) > 1 ? 1 : 0;
			return Result;
		}

		template <typename T>
		inline detail::tvec2<T> uaddCarry
		(
			detail::tvec2<T> const & x, 
			detail::tvec2<T> const & y, 
			detail::tvec2<T> & Carry
		)
		{
			return detail::tvec2<T>(
				uaddCarry(x[0], y[0], Carry[0]),
				uaddCarry(x[1], y[1], Carry[1]));
		}

		template <typename T>
		inline detail::tvec3<T> uaddCarry
		(
			detail::tvec3<T> const & x, 
			detail::tvec3<T> const & y, 
			detail::tvec3<T> & Carry
		)
		{
			return detail::tvec3<T>(
				uaddCarry(x[0], y[0], Carry[0]),
				uaddCarry(x[1], y[1], Carry[1]),
				uaddCarry(x[2], y[2], Carry[2]));
		}

		template <typename T>
		inline detail::tvec4<T> uaddCarry
		(
			detail::tvec4<T> const & x, 
			detail::tvec4<T> const & y, 
			detail::tvec4<T> & Carry
		)
		{
			return detail::tvec4<T>(
				uaddCarry(x[0], y[0], Carry[0]),
				uaddCarry(x[1], y[1], Carry[1]),
				uaddCarry(x[2], y[2], Carry[2]),
				uaddCarry(x[3], y[3], Carry[3]));
		}

		// usubBorrow
		template <typename genUType>
		inline genUType usubBorrow
		(
			genUType const & x, 
			genUType const & y, 
			genUType & Borrow
		)
		{
			Borrow = x >= y ? 0 : 1;
			if(x > y)
				return genUType(detail::highp_int_t(x) - detail::highp_int_t(y));
			else
				return genUType(detail::highp_int_t(1) << detail::highp_int_t(32) + detail::highp_int_t(x) - detail::highp_int_t(y));
		}

		template <typename T>
		inline detail::tvec2<T> usubBorrow
		(
			detail::tvec2<T> const & x, 
			detail::tvec2<T> const & y, 
			detail::tvec2<T> & Borrow
		)
		{
			return detail::tvec2<T>(
				usubBorrow(x[0], y[0], Borrow[0]),
				usubBorrow(x[1], y[1], Borrow[1]));
		}

		template <typename T>
		inline detail::tvec3<T> usubBorrow
		(
			detail::tvec3<T> const & x, 
			detail::tvec3<T> const & y, 
			detail::tvec3<T> & Borrow
		)
		{
			return detail::tvec3<T>(
				usubBorrow(x[0], y[0], Borrow[0]),
				usubBorrow(x[1], y[1], Borrow[1]),
				usubBorrow(x[2], y[2], Borrow[2]));
		}

		template <typename T>
		inline detail::tvec4<T> usubBorrow
		(
			detail::tvec4<T> const & x, 
			detail::tvec4<T> const & y, 
			detail::tvec4<T> & Borrow
		)
		{
			return detail::tvec4<T>(
				usubBorrow(x[0], y[0], Borrow[0]),
				usubBorrow(x[1], y[1], Borrow[1]),
				usubBorrow(x[2], y[2], Borrow[2]),
				usubBorrow(x[3], y[3], Borrow[3]));
		}

		// umulExtended
		template <typename genUType>
		inline void umulExtended
		(
			genUType const & x, 
			genUType const & y, 
			genUType & msb, 
			genUType & lsb
		)
		{
			detail::highp_uint_t ValueX64 = x;
			detail::highp_uint_t ValueY64 = y;
			detail::highp_uint_t Value64 = ValueX64 * ValueY64;
			msb = *(genUType*)&genUType(Value64 & ((detail::highp_uint_t(1) << detail::highp_uint_t(32)) - detail::highp_uint_t(1)));
			lsb = *(genUType*)&genUType(Value64 >> detail::highp_uint_t(32));
		}

		template <typename T>
		inline detail::tvec2<T> umulExtended
		(
			detail::tvec2<T> const & x, 
			detail::tvec2<T> const & y, 
			detail::tvec2<T> & msb, 
			detail::tvec2<T> & lsb
		)
		{
			return detail::tvec2<T>(
				umulExtended(x[0], y[0], msb, lsb),
				umulExtended(x[1], y[1], msb, lsb));
		}

		template <typename T>
		inline detail::tvec3<T> umulExtended
		(
			detail::tvec3<T> const & x, 
			detail::tvec3<T> const & y, 
			detail::tvec3<T> & msb, 
			detail::tvec3<T> & lsb
		)
		{
			return detail::tvec3<T>(
				umulExtended(x[0], y[0], msb, lsb),
				umulExtended(x[1], y[1], msb, lsb),
				umulExtended(x[2], y[2], msb, lsb));
		}

		template <typename T>
		inline detail::tvec4<T> umulExtended
		(
			detail::tvec4<T> const & x, 
			detail::tvec4<T> const & y, 
			detail::tvec4<T> & msb, 
			detail::tvec4<T> & lsb
		)
		{
			return detail::tvec4<T>(
				umulExtended(x[0], y[0], msb, lsb),
				umulExtended(x[1], y[1], msb, lsb),
				umulExtended(x[2], y[2], msb, lsb),
				umulExtended(x[3], y[3], msb, lsb));
		}

		// imulExtended
		template <typename genIType>
		void imulExtended
		(
			genIType const & x, 
			genIType const & y, 
			genIType & msb, 
			genIType & lsb
		)
		{
			detail::highp_int_t ValueX64 = x;
			detail::highp_int_t ValueY64 = y;
			detail::highp_int_t Value64 = ValueX64 * ValueY64;
			msb = *(genIType*)&genIType(Value64 & ((detail::highp_uint_t(1) << detail::highp_uint_t(32)) - detail::highp_uint_t(1)));
			lsb = *(genIType*)&genIType(Value64 >> detail::highp_uint_t(32));
		}

		template <typename T>
		inline detail::tvec2<T> imulExtended
		(
			detail::tvec2<T> const & x, 
			detail::tvec2<T> const & y, 
			detail::tvec2<T> & msb, 
			detail::tvec2<T> & lsb
		)
		{
			return detail::tvec2<T>(
				imulExtended(x[0], y[0], msb, lsb),
				imulExtended(x[1], y[1], msb, lsb));
		}

		template <typename T>
		inline detail::tvec3<T> imulExtended
		(
			detail::tvec3<T> const & x, 
			detail::tvec3<T> const & y, 
			detail::tvec3<T> & msb, 
			detail::tvec3<T> & lsb
		)
		{
			return detail::tvec3<T>(
				imulExtended(x[0], y[0], msb, lsb),
				imulExtended(x[1], y[1], msb, lsb),
				imulExtended(x[2], y[2], msb, lsb));
		}

		template <typename T>
		inline detail::tvec4<T> imulExtended
		(
			detail::tvec4<T> const & x, 
			detail::tvec4<T> const & y, 
			detail::tvec4<T> & msb, 
			detail::tvec4<T> & lsb
		)
		{
			return detail::tvec4<T>(
				imulExtended(x[0], y[0], msb, lsb),
				imulExtended(x[1], y[1], msb, lsb),
				imulExtended(x[2], y[2], msb, lsb),
				imulExtended(x[3], y[3], msb, lsb));
		}

		// bitfieldExtract
		template <typename genIUType>
		genIUType bitfieldExtract
		(
			genIUType const & Value, 
			int const & Offset, 
			int const & Bits
		)
		{
			GLM_STATIC_ASSERT(std::numeric_limits<genIUType>::is_integer, "'bitfieldExtract' only accept integer values");
			assert(Offset + Bits <= sizeof(genIUType));

			genIUType Result = 0;
			if(std::numeric_limits<genIUType>::is_signed)
				Result |= (1 << (sizeof(genIUType) * 8 - 1)) & (1 << (Offset + Bits - 1));

			genIUType Mask = 0;
			for(std::size_t Bit = Offset; Bit < Bits; ++Bit)
				Mask |= (1 << Bit);

			return Result | ((Mask & Value) >> Offset);
		}

		template <typename T>
		inline detail::tvec2<T> bitfieldExtract
		(
			detail::tvec2<T> const & Value, 
			int const & Offset, 
			int const & Bits
		)
		{
			return detail::tvec2<T>(
				bitfieldExtract(Value[0]),
				bitfieldExtract(Value[1]));
		}

		template <typename T>
		inline detail::tvec3<T> bitfieldExtract
		(
			detail::tvec3<T> const & Value, 
			int const & Offset, 
			int const & Bits
		)
		{
			return detail::tvec3<T>(
				bitfieldExtract(Value[0]),
				bitfieldExtract(Value[1]),
				bitfieldExtract(Value[2]));
		}

		template <typename T>
		inline detail::tvec4<T> bitfieldExtract
		(
			detail::tvec4<T> const & Value, 
			int const & Offset, 
			int const & Bits
		)
		{
			return detail::tvec4<T>(
				bitfieldExtract(Value[0]),
				bitfieldExtract(Value[1]),
				bitfieldExtract(Value[2]),
				bitfieldExtract(Value[3]));
		}

		// bitfieldInsert
		template <typename genIUType>
		inline genIUType bitfieldInsert
		(
			genIUType const & Base, 
			genIUType const & Insert, 
			int const & Offset, 
			int const & Bits
		)
		{
			GLM_STATIC_ASSERT(std::numeric_limits<genIUType>::is_integer, "'bitfieldInsert' only accept integer values");
			assert(Offset + Bits <= sizeof(genIUType));

			if(Bits == 0)
				return Base;

			genIUType Mask = 0;
			for(std::size_t Bit = Offset; Bit < Offset + Bits; ++Bit)
				Mask |= (1 << Bit);

			return (Base & ~Mask) | (Insert & Mask);
		}

		template <typename T>
		inline detail::tvec2<T> bitfieldInsert
		(
			detail::tvec2<T> const & Base, 
			detail::tvec2<T> const & Insert, 
			int const & Offset, 
			int const & Bits
		)
		{
			return detail::tvec2<T>(
				bitfieldInsert(Base[0], Insert[0], Offset, Bits),
				bitfieldInsert(Base[1], Insert[1], Offset, Bits));
		}

		template <typename T>
		inline detail::tvec3<T> bitfieldInsert
		(
			detail::tvec3<T> const & Base, 
			detail::tvec3<T> const & Insert, 
			int const & Offset, 
			int const & Bits
		)
		{
			return detail::tvec3<T>(
				bitfieldInsert(Base[0], Insert[0], Offset, Bits),
				bitfieldInsert(Base[1], Insert[1], Offset, Bits),
				bitfieldInsert(Base[2], Insert[2], Offset, Bits));
		}

		template <typename T>
		inline detail::tvec4<T> bitfieldInsert
		(
			detail::tvec4<T> const & Base, 
			detail::tvec4<T> const & Insert, 
			int const & Offset, 
			int const & Bits
		)
		{
			return detail::tvec4<T>(
				bitfieldInsert(Base[0], Insert[0], Offset, Bits),
				bitfieldInsert(Base[1], Insert[1], Offset, Bits),
				bitfieldInsert(Base[2], Insert[2], Offset, Bits),
				bitfieldInsert(Base[3], Insert[3], Offset, Bits));
		}

		// bitfieldReverse
		template <typename genIUType>
		inline genIUType bitfieldReverse(genIUType const & Value)
		{
			GLM_STATIC_ASSERT(std::numeric_limits<genIUType>::is_integer, "'bitfieldReverse' only accept integer values");

			genIUType Result = 0;
			for(std::size_t i = 0; i < sizeof(genIUType) * std::size_t(8); ++i)
				if(Value & (1 << i))
					Result |= (genIUType(1) << (sizeof(genIUType) * std::size_t(8)) - genIUType(1) - i);
			return Result;
		}	

		template <typename T>
		inline detail::tvec2<T> bitfieldReverse
		(
			detail::tvec2<T> const & value
		)
		{
			return detail::tvec2<T>(
				bitfieldReverse(value[0]),
				bitfieldReverse(value[1]));
		}

		template <typename T>
		inline detail::tvec3<T> bitfieldReverse
		(
			detail::tvec3<T> const & value
		)
		{
			return detail::tvec3<T>(
				bitfieldReverse(value[0]),
				bitfieldReverse(value[1]),
				bitfieldReverse(value[2]));
		}

		template <typename T>
		inline detail::tvec4<T> bitfieldReverse
		(
			detail::tvec4<T> const & value
		)
		{
			return detail::tvec4<T>(
				bitfieldReverse(value[0]),
				bitfieldReverse(value[1]),
				bitfieldReverse(value[2]),
				bitfieldReverse(value[3]));
		}

		// bitCount
		template <typename genIUType>
		int bitCount(genIUType const & Value)
		{
			GLM_STATIC_ASSERT(std::numeric_limits<genIUType>::is_integer, "'bitCount' only accept integer values");

			int Count = 0;
			for(std::size_t i = 0; i < sizeof(genIUType) * std::size_t(8); ++i)
			{
				if(Value & (1 << i))
					++Count;
			}
			return Count;
		}

		template <typename T>
		inline detail::tvec2<int> bitCount
		(
			detail::tvec2<T> const & value
		)
		{
			return detail::tvec2<int>(
				bitCount(value[0]),
				bitCount(value[1]));
		}

		template <typename T>
		inline detail::tvec3<int> bitCount
		(
			detail::tvec3<T> const & value
		)
		{
			return detail::tvec3<int>(
				bitCount(value[0]),
				bitCount(value[1]),
				bitCount(value[2]));
		}

		template <typename T>
		inline detail::tvec4<int> bitCount
		(
			detail::tvec4<T> const & value
		)
		{
			return detail::tvec4<int>(
				bitCount(value[0]),
				bitCount(value[1]),
				bitCount(value[2]),
				bitCount(value[3]));
		}

		// findLSB
		template <typename genIUType>
		inline int findLSB
		(
			genIUType const & Value
		)
		{
			GLM_STATIC_ASSERT(std::numeric_limits<genIUType>::is_integer, "'findLSB' only accept integer values");
			if(Value == 0)
				return -1;

			genIUType Bit;
			for(Bit = genIUType(0); !(Value & (1 << Bit)); ++Bit){}
			return Bit;
		}

		template <typename T>
		inline detail::tvec2<int> findLSB
		(
			detail::tvec2<T> const & value
		)
		{
			return detail::tvec2<int>(
				findLSB(value[0]),
				findLSB(value[1]));
		}

		template <typename T>
		inline detail::tvec3<int> findLSB
		(
			detail::tvec3<T> const & value
		)
		{
			return detail::tvec3<int>(
				findLSB(value[0]),
				findLSB(value[1]),
				findLSB(value[2]));
		}

		template <typename T>
		inline detail::tvec4<int> findLSB
		(
			detail::tvec4<T> const & value
		)
		{
			return detail::tvec4<int>(
				findLSB(value[0]),
				findLSB(value[1]),
				findLSB(value[2]),
				findLSB(value[3]));
		}

		// findMSB
		template <typename genIUType>
		inline int findMSB
		(
			genIUType const & Value
		)
		{
			GLM_STATIC_ASSERT(std::numeric_limits<genIUType>::is_integer, "'findMSB' only accept integer values");
			if(Value == 0)
				return -1;

			genIUType bit = genIUType(-1);
			for(genIUType tmp = Value; tmp; tmp >>= 1, ++bit){}
			return bit;
		}

		template <typename T>
		inline detail::tvec2<int> findMSB
		(
			detail::tvec2<T> const & value
		)
		{
			return detail::tvec2<int>(
				findMSB(value[0]),
				findMSB(value[1]));
		}

		template <typename T>
		inline detail::tvec3<int> findMSB
		(
			detail::tvec3<T> const & value
		)
		{
			return detail::tvec3<int>(
				findMSB(value[0]),
				findMSB(value[1]),
				findMSB(value[2]));
		}

		template <typename T>
		inline detail::tvec4<int> findMSB
		(
			detail::tvec4<T> const & value
		)
		{
			return detail::tvec4<int>(
				findMSB(value[0]),
				findMSB(value[1]),
				findMSB(value[2]),
				findMSB(value[3]));
		}

	}//namespace integer
	}//namespace function
	}//namespace core
}//namespace glm
