# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (Tutorials)

find_package(OpenGL REQUIRED)

# Compile external dependencies 
add_subdirectory (external)

# On Visual 2005 and above, this module can set the debug working directory
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-1c73e35")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

if(INCLUDE_DISTRIB)
	add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)



include_directories(
	external/AntTweakBar-1.15/include/
	external/glfw-2.7.6/include/
	external/glm-0.9.4.0/
	external/glew-1.9.0/include/
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	GLFW_276
	GLEW_190
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
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
# Xcode and Visual working directories
set_target_properties(tutorial01_first_window PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial01_first_window/")
create_target_launcher(tutorial01_first_window WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial01_first_window/")

# Tutorial 2
add_executable(tutorial02_red_triangle 
	tutorial02_red_triangle/tutorial02.cpp
	common/shader.cpp
	common/shader.hpp
)
target_link_libraries(tutorial02_red_triangle
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(tutorial02_red_triangle PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial02_red_triangle/")
create_target_launcher(tutorial02_red_triangle WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial02_red_triangle/")
create_default_target_launcher(tutorial02_red_triangle WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial02_red_triangle/") # tut 1 is not the default or people would complain that tut 2 doesn't work

# Tutorial 3
add_executable(tutorial03_matrices 
	tutorial03_matrices/tutorial03.cpp
	common/shader.cpp
	common/shader.hpp
)
#set_target_properties(tutorial03_matrices PROPERTIES RUNTIME_OUTPUT_DIRECTORY /test1)
target_link_libraries(tutorial03_matrices
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(tutorial03_matrices PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial03_matrices/")
create_target_launcher(tutorial03_matrices WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial03_matrices/") # Visual

# Tutorial 4
add_executable(tutorial04_colored_cube
	tutorial04_colored_cube/tutorial04.cpp
	common/shader.cpp
	common/shader.hpp
)
target_link_libraries(tutorial04_colored_cube
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(tutorial04_colored_cube PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial04_colored_cube/")
create_target_launcher(tutorial04_colored_cube WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial04_colored_cube/")

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
# Xcode and Visual working directories
set_target_properties(tutorial05_textured_cube PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial05_textured_cube/")
create_target_launcher(tutorial05_textured_cube WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial05_textured_cube/")

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
# Xcode and Visual working directories
set_target_properties(tutorial06_keyboard_and_mouse PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial06_keyboard_and_mouse/")
create_target_launcher(tutorial06_keyboard_and_mouse WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial06_keyboard_and_mouse/")

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
# Xcode and Visual working directories
set_target_properties(tutorial07_model_loading PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial07_model_loading/")
create_target_launcher(tutorial07_model_loading WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial07_model_loading/")

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
# Xcode and Visual working directories
set_target_properties(tutorial08_basic_shading PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial08_basic_shading/")
create_target_launcher(tutorial08_basic_shading WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial08_basic_shading/")

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
# Xcode and Visual working directories
set_target_properties(tutorial09_vbo_indexing PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial09_vbo_indexing/")
create_target_launcher(tutorial09_vbo_indexing WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial09_vbo_indexing/")

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
# Xcode and Visual working directories
set_target_properties(tutorial10_transparency PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial10_transparency/")
create_target_launcher(tutorial10_transparency WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial10_transparency/")

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
# Xcode and Visual working directories
set_target_properties(tutorial11_2d_fonts PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial11_2d_fonts/")
create_target_launcher(tutorial11_2d_fonts WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial11_2d_fonts/")

# Tutorial 12
add_executable(tutorial12_extensions
	tutorial12_extensions/tutorial12.cpp
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
target_link_libraries(tutorial12_extensions
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(tutorial12_extensions PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial12_extensions/")
create_target_launcher(tutorial12_extensions WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial12_extensions/")

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
# Xcode and Visual working directories
set_target_properties(tutorial13_normal_mapping PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial13_normal_mapping/")
create_target_launcher(tutorial13_normal_mapping WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial13_normal_mapping/")


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
# Xcode and Visual working directories
set_target_properties(tutorial14_render_to_texture PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial14_render_to_texture/")
create_target_launcher(tutorial14_render_to_texture WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial14_render_to_texture/")


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
# Xcode and Visual working directories
set_target_properties(tutorial15_lightmaps PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial15_lightmaps/")
create_target_launcher(tutorial15_lightmaps WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial15_lightmaps/")

# Tutorial 16, simple version
add_executable(tutorial16_shadowmaps_simple
	tutorial16_shadowmaps/tutorial16_SimpleVersion.cpp
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
target_link_libraries(tutorial16_shadowmaps_simple
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(tutorial16_shadowmaps_simple PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial16_shadowmaps/")
create_target_launcher(tutorial16_shadowmaps_simple WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial16_shadowmaps/")


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
# Xcode and Visual working directories
set_target_properties(tutorial16_shadowmaps PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial16_shadowmaps/")
create_target_launcher(tutorial16_shadowmaps WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial16_shadowmaps/")

# Tutorial 17
add_executable(tutorial17_rotations
	tutorial17_rotations/tutorial17.cpp
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
	common/quaternion_utils.cpp
	common/quaternion_utils.hpp
)
target_link_libraries(tutorial17_rotations
	${ALL_LIBS}
	ANTTWEAKBAR_151_OGLCORE_GLFW
)
# Xcode and Visual working directories
set_target_properties(tutorial17_rotations PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tutorial17_rotations/")
create_target_launcher(tutorial17_rotations WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tutorial17_rotations/")

# User playground
add_executable(playground 
	playground/playground.cpp
	common/shader.cpp
	common/shader.hpp
)
target_link_libraries(playground
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(playground PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/playground/")
create_target_launcher(playground WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/playground/")

SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*" )


if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )
add_custom_command(
   TARGET tutorial01_first_window POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial01_first_window${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial01_first_window/"
)
add_custom_command(
   TARGET tutorial02_red_triangle POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial02_red_triangle${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial02_red_triangle/"
)
add_custom_command(
   TARGET tutorial03_matrices POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial03_matrices${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial03_matrices/"
)
add_custom_command(
   TARGET tutorial04_colored_cube POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial04_colored_cube${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial04_colored_cube/"
)
add_custom_command(
   TARGET tutorial05_textured_cube POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial05_textured_cube${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial05_textured_cube/"
)
add_custom_command(
   TARGET tutorial06_keyboard_and_mouse POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial06_keyboard_and_mouse${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial06_keyboard_and_mouse/"
)
add_custom_command(
   TARGET tutorial07_model_loading POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial07_model_loading${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial07_model_loading/"
)
add_custom_command(
   TARGET tutorial08_basic_shading POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial08_basic_shading${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial08_basic_shading/"
)
add_custom_command(
   TARGET tutorial09_vbo_indexing POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial09_vbo_indexing${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial09_vbo_indexing/"
)
add_custom_command(
   TARGET tutorial10_transparency POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial10_transparency${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial10_transparency/"
)
add_custom_command(
   TARGET tutorial11_2d_fonts POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial11_2d_fonts${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial11_2d_fonts/"
)
add_custom_command(
   TARGET tutorial12_extensions POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial12_extensions${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial12_extensions/"
)
add_custom_command(
   TARGET tutorial13_normal_mapping POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial13_normal_mapping${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial13_normal_mapping/"
)
add_custom_command(
   TARGET tutorial14_render_to_texture POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial14_render_to_texture${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial14_render_to_texture/"
)
add_custom_command(
   TARGET tutorial16_shadowmaps_simple POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial16_shadowmaps_simple${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial16_shadowmaps/"
)
add_custom_command(
   TARGET tutorial16_shadowmaps POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial16_shadowmaps${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial16_shadowmaps/"
)
add_custom_command(
   TARGET tutorial17_rotations POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial17_rotations${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial17_rotations/"
)
add_custom_command(
   TARGET playground POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/playground${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/playground/"
)

elseif (${CMAKE_GENERATOR} MATCHES "Xcode" )

endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )

