///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2007-06-21
// Updated : 2007-08-03
// Licence : This source is under MIT License
// File    : glm/gtx/color_cast.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtx{
//! GLM_GTX_color_cast extension: Conversion between two color types
namespace color_cast{

template <typename T> 
inline gtc::type_precision::uint8 u8channel_cast(T a)
{
	return static_cast<gtc::type_precision::uint8>(a * T(255));
}

template <typename T> 
inline gtc::type_precision::uint16 u16channel_cast(T a)
{
	return static_cast<gtc::type_precision::uint16>(a * T(65535));
}

template <typename T>
inline gtc::type_precision::uint32 u32_rgbx_cast(const detail::tvec3<T>& c)
{
	gtc::type_precision::uint32 result = 0;
	result += static_cast<gtc::type_precision::uint32>(c.x * detail::tvec3<T>::value_type(255)) <<  0;
	result += static_cast<gtc::type_precision::uint32>(c.y * detail::tvec3<T>::value_type(255)) <<  8;
	result += static_cast<gtc::type_precision::uint32>(c.z * detail::tvec3<T>::value_type(255)) << 16;
	return result;
}

template <typename T>
inline gtc::type_precision::uint32 u32_xrgb_cast(const detail::tvec3<T>& c)
{
	gtc::type_precision::uint32 result = 0;
    result += static_cast<gtc::type_precision::uint32>(c.x * detail::tvec3<T>::value_type(255)) <<  8;
	result += static_cast<gtc::type_precision::uint32>(c.y * detail::tvec3<T>::value_type(255)) << 16;
	result += static_cast<gtc::type_precision::uint32>(c.z * detail::tvec3<T>::value_type(255)) << 24;
	return result;
}

template <typename T>
inline gtc::type_precision::uint32 u32_bgrx_cast(const detail::tvec3<T>& c)
{
	gtc::type_precision::uint32 result = 0;
	result += static_cast<gtc::type_precision::uint32>(c.x * detail::tvec3<T>::value_type(255)) << 16;
	result += static_cast<gtc::type_precision::uint32>(c.y * detail::tvec3<T>::value_type(255)) <<  8;
	result += static_cast<gtc::type_precision::uint32>(c.z * detail::tvec3<T>::value_type(255)) <<  0;
	return result;
}

template <typename T>
inline gtc::type_precision::uint32 u32_xbgr_cast(const detail::tvec3<T>& c)
{
	gtc::type_precision::uint32 result = 0;
	result += static_cast<gtc::type_precision::uint32>(c.x * detail::tvec3<T>::value_type(255)) << 24;
	result += static_cast<gtc::type_precision::uint32>(c.y * detail::tvec3<T>::value_type(255)) << 16;
	result += static_cast<gtc::type_precision::uint32>(c.z * detail::tvec3<T>::value_type(255)) <<  8;
	result += static_cast<gtc::type_precision::uint32>(c.w * detail::tvec3<T>::value_type(255)) <<  0;
	return result;
}

template <typename T>
inline gtc::type_precision::uint32 u32_rgba_cast(const detail::tvec4<T>& c)
{
	gtc::type_precision::uint32 result = 0;
	result += static_cast<gtc::type_precision::uint32>(c.x * detail::tvec4<T>::value_type(255)) <<  0;
	result += static_cast<gtc::type_precision::uint32>(c.y * detail::tvec4<T>::value_type(255)) <<  8;
	result += static_cast<gtc::type_precision::uint32>(c.z * detail::tvec4<T>::value_type(255)) << 16;
	result += static_cast<gtc::type_precision::uint32>(c.w * detail::tvec4<T>::value_type(255)) << 24;
	return result;
}

template <typename T>
inline gtc::type_precision::uint32 u32_argb_cast(const detail::tvec4<T>& c)
{
	gtc::type_precision::uint32 result = 0;
	result += static_cast<gtc::type_precision::uint32>(c.x * detail::tvec4<T>::value_type(255)) <<  8;
	result += static_cast<gtc::type_precision::uint32>(c.y * detail::tvec4<T>::value_type(255)) << 16;
	result += static_cast<gtc::type_precision::uint32>(c.z * detail::tvec4<T>::value_type(255)) << 24;
	result += static_cast<gtc::type_precision::uint32>(c.w * detail::tvec4<T>::value_type(255)) <<  0;
	return result;
}

template <typename T>
inline gtc::type_precision::uint32 u32_bgra_cast(const detail::tvec4<T>& c)
{
	gtc::type_precision::uint32 result = 0;
	result += static_cast<gtc::type_precision::uint32>(c.x * detail::tvec4<T>::value_type(255)) << 16;
	result += static_cast<gtc::type_precision::uint32>(c.y * detail::tvec4<T>::value_type(255)) <<  8;
	result += static_cast<gtc::type_precision::uint32>(c.z * detail::tvec4<T>::value_type(255)) <<  0;
	result += static_cast<gtc::type_precision::uint32>(c.w * detail::tvec4<T>::value_type(255)) << 24;
	return result;
}

template <typename T>
inline gtc::type_precision::uint32 u32_abgr_cast(const detail::tvec4<T>& c)
{
	gtc::type_precision::uint32 result = 0;
	result += static_cast<gtc::type_precision::uint32>(c.x * detail::tvec4<T>::value_type(255)) << 24;
	result += static_cast<gtc::type_precision::uint32>(c.y * detail::tvec4<T>::value_type(255)) << 16;
	result += static_cast<gtc::type_precision::uint32>(c.z * detail::tvec4<T>::value_type(255)) <<  8;
	result += static_cast<gtc::type_precision::uint32>(c.w * detail::tvec4<T>::value_type(255)) <<  0;
	return result;
}

template <typename T>
inline gtc::type_precision::uint64 u64_rgbx_cast(const detail::tvec3<T>& c)
{
	gtc::type_precision::uint64 result = 0;
	result += static_cast<gtc::type_precision::uint64>(c.x * detail::tvec3<T>::value_type(65535)) <<  0;
	result += static_cast<gtc::type_precision::uint64>(c.y * detail::tvec3<T>::value_type(65535)) << 16;
	result += static_cast<gtc::type_precision::uint64>(c.z * detail::tvec3<T>::value_type(65535)) << 32;
	return result;
}

template <typename T>
inline gtc::type_precision::uint64 u32_xrgb_cast(const detail::tvec3<T>& c)
{
	gtc::type_precision::uint64 result = 0;
	result += static_cast<gtc::type_precision::uint64>(c.x * detail::tvec3<T>::value_type(65535)) << 16;
	result += static_cast<gtc::type_precision::uint64>(c.y * detail::tvec3<T>::value_type(65535)) << 32;
	result += static_cast<gtc::type_precision::uint64>(c.z * detail::tvec3<T>::value_type(65535)) << 48;
	return result;
}

template <typename T>
inline gtc::type_precision::uint64 u32_bgrx_cast(const detail::tvec3<T>& c)
{
	gtc::type_precision::uint64 result = 0;
	result += static_cast<gtc::type_precision::uint64>(c.x * detail::tvec3<T>::value_type(65535)) << 32;
	result += static_cast<gtc::type_precision::uint64>(c.y * detail::tvec3<T>::value_type(65535)) << 16;
	result += static_cast<gtc::type_precision::uint64>(c.z * detail::tvec3<T>::value_type(65535)) <<  0;
	return result;
}

template <typename T>
inline gtc::type_precision::uint64 u32_xbgr_cast(const detail::tvec3<T>& c)
{
	gtc::type_precision::uint64 result = 0;
	result += static_cast<gtc::type_precision::uint64>(c.x * detail::tvec3<T>::value_type(65535)) << 48;
	result += static_cast<gtc::type_precision::uint64>(c.y * detail::tvec3<T>::value_type(65535)) << 32;
	result += static_cast<gtc::type_precision::uint64>(c.z * detail::tvec3<T>::value_type(65535)) << 16;
	result += static_cast<gtc::type_precision::uint64>(c.w * detail::tvec3<T>::value_type(65535)) <<  0;
	return result;
}

template <typename T>
inline gtc::type_precision::uint64 u64_rgba_cast(const detail::tvec4<T>& c)
{
	gtc::type_precision::uint64 result = 0;
	result += static_cast<gtc::type_precision::uint64>(c.x * detail::tvec4<T>::value_type(65535)) <<  0;
	result += static_cast<gtc::type_precision::uint64>(c.y * detail::tvec4<T>::value_type(65535)) << 16;
	result += static_cast<gtc::type_precision::uint64>(c.z * detail::tvec4<T>::value_type(65535)) << 32;
	result += static_cast<gtc::type_precision::uint64>(c.w * detail::tvec4<T>::value_type(65535)) << 48;
	return result;
}

template <typename T>
inline gtc::type_precision::uint64 u64_argb_cast(const detail::tvec4<T>& c)
{
	gtc::type_precision::uint64 result = 0;
	result += static_cast<gtc::type_precision::uint64>(c.x * detail::tvec4<T>::value_type(65535)) << 16;
	result += static_cast<gtc::type_precision::uint64>(c.y * detail::tvec4<T>::value_type(65535)) << 32;
	result += static_cast<gtc::type_precision::uint64>(c.z * detail::tvec4<T>::value_type(65535)) << 48;
	result += static_cast<gtc::type_precision::uint64>(c.w * detail::tvec4<T>::value_type(65535)) <<  0;
	return result;
}

template <typename T>
inline gtc::type_precision::uint64 u64_bgra_cast(const detail::tvec4<T>& c)
{
	gtc::type_precision::uint64 result = 0;
	result += static_cast<gtc::type_precision::uint64>(c.x * detail::tvec4<T>::value_type(65535)) << 32;
	result += static_cast<gtc::type_precision::uint64>(c.y * detail::tvec4<T>::value_type(65535)) << 16;
	result += static_cast<gtc::type_precision::uint64>(c.z * detail::tvec4<T>::value_type(65535)) <<  0;
	result += static_cast<gtc::type_precision::uint64>(c.w * detail::tvec4<T>::value_type(65535)) << 48;
	return result;
}

template <typename T>
inline gtc::type_precision::uint64 u64_abgr_cast(const detail::tvec4<T>& c)
{
	gtc::type_precision::uint64 result = 0;
	result += static_cast<gtc::type_precision::uint64>(c.x * detail::tvec4<T>::value_type(65535)) << 48;
	result += static_cast<gtc::type_precision::uint64>(c.y * detail::tvec4<T>::value_type(65535)) << 32;
	result += static_cast<gtc::type_precision::uint64>(c.z * detail::tvec4<T>::value_type(65535)) << 16;
	result += static_cast<gtc::type_precision::uint64>(c.w * detail::tvec4<T>::value_type(65535)) <<  0;
	return result;
}

template <>
inline f16vec1 f16_channel_cast<gtc::type_precision::uint32>(gtc::type_precision::uint32 color)
{
	return gtc::type_precision::f16(static_cast<float>(color >>  0) / static_cast<float>(255));
}

template <>
inline gtc::type_precision::f16vec3 f16_rgbx_cast<gtc::type_precision::uint32>(gtc::type_precision::uint32 color)
{
	gtc::type_precision::f16vec3 result;
	result.x = gtc::type_precision::f16(static_cast<float>(color >>  0) / static_cast<float>(255));
	result.y = gtc::type_precision::f16(static_cast<float>(color >>  8) / static_cast<float>(255));
	result.z = gtc::type_precision::f16(static_cast<float>(color >> 16) / static_cast<float>(255));
	return result;
}

template <>
inline gtc::type_precision::f16vec3 f16_xrgb_cast<gtc::type_precision::uint32>(gtc::type_precision::uint32 color)
{
	gtc::type_precision::f16vec3 result;
	result.x = gtc::type_precision::f16(static_cast<float>(color >>  8) / static_cast<float>(255));
	result.y = gtc::type_precision::f16(static_cast<float>(color >> 16) / static_cast<float>(255));
	result.z = gtc::type_precision::f16(static_cast<float>(color >> 24) / static_cast<float>(255));
	return result;
}

template <>
inline f16vec3 f16_bgrx_cast<uint32>(uint32 color)
{
	f16vec3 result;
	result.x = f16(static_cast<float>(color >> 16) / static_cast<float>(255));
	result.y = f16(static_cast<float>(color >>  8) / static_cast<float>(255));
	result.z = f16(static_cast<float>(color >>  0) / static_cast<float>(255));
	return result;
}

template <>
inline f16vec3 f16_xbgr_cast<uint32>(uint32 color)
{
	f16vec3 result;
	result.x = f16(static_cast<float>(color >> 24) / static_cast<float>(255));
	result.y = f16(static_cast<float>(color >> 16) / static_cast<float>(255));
	result.z = f16(static_cast<float>(color >>  8) / static_cast<float>(255));
	return result;
}

template <>
inline f16vec4 f16_rgba_cast<uint32>(uint32 color)
{
	f16vec4 result;
	result.x = f16(static_cast<float>(color >>  0) / static_cast<float>(255));
	result.y = f16(static_cast<float>(color >>  8) / static_cast<float>(255));
	result.z = f16(static_cast<float>(color >> 16) / static_cast<float>(255));
	result.w = f16(static_cast<float>(color >> 24) / static_cast<float>(255));
	return result;
}

template <>
inline f16vec4 f16_argb_cast<uint32>(uint32 color)
{
	f16vec4 result;
	result.x = f16(static_cast<float>(color >>  8) / static_cast<float>(255));
	result.y = f16(static_cast<float>(color >> 16) / static_cast<float>(255));
	result.z = f16(static_cast<float>(color >> 24) / static_cast<float>(255));
	result.w = f16(static_cast<float>(color >>  0) / static_cast<float>(255));
	return result;
}

template <>
inline f16vec4 f16_bgra_cast<uint32>(uint32 color)
{
	f16vec4 result;
	result.x = f16(static_cast<float>(color >> 16) / static_cast<float>(255));
	result.y = f16(static_cast<float>(color >>  8) / static_cast<float>(255));
	result.z = f16(static_cast<float>(color >>  0) / static_cast<float>(255));
	result.w = f16(static_cast<float>(color >> 24) / static_cast<float>(255));
	return result;
}

template <>
inline f16vec4 f16_abgr_cast<uint32>(uint32 color)
{
	f16vec4 result;
	result.x = f16(static_cast<float>(color >> 24) / static_cast<float>(255));
	result.y = f16(static_cast<float>(color >> 16) / static_cast<float>(255));
	result.z = f16(static_cast<float>(color >>  8) / static_cast<float>(255));
	result.w = f16(static_cast<float>(color >>  0) / static_cast<float>(255));
	return result;
}

template <>
inline float f32_channel_cast<uint8>(uint8 color)
{
	return static_cast<float>(color >>  0) / static_cast<float>(255);
}

template <>
inline detail::tvec3<float> f32_rgbx_cast<uint32>(uint32 color)
{
	detail::tvec3<float> result;
	result.x = static_cast<float>(color >>  0) / static_cast<float>(255);
	result.y = static_cast<float>(color >>  8) / static_cast<float>(255);
	result.z = static_cast<float>(color >> 16) / static_cast<float>(255);
	return result;
}

template <>
inline detail::tvec3<float> f32_xrgb_cast<uint32>(uint32 color)
{
	detail::tvec3<float> result;
	result.x = static_cast<float>(color >>  8) / static_cast<float>(255);
	result.y = static_cast<float>(color >> 16) / static_cast<float>(255);
	result.z = static_cast<float>(color >> 24) / static_cast<float>(255);
	return result;
}

template <>
inline detail::tvec3<float> f32_bgrx_cast<uint32>(uint32 color)
{
	detail::tvec3<float> result;
	result.x = static_cast<float>(color >> 16) / static_cast<float>(255);
	result.y = static_cast<float>(color >>  8) / static_cast<float>(255);
	result.z = static_cast<float>(color >>  0) / static_cast<float>(255);
	return result;
}

template <>
inline detail::tvec3<float> f32_xbgr_cast<uint32>(uint32 color)
{
	detail::tvec3<float> result;
	result.x = static_cast<float>(color >> 24) / static_cast<float>(255);
	result.y = static_cast<float>(color >> 16) / static_cast<float>(255);
	result.z = static_cast<float>(color >>  8) / static_cast<float>(255);
	return result;
}

template <>
inline detail::tvec4<float> f32_rgba_cast<uint32>(uint32 color)
{
	detail::tvec4<float> result;
	result.x = static_cast<float>(color >>  0) / static_cast<float>(255);
	result.y = static_cast<float>(color >>  8) / static_cast<float>(255);
	result.z = static_cast<float>(color >> 16) / static_cast<float>(255);
	result.w = static_cast<float>(color >> 24) / static_cast<float>(255);
	return result;
}

template <>
inline detail::tvec4<float> f32_argb_cast<uint32>(uint32 color)
{
	detail::tvec4<float> result;
	result.x = static_cast<float>(color >>  8) / static_cast<float>(255);
	result.y = static_cast<float>(color >> 16) / static_cast<float>(255);
	result.z = static_cast<float>(color >> 24) / static_cast<float>(255);
	result.w = static_cast<float>(color >>  0) / static_cast<float>(255);
	return result;
}

template <>
inline detail::tvec4<float> f32_bgra_cast<uint32>(uint32 color)
{
	detail::tvec4<float> result;
	result.x = static_cast<float>(color >> 16) / static_cast<float>(255);
	result.y = static_cast<float>(color >>  8) / static_cast<float>(255);
	result.z = static_cast<float>(color >>  0) / static_cast<float>(255);
	result.w = static_cast<float>(color >> 24) / static_cast<float>(255);
	return result;
}

template <>
inline detail::tvec4<float> f32_abgr_cast<uint32>(uint32 color)
{
	detail::tvec4<float> result;
	result.x = static_cast<float>(color >> 24) / static_cast<float>(255);
	result.y = static_cast<float>(color >> 16) / static_cast<float>(255);
	result.z = static_cast<float>(color >>  8) / static_cast<float>(255);
	result.w = static_cast<float>(color >>  0) / static_cast<float>(255);
	return result;
}

template <>
inline double f64_channel_cast<uint8>(uint8 color)
{
	return static_cast<double>(color >>  0) / static_cast<double>(255);
}

template <>
inline detail::tvec3<double> f64_rgbx_cast<uint32>(uint32 color)
{
	detail::tvec3<double> result;
	result.x = static_cast<double>(color >>  0) / static_cast<double>(255);
	result.y = static_cast<double>(color >>  8) / static_cast<double>(255);
	result.z = static_cast<double>(color >> 16) / static_cast<double>(255);
	return result;
}

template <>
inline detail::tvec3<double> f64_xrgb_cast<uint32>(uint32 color)
{
	detail::tvec3<double> result;
	result.x = static_cast<double>(color >>  8) / static_cast<double>(255);
	result.y = static_cast<double>(color >> 16) / static_cast<double>(255);
	result.z = static_cast<double>(color >> 24) / static_cast<double>(255);
	return result;
}

template <>
inline detail::tvec3<double> f64_bgrx_cast<uint32>(uint32 color)
{
	detail::tvec3<double> result;
	result.x = static_cast<double>(color >> 16) / static_cast<double>(255);
	result.y = static_cast<double>(color >>  8) / static_cast<double>(255);
	result.z = static_cast<double>(color >>  0) / static_cast<double>(255);
	return result;
}

template <>
inline detail::tvec3<double> f64_xbgr_cast<uint32>(uint32 color)
{
	detail::tvec3<double> result;
	result.x = static_cast<double>(color >> 24) / static_cast<double>(255);
	result.y = static_cast<double>(color >> 16) / static_cast<double>(255);
	result.z = static_cast<double>(color >>  8) / static_cast<double>(255);
	return result;
}

template <>
inline detail::tvec4<double> f64_rgba_cast<uint32>(uint32 color)
{
	detail::tvec4<double> result;
	result.x = static_cast<double>(color >>  0) / static_cast<double>(255);
	result.y = static_cast<double>(color >>  8) / static_cast<double>(255);
	result.z = static_cast<double>(color >> 16) / static_cast<double>(255);
	result.w = static_cast<double>(color >> 24) / static_cast<double>(255);
	return result;
}

template <>
inline detail::tvec4<double> f64_argb_cast<uint32>(uint32 color)
{
	detail::tvec4<double> result;
	result.x = static_cast<double>(color >>  8) / static_cast<double>(255);
	result.y = static_cast<double>(color >> 16) / static_cast<double>(255);
	result.z = static_cast<double>(color >> 24) / static_cast<double>(255);
	result.w = static_cast<double>(color >>  0) / static_cast<double>(255);
	return result;
}

template <>
inline detail::tvec4<double> f64_bgra_cast<uint32>(uint32 color)
{
	detail::tvec4<double> result;
	result.x = static_cast<double>(color >> 16) / static_cast<double>(255);
	result.y = static_cast<double>(color >>  8) / static_cast<double>(255);
	result.z = static_cast<double>(color >>  0) / static_cast<double>(255);
	result.w = static_cast<double>(color >> 24) / static_cast<double>(255);
	return result;
}

template <>
inline detail::tvec4<double> f64_abgr_cast<uint32>(uint32 color)
{
	detail::tvec4<double> result;
	result.x = static_cast<double>(color >> 24) / static_cast<double>(255);
	result.y = static_cast<double>(color >> 16) / static_cast<double>(255);
	result.z = static_cast<double>(color >>  8) / static_cast<double>(255);
	result.w = static_cast<double>(color >>  0) / static_cast<double>(255);
	return result;
}

template <>
inline detail::thalf f16_channel_cast<uint16>(uint16 color)
{
	return detail::thalf(static_cast<float>(color >>  0) / static_cast<float>(65535));
}

template <>
inline detail::tvec3<detail::thalf> f16_rgbx_cast<uint64>(uint64 color)
{
	detail::tvec3<detail::thalf> result;
	result.x = detail::thalf(static_cast<float>(color >>  0) / static_cast<float>(65535));
	result.y = detail::thalf(static_cast<float>(color >> 16) / static_cast<float>(65535));
	result.z = detail::thalf(static_cast<float>(color >> 32) / static_cast<float>(65535));
	return result;
}

template <>
inline detail::tvec3<detail::thalf> f16_xrgb_cast<uint64>(uint64 color)
{
	detail::tvec3<detail::thalf> result;
	result.x = detail::thalf(static_cast<float>(color >> 16) / static_cast<float>(65535));
	result.y = detail::thalf(static_cast<float>(color >> 32) / static_cast<float>(65535));
	result.z = detail::thalf(static_cast<float>(color >> 48) / static_cast<float>(65535));
	return result;
}

template <>
inline detail::tvec3<detail::thalf> f16_bgrx_cast<uint64>(uint64 color)
{
	detail::tvec3<detail::thalf> result;
	result.x = detail::thalf(static_cast<float>(color >> 32) / static_cast<float>(65535));
	result.y = detail::thalf(static_cast<float>(color >> 16) / static_cast<float>(65535));
	result.z = detail::thalf(static_cast<float>(color >>  0) / static_cast<float>(65535));
	return result;
}

template <>
inline detail::tvec3<detail::thalf> f16_xbgr_cast<uint64>(uint64 color)
{
	detail::tvec3<detail::thalf> result;
	result.x = detail::thalf(static_cast<float>(color >> 48) / static_cast<float>(65535));
	result.y = detail::thalf(static_cast<float>(color >> 32) / static_cast<float>(65535));
	result.z = detail::thalf(static_cast<float>(color >> 16) / static_cast<float>(65535));
	return result;
}

template <>
inline detail::tvec4<detail::thalf> f16_rgba_cast<uint64>(uint64 color)
{
	detail::tvec4<detail::thalf> result;
	result.x = detail::thalf(static_cast<float>(color >>  0) / static_cast<float>(65535));
	result.y = detail::thalf(static_cast<float>(color >> 16) / static_cast<float>(65535));
	result.z = detail::thalf(static_cast<float>(color >> 32) / static_cast<float>(65535));
	result.w = detail::thalf(static_cast<float>(color >> 48) / static_cast<float>(65535));
	return result;
}

template <>
inline detail::tvec4<detail::thalf> f16_argb_cast<uint64>(uint64 color)
{
	detail::tvec4<detail::thalf> result;
	result.x = detail::thalf(static_cast<float>(color >> 16) / static_cast<float>(65535));
	result.y = detail::thalf(static_cast<float>(color >> 32) / static_cast<float>(65535));
	result.z = detail::thalf(static_cast<float>(color >> 48) / static_cast<float>(65535));
	result.w = detail::thalf(static_cast<float>(color >>  0) / static_cast<float>(65535));
	return result;
}

template <>
inline detail::tvec4<detail::thalf> f16_bgra_cast<uint64>(uint64 color)
{
	detail::tvec4<detail::thalf> result;
	result.x = detail::thalf(static_cast<float>(color >> 32) / static_cast<float>(65535));
	result.y = detail::thalf(static_cast<float>(color >> 16) / static_cast<float>(65535));
	result.z = detail::thalf(static_cast<float>(color >>  0) / static_cast<float>(65535));
	result.w = detail::thalf(static_cast<float>(color >> 48) / static_cast<float>(65535));
	return result;
}

template <>
inline detail::tvec4<detail::thalf> f16_abgr_cast<uint64>(uint64 color)
{
	detail::tvec4<detail::thalf> result;
	result.x = detail::thalf(static_cast<float>(color >> 48) / static_cast<float>(65535));
	result.y = detail::thalf(static_cast<float>(color >> 32) / static_cast<float>(65535));
	result.z = detail::thalf(static_cast<float>(color >> 16) / static_cast<float>(65535));
	result.w = detail::thalf(static_cast<float>(color >>  0) / static_cast<float>(65535));
	return result;
}

template <>
inline float f32_channel_cast<uint16>(uint16 color)
{
	return static_cast<float>(color >>  0) / static_cast<float>(65535);
}

template <>
inline detail::tvec3<float> f32_rgbx_cast<uint64>(uint64 color)
{
	detail::tvec3<float> result;
	result.x = static_cast<float>(color >>  0) / static_cast<float>(65535);
	result.y = static_cast<float>(color >> 16) / static_cast<float>(65535);
	result.z = static_cast<float>(color >> 32) / static_cast<float>(65535);
	return result;
}

template <>
inline detail::tvec3<float> f32_xrgb_cast<uint64>(uint64 color)
{
	detail::tvec3<float> result;
	result.x = static_cast<float>(color >> 16) / static_cast<float>(65535);
	result.y = static_cast<float>(color >> 32) / static_cast<float>(65535);
	result.z = static_cast<float>(color >> 48) / static_cast<float>(65535);
	return result;
}

template <>
inline detail::tvec3<float> f32_bgrx_cast<uint64>(uint64 color)
{
	detail::tvec3<float> result;
	result.x = static_cast<float>(color >> 32) / static_cast<float>(65535);
	result.y = static_cast<float>(color >> 16) / static_cast<float>(65535);
	result.z = static_cast<float>(color >>  0) / static_cast<float>(65535);
	return result;
}

template <>
inline detail::tvec3<float> f32_xbgr_cast<uint64>(uint64 color)
{
	detail::tvec3<float> result;
	result.x = static_cast<float>(color >> 48) / static_cast<float>(65535);
	result.y = static_cast<float>(color >> 32) / static_cast<float>(65535);
	result.z = static_cast<float>(color >> 16) / static_cast<float>(65535);
	return result;
}

template <>
inline detail::tvec4<float> f32_rgba_cast<uint64>(uint64 color)
{
	detail::tvec4<float> result;
	result.x = static_cast<float>(color >>  0) / static_cast<float>(65535);
	result.y = static_cast<float>(color >> 16) / static_cast<float>(65535);
	result.z = static_cast<float>(color >> 32) / static_cast<float>(65535);
	result.w = static_cast<float>(color >> 48) / static_cast<float>(65535);
	return result;
}

template <>
inline detail::tvec4<float> f32_argb_cast<uint64>(uint64 color)
{
	detail::tvec4<float> result;
	result.x = static_cast<float>(color >> 16) / static_cast<float>(65535);
	result.y = static_cast<float>(color >> 32) / static_cast<float>(65535);
	result.z = static_cast<float>(color >> 48) / static_cast<float>(65535);
	result.w = static_cast<float>(color >>  0) / static_cast<float>(65535);
	return result;
}

template <>
inline detail::tvec4<float> f32_bgra_cast<uint64>(uint64 color)
{
	detail::tvec4<float> result;
	result.x = static_cast<float>(color >> 32) / static_cast<float>(65535);
	result.y = static_cast<float>(color >> 16) / static_cast<float>(65535);
	result.z = static_cast<float>(color >>  0) / static_cast<float>(65535);
	result.w = static_cast<float>(color >> 48) / static_cast<float>(65535);
	return result;
}

template <>
inline detail::tvec4<float> f32_abgr_cast<uint64>(uint64 color)
{
	detail::tvec4<float> result;
	result.x = static_cast<float>(color >> 48) / static_cast<float>(65535);
	result.y = static_cast<float>(color >> 32) / static_cast<float>(65535);
	result.z = static_cast<float>(color >> 16) / static_cast<float>(65535);
	result.w = static_cast<float>(color >>  0) / static_cast<float>(65535);
	return result;
}

template <>
inline double f64_channel_cast<uint16>(uint16 color)
{
	return static_cast<double>(color >>  0) / static_cast<double>(65535);
}

template <>
inline detail::tvec3<double> f64_rgbx_cast<uint64>(uint64 color)
{
	detail::tvec3<double> result;
	result.x = static_cast<double>(color >>  0) / static_cast<double>(65535);
	result.y = static_cast<double>(color >> 16) / static_cast<double>(65535);
	result.z = static_cast<double>(color >> 32) / static_cast<double>(65535);
	return result;
}

template <>
inline detail::tvec3<double> f64_xrgb_cast<uint64>(uint64 color)
{
	detail::tvec3<double> result;
	result.x = static_cast<double>(color >> 16) / static_cast<double>(65535);
	result.y = static_cast<double>(color >> 32) / static_cast<double>(65535);
	result.z = static_cast<double>(color >> 48) / static_cast<double>(65535);
	return result;
}

template <>
inline detail::tvec3<double> f64_bgrx_cast<uint64>(uint64 color)
{
	detail::tvec3<double> result;
	result.x = static_cast<double>(color >> 32) / static_cast<double>(65535);
	result.y = static_cast<double>(color >> 16) / static_cast<double>(65535);
	result.z = static_cast<double>(color >>  0) / static_cast<double>(65535);
	return result;
}

template <>
inline detail::tvec3<double> f64_xbgr_cast<uint64>(uint64 color)
{
	detail::tvec3<double> result;
	result.x = static_cast<double>(color >> 48) / static_cast<double>(65535);
	result.y = static_cast<double>(color >> 32) / static_cast<double>(65535);
	result.z = static_cast<double>(color >> 16) / static_cast<double>(65535);
	return result;
}

template <>
inline detail::tvec4<double> f64_rgba_cast<uint64>(uint64 color)
{
	detail::tvec4<double> result;
	result.x = static_cast<double>(color >>  0) / static_cast<double>(65535);
	result.y = static_cast<double>(color >> 16) / static_cast<double>(65535);
	result.z = static_cast<double>(color >> 32) / static_cast<double>(65535);
	result.w = static_cast<double>(color >> 48) / static_cast<double>(65535);
	return result;
}

template <>
inline detail::tvec4<double> f64_argb_cast<uint64>(uint64 color)
{
	detail::tvec4<double> result;
	result.x = static_cast<double>(color >> 16) / static_cast<double>(65535);
	result.y = static_cast<double>(color >> 32) / static_cast<double>(65535);
	result.z = static_cast<double>(color >> 48) / static_cast<double>(65535);
	result.w = static_cast<double>(color >>  0) / static_cast<double>(65535);
	return result;
}

template <>
inline detail::tvec4<double> f64_bgra_cast<uint64>(uint64 color)
{
	detail::tvec4<double> result;
	result.x = static_cast<double>(color >> 32) / static_cast<double>(65535);
	result.y = static_cast<double>(color >> 16) / static_cast<double>(65535);
	result.z = static_cast<double>(color >>  0) / static_cast<double>(65535);
	result.w = static_cast<double>(color >> 48) / static_cast<double>(65535);
	return result;
}

template <>
inline detail::tvec4<double> f64_abgr_cast<uint64>(uint64 color)
{
	detail::tvec4<double> result;
	result.x = static_cast<double>(color >> 48) / static_cast<double>(65535);
	result.y = static_cast<double>(color >> 32) / static_cast<double>(65535);
	result.z = static_cast<double>(color >> 16) / static_cast<double>(65535);
	result.w = static_cast<double>(color >>  0) / static_cast<double>(65535);
	return result;
}

}//namespace color_space
}//namespace gtx
}//namespace glm
