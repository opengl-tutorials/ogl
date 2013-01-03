
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")

	add_executable(selectoptimus
		selectoptimus.cpp
	)
	
	include_directories(
		external/NVAPI-R304-developer/
	)

	if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
		#link_directories("${CMAKE_CURRENT_SOURCE_DIR}/external/NVAPI-R304-developer/amd64/")
		target_link_libraries(selectoptimus ${CMAKE_CURRENT_SOURCE_DIR}/external/NVAPI-R304-developer/amd64/nvapi64.lib)
	else( CMAKE_SIZEOF_VOID_P EQUAL 8 )
		#link_directories("${CMAKE_CURRENT_SOURCE_DIR}/external/NVAPI-R304-developer/x86/")
		target_link_libraries(selectoptimus ${CMAKE_CURRENT_SOURCE_DIR}/external/NVAPI-R304-developer/x86/nvapi.lib)
	endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )
 
	add_custom_command(
	   TARGET selectoptimus POST_BUILD
	   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/selectoptimus${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}"
	)
	
endif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
