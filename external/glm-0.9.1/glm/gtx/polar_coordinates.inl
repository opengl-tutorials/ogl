///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2007-03-06
// Updated : 2009-05-01
// Licence : This source is under MIT License
// File    : glm/gtx/polar_coordinates.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtx{
namespace polar_coordinates
{
	template <typename T> 
	inline detail::tvec3<T> polar(
		const detail::tvec3<T>& euclidean)
	{
		T length = length(euclidean);
		detail::tvec3<T> tmp = euclidean / length;
		T xz_dist = sqrt(tmp.x * tmp.x + tmp.z * tmp.z);

		return detail::tvec3<T>(
			degrees(atan(xz_dist, tmp.y)),	// latitude
			degrees(atan(tmp.x, tmp.z)),		// longitude
			xz_dist);									// xz distance
	}

	template <typename T> 
	inline detail::tvec3<T> euclidean(
		const detail::tvec3<T>& polar)
	{
		T latitude = radians(polar.x);
		T longitude = radians(polar.y);
		return detail::tvec3<T>(
			cos(latitude) * sin(longitude),
			sin(latitude),
			cos(latitude) * cos(longitude));
	}

}//namespace polar_coordinates
}//namespace gtx
}//namespace glm
