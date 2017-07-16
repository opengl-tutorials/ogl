---
layout: page
status: publish
published: true
title: Useful Tools & Links
date: '2011-05-11 20:31:21 +0200'
date_gmt: '2011-05-11 20:31:21 +0200'
categories: []
order: 30
tags: []
---

# Documentation



## OpenGL references


* [OpenGL Quick Reference PDF](http://www.opengl.org/sdk/docs/reference_card/opengl45-reference-card.pdf)
* [OpenGL 4.5 Reference Pages](http://www.opengl.org/sdk/docs/man4/)
* [OpenGL 4.5 (Core Profile) Specification](https://www.khronos.org/registry/OpenGL/specs/gl/glspec45.core.pdf). A heavy read.
* [GLSL Specifications](https://www.khronos.org/registry/OpenGL/specs/gl/GLSLangSpec.4.50.pdf)
* [List of all extensions, and up-to-date specs](http://www.opengl.org/registry/) If your GPU is recent enough, most of them will be available through GLEW.


## Other tutorials


* [ogldev](http://ogldev.atspace.co.uk/index.html) A nice and thorough tutorial
* [NeHe ](http://nehe.gamedev.net/)Extensive OpenGL 1.1 programming tutorials and resources. Mostly deprecated now, but there are still a few intersting things.


## Books


* [Real-time Rendering 3](http://www.realtimerendering.com/). Fantastic for learning the high-level concepts.
* [GPU Pro book series](http://gpupro.blogspot.fr/). For detailed explanation of specific algorithms.

## Others


* [A trip trough the graphic pipeline](http://fgiesen.wordpress.com/2011/07/09/a-trip-through-the-graphics-pipeline-2011-index/) : In-depth information about how the drivers & GPUs actually work. Fantastic source of information. Highly recommended.
* [Unity stats](https://hwstats.unity3d.com/)
* [Extensions stats](http://gpuinfo.org/)


# Debugging tools


* [NVidia Parallel NSight](http://developer.nvidia.com/nvidia-parallel-nsight) A wonderful tool which gives access to extremely precise performance numbers. Highly recommended. Visual Studio + NVidia only. The one I use most.
* [GLIntercept ](http://glintercept.nutty.org/) Generates a webpage with the list of OpenGL commands issued. Displays shader code, content of images, content of framebuffers, etc. A bit hard to master, but very precise and useful.
* [gdebugger](http://www.gremedy.com/) A profiler


# Libraries


## Windowing & misc

* [GLFW ](http://www.glfw.org/), the one we use
* GLUT, the oldest. Not maintained, horrible license. Not recommended.
* [FreeGlut](http://freeglut.sourceforge.net/), same API, but Open Source.
* [SDL](http://www.libsdl.org/) I think this one is weird but some people like it.
* [SFML](http://www.sfml-dev.org/index-fr.php). Includes a coffee machine, a washing machine, and a cellular.

## Extension loading

Beware, most extensions loading library don't work well with OpenGL 3+ Core. Actually, GLEW is the only one I managed to make work, with changes in the source code.

If unsure, simply use the GLEW version included in the source code.

* [GLEW ](http://glew.sourceforge.net/), the one we use
* [GLEE ](http://elf-stone.com/glee.php)I hear it's not bad either
* [gl3w ](https://github.com/skaslev/gl3w/wiki). A Python scripts that generates a C++ file.

## Math library

* [GLM](http://glm.g-truc.net/), the one we use. Very complete. Directly OpenGL and CUDA compatible.
* [Bullet's Vectormath](http://bulletphysics.com/Bullet/BulletFull/) Never used it but it seems to be SIMD'ed ( = faster, even if you seldom make big computations on the CPU side )
* [Boost.ublas ](http://www.boost.org/). Heavyweight. I don't recommend it for OpenGL.
* [MathFu](https://google.github.io/mathfu/) Google's tak on math libraries, SIMD optimised.

## Image loading

* [stbimage](http://nothings.org/) A single .c file to include to your project, and you can load jpeg, bmp and png files !!!
* [SOIL ](http://www.lonesock.net/soil.html)I recommend this one. Based on stbimage, provides handy functions for use with OpenGL, and a DDS loader.
* [DevIL](http://openil.sourceforge.net/) An all-in-one image loading library
* [FreeImage](http://freeimage.sourceforge.net/) ... and another one
* [Boost.GIL](http://www.boost.org/) Big and bulky, doesn't do jpg.
* libjpg The usual library for .jpg loading. Quite hard to use, but plenty of examples on the net.
* libpng Same thing here.

## Static objects loading

* [ASSIMP ](http://assimp.sourceforge.net/)

## Articulated objects loading & stuff

* Any Quake III or Quake IV loader around
* [Cal3D](http://gna.org/projects/cal3d/)


## Physics


* [Bullet](http://bulletphysics.org/wordpress/) Open source, used by many games and even films
* [Newton](http://newtondynamics.com/forum/newton.php) Free, very good too.
* [ODE](http://www.ode.org/). Old and unstable. Avoid.
* PhysX
* Havok (expensive)

