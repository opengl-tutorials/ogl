if(MSVC AND NOT "${MSVC_VERSION}" LESS 1400)
	add_definitions( "/MP" )
endif()


add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

### GLFW ###

add_subdirectory (glfw-3.1.2)

include_directories(
	glfw-3.1.2/include/GLFW/
	glew-1.13.0/include/
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(OPENGL_LIBRARY
	${OPENGL_LIBRARY}
	-lGL -lGLU -lXrandr -lXext -lX11 -lrt
	${CMAKE_DL_LIBS}
	${GLFW_LIBRARIES}
)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
set(OPENGL_LIBRARY
	${OPENGL_LIBRARY}
	${CMAKE_DL_LIBS}
	${GLFW_LIBRARIES}
)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

### GLEW ###

set(GLEW_SOURCE
	glew-1.13.0/src/glew.c
)

set(GLEW_HEADERS
)


add_library( GLEW_1130 STATIC
	${GLEW_SOURCE}
	${GLEW_INCLUDE}
)

target_link_libraries(GLEW_1130
	${OPENGL_LIBRARY}
	${EXTRA_LIBS}
)


### ANTTWEAKBAR ###

set(ANTTWEAKBAR_SOURCE
	AntTweakBar-1.16/src/LoadOGL.cpp
	AntTweakBar-1.16/src/LoadOGLCore.cpp
	AntTweakBar-1.16/src/TwColors.cpp
	AntTweakBar-1.16/src/TwBar.cpp
	AntTweakBar-1.16/src/TwEventGLFW.c
	AntTweakBar-1.16/src/TwFonts.cpp
	AntTweakBar-1.16/src/TwMgr.cpp
	AntTweakBar-1.16/src/TwOpenGL.cpp
	AntTweakBar-1.16/src/TwOpenGLCore.cpp
	AntTweakBar-1.16/src/TwPrecomp.cpp
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") # If on Xcode, rename files to .mm
file(COPY ${ANTTWEAKBAR_SOURCE} DESTINATION AntTweakBar-ObjectiveC/)
file(RENAME ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/LoadOGL.cpp      ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/LoadOGL.mm     )
file(RENAME ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/LoadOGLCore.cpp  ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/LoadOGLCore.mm )
file(RENAME ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwColors.cpp     ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwColors.mm    )
file(RENAME ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwBar.cpp        ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwBar.mm       )
file(RENAME ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwEventGLFW.c    ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwEventGLFW.m  )
file(RENAME ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwFonts.cpp      ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwFonts.mm     )
file(RENAME ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwMgr.cpp        ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwMgr.mm       )
file(RENAME ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwOpenGL.cpp     ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwOpenGL.mm    )
file(RENAME ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwOpenGLCore.cpp ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwOpenGLCore.mm)
file(RENAME ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwPrecomp.cpp    ${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwPrecomp.mm   )

set(ANTTWEAKBAR_SOURCE
	${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/LoadOGL.mm
	${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/LoadOGLCore.mm
	${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwColors.mm
	${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwBar.mm
	${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwEventGLFW.m
	${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwFonts.mm
	${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwMgr.mm
	${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwOpenGL.mm
	${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwOpenGLCore.mm
	${CMAKE_BINARY_DIR}/external/AntTweakBar-ObjectiveC/TwPrecomp.mm
)
include_directories(
	${CMAKE_SOURCE_DIR}/external/AntTweakBar-1.16/src/
)
add_definitions(
	-D_MACOSX
)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
add_definitions(
	-D_UNIX
)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
add_definitions(
	-D_WINDOWS
)

endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")


set(ANTTWEAKBAR_HEADERS
	AntTweakBar-1.16/src/AntPerfTimer.h
	AntTweakBar-1.16/src/LoadOGL.h
	AntTweakBar-1.16/src/LoadOGLCore.h
	AntTweakBar-1.16/src/MiniGLFW.h
	AntTweakBar-1.16/src/resource.h
	AntTweakBar-1.16/src/TwBar.h
	AntTweakBar-1.16/src/TwColors.h
	AntTweakBar-1.16/src/TwFonts.h
	AntTweakBar-1.16/src/TwGraph.h
	AntTweakBar-1.16/src/TwMgr.h
	AntTweakBar-1.16/src/TwOpenGL.h
	AntTweakBar-1.16/src/TwOpenGLCore.h
	AntTweakBar-1.16/src/TwPrecomp.h
)

include_directories(
	AntTweakBar-1.16/include/
)

add_library( ANTTWEAKBAR_116_OGLCORE_GLFW STATIC
	${ANTTWEAKBAR_SOURCE}
	${ANTTWEAKBAR_HEADERS}
)

target_link_libraries(ANTTWEAKBAR_116_OGLCORE_GLFW
	${OPENGL_LIBRARY}
	${EXTRA_LIBS}
)

### ASSIMP ###
# AssImp already has a CMakeLists.txt so let's use these

# Compile built-in, modified version of Zlib
include(CheckIncludeFile)
include(CheckTypeSize)
include(CheckFunctionExists)
add_subdirectory( assimp-3.0.1270/contrib/zlib )

# Compile without Boost
include_directories( assimp-3.0.1270/code/BoostWorkaround )
add_definitions( -DASSIMP_BUILD_BOOST_WORKAROUND )

# Compile AssImp
set( LIB_INSTALL_DIR "lib")
set(LIBASSIMP_COMPONENT libassimp3.0-r1270-OGLtuts)
set(ZLIB_LIBRARIES zlib)
set(BUILD_STATIC_LIB ON)
#set(ZLIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/zlib)
add_subdirectory( assimp-3.0.1270/code )


### BULLET ###
# Bullet already has a CMakeLists.txt so let's use these

set(BULLET_VERSION 2.81)
include_directories(
	bullet-2.81-rev2613/src
)
add_subdirectory( bullet-2.81-rev2613/src/BulletSoftBody )
add_subdirectory( bullet-2.81-rev2613/src/BulletCollision )
add_subdirectory( bullet-2.81-rev2613/src/BulletDynamics )
add_subdirectory( bullet-2.81-rev2613/src/LinearMath )

