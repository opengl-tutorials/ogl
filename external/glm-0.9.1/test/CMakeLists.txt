function(glmCreateTestGTC NAME)
	set(SAMPLE_NAME test-${NAME})
	add_executable(${SAMPLE_NAME} ${NAME}.cpp ../test.hpp ../test.cpp)
	#For GLM 0.9.2, not ready yet
	#add_test( 
	#    NAME ${SAMPLE_NAME}
	#    COMMAND $<TARGET_FILE:${SAMPLE_NAME}> )
endfunction()

add_subdirectory(bug)
add_subdirectory(core)
add_subdirectory(gtc)
add_subdirectory(gtx)


