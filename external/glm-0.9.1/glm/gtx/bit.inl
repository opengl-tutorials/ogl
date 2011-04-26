///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2007-03-14
// Updated : 2008-11-14
// Licence : This source is under MIT License
// File    : glm/gtx/bit.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "../core/_detail.hpp"

namespace glm{
namespace gtx{
namespace bit{

template <typename genIType>
inline genIType mask
(
	genIType const & count
)
{
	return ((genIType(1) << (count)) - genIType(1));
}

template <typename valIType>
inline detail::tvec2<valIType> mask
(
	detail::tvec2<valIType> const & count
)
{
	return detail::tvec2<valIType>(
		mask(count[0]),
		mask(count[1]));
}

template <typename valIType>
inline detail::tvec3<valIType> mask
(
	detail::tvec3<valIType> const & count
)
{
	return detail::tvec3<valIType>(
		mask(count[0]),
		mask(count[1]),
		mask(count[2]));
}

template <typename valIType>
inline detail::tvec4<valIType> mask
(
	detail::tvec4<valIType> const & count
)
{
	return detail::tvec4<valIType>(
		mask(count[0]),
		mask(count[1]),
		mask(count[2]),
		mask(count[3]));
}

// extractField
template <typename genIType>
inline genIType extractField
(
	gtc::half_float::half const & value, 
	genIType const & first, 
	genIType const & count
)
{
	assert(first + count < sizeof(gtc::half_float::half));
	return (value._data() << first) >> ((sizeof(gtc::half_float::half) << 3) - count);
}

template <typename genIType>
inline genIType extractField
(
	float const & value, 
	genIType const & first, 
	genIType const & count
)
{
	assert(first + count < sizeof(float));
	return (detail::uif32(value).i << first) >> ((sizeof(float) << 3) - count);
}

template <typename genIType>
inline genIType extractField
(
	double const & value, 
	genIType const & first, 
	genIType const & count
)
{
	assert(first + count < sizeof(double));
	return (detail::uif64(value).i << first) >> ((sizeof(double) << genIType(3)) - count);
}

template <typename genIUType, typename sizeType>
inline genIUType extractField
(
	genIUType const & Value, 
	sizeType const & First, 
	sizeType const & Count
)
{
	sizeType GenSize = sizeof(genIUType) << 3;

	assert(First + Count <= GenSize);

	genIUType ShiftLeft = Count ? Value << (GenSize - (Count + First)) : 0;
	genIUType ShiftBack = ShiftLeft >> genIUType(GenSize - Count);

	return ShiftBack;
}

template <typename genIUType, typename sizeType>
inline detail::tvec2<genIUType> extractField
(
	detail::tvec2<genIUType> const & value, 
	sizeType const & first, 
	sizeType const & count
)
{
	return detail::tvec2<genIUType>(
		extractField(value[0], first, count),
		extractField(value[1], first, count));
}

template <typename genIUType, typename sizeType>
inline detail::tvec3<genIUType> extractField
(
	detail::tvec3<genIUType> const & value, 
	sizeType const & first, 
	sizeType const & count
)
{
	return detail::tvec3<genIUType>(
		extractField(value[0], first, count),
		extractField(value[1], first, count),
		extractField(value[2], first, count));
}

template <typename genIUType, typename sizeType>
inline detail::tvec4<genIUType> extractField
(
	detail::tvec4<genIUType> const & value, 
	sizeType const & first, 
	sizeType const & count
)
{
	return detail::tvec4<genIUType>(
		extractField(value[0], first, count),
		extractField(value[1], first, count),
		extractField(value[2], first, count),
		extractField(value[3], first, count));
}

template <typename genIUType, typename sizeType>
inline detail::tvec2<genIUType> extractField
(
	detail::tvec2<genIUType> const & value, 
	detail::tvec2<sizeType> const & first, 
	detail::tvec2<sizeType> const & count
)
{
	return detail::tvec2<genIUType>(
		extractField(value[0], first[0], count[0]),
		extractField(value[1], first[1], count[1]));
}

template <typename genIUType, typename sizeType>
inline detail::tvec3<genIUType> extractField
(
	detail::tvec3<genIUType> const & value, 
	detail::tvec3<sizeType> const & first, 
	detail::tvec3<sizeType> const & count
)
{
	return detail::tvec3<genIUType>(
		extractField(value[0], first[0], count[0]),
		extractField(value[1], first[1], count[1]),
		extractField(value[2], first[2], count[2]));
}

template <typename genIUType, typename sizeType>
inline detail::tvec4<genIUType> extractField
(
	detail::tvec4<genIUType> const & value, 
	detail::tvec4<sizeType> const & first, 
	detail::tvec4<sizeType> const & count
)
{
	return detail::tvec4<genIUType>(
		extractField(value[0], first[0], count[0]),
		extractField(value[1], first[1], count[1]),
		extractField(value[2], first[2], count[2]),
		extractField(value[3], first[3], count[3]));
}

template <typename genIUType, typename sizeType>
inline detail::tvec2<genIUType> extractField
(
	genIUType const & value, 
	detail::tvec2<sizeType> const & first, 
	detail::tvec2<sizeType> const & count
)
{
	return detail::tvec2<genIUType>(
		extractField(value, first[0], count[0]),
		extractField(value, first[1], count[1]));
}

template <typename genIUType, typename sizeType>
inline detail::tvec3<genIUType> extractField
(
	genIUType const & value, 
	detail::tvec3<sizeType> const & first, 
	detail::tvec3<sizeType> const & count
)
{
	return detail::tvec3<genIUType>(
		extractField(value, first[0], count[0]),
		extractField(value, first[1], count[1]),
		extractField(value, first[2], count[2]));
}

template <typename genIUType, typename sizeType>
inline detail::tvec4<genIUType> extractField
(
	genIUType const & value, 
	detail::tvec4<sizeType> const & first, 
	detail::tvec4<sizeType> const & count
)
{
	return detail::tvec4<genIUType>(
		extractField(value, first[0], count[0]),
		extractField(value, first[1], count[1]),
		extractField(value, first[2], count[2]),
		extractField(value, first[3], count[3]));
}

// lowestBit
template <typename genType>
inline int lowestBit
(
	genType const & Value
)
{
	assert(Value != genType(0)); // not valid call

	genType Bit;
	for(Bit = genType(0); !(Value & (1 << Bit)); ++Bit){}
	return Bit;
}

template <typename valType>
inline detail::tvec2<int> lowestBit
(
	detail::tvec2<valType> const & value
)
{
	return detail::tvec2<int>(
		lowestBit(value[0]),
		lowestBit(value[1]));
}

template <typename valType>
inline detail::tvec3<int> lowestBit
(
	detail::tvec3<valType> const & value
)
{
	return detail::tvec3<int>(
		lowestBit(value[0]),
		lowestBit(value[1]),
		lowestBit(value[2]));
}

template <typename valType>
inline detail::tvec4<int> lowestBit
(
	detail::tvec4<valType> const & value
)
{
	return detail::tvec4<int>(
		lowestBit(value[0]),
		lowestBit(value[1]),
		lowestBit(value[2]),
		lowestBit(value[3]));
}

// highestBit
template <typename genType>
inline int highestBit
(
	genType const & value
)
{
	assert(value != genType(0)); // not valid call

	genType bit = genType(-1);
	for(genType tmp = value; tmp; tmp >>= 1, ++bit){}
	return bit;
}

//template <>
//inline int highestBit<int>
//(
//	int value
//)
//{
//	int bit = -1;
//	for(int tmp = value; tmp; tmp >>= 1, ++bit);
//	return bit;
//}

template <typename valType>
inline detail::tvec2<int> highestBit
(
	detail::tvec2<valType> const & value
)
{
	return detail::tvec2<int>(
		highestBit(value[0]),
		highestBit(value[1]));
}

template <typename valType>
inline detail::tvec3<int> highestBit
(
	detail::tvec3<valType> const & value
)
{
	return detail::tvec3<int>(
		highestBit(value[0]),
		highestBit(value[1]),
		highestBit(value[2]));
}

template <typename valType>
inline detail::tvec4<int> highestBit
(
	detail::tvec4<valType> const & value
)
{
	return detail::tvec4<int>(
		highestBit(value[0]),
		highestBit(value[1]),
		highestBit(value[2]),
		highestBit(value[3]));
}

// highestBitValue
template <typename genType>
inline genType highestBitValue
(
	genType const & value
)
{
	genType tmp = value;
	genType result = genType(0);
	while(tmp)
	{
		result = (tmp & (~tmp + 1)); // grab lowest bit
		tmp &= ~result; // clear lowest bit
	}
	return result;
}

template <typename valType>
inline detail::tvec2<int> highestBitValue
(
	detail::tvec2<valType> const & value
)
{
	return detail::tvec2<int>(
		highestBitValue(value[0]),
		highestBitValue(value[1]));
}

template <typename valType>
inline detail::tvec3<int> highestBitValue
(
	detail::tvec3<valType> const & value
)
{
	return detail::tvec3<int>(
		highestBitValue(value[0]),
		highestBitValue(value[1]),
		highestBitValue(value[2]));
}

template <typename valType>
inline detail::tvec4<int> highestBitValue
(
	detail::tvec4<valType> const & value
)
{
	return detail::tvec4<int>(
		highestBitValue(value[0]),
		highestBitValue(value[1]),
		highestBitValue(value[2]),
		highestBitValue(value[3]));
}

// isPowerOfTwo
template <typename genType>
inline bool isPowerOfTwo(genType const & Value)
{
	//detail::If<std::numeric_limits<genType>::is_signed>::apply(abs, Value);
	//return !(Value & (Value - 1));

    // For old complier?
	genType Result = Value;
	if(std::numeric_limits<genType>::is_signed)
		Result = abs(Result);
	return !(Result & (Result - 1));
}

template <typename valType>
inline detail::tvec2<bool> isPowerOfTwo
(
	detail::tvec2<valType> const & value
)
{
	return detail::tvec2<bool>(
		isPowerOfTwo(value[0]),
		isPowerOfTwo(value[1]));
}

template <typename valType>
inline detail::tvec3<bool> isPowerOfTwo
(
	detail::tvec3<valType> const & value
)
{
	return detail::tvec3<bool>(
		isPowerOfTwo(value[0]),
		isPowerOfTwo(value[1]),
		isPowerOfTwo(value[2]));
}

template <typename valType>
inline detail::tvec4<bool> isPowerOfTwo
(
	detail::tvec4<valType> const & value
)
{
	return detail::tvec4<bool>(
		isPowerOfTwo(value[0]),
		isPowerOfTwo(value[1]),
		isPowerOfTwo(value[2]),
		isPowerOfTwo(value[3]));
}

// powerOfTwoAbove
template <typename genType>
inline genType powerOfTwoAbove(genType const & value)
{
	return isPowerOfTwo(value) ? value : highestBitValue(value) << 1;
}

template <typename valType>
inline detail::tvec2<valType> powerOfTwoAbove
(
	detail::tvec2<valType> const & value
)
{
	return detail::tvec2<valType>(
		powerOfTwoAbove(value[0]),
		powerOfTwoAbove(value[1]));
}

template <typename valType>
inline detail::tvec3<valType> powerOfTwoAbove
(
	detail::tvec3<valType> const & value
)
{
	return detail::tvec3<valType>(
		powerOfTwoAbove(value[0]),
		powerOfTwoAbove(value[1]),
		powerOfTwoAbove(value[2]));
}

template <typename valType>
inline detail::tvec4<valType> powerOfTwoAbove
(
	detail::tvec4<valType> const & value
)
{
	return detail::tvec4<valType>(
		powerOfTwoAbove(value[0]),
		powerOfTwoAbove(value[1]),
		powerOfTwoAbove(value[2]),
		powerOfTwoAbove(value[3]));
}

// powerOfTwoBelow
template <typename genType>
inline genType powerOfTwoBelow
(
	genType const & value
)
{
	return isPowerOfTwo(value) ? value : highestBitValue(value);
}

template <typename valType>
inline detail::tvec2<valType> powerOfTwoBelow
(
	detail::tvec2<valType> const & value
)
{
	return detail::tvec2<valType>(
		powerOfTwoBelow(value[0]),
		powerOfTwoBelow(value[1]));
}

template <typename valType>
inline detail::tvec3<valType> powerOfTwoBelow
(
	detail::tvec3<valType> const & value
)
{
	return detail::tvec3<valType>(
		powerOfTwoBelow(value[0]),
		powerOfTwoBelow(value[1]),
		powerOfTwoBelow(value[2]));
}

template <typename valType>
inline detail::tvec4<valType> powerOfTwoBelow
(
	detail::tvec4<valType> const & value
)
{
	return detail::tvec4<valType>(
		powerOfTwoBelow(value[0]),
		powerOfTwoBelow(value[1]),
		powerOfTwoBelow(value[2]),
		powerOfTwoBelow(value[3]));
}

// powerOfTwoNearest
template <typename genType>
inline genType powerOfTwoNearest
(
	genType const & value
)
{
	if(isPowerOfTwo(value))
		return value;

	genType prev = highestBitValue(value);
	genType next = prev << 1;
	return (next - value) < (value - prev) ? next : prev;
}

template <typename valType>
inline detail::tvec2<valType> powerOfTwoNearest
(
	detail::tvec2<valType> const & value
)
{
	return detail::tvec2<valType>(
		powerOfTwoNearest(value[0]),
		powerOfTwoNearest(value[1]));
}

template <typename valType>
inline detail::tvec3<valType> powerOfTwoNearest
(
	detail::tvec3<valType> const & value
)
{
	return detail::tvec3<valType>(
		powerOfTwoNearest(value[0]),
		powerOfTwoNearest(value[1]),
		powerOfTwoNearest(value[2]));
}

template <typename valType>
inline detail::tvec4<valType> powerOfTwoNearest
(
	detail::tvec4<valType> const & value
)
{
	return detail::tvec4<valType>(
		powerOfTwoNearest(value[0]),
		powerOfTwoNearest(value[1]),
		powerOfTwoNearest(value[2]),
		powerOfTwoNearest(value[3]));
}

template <typename genType>
inline genType bitRevert(genType const & In)
{
	GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_integer, "'bitRevert' only accept integer values");

