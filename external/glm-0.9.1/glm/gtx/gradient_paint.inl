///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2009-03-06
// Updated : 2009-03-09
// Licence : This source is under MIT License
// File    : glm/gtx/gradient_paint.inl
///////////////////////////////////////////////////////////////////////////////////////////////////

namespace glm{
namespace gtx{
namespace gradient_paint{

	template <typename valType>
	valType radialGradient(
		glm::detail::tvec2<valType> const & Center,
		valType const & Radius,
		glm::detail::tvec2<valType> const & Focal,
		glm::detail::tvec2<valType> const & Position)
	{
		glm::detail::tvec2<valType> F = Focal - Center;
		glm::detail::tvec2<valType> D = Position - Focal;
		valType Radius2 = gtx::optimum_pow::pow2(Radius);
		valType Fx2 = gtx::optimum_pow::pow2(F.x);
		valType Fy2 = gtx::optimum_pow::pow2(F.y);

		valType Numerator = (D.x * F.x + D.y * F.y) + glm::sqrt(Radius2 * (gtx::optimum_pow::pow2(D.x) + gtx::optimum_pow::pow2(D.y)) - gtx::optimum_pow::pow2(D.x * F.y - D.y * F.x));
		valType Denominator = Radius2 - (Fx2 + Fy2);
		return Numerator / Denominator;
	}

	template <typename valType>
	valType linearGradient(
		glm::detail::tvec2<valType> const & Point0,
		glm::detail::tvec2<valType> const & Point1,
		glm::detail::tvec2<valType> const & Position)
	{
		glm::detail::tvec2<valType> Dist = Point1 - Point0;
		return (Dist.x * (Position.x - Point0.x) + Dist.y * (Position.y - Point0.y)) / glm::dot(Dist, Dist);
	}

}//namespace gradient_paint
}//namespace gtx
}//namespace glm
