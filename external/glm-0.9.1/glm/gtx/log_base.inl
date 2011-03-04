///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-10-24
// Updated : 2008-10-24
// Licence : This source is under MIT License
// File    : glm/gtx/log_base.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtx{
namespace log_base{

template <typename genType> 
inline genType log(
	genType const & x, 
	genType const & base)
{
	assert(x != genType(0));

	return glm::log(x) / glm::log(base);
}

template <typename valType> 
inline detail::tvec2<valType> log(
	detail::tvec2<valType> const & v, 
	valType const & base)
{
	return detail::tvec2<valType>(
		log(v.x, base),
		log(v.y, base));
}

template <typename valType> 
inline detail::tvec3<valType> log(
	detail::tvec3<valType> const & v, 
	valType const & base)
{
	return detail::tvec3<valType>(
		log(v.x, base),
		log(v.y, base),
		log(v.z, base));
}

template <typename valType> 
inline detail::tvec4<valType> log(
	detail::tvec4<valType> const & v, 
	valType const & base)
{
	return detail::tvec4<valType>(
		log(v.x, base),
		log(v.y, base),
		log(v.z, base),
		log(v.w, base));
}

template <typename valType> 
inline detail::tvec2<valType> log(
	detail::tvec2<valType> const & v, 
	detail::tvec2<valType> const & base)
{
	return detail::tvec2<valType>(
		log(v.x, base.x),
		log(v.y, base.y));
}

template <typename valType> 
inline detail::tvec3<valType> log(
	detail::tvec3<valType> const & v, 
	detail::tvec3<valType> const & base)
{
	return detail::tvec3<valType>(
		log(v.x, base.x),
		log(v.y, base.y),
		log(v.z, base.z));
}

template <typename valType> 
inline detail::tvec4<valType> log(
	detail::tvec4<valType> const & v, 
	detail::tvec4<valType> const & base)
{
	return detail::tvec4<valType>(
		log(v.x, base.x),
		log(v.y, base.y),
		log(v.z, base.z),
		log(v.w, base.w));
}

}//namespace log_base
}//namespace gtx
}//namespace glm
