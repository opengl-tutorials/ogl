---
layout: page
status: publish
published: true
title: 'Tutorial 12 : OpenGL Extensions'
date: '2012-02-03 20:46:21 +0100'
date_gmt: '2012-02-03 20:46:21 +0100'
categories: [tuto]
order: 40
tags: []
---

# Extensions

With each new generation, the performance of GPU increases, allowing to render more triangles and more pixels. However, raw performance isn't the only concern. NVIDIA, AMD and Intel also improve their graphic cards by providing more functionality. Let's have a look at some examples.

## ARB_fragment_program

Back in 2002, GPUs had no vertex shaders or fragment shaders : everything was hardcoded inside the chip. This was called the Fixed-Function Pipeline (FFP). As such, the most recent version of the API, which was OpenGL 1.3, proposed no way to create, manipulate and use so-called "shaders", since it didn't even exist. But then NVIDIA decided that it could be handy to describe the rendering process with actual code, instead of hundreds of flags and state variables. This is how ARB_fragment_program was created : there was no GLSL, but instead you could write stuff like this :

```
!!ARBfp1.0 MOV result.color, fragment.color; END
```

But obviously to tell OpenGL to use such code, you needed special functions, which were not yet in OpenGL. Before moving on to the explanations, one more example.

## ARB_debug_output

Ok, you say, but this ARB_fragment_program is too old, surely I don't need this extension stuff anymore ? Well there are newer extensions which are very handy. One of them is ARB_debug_output, which expose a functionality that doesn't exist in OpenGL 3.3 but that you can/should use anyway. It defines tokens like GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB or GL_DEBUG_SEVERITY_MEDIUM_ARB, and functions like DebugMessageCallbackARB. The great thing about this extension is that whenever you write some incorrect code, for instance :

``` cpp
glEnable(GL_TEXTURE); // Incorrect ! You probably meant GL_TEXTURE_2D !
```

you can have an error message and the exact location of the problem. Lessons learned :

* Extensions are still very useful, even in modern, 3.3 OpenGL
* Use ARB_debug_output ! See below for links.

![]({{site.baseurl}}/assets/images/tuto-12-ogl-ext/breakpoint.png)


## Getting an extension - the hard way

The "manual" way for checking is an extension is present is to use this code snippet (from the [OpenGL.org wiki](http://www.opengl.org/wiki/GlGetString)) :

``` cpp
int NumberOfExtensions;
glGetIntegerv(GL_NUM_EXTENSIONS, &NumberOfExtensions);
for(i=0; i<NumberOfExtensions; i++) {
  const GLubyte *ccc=glGetStringi(GL_EXTENSIONS, i);
  if ( strcmp(ccc, (const GLubyte *)"GL_ARB_debug_output") == 0 ){
    // The extension is supported by our hardware and driver
    // Try to get the "glDebugMessageCallbackARB" function :
    glDebugMessageCallbackARB  = (PFNGLDEBUGMESSAGECALLBACKARBPROC) wglGetProcAddress("glDebugMessageCallbackARB");
  }
}
```

## Getting all extensions - the easy way

All in all this is very complicated. Libraries like GLEW, GLee, gl3w, etc, make it much easier. For instance, with GLEW, you just have to call glewInit() after you created your window, and handy variables are created :

``` cpp
if (GLEW_ARB_debug_output){ // Ta-Dah ! }
```

( a word of caution : debug_output is special because you have to enable it at context creation. In GLFW, this is done with glfwOpenWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1); )

## ARB vs EXT vs ...

The name of each extention contains information on its availability :

GL_ : all platforms;
GLX_ : Linux & Mac only (X11);
WGL_ : Windows only

EXT : A generic extention.
ARB : the extention has been accepted by all the members of the OpenGL Architecture Review Board (EXT extentions are often promoted to ARB after a while).
NV/AMD/INTEL : Quite self-explanatory =)

# Designing with Extentions


## The problem

Let's say that your OpenGL 3.3 application needs to render some large lines. You could write a complicated vertex shader to do that, or simply rely on [GL_NV_path_rendering](http://www.opengl.org/registry/specs/NV/path_rendering.txt), which will handle all the complicated stuff for you.

You will thus have code that look like this :

``` cpp
if ( GLEW_NV_path_rendering ){
    glPathStringNV( ... ); // Draw the shape. Easy !
}else{
    // Else what ? You still have to draw the lines
    // on older NVIDIA hardware, on AMD and on INTEL !
    // So you have to implement it yourself anyway !
}
```

## Choosing the limit

One usually choose to use an extention when the gain in rendering quality or performance outweights the pain of maintaining two different paths.

For instance, Braid (the 2D game where you travel in time) has all kinds of image-warping effects when you mess with the time, which simply aren't rendered on older hardware.

With OpenGL 3.3 and above, you already have 99% of the tools you're likely to need. Some extensions can be very useful, like GL_AMD_pinned_memory, but this is often not like a few years ago when having GL_ARB_framebuffer_object ( used for Render To Texture ) could make your game look 10 times better.

If you have to handle older hardware, though, OpenGL 3+ won't be available, and you'll have to use OpenGL 2+ instead. You won't be able to assume that you have all the fancy extensions anymore, and you'll need to cope with that.

For further details, see for instance the [OpenGL 2.1 version of Tutorial  14 - Render To Texture, line 167](https://github.com/opengl-tutorials/ogl/blob/2.1_branch/tutorial14_render_to_texture/tutorial14.cpp#L167), where I have to check the presence of GL_ARB_framebuffer_object by hand. See also the [FAQ](http://www.opengl-tutorial.org/miscellaneous/faq/).

# Conclusion

OpenGL Extentions provide a nice way to extend OpenGL's capabilities, depending on your user's GPU.

While extentions are nowaday mostly for advanced use since most functionality is already in the core, it's still important to know how they work and how you can use them to improve your software - at the expense of higher maintainance.

# Further reading


* [debug_output tutorial by Aks](http://sites.google.com/site/opengltutorialsbyaks/introduction-to-opengl-4-1---tutorial-05 ) you can skip Step 1 thanks to GLEW.
* [The OpenGL extension registry](http://www.opengl.org/registry/) All extensions specifications. The bible.
* [GLEW](http://glew.sourceforge.net/) The OpenGL Extension Wrangler Library
* [gl3w](https://github.com/skaslev/gl3w) Simple OpenGL 3/4 core profile loading

