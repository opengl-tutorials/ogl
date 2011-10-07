///////////////////////////////////////////////////////////////////////////////////////////////////
// OpenGL Mathematics Copyright (c) 2005 - 2011 G-Truc Creation (www.g-truc.net)
///////////////////////////////////////////////////////////////////////////////////////////////////
// Created : 2006-11-13
// Updated : 2011-01-26
// Licence : This source is under MIT License
// File    : glm/setup.hpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef glm_setup
#define glm_setup

///////////////////////////////////////////////////////////////////////////////////////////////////
// Version

#define GLM_VERSION					91
#define GLM_VERSION_MAJOR			0
#define GLM_VERSION_MINOR			9
#define GLM_VERSION_PATCH			1
#define GLM_VERSION_REVISION		0

///////////////////////////////////////////////////////////////////////////////////////////////////
// Compiler

// User defines: GLM_FORCE_COMPILER_UNKNOWN

#define GLM_COMPILER_UNKNOWN		0x00000000

// Visual C++ defines
#define GLM_COMPILER_VC				0x01000000
#define GLM_COMPILER_VC2			0x01000010
#define GLM_COMPILER_VC4			0x01000020
#define GLM_COMPILER_VC5			0x01000030
#define GLM_COMPILER_VC6			0x01000040
#define GLM_COMPILER_VC2002			0x01000050
#define GLM_COMPILER_VC2003			0x01000060
#define GLM_COMPILER_VC2005			0x01000070
#define GLM_COMPILER_VC2008			0x01000080
#define GLM_COMPILER_VC2010			0x01000090

// GCC defines
#define GLM_COMPILER_GCC            0x02000000
#define GLM_COMPILER_GCC30			0x02000010
#define GLM_COMPILER_GCC31			0x02000020
#define GLM_COMPILER_GCC32			0x02000030
#define GLM_COMPILER_GCC33			0x02000040
#define GLM_COMPILER_GCC34			0x02000050
#define GLM_COMPILER_GCC35			0x02000060
#define GLM_COMPILER_GCC40			0x02000070
#define GLM_COMPILER_GCC41			0x02000080
#define GLM_COMPILER_GCC42			0x02000090
#define GLM_COMPILER_GCC43			0x020000A0
#define GLM_COMPILER_GCC44			0x020000B0
#define GLM_COMPILER_GCC45			0x020000C0
#define GLM_COMPILER_GCC46			0x020000D0
#define GLM_COMPILER_GCC47			0x020000E0
#define GLM_COMPILER_GCC48			0x020000F0
#define GLM_COMPILER_GCC49			0x02000100
#define GLM_COMPILER_GCC50			0x02000200

// G++ command line to display defined
// echo "" | g++ -E -dM -x c++ - | sort

// Borland C++ defines. How to identify BC?
#define GLM_COMPILER_BC				0x03000000
#define GLM_COMPILER_BCB4			0x03000100
#define GLM_COMPILER_BCB5			0x03000200
#define GLM_COMPILER_BCB6			0x03000300
//#define GLM_COMPILER_BCBX			0x03000400 // What's the version value?
#define GLM_COMPILER_BCB2009		0x03000500

#define GLM_MODEL_32				0x00000010
#define GLM_MODEL_64				0x00000020

// CodeWarrior
#define GLM_COMPILER_CODEWARRIOR	0x04000000

// Force generic C++ compiler
#ifdef GLM_FORCE_COMPILER_UNKNOWN
#		define GLM_COMPILER GLM_COMPILER_UNKNOWN
// Visual C++
#elif defined(_MSC_VER)
#	if _MSC_VER == 900
#		define GLM_COMPILER GLM_COMPILER_VC2
#	elif _MSC_VER == 1000
#		define GLM_COMPILER GLM_COMPILER_VC4
#	elif _MSC_VER == 1100
#		define GLM_COMPILER GLM_COMPILER_VC5
#	elif _MSC_VER == 1200
#		define GLM_COMPILER GLM_COMPILER_VC6
#	elif _MSC_VER == 1300
#		define GLM_COMPILER GLM_COMPILER_VC2002
#	elif _MSC_VER == 1310
#		define GLM_COMPILER GLM_COMPILER_VC2003
#	elif _MSC_VER == 1400
#		define GLM_COMPILER GLM_COMPILER_VC2005
#	elif _MSC_VER == 1500
#		define GLM_COMPILER GLM_COMPILER_VC2008
#	elif _MSC_VER == 1600
#		define GLM_COMPILER GLM_COMPILER_VC2010
#	else//_MSC_VER
#		define GLM_COMPILER GLM_COMPILER_VC
#	endif//_MSC_VER

