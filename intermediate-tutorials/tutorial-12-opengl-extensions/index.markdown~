---
layout: page
status: publish
published: true
title: 'Tutorial 12 : OpenGL Extensions'
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 323
wordpress_url: http://www.opengl-tutorial.org/?page_id=323
date: '2012-02-03 20:46:21 +0100'
date_gmt: '2012-02-03 20:46:21 +0100'
categories: []
tags: []
---
<h1>Extensions</h1><br />
With each new generation, the performance of GPU increases, allowing to render more triangles and more pixels. However, raw performance isn't the only concern. NVIDIA, AMD and Intel also improve their graphic cards by providing more functionality. Let's have a look at some examples.</p>
<h2>ARB_fragment_program</h2><br />
Back in 2002, GPUs had no vertex shaders or fragment shaders : everything was hardcoded inside the chip. This was called the Fixed-Function Pipeline (FFP). As such, the most recent version of the API, which was OpenGL 1.3, proposed no way to create, manipulate and use so-called "shaders", since it didn't even exist. But then NVIDIA decided that it could be handy to describe the rendering process with actual code, instead of hundreds of flags and state variables. This is how ARB_fragment_program was created : there was no GLSL, but instead you could write stuff like this :</p>
<pre>!!ARBfp1.0 MOV result.color, fragment.color; END</pre><br />
But obviously to tell OpenGL to use such code, you needed special functions, which were not yet in OpenGL. Before moving on to the explanations, one more example.</p>
<h2>ARB_debug_output</h2><br />
Ok, you say, but this ARB_fragment_program is too old, surely I don't need this extension stuff anymore ? Well there are newer extensions which are very handy. One of them is ARB_debug_output, which expose a functionality that doesn't exist in OpenGL 3.3 but that you can/should use anyway. It defines tokens like GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB or GL_DEBUG_SEVERITY_MEDIUM_ARB, and functions like DebugMessageCallbackARB. The great thing about this extension is that whenever you write some incorrect code, for instance :</p>
<pre class="brush: cpp">glEnable(GL_TEXTURE); // Incorrect ! You probably meant GL_TEXTURE_2D !</pre><br />
you can have an error message and the exact location of the problem. Lessons learned :</p>
<ul>
<li>Extensions are still very useful, even in modern, 3.3 OpenGL</li>
<li>Use ARB_debug_output ! See below for links.</li><br />
</ul><br />
<a href="http://www.opengl-tutorial.org/wp-content/uploads/2012/02/breakpoint.png"><img class="alignnone size-large wp-image-622" title="breakpoint" src="http://www.opengl-tutorial.org/wp-content/uploads/2012/02/breakpoint-1024x678.png" alt="" width="640" height="423" /></a></p>
<h2>Getting an extension - the hard way</h2><br />
The "manual" way for checking is an extension is present is to use this code snippet (from the <a href="http://www.opengl.org/wiki/GlGetString">OpenGL.org wiki</a>) :</p>
<pre class="brush: cpp">int NumberOfExtensions;<br />
glGetIntegerv(GL_NUM_EXTENSIONS, &amp;NumberOfExtensions);<br />
for(i=0; i<NumberOfExtensions; i++) {<br />
  const GLubyte *ccc=glGetStringi(GL_EXTENSIONS, i);<br />
  if ( strcmp(ccc, (const GLubyte *)"GL_ARB_debug_output") == 0 ){<br />
    // The extension is supported by our hardware and driver<br />
    // Try to get the "glDebugMessageCallbackARB" function :<br />
    glDebugMessageCallbackARB  = (PFNGLDEBUGMESSAGECALLBACKARBPROC) wglGetProcAddress("glDebugMessageCallbackARB");<br />
  }<br />
}</pre></p>
<h2>Getting all extensions - the easy way</h2><br />
All in all this is very complicated. Libraries like GLEW, GLee, gl3w, etc, make it much easier. For instance, with GLEW, you just have to call glewInit() after you created your window, and handy variables are created :</p>
<pre class="brush: cpp">if (GLEW_ARB_debug_output){ // Ta-Dah ! }</pre><br />
( a word of caution : debug_output is special because you have to enable it at context creation. In GLFW, this is done with glfwOpenWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1); )</p>
<h2>ARB vs EXT vs ...</h2><br />
The name of each extention contains information on its availability :</p>
<p>GL_ : all platforms;<br />
GLX_ : Linux &amp; Mac only (X11);<br />
WGL_ : Windows only</p>
<p>EXT : A generic extention.<br />
ARB : the extention has been accepted by all the members of the OpenGL Architecture Review Board (EXT extentions are often promoted to ARB after a while).<br />
NV/AMD/INTEL : Quite self-explanatory =)</p>
<h1>Designing with Extentions</h1></p>
<h2>The problem</h2><br />
Let's say that your OpenGL 3.3 application needs to render some large lines. You could write a complicated vertex shader to do that, or simply rely on <a href="http://www.opengl.org/registry/specs/NV/path_rendering.txt">GL_NV_path_rendering</a>, which will handle all the complicated stuff for you.</p>
<p>You will thus have code that look like this :</p>
<pre class="brush: cpp">if ( GLEW_NV_path_rendering ){<br />
    glPathStringNV( ... ); // Draw the shape. Easy !<br />
}else{<br />
    // Else what ? You still have to draw the lines<br />
    // on older NVIDIA hardware, on AMD and on INTEL !<br />
    // So you have to implement it yourself anyway !<br />
}</pre></p>
<h2>Choosing the limit</h2><br />
One usually choose to use an extention when the gain in rendering quality or performance outweights the pain of maintaining two different paths.</p>
<p>For instance, Braid (the 2D game where you travel in time) has all kinds of image-warping effects when you mess with the time, which simply aren't rendered on older hardware.</p>
<p>With OpenGL 3.3 and above, you already have 99% of the tools you're likely to need. Some extensions can be very useful, like GL_AMD_pinned_memory, but this is often not like a few years ago when having GL_ARB_framebuffer_object ( used for Render To Texture ) could make your game look 10 times better.</p>
<p>If you have to handle older hardware, though, OpenGL 3+ won't be available, and you'll have to use OpenGL 2+ instead. You won't be able to assume that you have all the fancy extensions anymore, and you'll need to cope with that.</p>
<p>For further details, see for instance the <a href="http://code.google.com/p/opengl-tutorial-org/source/browse/tutorial14_render_to_texture/tutorial14.cpp?name=2.1%20branch#152">OpenGL 2.1 version of Tutorial&nbsp; 14 - Render To Texture, line 152</a>, where I have to check the presence of GL_ARB_framebuffer_object by hand. See also the <a href="http://www.opengl-tutorial.org/miscellaneous/faq/">FAQ</a>.</p>
<h1>Conclusion</h1><br />
OpenGL Extentions provide a nice way to extend OpenGL's capabilities, depending on your user's GPU.</p>
<p>While extentions are nowaday mostly for advanced use since most functionality is already in the core, it's still important to know how they work and how you can use them to improve your software - at the expense of higher maintainance.</p>
<h1>Further reading</h1></p>
<ul>
<li><a href="http://sites.google.com/site/opengltutorialsbyaks/introduction-to-opengl-4-1---tutorial-05 ">debug_output tutorial by Aks</a> you can skip Step 1 thanks to GLEW.</li>
<li><a href="http://www.opengl.org/registry/">The OpenGL extension registry</a> All extensions specifications. The bible.</li>
<li><a href="http://glew.sourceforge.net/">GLEW</a> The OpenGL Extension Wrangler Library</li>
<li><a href="https://github.com/skaslev/gl3w">gl3w</a> Simple OpenGL 3/4 core profile loading</li><br />
</ul></p>
