#ifndef GLM_EXT_VIRTREV_XSTREAM_HPP
#define GLM_EXT_VIRTREV_XSTREAM_HPP

///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
// Virtrev SDK copyright matrem (matrem84.free.fr)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2008-05-24
// Updated : 2008-05-26
// Licence : This source is under MIT License
// File    : glm/ext/virtrev/xstream.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////
// Dependency:
// - GLM core
// - GLM_GTX_matrix_selection
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "../glm.hpp"
#include "../gtc/matrix_access.hpp"
#include <iostream>

#if(defined(GLM_MESSAGES) && !defined(glm_ext))
#	pragma message("GLM: GLM_VIRTREV_xstream extension included")
#endif

namespace glm
{
	namespace virtrev_glmext
	{
		//! GLM_VIRTREV_xstream extension: Streaming vector and matrix in a xml way
		namespace xstream
		{
			template<typename T>
			std::ostream & operator << (std::ostream & stream, glm::detail::tvec2<T> const & vec)
			{
				stream << "<glm_vec2 ";
				stream << "x=\"" << vec.x << "\" ";
				stream << "y=\"" << vec.y << "\" ";
				stream << "/>";

				return stream;
			}

			template<typename T>
			std::ostream & operator << (std::ostream & stream, glm::detail::tvec3<T> const & vec)
			{
				stream << "<glm_vec3 ";
				stream << "x=\"" << vec.x << "\" ";
				stream << "y=\"" << vec.y << "\" ";
				stream << "z=\"" << vec.z << "\" ";
				stream << "/>";

				return stream;
			}

			template<typename T>
			std::ostream & operator << (std::ostream & stream, glm::detail::tvec4<T> const & vec)
			{
				stream << "<glm_vec4 ";
				stream << "x=\"" << vec.x << "\" ";
				stream << "y=\"" << vec.y << "\" ";
				stream << "z=\"" << vec.z << "\" ";
				stream << "w=\"" << vec.w << "\" ";
				stream << "/>";

				return stream;
			}

			template<typename T>
			std::ostream & operator << (std::ostream & stream, glm::detail::tmat2x2<T> const & mat)
			{
				stream << "<glm_mat2>" << std::endl;
				stream << "<row ";
				stream << "x=\"" << glm::row(mat, 0)[0] << "\" ";
				stream << "y=\"" << glm::row(mat, 0)[1] << "\" ";
				stream << "/>" << std::endl;
				stream << "<row ";
				stream << "x=\"" << glm::row(mat, 1)[0] << "\" ";
				stream << "y=\"" << glm::row(mat, 1)[1] << "\" ";
				stream << "/>" << std::endl;
				stream << "</glm_mat2>";

				return stream;
			}

			template<typename T>
			std::ostream & operator << (std::ostream & stream, glm::detail::tmat3x3<T> const & mat)
			{
				stream << "<glm_mat3>" << std::endl;
				stream << "<row ";
				stream << "x=\"" << glm::row(mat, 0)[0] << "\" ";
				stream << "y=\"" << glm::row(mat, 0)[1] << "\" ";
				stream << "z=\"" << glm::row(mat, 0)[2] << "\" ";
				stream << "/>" << std::endl;
				stream << "<row ";
				stream << "x=\"" << glm::row(mat, 1)[0] << "\" ";
				stream << "y=\"" << glm::row(mat, 1)[1] << "\" ";
				stream << "z=\"" << glm::row(mat, 1)[2] << "\" ";
				stream << "/>" << std::endl;
				stream << "<row ";
				stream << "x=\"" << glm::row(mat, 2)[0] << "\" ";
				stream << "y=\"" << glm::row(mat, 2)[1] << "\" ";
				stream << "z=\"" << glm::row(mat, 2)[2] << "\" ";
				stream << "/>" << std::endl;
				stream << "</glm_mat3>";

				return stream;
			}

			template<typename T>
			std::ostream & operator << (std::ostream & stream, glm::detail::tmat4x4<T> const & mat)
			{
				stream << "<glm_mat4>" << std::endl;
				stream << "<row ";
				stream << "x=\"" << glm::row(mat, 0)[0] << "\" ";
				stream << "y=\"" << glm::row(mat, 0)[1] << "\" ";
				stream << "z=\"" << glm::row(mat, 0)[2] << "\" ";
				stream << "w=\"" << glm::row(mat, 0)[3] << "\" ";
				stream << "/>" << std::endl;
				stream << "<row ";
				stream << "x=\"" << glm::row(mat, 1)[0] << "\" ";
				stream << "y=\"" << glm::row(mat, 1)[1] << "\" ";
				stream << "z=\"" << glm::row(mat, 1)[2] << "\" ";
				stream << "w=\"" << glm::row(mat, 1)[3] << "\" ";
				stream << "/>" << std::endl;
				stream << "<row ";
				stream << "x=\"" << glm::row(mat, 2)[0] << "\" ";
				stream << "y=\"" << glm::row(mat, 2)[1] << "\" ";
				stream << "z=\"" << glm::row(mat, 2)[2] << "\" ";
				stream << "w=\"" << glm::row(mat, 2)[3] << "\" ";
				stream << "/>" << std::endl;
				stream << "<row ";
				stream << "x=\"" << glm::row(mat, 3)[0] << "\" ";
				stream << "y=\"" << glm::row(mat, 3)[1] << "\" ";
				stream << "z=\"" << glm::row(mat, 3)[2] << "\" ";
				stream << "w=\"" << glm::row(mat, 3)[3] << "\" ";
				stream << "/>" << std::endl;
				stream << "</glm_mat4>";
			
				return stream;
			}
		}
	}
}

namespace glm{using namespace glm::virtrev_glmext::xstream;}

#endif//GLM_EXT_VIRTREV_XSTREAM_HPP
