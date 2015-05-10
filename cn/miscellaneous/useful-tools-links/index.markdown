---
layout: page
status: publish
published: true
title: Useful Tools &amp; Links
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 210
wordpress_url: http://www.opengl-tutorial.org/?page_id=210
date: '2011-05-11 20:31:21 +0200'
date_gmt: '2011-05-11 20:31:21 +0200'
categories: []
tags: []
order: 30
language: cn
---
<h1>Documentation</h1><p></p>
<h2>OpenGL references</h2></p>
<ul>
<li><a href="http://www.khronos.org/files/opengl-quick-reference-card.pdf">OpenGL 3.2 Quick Reference</a></li>
<li><a href="http://www.opengl.org/sdk/docs/man4/">OpenGL 4.1 Reference Pages</a></li>
<li><a href="http://www.opengl.org/registry/doc/glspec40.core.20100311.pdf">OpenGL 4.0 Specification</a>. A heavy read.</li>
<li><a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.10.6.clean.pdf">GLSL Specifications</a></li>
<li><a href="http://www.opengl.org/registry/">List of all extensions</a> If your GPU is recent enough, some (many) of them will be available through GLEW</li><br />
</ul></p>
<h2>Other tutorials</h2></p>
<ul>
<li><a href="http://arcsynthesis.org/gltut/" target="_blank">http://arcsynthesis.org/gltut/</a> A very thorough tutorial; high learning curve</li>
<li><a href="http://ogldev.atspace.co.uk/index.html">ogldev</a> Our main competitor :)</li>
<li><a href="http://openglbook.com/">http://openglbook.com/</a> A few other introductory tutorials</li>
<li><a href="http://nehe.gamedev.net/">NeHe </a>Extensive OpenGL 1.1 programming tutorials and resources. Mostly deprecated now, but there are still a few intersting things.</li><br />
</ul></p>
<h2>Books</h2></p>
<ul>
<li><a href="http://www.realtimerendering.com/">Real-time Rendering 3</a></li>
<li><a href="http://www.openglsuperbible.com/">OpenGL SuperBible</a></li>
<li><a href="http://glbook.gamedev.net/GLBOOK/glbook.gamedev.net/moglgp/index.html">More Opengl Programming</a></li><br />
</ul></p>
<h2>Others</h2></p>
<ul>
<li><a href="http://fgiesen.wordpress.com/2011/07/09/a-trip-through-the-graphics-pipeline-2011-index/">A trip trough the graphic pipeline</a> : In-depth information about how the drivers &amp; GPUs actually work. Fantastic source of information. Highly recommended.</li>
<li><a href="http://stats.unity3d.com/web/gpu.html">Unity stats</a> : You can see why I don't recommend OpenGL 3+ for production.</li>
<li><a href="http://feedback.wildfiregames.com/report/opengl/">Extensions stats</a> : More precise, but contains outdated data.</li><br />
</ul></p>
<h1>Debugging tools</h1></p>
<ul>
<li><a href="http://cumbia.informatik.uni-stuttgart.de/glsldevil/" target="_blank">glslDevil </a>. Fantastic GLSL debugger - when it works. Even the website is often down.</li>
<li><a href="http://glintercept.nutty.org/" target="_blank">GLIntercept </a>Generates a webpage with the list of OpenGL commands issued. Displays shader code, content of images, content of framebuffers, etc.</li>
<li><a href="http://www.gremedy.com/" target="_blank">gdebugger</a> A profiler</li>
<li><a href="http://developer.nvidia.com/nvidia-parallel-nsight">NVidia Parallel NSight</a> A wonderful tool which gives access to extremely precise performance numbers. Highly recommended. Visual Studio + NVidia only.</li><br />
</ul></p>
<h1>Libraries</h1></p>
<h2>Windowing &amp; misc</h2></p>
<ul>
<li><a href="http://www.glfw.org/">GLFW </a>, the one we use</li>
<li>GLUT, the oldest. Not maintained, horrible license. Not recommended.</li>
<li><a href="http://freeglut.sourceforge.net/">FreeGlut</a>, same API, but Open Source.</li>
<li><a href="http://www.libsdl.org/">SDL</a> I think this one is weird but some people like it.</li>
<li><a href="http://www.sfml-dev.org/index-fr.php">SFML</a>. Includes a coffee machine, a washing machine, and a cellular.</li><br />
</ul></p>
<h2>Extension loading</h2><br />
Beware, most extensions loading library don't work well with OpenGL 3+ Core. Actually, GLEW is the only one I managed to make work, with changes in the source code.</p>
<p>If unsure, simply use the GLEW version included in the source code.</p>
<ul>
<li><a href="http://glew.sourceforge.net/">GLEW </a>, the one we use</li>
<li><a href="http://elf-stone.com/glee.php">GLEE </a>I hear it's not bad either</li>
<li><a href="https://github.com/skaslev/gl3w/wiki">gl3w </a>. A Python scripts that generates a C++ file.</li><br />
</ul></p>
<h2>Math library</h2></p>
<ul>
<li><a href="http://glm.g-truc.net/">GLM</a>, the one we use. Very complete. Directly OpenGL and CUDA compatible.</li>
<li><a href="http://bulletphysics.com/Bullet/BulletFull/">Bullet's Vectormath</a> Never used it but it seems to be SIMD'ed ( = faster, even if you seldom make big computations on the CPU side )</li>
<li><a href="http://www.boost.org/">Boost.ublas </a>. Heavyweight. I don't recommend it for OpenGL.</li><br />
</ul></p>
<h2>Image loading</h2></p>
<ul>
<li><a href="http://nothings.org/">stbimage</a> A single .c file to include to your project, and you can load jpeg, bmp and png files !!!</li>
<li><a title="SOIL" href="http://www.lonesock.net/soil.html">SOIL </a>I recommend this one. Based on stbimage, provides handy functions for use with OpenGL, and a DDS loader.</li>
<li><a href="http://openil.sourceforge.net/" target="_blank">DevIL</a> An all-in-one image loading library</li>
<li><a href="http://freeimage.sourceforge.net/">FreeImage</a> ... and another one</li>
<li><a href="http://www.boost.org/">Boost.GIL</a> Big and bulky, doesn't do jpg.</li>
<li>libjpg The usual library for .jpg loading. Quite hard to use, but plenty of examples on the net.</li>
<li>libpng Same thing here.</li><br />
</ul></p>
<h2>Static objects loading</h2></p>
<ul>
<li><a href="http://assimp.sourceforge.net/" target="_blank">ASSIMP </a></li><br />
</ul></p>
<h2>Articulated objects loading &amp; stuff</h2></p>
<ul>
<li>Any Quake III or Quake IV loader around</li>
<li><a href="http://gna.org/projects/cal3d/" target="_blank">Cal3D</a></li><br />
</ul></p>
<h2>Physics</h2></p>
<ul>
<li><a href="http://bulletphysics.org/wordpress/" target="_blank">Bullet</a> Open source, used by many games and even films</li>
<li><a href="http://newtondynamics.com/forum/newton.php" target="_blank">Newton</a> Free, very good too.</li>
<li><a href="http://www.ode.org/" target="_blank">ODE</a>. Old and unstable. Avoid.</li>
<li>PhysX</li>
<li>Havok (expensive)</li><br />
</ul></p>
