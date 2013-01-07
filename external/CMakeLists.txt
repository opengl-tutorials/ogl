add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

### GLFW ###


set(GLFW_SOURCE	
	glfw-2.7.6/lib/enable.c 
	glfw-2.7.6/lib/fullscreen.c 
	glfw-2.7.6/lib/glext.c 
	glfw-2.7.6/lib/image.c 
	glfw-2.7.6/lib/init.c 
	glfw-2.7.6/lib/input.c 
	glfw-2.7.6/lib/joystick.c 
	glfw-2.7.6/lib/stream.c 
	glfw-2.7.6/lib/tga.c 
	glfw-2.7.6/lib/thread.c 
	glfw-2.7.6/lib/time.c 
	glfw-2.7.6/lib/window.c
)


if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
set(GLFW_SOURCE	${GLFW_SOURCE}
	glfw-2.7.6/lib/win32/win32_enable.c 
	glfw-2.7.6/lib/win32/win32_fullscreen.c 
	glfw-2.7.6/lib/win32/win32_glext.c 
	glfw-2.7.6/lib/win32/win32_init.c 
	glfw-2.7.6/lib/win32/win32_joystick.c 
	glfw-2.7.6/lib/win32/win32_thread.c 
	glfw-2.7.6/lib/win32/win32_time.c 
	glfw-2.7.6/lib/win32/win32_window.c 
)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(GLFW_SOURCE	${GLFW_SOURCE}
	glfw-2.7.6/lib/x11/x11_enable.c 
	glfw-2.7.6/lib/x11/x11_fullscreen.c 
	glfw-2.7.6/lib/x11/x11_glext.c 
	glfw-2.7.6/lib/x11/x11_init.c 
	glfw-2.7.6/lib/x11/x11_joystick.c 
	glfw-2.7.6/lib/x11/x11_keysym2unicode.c 
	glfw-2.7.6/lib/x11/x11_thread.c 
	glfw-2.7.6/lib/x11/x11_time.c 
	glfw-2.7.6/lib/x11/x11_window.c
)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
set(GLFW_OBJC_SOURCE
	glfw-2.7.6/lib/cocoa/cocoa_enable.m 
	glfw-2.7.6/lib/cocoa/cocoa_fullscreen.m 
	glfw-2.7.6/lib/cocoa/cocoa_glext.m 
	glfw-2.7.6/lib/cocoa/cocoa_init.m 
	glfw-2.7.6/lib/cocoa/cocoa_joystick.m 
	glfw-2.7.6/lib/cocoa/cocoa_thread.c 
	glfw-2.7.6/lib/cocoa/cocoa_time.m 
	glfw-2.7.6/lib/cocoa/cocoa_window.m 
)
set(GLFW_SOURCE	${GLFW_SOURCE} ${GLFW_OBJC_SOURCE})

set_source_files_properties(${GLFW_SOURCE} 
	PROPERTIES COMPILE_FLAGS "-x objective-c") #-fobjc-exceptions


#add_definitions(-D_MACOSX)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")


if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
set(GLFW_HEADERS
	glfw-2.7.6/lib/win32/platform.h
	glfw-2.7.6/lib/internal.h
)
include_directories(
	glfw-2.7.6/lib/win32/
	glfw-2.7.6/lib/
	glfw-2.7.6/include/
	glew-1.9.0/include/
)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(GLFW_HEADERS
	glfw-2.7.6/lib/x11/platform.h
	glfw-2.7.6/lib/internal.h
)
include_directories(
	glfw-2.7.6/lib/x11/
	glfw-2.7.6/lib/
	glfw-2.7.6/include/
	glew-1.9.0/include/
)
set(OPENGL_LIBRARY
	${OPENGL_LIBRARY}
	-lGL -lGLU -lXrandr -lXext -lX11 -lrt
	${CMAKE_DL_LIBS}
)
#Since there is no easy wat to choose between _GLFW_HAS_GLXGETPROCADDRESS, _GLFW_HAS_GLXGETPROCADDRESSARB, _GLFW_HAS_GLXGETPROCADDRESSEXT and _GLFW_HAS_DLOPEN,
#I force the latter, which as least should exist (and work?) everywhere.
add_definitions(
	-D_GLFW_HAS_DLOPEN
	-D_GLFW_HAS_XRANDR
)
add_definitions(-D_UNIX)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
set(GLFW_HEADERS
	glfw-2.7.6/lib/cocoa/platform.h
	glfw-2.7.6/lib/internal.h
)
include_directories(
	glfw-2.7.6/lib/cocoa/
	glfw-2.7.6/lib/
	glfw-2.7.6/include/
	glew-1.9.0/include/
)
SET(EXTRA_LIBS "-framework Cocoa -framework OpenGL -framework IOKit -framework Foundation -framework AppKit")
add_definitions(-D_MACOSX -ObjC++)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")


add_library( GLFW_276 STATIC
	${GLFW_SOURCE}
	${GLFW_HEADERS}
)

target_link_libraries(GLFW_276
	${OPENGL_LIBRARY}
)

### GLEW ###

set(GLEW_SOURCE
	glew-1.9.0/src/glew.c
)

set(GLEW_HEADERS
)


add_library( GLEW_190 STATIC
	${GLEW_SOURCE}
	${GLEW_INCLUDE}
)

target_link_libraries(GLEW_190
	${OPENGL_LIBRARY}
	${EXTRA_LIBS}
)


### ANTTWEAKBAR ###

set(ANTTWEAKBAR_SOURCE
	AntTweakBar-1.15/src/LoadOGL.cpp
	AntTweakBar-1.15/src/LoadOGLCore.cpp
	AntTweakBar-1.15/src/TwColors.cpp
	AntTweakBar-1.15/src/TwBar.cpp
	AntTweakBar-1.15/src/TwEventGLFW.c
	AntTweakBar-1.15/src/TwFonts.cpp
	AntTweakBar-1.15/src/TwMgr.cpp
	AntTweakBar-1.15/src/TwOpenGL.cpp
	AntTweakBar-1.15/src/TwOpenGLCore.cpp
	AntTweakBar-1.15/src/TwPrecomp.cpp
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
	${CMAKE_SOURCE_DIR}/external/AntTweakBar-1.15/src/
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
	AntTweakBar-1.15/src/AntPerfTimer.h
	AntTweakBar-1.15/src/LoadOGL.h
	AntTweakBar-1.15/src/LoadOGLCore.h
	AntTweakBar-1.15/src/MiniGLFW.h
	AntTweakBar-1.15/src/resource.h
	AntTweakBar-1.15/src/TwBar.h
	AntTweakBar-1.15/src/TwColors.h
	AntTweakBar-1.15/src/TwFonts.h
	AntTweakBar-1.15/src/TwGraph.h
	AntTweakBar-1.15/src/TwMgr.h
	AntTweakBar-1.15/src/TwOpenGL.h
	AntTweakBar-1.15/src/TwOpenGLCore.h
	AntTweakBar-1.15/src/TwPrecomp.h
)

include_directories(
	AntTweakBar-1.15/include/
)

add_library( ANTTWEAKBAR_151_OGLCORE_GLFW STATIC
	${ANTTWEAKBAR_SOURCE}
	${ANTTWEAKBAR_HEADERS}
)

target_link_libraries(ANTTWEAKBAR_151_OGLCORE_GLFW
	${OPENGL_LIBRARY}
)