// G++
#elif defined(__GNUC__)
#	if   (__GNUC__ == 3) && (__GNUC_MINOR__ == 2)
#		define GLM_COMPILER GLM_COMPILER_GCC32
#	elif (__GNUC__ == 3) && (__GNUC_MINOR__ == 3)
#		define GLM_COMPILER GLM_COMPILER_GCC33
#	elif (__GNUC__ == 3) && (__GNUC_MINOR__ == 4)
#		define GLM_COMPILER GLM_COMPILER_GCC34
#	elif (__GNUC__ == 3) && (__GNUC_MINOR__ == 5)
#		define GLM_COMPILER GLM_COMPILER_GCC35
#	elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 0)
#		define GLM_COMPILER GLM_COMPILER_GCC40
#	elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 1)
#		define GLM_COMPILER GLM_COMPILER_GCC41
#	elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 2)
#		define GLM_COMPILER GLM_COMPILER_GCC42
#	elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 3)
#		define GLM_COMPILER GLM_COMPILER_GCC43
#	elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 4)
#		define GLM_COMPILER GLM_COMPILER_GCC44
#	elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 5)
#		define GLM_COMPILER GLM_COMPILER_GCC45
#	elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 6)
#		define GLM_COMPILER GLM_COMPILER_GCC46
#	elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 7)
#		define GLM_COMPILER GLM_COMPILER_GCC47
#	elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 8)
#		define GLM_COMPILER GLM_COMPILER_GCC48
#	elif (__GNUC__ == 4) && (__GNUC_MINOR__ == 9)
#		define GLM_COMPILER GLM_COMPILER_GCC49
#	elif (__GNUC__ == 5) && (__GNUC_MINOR__ == 0)
#		define GLM_COMPILER GLM_COMPILER_GCC50
#	else
#		define GLM_COMPILER GLM_COMPILER_GCC
#	endif

// Borland C++
#elif defined(_BORLANDC_)
#	if defined(VER125)
#		define GLM_COMPILER GLM_COMPILER_BCB4
#	elif defined(VER130)
#		define GLM_COMPILER GLM_COMPILER_BCB5
#	elif defined(VER140)
#		define GLM_COMPILER GLM_COMPILER_BCB6
#	elif defined(VER200)
#		define GLM_COMPILER GLM_COMPILER_BCB2009
#	else
#		define GLM_COMPILER GLM_COMPILER_BC
#	endif

// Codewarrior
#elif defined(__MWERKS__)
#	define GLM_COMPILER GLM_COMPILER_CODEWARRIOR

#else
#	define GLM_COMPILER GLM_COMPILER_UNKNOWN
#endif

#ifndef GLM_COMPILER
#error "GLM_COMPILER undefined, your compiler may not be supported by GLM. Add #define GLM_COMPILER 0 to ignore this message."
#endif//GLM_COMPILER

// Report compiler detection
#if(defined(GLM_MESSAGES) && !defined(GLM_MESSAGE_COMPILER_DISPLAYED))
#	define GLM_MESSAGE_COMPILER_DISPLAYED
#	if(defined(GLM_COMPILER) && GLM_COMPILER & GLM_COMPILER_VC)
#		pragma message("GLM: Visual C++ compiler detected")
#	elif(defined(GLM_COMPILER) && GLM_COMPILER & GLM_COMPILER_GCC)
#		pragma message("GLM: GCC compiler detected")
#	elif(defined(GLM_COMPILER) && GLM_COMPILER & GLM_COMPILER_BC)
#		pragma message("GLM: Borland compiler detected but not supported")
#	elif(defined(GLM_COMPILER) && GLM_COMPILER & GLM_COMPILER_CODEWARRIOR)
#		pragma message("GLM: Codewarrior compiler detected but not supported")
#	else
#		pragma message("GLM: Compiler not detected")
#	endif
#endif//GLM_MESSAGE

