function(glmCreateBenchGTC NAME)
	set(SAMPLE_NAME bench-${NAME})

	add_executable(${SAMPLE_NAME} ${NAME}.cpp)
endfunction(glmCreateBenchGTC)

add_subdirectory(core)
add_subdirectory(gtc)
add_subdirectory(gtx)


