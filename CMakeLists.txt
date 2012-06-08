# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (Tutorials)

find_package(OpenGL REQUIRED)

# Compile external dependencies 
add_subdirectory (external)

include_directories(
	external/glfw-2.7.2/include/
	external/glm-0.9.1/
	external/glew-1.5.8/include/
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	GLFW_272
	GLEW_158
)

add_definitions(
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

# Tutorial 1
add_executable(tutorial01_first_window 
	tutorial01_first_window/tutorial01.cpp
)
target_link_libraries(tutorial01_first_window
	${ALL_LIBS}
)
add_custom_command(
   TARGET tutorial01_first_window POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial01_first_window${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial01_first_window/"
)


# Tutorial 2
add_executable(tutorial02_red_triangle 
	tutorial02_red_triangle/tutorial02.cpp
	common/shader.cpp
	common/shader.hpp
)
target_link_libraries(tutorial02_red_triangle
	${ALL_LIBS}
)
add_custom_command(
   TARGET tutorial02_red_triangle POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial02_red_triangle${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial02_red_triangle/"
)

# Tutorial 3
add_executable(tutorial03_matrices 
	tutorial03_matrices/tutorial03.cpp
	common/shader.cpp
	common/shader.hpp
)
target_link_libraries(tutorial03_matrices
	${ALL_LIBS}
)
add_custom_command(
   TARGET tutorial03_matrices POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial03_matrices${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial03_matrices/"
)

# Tutorial 4
add_executable(tutorial04_colored_cube
	tutorial04_colored_cube/tutorial04.cpp
	common/shader.cpp
	common/shader.hpp
)
target_link_libraries(tutorial04_colored_cube
	${ALL_LIBS}
)
add_custom_command(
   TARGET tutorial04_colored_cube POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial04_colored_cube${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial04_colored_cube/"
)

# Tutorial 5
add_executable(tutorial05_textured_cube
	tutorial05_textured_cube/tutorial05.cpp
	common/shader.cpp
	common/shader.hpp
	common/texture.cpp
	common/texture.hpp
)
target_link_libraries(tutorial05_textured_cube
	${ALL_LIBS}
)
add_custom_command(
   TARGET tutorial05_textured_cube POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial05_textured_cube${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial05_textured_cube/"
)

# Tutorial 6
add_executable(tutorial06_keyboard_and_mouse
	tutorial06_keyboard_and_mouse/tutorial06.cpp
	common/shader.cpp
	common/shader.hpp
	common/controls.cpp
	common/controls.hpp
	common/texture.cpp
	common/texture.hpp
)
target_link_libraries(tutorial06_keyboard_and_mouse
	${ALL_LIBS}
)
add_custom_command(
   TARGET tutorial06_keyboard_and_mouse POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial06_keyboard_and_mouse${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial06_keyboard_and_mouse/"
)

# Tutorial 7
add_executable(tutorial07_model_loading
	tutorial07_model_loading/tutorial07.cpp
	common/shader.cpp
	common/shader.hpp
	common/controls.cpp
	common/controls.hpp
	common/texture.cpp
	common/texture.hpp
	common/objloader.cpp
	common/objloader.hpp
)
target_link_libraries(tutorial07_model_loading
	${ALL_LIBS}
)
add_custom_command(
   TARGET tutorial07_model_loading POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial07_model_loading${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial07_model_loading/"
)

# Tutorial 8
add_executable(tutorial08_basic_shading
	tutorial08_basic_shading/tutorial08.cpp
	common/shader.cpp
	common/shader.hpp
	common/controls.cpp
	common/controls.hpp
	common/texture.cpp
	common/texture.hpp
	common/objloader.cpp
	common/objloader.hpp
)
target_link_libraries(tutorial08_basic_shading
	${ALL_LIBS}
)
add_custom_command(
   TARGET tutorial08_basic_shading POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial08_basic_shading${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial08_basic_shading/"
)

# Tutorial 9
add_executable(tutorial09_vbo_indexing
	tutorial09_vbo_indexing/tutorial09.cpp
	common/shader.cpp
	common/shader.hpp
	common/controls.cpp
	common/controls.hpp
	common/texture.cpp
	common/texture.hpp
	common/objloader.cpp
	common/objloader.hpp
	common/vboindexer.cpp
	common/vboindexer.hpp
)
target_link_libraries(tutorial09_vbo_indexing
	${ALL_LIBS}
)
add_custom_command(
   TARGET tutorial09_vbo_indexing POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial09_vbo_indexing${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial09_vbo_indexing/"
)

# Tutorial 10
add_executable(tutorial10_transparency
	tutorial10_transparency/tutorial10.cpp
	common/shader.cpp
	common/shader.hpp
	common/controls.cpp
	common/controls.hpp
	common/texture.cpp
	common/texture.hpp
	common/objloader.cpp
	common/objloader.hpp
	common/vboindexer.cpp
	common/vboindexer.hpp
)
target_link_libraries(tutorial10_transparency
	${ALL_LIBS}
)
add_custom_command(
   TARGET tutorial10_transparency POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial10_transparency${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial10_transparency/"
)

# Tutorial 11
add_executable(tutorial11_2d_fonts
	tutorial11_2d_fonts/tutorial11.cpp
	common/shader.cpp
	common/shader.hpp
	common/controls.cpp
	common/controls.hpp
	common/texture.cpp
	common/texture.hpp
	common/objloader.cpp
	common/objloader.hpp
	common/vboindexer.cpp
	common/vboindexer.hpp
	common/text2D.hpp
	common/text2D.cpp
)
target_link_libraries(tutorial11_2d_fonts
	${ALL_LIBS}
)
add_custom_command(
   TARGET tutorial11_2d_fonts POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial11_2d_fonts${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial11_2d_fonts/"
)

# Tutorial 13
add_executable(tutorial13_normal_mapping
	tutorial13_normal_mapping/tutorial13.cpp
	common/shader.cpp
	common/shader.hpp
	common/controls.cpp
	common/controls.hpp
	common/texture.cpp
	common/texture.hpp
	common/objloader.cpp
	common/objloader.hpp
	common/vboindexer.cpp
	common/vboindexer.hpp
	common/text2D.hpp
	common/text2D.cpp
	common/tangentspace.hpp
	common/tangentspace.cpp
)
target_link_libraries(tutorial13_normal_mapping
	${ALL_LIBS}
)
add_custom_command(
   TARGET tutorial13_normal_mapping POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial13_normal_mapping${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial13_normal_mapping/"
)


# Tutorial 14
add_executable(tutorial14_render_to_texture
	tutorial14_render_to_texture/tutorial14.cpp
	common/shader.cpp
	common/shader.hpp
	common/controls.cpp
	common/controls.hpp
	common/texture.cpp
	common/texture.hpp
	common/objloader.cpp
	common/objloader.hpp
	common/vboindexer.cpp
	common/vboindexer.hpp
	common/text2D.hpp
	common/text2D.cpp
)
target_link_libraries(tutorial14_render_to_texture
	${ALL_LIBS}
)
add_custom_command(
   TARGET tutorial14_render_to_texture POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial14_render_to_texture${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial14_render_to_texture/"
)


# Tutorial 15
add_executable(tutorial15_lightmaps
	tutorial15_lightmaps/tutorial15.cpp
	common/shader.cpp
	common/shader.hpp
	common/controls.cpp
	common/controls.hpp
	common/texture.cpp
	common/texture.hpp
	common/objloader.cpp

	common/objloader.hpp
	common/vboindexer.cpp
	common/vboindexer.hpp
)
target_link_libraries(tutorial15_lightmaps
	${ALL_LIBS}
)
add_custom_command(
   TARGET tutorial15_lightmaps POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial15_lightmaps${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial15_lightmaps/"
)

# Tutorial 16
add_executable(tutorial16_shadowmaps
	tutorial16_shadowmaps/tutorial16.cpp
	common/shader.cpp
	common/shader.hpp
	common/controls.cpp
	common/controls.hpp
	common/texture.cpp
	common/texture.hpp
	common/objloader.cpp
	common/objloader.hpp
	common/vboindexer.cpp
	common/vboindexer.hpp
)
target_link_libraries(tutorial16_shadowmaps
	${ALL_LIBS}
)
add_custom_command(
   TARGET tutorial16_shadowmaps POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial16_shadowmaps${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial16_shadowmaps/"
)

# User playground
add_executable(playground 
	playground/playground.cpp
	common/shader.cpp
	common/shader.hpp
)
target_link_libraries(playground
	${ALL_LIBS}
)
add_custom_command(
   TARGET playground POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/playground${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/playground/"
)

SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*" )