/////////////////
// Build model //

#if(GLM_COMPILER & GLM_COMPILER_VC)
#	if defined(_M_X64)
#		define GLM_MODEL	GLM_MODEL_64
#	else
#		define GLM_MODEL	GLM_MODEL_32
#	endif//_M_X64
#elif(GLM_COMPILER & GLM_COMPILER_GCC)
#	if(defined(__WORDSIZE) && (__WORDSIZE == 64)) || defined(__arch64__) || defined(__LP64__) || defined(__x86_64__)
#		define GLM_MODEL	GLM_MODEL_64
#	else
#		define GLM_MODEL	GLM_MODEL_32
#	endif//
#else
#	define GLM_MODEL	GLM_MODEL_32
#endif//

#if(!defined(GLM_MODEL) && GLM_COMPILER != 0)
#error "GLM_MODEL undefined, your compiler may not be supported by GLM. Add #define GLM_MODEL 0 to ignore this message."
#endif//GLM_MODEL

#if(defined(GLM_MESSAGES) && !defined(GLM_MESSAGE_MODEL_DISPLAYED))
#	define GLM_MESSAGE_MODEL_DISPLAYED
#	if(GLM_MODEL == GLM_MODEL_64)
#		pragma message("GLM: 64 bits model")
#	elif(GLM_MODEL == GLM_MODEL_32)
#		pragma message("GLM: 32 bits model")
#	endif//GLM_MODEL
#endif//GLM_MESSAGE

/////////////////
// C++ Version //

// User defines: GLM_FORCE_CXX98

#define GLM_LANG_CXX			0
#define GLM_LANG_CXX98			1
#define GLM_LANG_CXX0X			2
#define GLM_LANG_CXXMS			3
#define GLM_LANG_CXXGNU			4

#if(defined(GLM_FORCE_CXX98))
#	define GLM_LANG GLM_LANG_CXX98
#elif(((GLM_COMPILER & GLM_COMPILER_GCC) == GLM_COMPILER_GCC) && defined(__GXX_EXPERIMENTAL_CXX0X__)) // -std=c++0x or -std=gnu++0x
#	define GLM_LANG GLM_LANG_CXX0X
#elif(GLM_COMPILER == GLM_COMPILER_VC2010) //_MSC_EXTENSIONS for MS language extensions
#	define GLM_LANG GLM_LANG_CXX0X
#elif(((GLM_COMPILER & GLM_COMPILER_GCC) == GLM_COMPILER_GCC) && defined(__STRICT_ANSI__))
#	define GLM_LANG GLM_LANG_CXX98
#elif(((GLM_COMPILER & GLM_COMPILER_VC) == GLM_COMPILER_VC) && !defined(_MSC_EXTENSIONS))
#	define GLM_LANG GLM_LANG_CXX98
#else
#	define GLM_LANG GLM_LANG_CXX
#endif

#if(defined(GLM_MESSAGES) && !defined(GLM_MESSAGE_LANG_DISPLAYED))
#	define GLM_MESSAGE_LANG_DISPLAYED
#	if(GLM_LANG == GLM_LANG_CXX98)
#		pragma message("GLM: C++98")
#	elif(GLM_LANG == GLM_LANG_CXX0X)
#		pragma message("GLM: C++0x")
#	endif//GLM_MODEL
#endif//GLM_MESSAGE

/////////////////
// Platform 

// User defines: GLM_FORCE_PURE GLM_FORCE_SSE2 GLM_FORCE_AVX

#define GLM_ARCH_PURE		0x0000 //(0x0000)
#define GLM_ARCH_SSE2		0x0001 //(0x0001)
#define GLM_ARCH_SSE3		0x0003 //(0x0002 | GLM_ARCH_SSE2)
#define GLM_ARCH_AVX		0x0007 //(0x0004 | GLM_ARCH_SSE3 | GLM_ARCH_SSE2)

