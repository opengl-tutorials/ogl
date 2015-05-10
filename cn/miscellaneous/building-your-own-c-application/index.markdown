---
layout: page
status: publish
published: true
title: Building your own C application
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 587
wordpress_url: http://www.opengl-tutorial.org/?page_id=587
date: '2012-10-06 14:03:21 +0200'
date_gmt: '2012-10-06 14:03:21 +0200'
categories: []
tags: []
order: 50
language: cn
---
<p>A lot of efforts have been made so that these tutorials are as simple to compile &amp; run as possible. Unfortunately, this also means that CMakes hides how to do that on your own project.</p>
<p>So, this tutorial will explain how to build your own C application from scatch. But first, you need a basic knowledge of what the compiler actually does.</p>
<p><span style="color: #ff0000;">Please don't skip the first two sections. If you're reading this tutorial, you probably need to know this stuff.</span></p>
<h1>&nbsp;The C application model</h1></p>
<h2>Preprocessing</h2><br />
This is what all those <em>#defines</em> and <em>#includes</em> are about.</p>
<p>C preprocessing is a very simple process : cut'n pasting.</p>
<p>When the preprocessor sees the following MyCode.c :</p>
<pre class="brush: cpp;">#include "MyHeader.h"</p>
<p>void main(){<br />
&nbsp;&nbsp;&nbsp; FunctionDefinedInHeader();<br />
}</pre><br />
, it simply opens the file MyHeader.h, and cut'n pastes its contents into MyCode.c :</p>
<pre>// Begin of MyCode.c<br />
// Begin of MyHeader.h<br />
#ifndef MYHEADER_H<br />
#define MYHEADER_H</p>
<p>void FunctionDefinedInHeader(); // Declare the function</p>
<p>#endif<br />
// End of MyHeader.h</p>
<p>void main(){<br />
    FunctionDefinedInHeader(); // Use it<br />
}</p>
<p>// End of MyCode</pre><br />
Similarly, <em>#define</em>s are cut'n pasted, <em>#if</em>s are analysed and potentially removed, etc.</p>
<p>At the end of this step we have a preprocessed C++ file, without any #define, #if, #ifdef, #include, ready to be compiled.</p>
<p>As an example, here is the main.cpp file of the 6th tutorial, fully preprocessed in Visual : <a href="http://www.opengl-tutorial.org/wp-content/uploads/2012/09/tutorial06_preprocessed.txt">tutorial06_preprocessed</a>. Warning, it's a huge file ! But it's worth knowing what a seemingly simple .cpp really looks to the compiler.</p>
<h2>Compilation</h2><br />
The compiler translates C++ code into a representation that the CPU can directly understand. For instance, the following code :</p>
<pre class="brush: cpp">int i=3;<br />
int j=4*i+2;</pre><br />
will be translated into this : x86 opcodes.</p>
<pre>mov         dword ptr [i],3<br />
mov         eax,dword ptr [i]<br />
lea         ecx,[eax*4+2]<br />
mov         dword ptr [j],ecx</pre><br />
Each .cpp file is compiled separately, and the resulting binary code is written in .o/.obj files.</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2012/09/compilation.png"><img class="alignnone size-full wp-image-596" title="compilation" src="http://www.opengl-tutorial.org/wp-content/uploads/2012/09/compilation.png" alt="" width="813" height="544" /></a></p>
<p>Note that we don't have an executable yet : one remaining step is needed.</p>
<h2>Linking</h2><br />
The linker takes all the binary code (yours, and the one from external libraries), and generates the final executable. A few notes :</p>
<ul>
<li>A library has the .lib extension.</li>
<li>Some libraries are <em>static</em>. This means that the .lib contains all the x86 opcodes needed.</li>
<li>Some library are <em>dynamic</em> ( also said <em>shared</em> ). This means that the .lib doesn't contain any x86 code; it simply says "I swear that functions <em>Foo</em>, <em>Bar</em> and <em>WhatsNot</em> will be available at runtime".</li><br />
</ul><br />
When the linker has run, you have an executable (.exe on Windows, .nothing_at_all on unix) :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2012/09/linking.png"><img class="wp-image-597 alignnone" title="linking" src="http://www.opengl-tutorial.org/wp-content/uploads/2012/09/linking.png" alt="" width="483" height="254" /></a></p>
<h2>Runtime</h2><br />
When you launch the executable, the OS will open the .exe, and put the x86 opcodes in memory. As said earlier, some code isn't available at this point : the code from dynamic libraries. But the linker was nice enough to say where to look for it : the .exe clearly says that the glClearColor function is implemented in OpenGL32.dll.</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2012/10/dynamiclinking.png"><img class="alignnone size-full wp-image-640" title="dynamiclinking" src="http://www.opengl-tutorial.org/wp-content/uploads/2012/10/dynamiclinking.png" alt="" width="576" height="288" /></a></p>
<p>Windows will happily open the .dll and find glClearColor :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2012/10/depends.png"><img class="alignnone size-full wp-image-639" title="depends" src="http://www.opengl-tutorial.org/wp-content/uploads/2012/10/depends.png" alt="" width="1073" height="298" /></a></p>
<p>Sometimes a .dll can't be found, probably because you screwed the installation process, and the program just can't be run.</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2012/09/dynamiclinking.png"><img class="size-full wp-image-598 alignnone" title="dynamiclinking" src="http://www.opengl-tutorial.org/wp-content/uploads/2012/09/dynamiclinking.png" alt="" width="437" height="223" /></a></p>
<h1>How do I do X with IDE Y ?</h1><br />
The instructions on how to build an OpenGL application are separated from the following basic operations. This is on purpose :</p>
<ul>
<li>First, you'll need to do these thinks all of the time, so you'd better know them well</li>
<li>Second, you will know what is OpenGL-specific and what is not.</li><br />
</ul><br />
&nbsp;</p>
<h2>Visual Studio</h2></p>
<h3>Creating a new project</h3><br />
File -> New -> Project -> Empty project. Don't use any weird wizard. Don't use any option you may not know about (disable MFC, ATL, precompiled headers, stdafx, main file).</p>
<h3>Adding a source file in a project</h3><br />
Right clic on Source Files -> Add new.</p>
<h3>Adding include directories</h3><br />
Right clic on project -> Project Properties -> C++ -> General -> Additional include directories. This is actually a dropdown list, you can modify the list conveniently.</p>
<h3>Link with a library</h3><br />
Right clic on project -> Project Properties -> Linker -> Input -> Additional dependencies : type the name of the .lib. For instance : opengl32.lib</p>
<p>In Project Properties -> Linker -> General -> Additional library directories, make sure that the path to the above library is present.</p>
<h3>Build, Run &amp; Debug</h3><br />
Setting the working directory (where your textures &amp; shaders are) : Project Properties -> Debugging -> Working directory</p>
<p>Running : Shift-F5; but you'll probably never need to do that. <em>Debug</em> instead : F5</p>
<p>A short list of debugging shortcuts :</p>
<ul>
<li>F9 on a line, or clicking on the left of the line number: setting a breakpoint. A red dot will appear.</li>
<li>F10 : execute current line</li>
<li>F11 : execute current line, but step into the functions this line is calling ("step into")</li>
<li>Shift-F11 : run until the end of the function ("step out")</li><br />
</ul><br />
You also have plenty of debugging windows : watched variables, callstack, threads, ...</p>
<h2>QtCreator</h2><br />
QtCreator is available for free at <a href="http://qt-project.org/">http://qt-project.org/</a>.</p>
<h3>Creating a new project</h3><br />
Use a plain C or C++ project; avoid the templates filled with Qt stuff.</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2012/09/QtCreator_newproject.png"><img class="size-full wp-image-613 alignnone" title="QtCreator_newproject" src="http://www.opengl-tutorial.org/wp-content/uploads/2012/09/QtCreator_newproject.png" alt="" width="556" height="485" /></a></p>
<p>Use default options.</p>
<h3>Adding a source file in a project</h3><br />
Use the GUI, or add the file in the .pro :</p>
<pre>SOURCES += main.cpp \<br />
           other.cpp \<br />
           foo.cpp</pre></p>
