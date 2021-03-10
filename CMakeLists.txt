# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (ogl-hw)

find_package(OpenGL REQUIRED)


if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
	message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()



# Compile external dependencies 
add_subdirectory (external)

# On Visual 2005 and above, this module can set the debug working directory
cmake_policy(SET CMP0026 OLD)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-fe2273")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

if(INCLUDE_DISTRIB)
	add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)



include_directories(
	external/AntTweakBar-1.16/include/
	external/glfw-3.1.2/include/
	external/glm-0.9.7.1/
	external/glew-1.13.0/include/
	external/assimp-3.0.1270/include/
	external/bullet-2.81-rev2613/src/
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_1130
	)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

# task 1: triangles
add_executable(task_1-triangles
	task_1/triangles/triangles.cpp
	common/shader.cpp
	common/shader.hpp

		task_1/triangles/YellowTriangleFragmentShader.glsl
		task_1/triangles/PurpleTriangleFragmentShader.glsl
		task_1/triangles/TransformVertexShader.glsl
		)
target_link_libraries(task_1-triangles
	${ALL_LIBS}
	)
# Xcode and Visual working directories
set_target_properties(task_1-triangles PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/task_1/triangles/")
create_target_launcher(task_1-triangles WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/task_1/triangles/")
create_default_target_launcher(task_1-triangles WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/task_1/triangles/")

# task 1: three dim
add_executable(task_1-three_dim
		task_1/three_dim/three_dim.cpp

		common/shader.cpp
		common/shader.hpp

		task_1/three_dim/ColorFragmentShader.glsl
		task_1/triangles/TransformVertexShader.glsl
		)
target_link_libraries(task_1-three_dim
		${ALL_LIBS}
		)
# Xcode and Visual working directories
set_target_properties(task_1-three_dim PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/task_1/three_dim/")
create_target_launcher(task_1-three_dim WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/task_1/three_dim/")
create_default_target_launcher(task_1-three_dim WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/task_1/three_dim/")











SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*" )
SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*shader$" )

if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )
	add_custom_command(
		TARGET task_1-triangles POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/task_1-triangles${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/task_1/triangles/"
	)

	add_custom_command(
			TARGET task_1-three_dim POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/task_1-three_dim${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/task_1/three_dim/"
	)
elseif (${CMAKE_GENERATOR} MATCHES "Xcode" )

endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )
