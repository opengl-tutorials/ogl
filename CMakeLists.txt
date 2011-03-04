# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (Tutorials)

find_package(OpenGL)

# Compile external dependencies 
add_subdirectory (external)

include_directories(
	external/glfw-2.7/include/
	external/glm-0.9.1/
	external/glew-1.5.8/include/
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	GLFW_27
	GLEW_158
)


# Tutorial 1
add_executable(tutorial01 
	tutorial01/tutorial01.cpp
)
target_link_libraries(tutorial01
	${ALL_LIBS}
)
add_custom_command(
   TARGET tutorial01 POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy ${GLEW_OUTPUT_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/tutorial01/"
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial01${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial01/"
)


# Tutorial 2
add_executable(tutorial02 
	tutorial02/tutorial02.cpp
	common/shader.cpp
	common/shader.hpp
)
target_link_libraries(tutorial02
	${ALL_LIBS}
)
add_custom_command(
   TARGET tutorial02 POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy ${GLEW_OUTPUT_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/tutorial02/"
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/tutorial02${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/tutorial02/"
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
   COMMAND ${CMAKE_COMMAND} -E copy ${GLEW_OUTPUT_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/playground/"
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/playground${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/playground/"
)