<h3>Adding include directories</h3><br />
In the .pro file :</p>
<pre><code>INCLUDEPATH += <your path> \ <other path> </code></pre></p>
<h3>Link with a library</h3><br />
Right clic on project -> Add library</p>
<ul>
<li>If you're on Linux and you installed the library with apt-get or similar, chances are that the library registered itself in the system. You can select "System package" and enter the name of the library ( ex : <em>libglfw</em> or <em>glew</em> )</li><br />
</ul><br />
<a href="http://www.opengl-tutorial.org/wp-content/uploads/2012/09/QtCreator_linking.png"><img class="alignnone size-full wp-image-614" title="QtCreator_linking" src="http://www.opengl-tutorial.org/wp-content/uploads/2012/09/QtCreator_linking.png" alt="" width="1112" height="729" /></a></p>
<ul>
<li>If not, use "System Library". Browse to where you compiled it.</li><br />
</ul></p>
<h3>Build, Run &amp; Debug</h3><br />
Building : Ctrl-B, or the hammer on the bottom left corner.</p>
<p>Running : the green arrow. You can set the program's arguments and working directory in Projects -> Run Settings</p>
<p>Debugging :</p>
<ul>
<li>Setting a breakpoint : Click on the left of the line number. A red dot will appear.</li>
<li>F10 : execute current line</li>
<li>F11 : execute current line, but step into the functions this line is calling ("step into")</li>
<li>Shift-F11 : run until the end of the function ("step out")</li><br />
</ul><br />
You also have plenty of debugging windows : watched variables, callstack, threads, ...</p>
<h2>XCode</h2><br />
Work in progress...</p>
<h3>Creating a new project</h3></p>
<h3>Adding a source file in a project</h3></p>
<h3>Adding include directories</h3></p>
<h3>Link with a library</h3></p>
<h3>Build, Run &amp; Debug</h3></p>
<h2>CMake</h2><br />
CMake will create projects for almost any software building tool : Visual, QtCreator, XCode, make, Code::Blocks, Eclipse, etc, on any OS. This frees you from maintaining many project files.</p>
<h3>Creating a new project</h3><br />
Create a CMakeLists.txt file and write the following inside (adapt if needed) :</p>
<pre>cmake_minimum_required (VERSION 2.6)<br />
project (your_project_name)</p>
<p>find_package(OpenGL REQUIRED)</p>
<p>add_executable(your_exe_name<br />
&nbsp;&nbsp; &nbsp;tutorial04_colored_cube/tutorial04.cpp<br />
&nbsp;&nbsp; &nbsp;common/shader.cpp<br />
&nbsp;&nbsp; &nbsp;common/shader.hpp<br />
)</pre><br />
Launch the CMake GUI, browse to your .txt file, and select your build folder. Click Configure, then Generate. Your solution will be created in the build folder.</p>
<h3>Adding a source file in a project</h3><br />
Simply add a line in the add_executable command.</p>
<h3>Adding include directories</h3></p>
<pre>include_directories(<br />
&nbsp;&nbsp; &nbsp;external/AntTweakBar-1.15/include/<br />
&nbsp;&nbsp; &nbsp;external/glfw-2.7.2/include/<br />
&nbsp;&nbsp; &nbsp;external/glm-0.9.1/<br />
&nbsp;&nbsp; &nbsp;external/glew-1.5.8/include/<br />
&nbsp;&nbsp; &nbsp;.<br />
)</pre></p>
<h3>Link with a library</h3></p>
<pre>set(ALL_LIBS<br />
&nbsp;&nbsp; &nbsp;${OPENGL_LIBRARY}<br />
&nbsp;&nbsp; &nbsp;GLFW_272<br />
&nbsp;&nbsp; &nbsp;GLEW_158<br />
&nbsp;&nbsp; &nbsp;ANTTWEAKBAR_151_OGLCORE_GLFW<br />
)</p>
<p>target_link_libraries(tutorial01_first_window<br />
&nbsp;&nbsp; &nbsp;${ALL_LIBS}<br />
)</pre></p>
<h3>Build, Run &amp; Debug</h3><br />
CMake doesn't do that. Use your favourite IDE.</p>
<h2>make</h2><br />
Please, just don't use that.</p>
<h2>gcc</h2><br />
It might be worth compiling a small project "by hand" in order to gain a better comprehension of the workflow. Just don't do this on a real project...</p>
<p>Note that you can also do that on Windows using mingw.</p>
<p>Compile each .cpp file separately :</p>
<pre>g++ -c main.cpp<br />
g++ -c tools.cpp</pre></p>
<div id=":2v"></div><br />
As said above, you will have a main.o and a tools.o files. Link them :</p>
<pre>g++ main.o tools.o</pre><br />
a <em>a.out</em> file appeared; It's your executable, run it :</p>
<pre>./a.out</pre><br />
That's it !</p>
<h1>Building your own C application</h1><br />
Armed with this knowledge, we can start building our own OpenGL application.</p>
<ol>
<li>Download the dependencies : Here we use GLFW, GLEW and GLM, but depending on your project, you might need something different. Save same preferably in a subdirectory of your project (for instance : external/)</li>
<li>They should be pre-compiled for your platform. GLM doesn't have to be compiled, though.</li>
<li>Create a new project with the IDE of your choice</li>
<li>Add a new .cpp file in the project</li>
<li>Copy and paste, for instance, the following code (this is actually playground.cpp) :
<pre class="brush: cpp">#include <stdio.h><br />
#include <stdlib.h></p>
<p>#include <GL/glew.h></p>
<p>#include <GL/glfw.h></p>
<p>#include <glm/glm.hpp><br />
using namespace glm;</p>
<p>int main( void )<br />
{<br />
	// Initialise GLFW<br />
	if( !glfwInit() )<br />
	{<br />
		fprintf( stderr, "Failed to initialize GLFW\n" );<br />
		return -1;<br />
	}</p>
<p>	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);<br />
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE,GL_TRUE);<br />
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);<br />
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);<br />
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);</p>
<p>	// Open a window and create its OpenGL context<br />
	if( !glfwOpenWindow( 1024, 768, 0,0,0,0, 32,0, GLFW_WINDOW ) )<br />
	{<br />
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );<br />
		glfwTerminate();<br />
		return -1;<br />
	}</p>
