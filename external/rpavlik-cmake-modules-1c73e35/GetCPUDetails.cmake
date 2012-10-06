# - Set a number of variables to indicate things about the current CPU and OS
#
#  CPU_INTEL
#  CPU_EXE_64BIT
#  CPU_EXE_32BIT
#  CPU_HAS_SSE
#  CPU_HAS_SSE2
#  CPU_HAS_SSE3
#  CPU_HAS_SSSE3
#  CPU_HAS_SSE4_1
#  CPU_HAS_SSE4_2
#
# Requires these CMake modules:
#  no additional modules required
#
# Original Author:
# 2010 Ryan Pavlik <rpavlik@iastate.edu> <abiryan@ryand.net>
# http://academic.cleardefinition.com
# Iowa State University HCI Graduate Program/VRAC
#
# Copyright Iowa State University 2009-2010.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)
#


if(__get_cpu_details)
	return()
endif()
set(__get_cpu_details YES)

function(get_cpu_details)
	option(CPUDETAILS_VERBOSE
		"Should we display results of the CPU info check?"
		NO)
	mark_as_advanced(CPUDETAILS_VERBOSE)

	###
	# CPU_INTEL

	if("${CMAKE_SYSTEM_PROCESSOR}" MATCHES "x86_64" OR "${CMAKE_SYSTEM_PROCESSOR}" MATCHES "i[3456]86")
		set(CPU_INTEL YES)
	elseif(APPLE)
		# Mac Intel boxes return i386 in 10.5 - so assume this is a PPC
		set(CPU_INTEL NO)
	else()
		# TODO: Assuming yes in case of doubt - probably not a great idea
		set(CPU_INTEL YES)
	endif()

	set(CPU_INTEL
		${CPU_INTEL}
		CACHE
		INTERNAL
		"Intel x86 or x86_64 architecture machine?")

	###
	# CPU_EXE_64BIT/32BIT
	if(CMAKE_SIZEOF_VOID_P EQUAL 8)
		set(CPU_EXE_64BIT ON)
		set(CPU_EXE_32BIT OFF)
	else()
		set(CPU_EXE_64BIT OFF)
		set(CPU_EXE_32BIT ON)
	endif()

	###
	# CPU_HAS_SSE/SSE2/SSE3/SSSE3/SSE4.1/SSE4.2
	if(CPU_INTEL)
		if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
			# Use /proc/cpuinfo to find this out.
			file(STRINGS "/proc/cpuinfo" _cpuinfo)
			if(_cpuinfo MATCHES "(sse)|(xmm)")
				set(CPU_HAS_SSE YES)
			else()
				set(CPU_HAS_SSE NO)
			endif()

			if(_cpuinfo MATCHES "(sse2)|(xmm2)")
				set(CPU_HAS_SSE2 YES)
			else()
				set(CPU_HAS_SSE2 NO)
			endif()

			if(_cpuinfo MATCHES "(sse3)|(xmm3)")
				set(CPU_HAS_SSE3 YES)
			else()
				set(CPU_HAS_SSE3 NO)
			endif()

			if(_cpuinfo MATCHES "ssse3")
				set(CPU_HAS_SSSE3 YES)
			else()
				set(CPU_HAS_SSSE3 NO)
			endif()

			if(_cpuinfo MATCHES "(sse4_1)|(xmm4_1)")
				set(CPU_HAS_SSE4_1 YES)
			else()
				set(CPU_HAS_SSE4_1 NO)
			endif()

			if(_cpuinfo MATCHES "(sse4_2)|(xmm4_2)")
				set(CPU_HAS_SSE4_2 YES)
			else()
				set(CPU_HAS_SSE4_2 NO)
			endif()

		elseif(APPLE)
			# Mac OS X Intel requires SSE3
			set(CPU_HAS_SSE YES)
			set(CPU_HAS_SSE2 YES)
			set(CPU_HAS_SSE3 YES)
			set(CPU_HAS_SSSE3 NO)
			set(CPU_HAS_SSE4_1 NO)
			set(CPU_HAS_SSE4_2 NO)
		elseif(WIN32)
			if(CPU_EXE_64BIT)
				#TODO: Assume only common-denominator for 64-bit machines,
				# since I don't know how to check.
				set(CPU_HAS_SSE YES)
				set(CPU_HAS_SSE2 YES)
				set(CPU_HAS_SSE3 NO)
				set(CPU_HAS_SSSE3 NO)
				set(CPU_HAS_SSE4_1 NO)
				set(CPU_HAS_SSE4_2 NO)
			else()
				#TODO:  Assume no SSE, since I don't know how to check.
				set(CPU_HAS_SSE NO)
				set(CPU_HAS_SSE2 NO)
				set(CPU_HAS_SSE3 NO)
				set(CPU_HAS_SSSE3 NO)
				set(CPU_HAS_SSE4_1 NO)
				set(CPU_HAS_SSE4_2 NO)
			endif()
		endif()
	endif()

	set(CPU_INTEL
		${CPU_INTEL}
		CACHE
		INTERNAL
		"Intel x86 or x86_64 architecture machine?")

	foreach(_var
		CPU_EXE_64BIT
		CPU_EXE_32BIT
		CPU_HAS_SSE
		CPU_HAS_SSE2
		CPU_HAS_SSE3
		CPU_HAS_SSSE3
		CPU_HAS_SSE4_1
		CPU_HAS_SSE4_2)
		set(${_var} ${${_var}} CACHE INTERNAL "")
	endforeach()

	if(CPUDETAILS_VERBOSE)
		foreach(_var
			CPU_INTEL
			CPU_EXE_64BIT
			CPU_EXE_32BIT
			CPU_HAS_SSE
			CPU_HAS_SSE2
			CPU_HAS_SSE3
			CPU_HAS_SSSE3
			CPU_HAS_SSE4_1
			CPU_HAS_SSE4_2)
			get_property(_help CACHE ${_var} PROPERTY HELPSTRING)
			message(STATUS "[get_cpu_details] ${_var} (${_help}): ${${_var}}")
		endforeach()
	endif()
endfunction()
