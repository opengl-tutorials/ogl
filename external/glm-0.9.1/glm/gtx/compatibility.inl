///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2007-03-16
// Updated : 2008-10-24
// Licence : This source is under MIT License
// File    : glm/gtx/compatibility.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtx{
namespace compatibility{

// isfinite
template <typename genType> 
inline bool isfinite(
	genType const & x)
{
#ifdef GLM_COMPILER_VC
	return _finite(x);
#else//GLM_COMPILER_GCC
	return std::isfinite(x);
#endif
}

template <typename valType> 
inline detail::tvec2<bool> isfinite(
	detail::tvec2<valType> const & x)
{
	return detail::tvec2<bool>(
		isfinite(x.x),
		isfinite(x.y));
}

template <typename valType> 
inline detail::tvec3<bool> isfinite(
	detail::tvec3<valType> const & x)
{
	return detail::tvec3<bool>(
		isfinite(x.x),
		isfinite(x.y),
		isfinite(x.z));
}

template <typename valType> 
inline detail::tvec4<bool> isfinite(
	detail::tvec4<valType> const & x)
{
	return detail::tvec4<bool>(
		isfinite(x.x),
		isfinite(x.y),
		isfinite(x.z),
		isfinite(x.w));
}

// isinf
template <typename genType> 
inline bool isinf(
	genType const & x)
{
#if(defined(GLM_COMPILER) && (GLM_COMPILER & GLM_COMPILER_VC))
	return _fpclass(x) == _FPCLASS_NINF || _fpclass(x) == _FPCLASS_PINF;
#else
	return std::isinf(x);
#endif
}

template <typename valType> 
inline detail::tvec2<bool> isinf(
	detail::tvec2<valType> const & x)
{
	return detail::tvec2<bool>(
		isinf(x.x),
		isinf(x.y));
}

template <typename valType> 
inline detail::tvec3<bool> isinf(
	detail::tvec3<valType> const & x)
{
	return detail::tvec3<bool>(
		isinf(x.x),
		isinf(x.y),
		isinf(x.z));
}

template <typename valType> 
inline detail::tvec4<bool> isinf(
	detail::tvec4<valType> const & x)
{
	return detail::tvec4<bool>(
		isinf(x.x),
		isinf(x.y),
		isinf(x.z),
		isinf(x.w));
}

// isnan
template <typename genType> 
inline bool isnan(genType const & x)
{
#if(defined(GLM_COMPILER) && (GLM_COMPILER & GLM_COMPILER_VC))
	return _isnan(x);
#else
	return std::isnan(x);
#endif
}

template <typename valType> 
inline detail::tvec2<bool> isnan(
	detail::tvec2<valType> const & x)
{
	return detail::tvec2<bool>(
		isnan(x.x),
		isnan(x.y));
}

template <typename valType> 
inline detail::tvec3<bool> isnan(
	detail::tvec3<valType> const & x)
{
	return detail::tvec3<bool>(
		isnan(x.x),
		isnan(x.y),
		isnan(x.z));
}

template <typename valType> 
inline detail::tvec4<bool> isnan(
	detail::tvec4<valType> const & x)
{
	return detail::tvec4<bool>(
		isnan(x.x),
		isnan(x.y),
		isnan(x.z),
		isnan(x.w));
}

}//namespace compatibility
}//namespace gtx
}//namespace glm