<p>	// Initialize GLEW<br />
	if (glewInit() != GLEW_OK) {<br />
		fprintf(stderr, "Failed to initialize GLEW\n");<br />
		return -1;<br />
	}</p>
<p>	glfwSetWindowTitle( "Playground" );</p>
<p>	// Ensure we can capture the escape key being pressed below<br />
	glfwEnable( GLFW_STICKY_KEYS );</p>
<p>	// Dark blue background<br />
	glClearColor(0.0f, 0.0f, 0.3f, 0.0f);</p>
<p>	do{<br />
		// Draw nothing, see you in tutorial 2 !</p>
<p>		// Swap buffers<br />
		glfwSwapBuffers();</p>
<p>	} // Check if the ESC key was pressed or the window was closed<br />
	while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &amp;&amp;<br />
		   glfwGetWindowParam( GLFW_OPENED ) );</p>
<p>	// Close OpenGL window and terminate GLFW<br />
	glfwTerminate();</p>
<p>	return 0;<br />
}</pre><br />
</li></p>
<li>Compile the project.</li><br />
</ol><br />
You will have many compiler errors. We will analyse all of them, one by one.</p>
<h1>Troubleshooting</h1><br />
The error messages below are for Visual Studio 2010, but they are more or less similar on GCC.</p>
<h2>Visual Studio - fatal error C1083:&nbsp;Cannot open filetype file: 'GL/glew.h'&nbsp;: No such file or directory</h2><br />
(or whichever other file)</p>
<p>Some headers are in weird locations. For instance, GLEW include files are located in external/glew-x.y.z/include/. The compiler has no way to magically guess this, so you have to tell him. In the project settings, add the appropriate path in the COMPILER (not linker) options.</p>
<p>Under <em>no circumstance</em> you should copy files in the compiler's default directory (Program Files/Visual Studio/...). Technically, this will work, but it's <em>very</em> bad practice.</p>
<p>Also, it's good practice to use relative paths ( ./external/glew/... instead of C:/Users/username/Downloads/... )</p>
<p>As an example, this is what the tutorial's CMake use :</p>
<pre>external/glfw-2.7.2/include<br />
external/glm-0.9.1<br />
external/glew-1.5.8/include</pre><br />
Repeat until all files are found.</p>
<h2>GCC - fatal error: GL/glew.h: No such file or directory</h2><br />
(or whichever other file)</p>
<p>This means that the library is not installed. If you're lucky, the library is well-known and you just have to install it. This is the case for GLFW, GLEW and GLM :</p>
<pre>sudo apt-get install libglfw-dev libglm-dev libglew1.6-dev</pre><br />
If this is not a widespread library, see the answer for Visual Studio above.</p>
<h2>Visual Studio - error LNK2019:&nbsp;unresolved external symbol glfwGetWindowParam&nbsp;referenced in function main</h2><br />
(or whichever other symbol in whichever other function)</p>
<p>Congratulations ! You have a linker error. This is excellent news : this means that the compilation succeeded. Just one last step !</p>
<p>glfw functions are in an external library. You have to tell the linker about this library. Add it in the linker options. Don't forget to add the path to the library.</p>
<p>As an <strong>example</strong>, this is what the Visual project use. The names are a bit unusual because this is a custom build. What's more, GLM doesn't need to be compiled or linked, so it's not here.</p>
<pre>external\Debug\GLFW_272.lib<br />
external\Debug\GLEW_158.lib</pre><br />
If you download these libraries from SourceForge (<a href="http://www.glfw.org/download.html">GLFW</a>, <a href="http://glew.sourceforge.net/index.html">GLEW</a>) and build a library yourself, you have to specify the correct path. For instance :</p>
<pre>C:\Where\You\Put\The\Library\glfw.lib<br />
C:\Where\You\Put\The\Other\Library\glew32.lib</pre></p>
<h2>GCC - main.cpp: undefined reference to `glfwInit'</h2><br />
(or whichever other symbol in whichever other file)</p>
<p>Same answer than for Visual Studio.</p>
<p>Note that on Linux, GLFW and GLEW (and many others) are usually installed with apt-get or similar : sudo apt-get install libglew-dev libglfw-dev (may vary). When you do that, the library is copied in the compiler's standard directory, so you don't have to specify the path. Just link to glfw and glew as shown in the 1rst section.</p>
<h2>I set everything right, but I still have an "unresolved external symbol" error !</h2><br />
This might me tricky to track down. Here are several options:</p>
<h3>I have a linker error with _imp_glewInit or some other symbol that begins with _imp</h3><br />
This means that the library (in this case, glew) has been compiled as a <em>static</em> library, but you're trying to use it as a <em>dynamic</em> library. Simply add the following preprocessor directive in your compiler's options (for your own project, not glew's) :</p>
<pre>GLEW_STATIC</pre><br />
&nbsp;</p>
<h3>I have some other weird problem with GLFW</h3><br />
Maybe GLFW was built as a dynamic library, but you're trying to use it as a static one ?</p>
<p>Try adding the following preprocessor directive :</p>
<pre>GLFW_DLL</pre></p>
<h3>&nbsp;I have another linker problem ! Help me, I'm stuck !</h3><br />
Please send us a detailed report and a fully featured zipped project, and we'll add instructions.</p>
<h3>I'd like to solve this myself. What are the generic rules ?</h3><br />
Let's say you're the author of GLFW. You want to provide the function glfwInit().</p>
<p>When building it as a DLL, you have to tell the compiler that glfwInit() is not like any other function in the DLL : it should be seen from others, unlike glfwPrivateImplementationMethodNobodyShouldCareAbout(). This is done by declaring the function "external" (with GCC) or "__declspec(dllexport)" (with Visual).</p>
<p>When you want to use glfw, you need to tell the compiler that this function is not really available : it should link to it dynamically. This is done by declaring the function "external" (with GCC) or "__declspec(dllimport)" (with Visual).</p>
<p>So you use a handy #define : GLFWAPI, and you use it to declare the functions :</p>
<p>GLFWAPI int&nbsp; glfwInit( void );</p>
<ul>
<li>When you're building as a DLL, you #define GLFW_BUILD_DLL. GLFWAPI then gets #define'd to __declspec(dllexport)</li>
<li>When you're using GLFW as a DLL, you #define GLFW_DLL. GLFWAPI then gets #define'd to __declspec(dllimport)</li>
<li>When you're building as a static lib, GLFWAPI is #define'd to nothing</li>
<li>When you're using GLFW as a static lib, GLFWAPI is #define'd to nothing.</li><br />
</ul><br />
So the rule is : these flags must be consistent. If you build a lib (any lib, not just GLFW) as a DLL, use the right preprocessor definition : GLFW_DLL, GLEW_STATIC</p>
<p>&nbsp;</p>
<h2>My program crashes !</h2><br />
There are many reasons why a C++ OpenGL application might crash. Here are a few. If you don't know the exact line where your program crashes, learn how to use a debugger ( see shortcuts above). PLEASE don't debug with printf().</p>
<h3>I don't even go inside main()</h3><br />
This is most probably because some dll could not be found. Try opening your application with Dependency Walker (Windows) or ldd (Linux; try also <a href="http://stackoverflow.com/questions/6977298/dependency-walker-equivalent-for-linux">this</a>)</p>
<h3>My program crashes on glfwOpenWindow(), or any other function that creates an OpenGL context</h3><br />
Several possible reasons :</p>
<ul>
<li>Your GPU doesn't support the requested OpenGL version. Try to see the supported version with GPU Caps Viewer or similar. Update driver if it seems too low. Integrated Intel cards on netbooks especially suck. Use a lower version of OpenGL (2.1 for instance), and use extensions if you lack features.</li>
<li>Your OS doesn't support the requested OpenGL version : Mac OS... same answer.</li>
<li>You're trying to use GLEW with an OpenGL Core context (i.e. without all the deprecated stuff). This is a GLEW bug. Use glewExperimental=true before glewInit(), or use a compatibility profile ( i.e. use GLFW_OPENGL_COMPAT_PROFILE instead of GLFW_OPENGL_CORE_PROFILE )</li><br />
</ul></p>
<h2>My program crashes on the first OpenGL call, or on the first buffer creation</h2><br />
Three possible reasons :</p>
<ul>
<li>You're not calling glewInit() AFTER glfwOpenWindow()</li>
<li>You're using a core OpenGL profile, and you didn't create a VAO. Add the following code after glewInit() :</li><br />
</ul></p>
<pre class="brush: cpp">	GLuint&nbsp;VertexArrayID;<br />
	glGenVertexArrays(1,&nbsp;&amp;VertexArrayID);<br />
	glBindVertexArray(VertexArrayID);</pre></p>
<ul>
<li>You're using the default build of GLEW, which has a bug. You can't use a Core OpenGL Profile due to this bug. Either Use glewExperimental=true before glewInit(),&nbsp;or ask GLFW for a Compatibility Profile instead :</li><br />
</ul></p>
<pre class="brush: cpp">&nbsp;&nbsp;&nbsp; glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);</pre></p>
<h2>My program crashes when I try to load some file</h2><br />
Setup your working directory correctly. See Tutorial 1.</p>
<p>Create a test.txt file and try the following code :</p>
<pre class="brush: cpp">if ( fopen("test.txt", "r" ) == NULL ){<br />
    printf("I'm probably running my program from a wrong folder");<br />
}</pre><br />
<span style="color: #ff0000;">USE THE DEBUGGER !!!!&nbsp;</span>Seriously ! Don't debug with printf(); use a good IDE. <a href="http://www.dotnetperls.com/debugging">http://www.dotnetperls.com/debugging</a> is for C# but is valid for C++ too. Will vary for XCode and QtCreator, but concepts remain exactly the same.</p>
<h2>Something else is wrong</h2><br />
Please contact us by mail</p>
<p>&nbsp;</p>
