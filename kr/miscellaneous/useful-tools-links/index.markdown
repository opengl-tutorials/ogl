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


* [OpenGL 3.2 Quick Reference](http://www.khronos.org/files/opengl-quick-reference-card.pdf)
* [OpenGL 4.1 Reference Pages](http://www.opengl.org/sdk/docs/man4/)
* [OpenGL 4.0 Specification](http://www.opengl.org/registry/doc/glspec40.core.20100311.pdf). A heavy read.
* [GLSL Specifications](http://www.opengl.org/registry/doc/GLSLangSpec.4.10.6.clean.pdf)
* [List of all extensions](http://www.opengl.org/registry/) If your GPU is recent enough, some (many) of them will be available through GLEW


## Other tutorials


* [http://arcsynthesis.org/gltut/](http://arcsynthesis.org/gltut/) A very thorough tutorial; high learning curve
* [ogldev](http://ogldev.atspace.co.uk/index.html) Our main competitor :)
* [http://openglbook.com/](http://openglbook.com/) A few other introductory tutorials
* [NeHe ](http://nehe.gamedev.net/)Extensive OpenGL 1.1 programming tutorials and resources. Mostly deprecated now, but there are still a few intersting things.


## Books


* [Real-time Rendering 3](http://www.realtimerendering.com/)
* [OpenGL SuperBible](http://www.openglsuperbible.com/)
* [More Opengl Programming](http://glbook.gamedev.net/GLBOOK/glbook.gamedev.net/moglgp/index.html)


## Others


* [A trip trough the graphic pipeline](http://fgiesen.wordpress.com/2011/07/09/a-trip-through-the-graphics-pipeline-2011-index/) : In-depth information about how the drivers & GPUs actually work. Fantastic source of information. Highly recommended.
* [Unity stats](http://stats.unity3d.com/web/gpu.html) : You can see why I don't recommend OpenGL 3+ for production.
* [Extensions stats](http://feedback.wildfiregames.com/report/opengl/) : More precise, but contains outdated data.


# Debugging tools


* [glslDevil ](http://cumbia.informatik.uni-stuttgart.de/glsldevil/). Fantastic GLSL debugger - when it works. Even the website is often down.
* [GLIntercept ](http://glintercept.nutty.org/)Generates a webpage with the list of OpenGL commands issued. Displays shader code, content of images, content of framebuffers, etc.
* [gdebugger](http://www.gremedy.com/) A profiler
* [NVidia Parallel NSight](http://developer.nvidia.com/nvidia-parallel-nsight) A wonderful tool which gives access to extremely precise performance numbers. Highly recommended. Visual Studio + NVidia only.


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