	genType Out = 0;
	std::size_t BitSize = sizeof(genType) * 8;
	for(std::size_t i = 0; i < BitSize; ++i)
		if(In & (1 << i))
			Out |= 1 << (BitSize - 1 - i);
	return Out;
}

template <typename valType>
inline detail::tvec2<valType> bitRevert
(
	detail::tvec2<valType> const & Value
)
{
	return detail::tvec2<valType>(
		bitRevert(Value[0]),
		bitRevert(Value[1]));
}

template <typename valType>
inline detail::tvec3<valType> bitRevert
(
	detail::tvec3<valType> const & Value
)
{
	return detail::tvec3<valType>(
		bitRevert(Value[0]),
		bitRevert(Value[1]),
		bitRevert(Value[2]));
}

template <typename valType>
inline detail::tvec4<valType> bitRevert
(
	detail::tvec4<valType> const & Value
)
{
	return detail::tvec4<valType>(
		bitRevert(Value[0]),
		bitRevert(Value[1]),
		bitRevert(Value[2]),
		bitRevert(Value[3]));
}

template <typename genType>
inline genType bitRotateRight(genType const & In, std::size_t Shift)
{
	GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_integer, "'bitRotateRight' only accept integer values");

	std::size_t BitSize = sizeof(genType) * 8;
	return (In << Shift) | (In >> (BitSize - Shift));
}

template <typename valType>
inline detail::tvec2<valType> bitRotateRight
(
	detail::tvec2<valType> const & Value, 
	std::size_t Shift
)
{
	return detail::tvec2<valType>(
		bitRotateRight(Value[0], Shift),
		bitRotateRight(Value[1], Shift));
}

template <typename valType>
inline detail::tvec3<valType> bitRotateRight
(
	detail::tvec3<valType> const & Value, 
	std::size_t Shift
)
{
	return detail::tvec3<valType>(
		bitRotateRight(Value[0], Shift),
		bitRotateRight(Value[1], Shift),
		bitRotateRight(Value[2], Shift));
}

template <typename valType>
inline detail::tvec4<valType> bitRotateRight
(
	detail::tvec4<valType> const & Value, 
	std::size_t Shift
)
{
	return detail::tvec4<valType>(
		bitRotateRight(Value[0], Shift),
		bitRotateRight(Value[1], Shift),
		bitRotateRight(Value[2], Shift),
		bitRotateRight(Value[3], Shift));
}

template <typename genType>
inline genType bitRotateLeft(genType const & In, std::size_t Shift)
{
	GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_integer, "'bitRotateLeft' only accept integer values");

	std::size_t BitSize = sizeof(genType) * 8;
	return (In >> Shift) | (In << (BitSize - Shift));
}

template <typename valType>
inline detail::tvec2<valType> bitRotateLeft
(
	detail::tvec2<valType> const & Value, 
	std::size_t Shift
)
{
	return detail::tvec2<valType>(
		bitRotateLeft(Value[0], Shift),
		bitRotateLeft(Value[1], Shift));
}

template <typename valType>
inline detail::tvec3<valType> bitRotateLeft
(
	detail::tvec3<valType> const & Value, 
	std::size_t Shift
)
{
	return detail::tvec3<valType>(
		bitRotateLeft(Value[0], Shift),
		bitRotateLeft(Value[1], Shift),
		bitRotateLeft(Value[2], Shift));
}

template <typename valType>
inline detail::tvec4<valType> bitRotateLeft
(
	detail::tvec4<valType> const & Value, 
	std::size_t Shift
)
{
	return detail::tvec4<valType>(
		bitRotateLeft(Value[0], Shift),
		bitRotateLeft(Value[1], Shift),
		bitRotateLeft(Value[2], Shift),
		bitRotateLeft(Value[3], Shift));
}

}//namespace bit
}//namespace gtx
}//namespace glm
