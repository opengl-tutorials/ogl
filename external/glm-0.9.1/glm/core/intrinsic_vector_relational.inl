///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2009-06-09
// Updated : 2009-06-09
// Licence : This source is under MIT License
// File    : glm/core/intrinsic_vector_relational.inl
///////////////////////////////////////////////////////////////////////////////////////////////////
//
//// lessThan
//template <typename valType>
//inline typename detail::tvec2<valType>::bool_type lessThan
//(
//	detail::tvec2<valType> const & x, 
//	detail::tvec2<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint);
//
//    return typename detail::tvec2<bool>::bool_type(x.x < y.x, x.y < y.y);
//}
//
//template <typename valType>
//inline typename detail::tvec3<valType>::bool_type lessThan
//(
//	detail::tvec3<valType> const & x, 
//	detail::tvec3<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint);
//	
//	return typename detail::tvec3<bool>::bool_type(x.x < y.x, x.y < y.y, x.z < y.z);
//}
//
//template <typename valType>
//inline typename detail::tvec4<valType>::bool_type lessThan
//(
//	detail::tvec4<valType> const & x, 
//	detail::tvec4<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint);
//
//	return typename detail::tvec4<bool>::bool_type(x.x < y.x, x.y < y.y, x.z < y.z, x.w < y.w);
//}
//
//// lessThanEqual
//template <typename valType>
//inline typename detail::tvec2<valType>::bool_type lessThanEqual
//(
//	detail::tvec2<valType> const & x, 
//	detail::tvec2<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint);
//
//	return typename detail::tvec2<bool>::bool_type(x.x <= y.x, x.y <= y.y);
//}
//
//template <typename valType>
//inline typename detail::tvec3<valType>::bool_type lessThanEqual
//(
//	detail::tvec3<valType> const & x, 
//	detail::tvec3<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint);
//	
//	return typename detail::tvec3<bool>::bool_type(x.x <= y.x, x.y <= y.y, x.z <= y.z);
//}
//
//template <typename valType>
//inline typename detail::tvec4<valType>::bool_type lessThanEqual
//(
//	detail::tvec4<valType> const & x, 
//	detail::tvec4<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint);
//	
//	return typename detail::tvec4<bool>::bool_type(x.x <= y.x, x.y <= y.y, x.z <= y.z, x.w <= y.w);
//}
//
//// greaterThan
//template <typename valType>
//inline typename detail::tvec2<valType>::bool_type greaterThan
//(
//	detail::tvec2<valType> const & x, 
//	detail::tvec2<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint);
//
//	return typename detail::tvec2<bool>::bool_type(x.x > y.x, x.y > y.y);
//}
//
//template <typename valType>
//inline typename detail::tvec3<valType>::bool_type greaterThan
//(
//	detail::tvec3<valType> const & x, 
//	detail::tvec3<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint);
//	
//	return typename detail::tvec3<bool>::bool_type(x.x > y.x, x.y > y.y, x.z > y.z);
//}
//
//template <typename valType>
//inline typename detail::tvec4<valType>::bool_type greaterThan
//(
//	detail::tvec4<valType> const & x, 
//	detail::tvec4<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint);
//	
//	return typename detail::tvec4<bool>::bool_type(x.x > y.x, x.y > y.y, x.z > y.z, x.w > y.w);
//}
//
//// greaterThanEqual
//template <typename valType>
//inline typename detail::tvec2<valType>::bool_type greaterThanEqual
//(
//	detail::tvec2<valType> const & x, 
//	detail::tvec2<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint);
//
//	return typename detail::tvec2<bool>::bool_type(x.x >= y.x, x.y >= y.y);
//}
//
//template <typename valType>
//inline typename detail::tvec3<valType>::bool_type greaterThanEqual
//(
//	detail::tvec3<valType> const & x, 
//	detail::tvec3<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint);
//
//	return typename detail::tvec3<bool>::bool_type(x.x >= y.x, x.y >= y.y, x.z >= y.z);
//}
//
//template <typename valType>
//inline typename detail::tvec4<valType>::bool_type greaterThanEqual
//(
//	detail::tvec4<valType> const & x, 
//	detail::tvec4<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint);
//
//	return typename detail::tvec4<bool>::bool_type(x.x >= y.x, x.y >= y.y, x.z >= y.z, x.w >= y.w);
//}
//
//// equal
//template <typename valType>
//inline typename detail::tvec2<valType>::bool_type equal
//(
//	detail::tvec2<valType> const & x, 
//	detail::tvec2<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint || 
//		detail::type<valType>::is_bool);
//
//	return typename detail::tvec2<valType>::bool_type(x.x == y.x, x.y == y.y);
//}
//
//template <typename valType>
//inline typename detail::tvec3<valType>::bool_type equal
//(
//	detail::tvec3<valType> const & x, 
//	detail::tvec3<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint || 
//		detail::type<valType>::is_bool);
//
//	return typename detail::tvec3<valType>::bool_type(x.x == y.x, x.y == y.y, x.z == y.z);
//}
//
//template <typename valType>
//inline typename detail::tvec4<valType>::bool_type equal
//(
//	detail::tvec4<valType> const & x, 
//	detail::tvec4<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint || 
//		detail::type<valType>::is_bool);
//
//	return typename detail::tvec4<valType>::bool_type(x.x == y.x, x.y == y.y, x.z == y.z, x.w == y.w);
//}
//
//// notEqual
//template <typename valType>
//inline typename detail::tvec2<valType>::bool_type notEqual
//(
//	detail::tvec2<valType> const & x, 
//	detail::tvec2<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint || 
//		detail::type<valType>::is_bool);
//
//	return typename detail::tvec2<valType>::bool_type(x.x != y.x, x.y != y.y);
//}
//
//template <typename valType>
//inline typename detail::tvec3<valType>::bool_type notEqual
//(
//	detail::tvec3<valType> const & x, 
//	detail::tvec3<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint || 
//		detail::type<valType>::is_bool);
//
//	return typename detail::tvec3<valType>::bool_type(x.x != y.x, x.y != y.y, x.z != y.z);
//}
//
//template <typename valType>
//inline typename detail::tvec4<valType>::bool_type notEqual
//(
//	detail::tvec4<valType> const & x, 
//	detail::tvec4<valType> const & y
//)
//{
//	GLM_STATIC_ASSERT(
//		detail::type<valType>::is_float || 
//		detail::type<valType>::is_int || 
//		detail::type<valType>::is_uint || 
//		detail::type<valType>::is_bool);
//
//	return typename detail::tvec4<valType>::bool_type(x.x != y.x, x.y != y.y, x.z != y.z, x.w != y.w);
//}
//
//// any
//inline bool any(detail::tvec2<bool> const & x)
//{
//	return x.x || x.y;
//}
//
//inline bool any(detail::tvec3<bool> const & x)
//{
//    return x.x || x.y || x.z;
//}
//
//inline bool any(detail::tvec4<bool> const & x)
//{
//    return x.x || x.y || x.z || x.w;
//}
//
//// all
//inline bool all(const detail::tvec2<bool>& x)
//{
//    return x.x && x.y;
//}
//
//inline bool all(const detail::tvec3<bool>& x)
//{
//    return x.x && x.y && x.z;
//}
//
//inline bool all(const detail::tvec4<bool>& x)
//{
//    return x.x && x.y && x.z && x.w;
//}
//
//// not
//inline detail::tvec2<bool>::bool_type not_
//(
//	detail::tvec2<bool> const & v
//)
//{
//    return detail::tvec2<bool>::bool_type(!v.x, !v.y);
//}
//
//inline detail::tvec3<bool>::bool_type not_
//(
//	detail::tvec3<bool> const & v
//)
//{
//    return detail::tvec3<bool>::bool_type(!v.x, !v.y, !v.z);
//}
//
//inline detail::tvec4<bool>::bool_type not_
//(
//	detail::tvec4<bool> const & v
//)
//{
//    return detail::tvec4<bool>::bool_type(!v.x, !v.y, !v.z, !v.w);
//}