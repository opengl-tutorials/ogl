add_definitions(
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

include_directories(
	glfw-2.7/lib/win32/
	glfw-2.7/lib/
	glfw-2.7/include/
	glew-1.5.8/include/
)

set(GLFW_SOURCE	
	glfw-2.7/lib/enable.c 
	glfw-2.7/lib/fullscreen.c 
	glfw-2.7/lib/glext.c 
	glfw-2.7/lib/image.c 
	glfw-2.7/lib/init.c 
	glfw-2.7/lib/input.c 
	glfw-2.7/lib/joystick.c 
	glfw-2.7/lib/stream.c 
	glfw-2.7/lib/tga.c 
	glfw-2.7/lib/thread.c 
	glfw-2.7/lib/time.c 
	glfw-2.7/lib/window.c
)


if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
set(GLFW_SOURCE	${GLFW_SOURCE}
	glfw-2.7/lib/win32/win32_enable.c 
	glfw-2.7/lib/win32/win32_fullscreen.c 
	glfw-2.7/lib/win32/win32_glext.c 
	glfw-2.7/lib/win32/win32_init.c 
	glfw-2.7/lib/win32/win32_joystick.c 
	glfw-2.7/lib/win32/win32_thread.c 
	glfw-2.7/lib/win32/win32_time.c 
	glfw-2.7/lib/win32/win32_window.c 
)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(GLFW_SOURCE	${GLFW_SOURCE}
	glfw-2.7/lib/win32/x11_enable.c 
	glfw-2.7/lib/win32/x11_fullscreen.c 
	glfw-2.7/lib/win32/x11_glext.c 
	glfw-2.7/lib/win32/x11_init.c 
	glfw-2.7/lib/win32/x11_joystick.c 
	glfw-2.7/lib/win32/x11_keysym2unicode.c 
	glfw-2.7/lib/win32/x11_thread.c 
	glfw-2.7/lib/win32/x11_time.c 
	glfw-2.7/lib/win32/x11_window.c
)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
set(GLFW_SOURCE	${GLFW_SOURCE}
	glfw-2.7/lib/win32/cocoa_enable.c 
	glfw-2.7/lib/win32/cocoa_fullscreen.c 
	glfw-2.7/lib/win32/cocoa_glext.c 
	glfw-2.7/lib/win32/cocoa_init.c 
	glfw-2.7/lib/win32/cocoa_joystick.c 
	glfw-2.7/lib/win32/cocoa_thread.c 
	glfw-2.7/lib/win32/cocoa_time.c 
	glfw-2.7/lib/win32/cocoa_window.c 
)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

set(GLFW_HEADERS
	glfw-2.7/lib/win32/platform.h
	glfw-2.7/lib/internal.h
)

add_library( GLFW_27 STATIC
	${GLFW_SOURCE}
	${GLFW_HEADERS}
)

target_link_libraries(GLFW_27
	${OPENGL_LIBRARY}
)



set(GLEW_SOURCE
	glew-1.5.8/src/glew.c
)

set(GLEW_HEADERS
)


add_library( GLEW_158 STATIC
	${GLEW_SOURCE}
	${GLEW_INCLUDE}
)

target_link_libraries(GLEW_158
	${OPENGL_LIBRARY}
)