#if(defined(GLM_FORCE_PURE))
#	define GLM_ARCH GLM_ARCH_PURE
#elif(defined(GLM_FORCE_AVX))
#	define GLM_ARCH GLM_ARCH_AVX
#elif(defined(GLM_FORCE_SSE3))
#	define GLM_ARCH GLM_ARCH_SSE3
#elif(defined(GLM_FORCE_SSE2))
#	define GLM_ARCH GLM_ARCH_SSE2
#elif((GLM_COMPILER & GLM_COMPILER_VC) && (defined(_M_IX86) || defined(_M_X64)))
#	if(defined(_M_CEE_PURE))
#		define GLM_ARCH GLM_ARCH_PURE
#	elif(GLM_COMPILER >= GLM_COMPILER_VC2010)
#		if(_MSC_FULL_VER >= 160031118) //160031118: VC2010 SP1 beta full version
#			define GLM_ARCH GLM_ARCH_AVX //GLM_ARCH_AVX (Require SP1)
#		else
#			define GLM_ARCH GLM_ARCH_SSE3
#		endif
#	elif(GLM_COMPILER >= GLM_COMPILER_VC2008) 
#		define GLM_ARCH GLM_ARCH_SSE3
#	elif(GLM_COMPILER >= GLM_COMPILER_VC2005)
#		define GLM_ARCH GLM_ARCH_SSE2
#	else
#		define GLM_ARCH GLM_ARCH_PURE
#	endif
#elif((GLM_COMPILER & GLM_COMPILER_GCC) && (defined(__i386__) || defined(__x86_64__)))
#	if(defined(__AVX__))
#		define GLM_ARCH GLM_ARCH_AVX
#	elif(defined(__SSE3__))
#		define GLM_ARCH GLM_ARCH_SSE3
#	elif(defined(__SSE2__))
#		define GLM_ARCH GLM_ARCH_SSE2
#	else
#		define GLM_ARCH GLM_ARCH_PURE
#	endif
#else
#	define GLM_ARCH GLM_ARCH_PURE
#endif

#if(GLM_ARCH != GLM_ARCH_PURE)
#if((GLM_ARCH & GLM_ARCH_AVX) == GLM_ARCH_AVX)
#	include <immintrin.h>
#endif//GLM_ARCH
#if((GLM_ARCH & GLM_ARCH_SSE3) == GLM_ARCH_SSE3)
#	include <pmmintrin.h>
#endif//GLM_ARCH
#if((GLM_ARCH & GLM_ARCH_SSE2) == GLM_ARCH_SSE2)
#	include <emmintrin.h>
#endif//GLM_ARCH
#endif//(GLM_ARCH != GLM_ARCH_PURE)

#if(defined(GLM_MESSAGES) && !defined(GLM_MESSAGE_ARCH_DISPLAYED))
#	define GLM_MESSAGE_ARCH_DISPLAYED
#	if(GLM_ARCH == GLM_ARCH_PURE)
#		pragma message("GLM: Platform independent")
#	elif(GLM_ARCH == GLM_ARCH_SSE2)
#		pragma message("GLM: SSE2 build platform")
#	elif(GLM_ARCH == GLM_ARCH_SSE3)
#		pragma message("GLM: SSE3 build platform")
#	elif(GLM_ARCH == GLM_ARCH_AVX)
#		pragma message("GLM: AVX build platform")
#	endif//GLM_ARCH
#endif//GLM_MESSAGE

///////////////////////////////////////////////////////////////////////////////////////////////////
// Components

//#define GLM_FORCE_ONLY_XYZW
#define GLM_COMPONENT_GLSL_NAMES			0 
#define GLM_COMPONENT_ONLY_XYZW				1 // To disable multiple vector component names access.
#define GLM_COMPONENT_MS_EXT				2 // To use anonymous union to provide multiple component names access for class valType. Visual C++ only.

#ifndef GLM_FORCE_ONLY_XYZW
#	if((GLM_COMPILER & GLM_COMPILER_VC) && defined(_MSC_EXTENSIONS))
#		define GLM_COMPONENT GLM_COMPONENT_MS_EXT
#	else
#		define GLM_COMPONENT GLM_COMPONENT_GLSL_NAMES
#	endif
#else
#	define GLM_COMPONENT GLM_COMPONENT_ONLY_XYZW
#endif

#if((GLM_COMPONENT == GLM_COMPONENT_MS_EXT) && !(GLM_COMPILER & GLM_COMPILER_VC))
#	error "GLM_COMPONENT value is GLM_COMPONENT_MS_EXT but this is not allowed with the current compiler."
#endif

#if(defined(GLM_MESSAGES) && !defined(GLM_MESSAGE_COMPONENT_DISPLAYED))
#	define GLM_MESSAGE_COMPONENT_DISPLAYED
#	if(GLM_COMPONENT == GLM_COMPONENT_GLSL_NAMES)
#		pragma message("GLM: GLSL multiple vector component names")
#	elif(GLM_COMPONENT == GLM_COMPONENT_ONLY_XYZW)
#		pragma message("GLM: x,y,z,w vector component names only")
#	elif(GLM_COMPONENT == GLM_COMPONENT_MS_EXT)
#		pragma message("GLM: Multiple vector component names through Visual C++ language extensions")
#	else
#		error "GLM_COMPONENT value unknown"
#	endif//GLM_MESSAGE_COMPONENT_DISPLAYED
#endif//GLM_MESSAGE

///////////////////////////////////////////////////////////////////////////////////////////////////
// Static assert

#if(GLM_LANG == GLM_LANG_CXX0X)
#	define GLM_STATIC_ASSERT(x, message) static_assert(x, message)
#elif(defined(BOOST_STATIC_ASSERT))
#	define GLM_STATIC_ASSERT(x, message) BOOST_STATIC_ASSERT(x)
#elif(GLM_COMPILER & GLM_COMPILER_VC)
#	define GLM_STATIC_ASSERT(x, message) typedef char __CASSERT__##__LINE__[(x) ? 1 : -1]
#else
#	define GLM_STATIC_ASSERT(x, message)
#	define GLM_STATIC_ASSERT_NULL
#endif//GLM_LANG

///////////////////////////////////////////////////////////////////////////////////////////////////
// inline 

// User defines: GLM_FORCE_INLINE

#if(defined(GLM_FORCE_INLINE))
#	if((GLM_COMPILER & GLM_COMPILER_VC) && (GLM_COMPILER >= GLM_COMPILER_VC2005))
#		define GLM_INLINE __forceinline
#	elif((GLM_COMPILER & GLM_COMPILER_GCC) && (GLM_COMPILER >= GLM_COMPILER_VC2005))
#		define GLM_INLINE __attribute__((always_inline))
#	else
#		define GLM_INLINE inline
#	endif//GLM_COMPILER
#else
#	define GLM_INLINE inline
#endif//defined(GLM_FORCE_INLINE)

///////////////////////////////////////////////////////////////////////////////////////////////////
// Swizzle operators

// User defines: GLM_SWIZZLE_XYZW GLM_SWIZZLE_RGBA GLM_SWIZZLE_STQP GLM_SWIZZLE

#if(defined(GLM_MESSAGES) && !defined(GLM_MESSAGE_SWIZZLE_DISPLAYED))
#	define GLM_MESSAGE_SWIZZLE_DISPLAYED
#	if(defined(GLM_SWIZZLE))
#		pragma message("GLM: Full swizzling operator enabled")
#	elif(!defined(GLM_SWIZZLE_XYZW) && !defined(GLM_SWIZZLE_RGBA) && !defined(GLM_SWIZZLE_STQP) && !defined(GLM_SWIZZLE))
#		pragma message("GLM: No swizzling operator enabled")
#	else
#		pragma message("GLM: Partial swizzling operator enabled")
#	endif
#endif//GLM_MESSAGE

///////////////////////////////////////////////////////////////////////////////////////////////////
// Precision

#define GLM_PRECISION_NONE			0x00000000

#define GLM_PRECISION_LOWP_FLOAT	0x00000011
#define GLM_PRECISION_MEDIUMP_FLOAT	0x00000012
#define GLM_PRECISION_HIGHP_FLOAT	0x00000013	

#define GLM_PRECISION_LOWP_INT		0x00001100
#define GLM_PRECISION_MEDIUMP_INT	0x00001200
#define GLM_PRECISION_HIGHP_INT		0x00001300

#define GLM_PRECISION_LOWP_UINT		0x00110000
#define GLM_PRECISION_MEDIUMP_UINT	0x00120000
#define GLM_PRECISION_HIGHP_UINT	0x00130000	

#endif//glm_setup
