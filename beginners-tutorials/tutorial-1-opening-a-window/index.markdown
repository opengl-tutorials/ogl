---
layout: page
status: publish
published: true
title: 'Tutorial 1 : Opening a window'
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 7
wordpress_url: http://www.dreamyourgame.com/wordpress/?page_id=7
date: '2011-04-07 17:54:16 +0200'
date_gmt: '2011-04-07 17:54:16 +0200'
categories: []
tags: []
---
<h1>Introduction</h1><br />
Welcome to the first tutorial !</p>
<p>Before jumping into OpenGL, you will first learn how to build the code that goes with each tutorial, how to run it, and most importantly, how to play with the code yourself.</p>
<h1>Prerequisites</h1><br />
No special prerequisite is needed to follow these tutorials. Experience with any programming langage ( C, Java, Lisp, Javascript, whatever ) is better to fully understand the code, but not needed ; it will merely be more complicated to learn two things at the same time.</p>
<p>All tutorials are written in "Easy C++" : Lots of effort has been made to make the code as simple as possible. No templates, no classes, no pointers. This way, you will be able to understand everything even if you only know Java.</p>
<h1>Forget Everything</h1><br />
You don't have to know anything, but you have to forget everything you know about OpenGL.<br />
If you know about something that looks like glBegin(), forget it. Here you will learn modern OpenGL (OpenGL 3 and 4) , and most online tutorials teach "old" OpenGL (OpenGL 1 and 2). So forget everything you might know before your brain melts from the mix.</p>
<h1>Building the tutorials</h1><br />
All tutorials can be built on Windows, Linux and Mac. For all these platforms, the procedure is roughly the same :</p>
<ol>
<li><strong>update your drivers</strong> !! doooo it. You've been warned.</li>
<li>Download a compiler, if you don't already have one.</li>
<li>Install CMake</li>
<li>Download the source code of the tutorials</li>
<li>Generate a project using CMake</li>
<li>Build the project</li>
<li>Play with the samples !</li><br />
</ol><br />
Detailed procedures will now be given for each platform. Adaptations may be required. If unsure, read the instruction for Windows and try to adapt them.</p>
<h2>Building on Windows</h2><br />
&nbsp;</p>
<ol>
<li>Updating your drivers shoud be easy. Just go to NVIDIA's or AMD's website and download the drivers. If unsure about your GPU model : Control Panel -> System and Security -> System -> Device Manager -> Display adapter. If you have an integrated Intel GPU, drivers are usually provided by your OEM (Dell, HP, ...).</li>
<li>We suggest using Visual Studio 2010 Express as a compiler. You can download it for free <a href="http://www.microsoft.com/express/Downloads/#2010-Visual-CPP" target="_blank">here</a>. If you prefer using MinGW, we recommend using <a href="http://qt-project.org/">Qt Creator</a>. Install whichever you want. Subsequent steps will be explained with Visual Studio, but should be similar with any other IDE.</li>
<li>Download <a href="http://www.cmake.org/cmake/resources/software.html" target="_blank">CMake </a>from here and install it</li>
<li><a title="Download" href="http://www.opengl-tutorial.org/download/" target="_blank">Download the source code</a> and unzip it, for instance in C:\Users\XYZ\Projects\OpenGLTutorials\ .</li>
<li>Launch CMake. In the first line, navigate to the unzipped folder. If unsure, choose the folder that contains the CMakeLists.txt file. In the second line, enter where you want all the compiler's stuff to live. For instance, you can choose C:\Users\XYZ\Projects\OpenGLTutorials-build-Visual2010-32bits\, or C:\Users\XYZ\Projects\OpenGLTutorials\build\Visual2010-32bits\. Notice that it can be anywhere, not necessarily in the same folder.<br />
<a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/CMake.png"><img class="alignnone size-medium wp-image-8" title="CMake" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/CMake.png" alt="" width="846" height="392" /></a></li></p>
<li>Click on the Configure button. Since this is the first time you configure the project, CMake will ask you which compiler you would like to use. Choose wisely depending on step 1. If you have a 64 bit Windows, you can choose 64 bits; if you don't know, choose 32 bits.</li>
<li>Click on Configure until all red lines disappear. Click on Generate. Your Visual Studio project is now created. You can forget about CMake; uninstall it if you want.</li>
<li>Open C:\Users\XYZ\Projects\OpenGLTutorials-build-Visual2010-32bits\. You will see a Tutorials.sln file : open it with Visual Studio.<br />
<a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/directories.png"><img class="alignnone size-medium wp-image-9" title="directories" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/directories.png" alt="" width="560" height="302" /></a><br />
In the <em>Build</em> menu, click <em>Build All</em>. Every tutorial and dependency will be compiled. Each executable will also be copied back into C:\Users\XYZ\Projects\OpenGLTutorials\ . Hopefuly no error occurs.<br />
<a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/visual_2010.png"><img class="alignnone size-medium wp-image-11" title="visual_2010" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/visual_2010-300x212.png" alt="" width="300" height="212" /></a></li></p>
<li>Open C:\Users\XYZ\Projects\OpenGLTutorials\playground, and launch playground.exe. A black window should appear.<br />
<a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/empty_window.png"><img class="alignnone size-medium wp-image-10" title="empty_window" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/empty_window-300x231.png" alt="" width="300" height="231" /></a></li><br />
</ol><br />
You can also launch any tutorial from inside Visual Studio. Right-click on Playground once, "Choose as startup project". You can now debug the code by pressing F5.</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/WorkingDir.png"><img class="size-medium wp-image-546 alignnone" title="WorkingDir" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/WorkingDir-300x211.png" alt="" width="300" height="211" /></a><a href="http://www.opengl-tutorial.org/wp-content/uploads/2012/04/StartupProject.png"><img class="size-medium wp-image-544 alignright" title="StartupProject" src="http://www.opengl-tutorial.org/wp-content/uploads/2012/04/StartupProject-185x300.png" alt="" width="185" height="300" /></a></p>
<h2></h2></p>
<h2></h2></p>
<h2></h2></p>
<h2>Building on Linux</h2><br />
They are so many Linux variants out there that it's impossible to list every possible platform. Adapt if required, and don't hesitate to read your distribution's documentation.</p>
<p>&nbsp;</p>
<ol>
<li>Install the latest drivers. We highly recommend the closed-source binary drivers. It's not GNU or whatever, but they work. If your distribution doesn't provide an automatic install, try <a href="http://help.ubuntu.com/community/BinaryDriverHowto" target="_blank">Ubuntu's guide</a>.</li>
<li>Install all needed compilers, tools &amp; libs. Complete list is : <em>cmake make g++ libx11-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxext-dev</em> . Use sudo apt-get install ***** or su &amp;&amp; yum install ******.</li>
<li><a title="Download" href="http://www.opengl-tutorial.org/download/" target="_blank">Download the source code</a> and unzip it, for instance in ~/Projects/OpenGLTutorials/</li>
<li>cd in ~/Projects/OpenGLTutorials/ and enter the following commands :
<ul>
<li>mkdir build</li>
<li>cd build</li>
<li>cmake ..</li><br />
</ul><br />
</li></p>
<li>A makefile has been created in the build/ directory.</li>
<li>type "make all". Every tutorial and dependency will be compiled. Each executable will also be copied back into ~/Projects/OpenGLTutorials/ . Hopefuly no error occurs.</li>
<li>Open ~/Projects/OpenGLTutorials/playground, and launch ./playground. A black window should appear.</li><br />
</ol><br />
Note that you really should use an IDE like <a href="http://qt-project.org/">Qt Creator</a>. In particular, this one has built-in support for CMake, and it will provide a much nicer experience when debugging. Here are the instructions for QtCreator :</p>
<ol>
<li>In QtCreator, go to File->Tools->Options->Compile&amp;Execute->CMake</li>
<li>Set the path to CMake. This is most probably /usr/bin/cmake</li>
<li>File->Open Project; Select tutorials/CMakeLists.txt</li>
<li>Select a build directory, preferably outside the tutorials folder</li>
<li>Optionally set -DCMAKE_BUILD_TYPE=Debug in the parameters box. Validate.</li>
<li>Click on the hammer on the bottom. The tutorials can now be launched from the tutorials/ folder.</li>
<li>To run the tutorials from QtCreator, click on Projects->Execution parameters->Working Directory, and select the directory where the shaders, textures &amp; models live. Example for tutorial 2 : ~/opengl-tutorial/tutorial02_red_triangle/</li><br />
</ol></p>
<h2>Building on Mac</h2><br />
Mac OS doesn't support OpenGL 3.3. Recent Macs with MacOS 10.7 Lion and compatible GPUs can run OpenGL 3.2, but not 3.3. Use the 2.1 port of the tutorials instead. Apart from that, the procedure is very similar to Windows' (Makefiles are also supported, but won't be explained here) :</p>
<ol>
<li>Install XCode from the Mac App Store</li>
<li><a href="http://www.cmake.org/cmake/resources/software.html">Download CMake</a>, and install the .dmg . You don't need to install the command-line tools.</li>
<li><a title="Download" href="http://www.opengl-tutorial.org/download/" target="_blank">Download the source code</a> (VERSION 2.1 !!) and unzip it, for instance in ~/Projects/OpenGLTutorials/ .</li>
<li>Launch CMake (Applications->CMake). In the first line, navigate to the unzipped folder. If unsure, choose the folder that contains the CMakeLists.txt file. In the second line, enter where you want all the compiler's stuff to live. For instance, you can choose ~/Projects/OpenGLTutorials_bin_XCode/. Notice that it can be anywhere, not necessarily in the same folder.</li>
<li>Click on the Configure button. Since this is the first time you configure the project, CMake will ask you which compiler you would like to use. Choose Xcode.</li>
<li>Click on Configure until all red lines disappear. Click on Generate. Your Xcode project is now created. You can forget about CMake; uninstall it if you want.</li>
<li>Open ~/Projects/OpenGLTutorials_bin_XCode/ . You will see a Tutorials.xcodeproj file : open it.</li>
<li>Select the desired tutorial to run in Xcode's Scheme panel, and use the Run button to compile &amp; run :</li><br />
</ol><br />
<a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/Xcode-projectselection.png"><img class="alignnone size-full wp-image-643" title="Xcode-projectselection" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/Xcode-projectselection.png" alt="" width="826" height="330" /></a></p>
<h2>Note for Code::Blocks</h2><br />
Due to 2 bugs (one in C::B, one in CMake), you have to edit the command-line in Project->Build Options->Make commands, as follows :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/CodeBlocksFix.png"><img class="alignnone size-full wp-image-712" title="CodeBlocksFix" src="http://www.opengl-tutorial.org/wp-content/uploads/2011/04/CodeBlocksFix.png" alt="" width="746" height="340" /></a></p>
<p>You also have to setup the working directory yourself : Project->Properties -> Build targets -> tutorial N -> execution working dir ( it's src_dir/tutorial_N/ ).</p>
<h1>Running the tutorials</h1><br />
You should run the tutorials directly from the right directory : simply double-click on the executable. If you like command line best, cd to the right directory.</p>
<p>If you want to run the tutorials from the IDE, don't forget to read the instructions above to set the correct working directory.</p>
<h1>How to follow these tutorials</h1><br />
Each tutorial comes with its source code and data, which can be found in tutorialXX/. However, you will never modify these projects : they are for reference only. Open playground/playground.cpp, and tweak this file instead. Torture it in any way you like. If you are lost, simply cut'n paste any tutorial in it, and everything should be back to normal.</p>
<p>We will provide snippets of code all along the tutorials. Don't hesitate to cut'n paste them directly in the playground while you're reading : experimentation is good. Avoid simply reading the finished code, you won't learn a lot this way. Even with simple cut'n pasting, you'll get your boatload of problems.</p>
<h1>Opening a window</h1><br />
Finally ! OpenGL code !<br />
Well, not really. All tutorials show you the "low level" way to do things, so that you can see that no magic happens. But this part is actually very boring and useless, so we will use GLFW, an external library, to do this for us instead. If you really wanted to, you could use the Win32 API on Windows, the X11 API on Linux, and the Cocoa API on Mac; or use another library like SFML, FreeGLUT, SDL, ... see the <a title="Useful Tools &amp; Links" href="http://www.opengl-tutorial.org/miscellaneous/useful-tools-links/" target="_blank">Links</a> page.</p>
<p>Ok, let's go. First, we'll have to deal with dependencies : we need some basic stuff to display messages in the console :</p>
<pre class="brush:cpp">// Include standard headers<br />
#include <stdio.h><br />
#include <stdlib.h></pre><br />
First, GLEW. So this one actually is a little bit magic, but let's leave this for later.</p>
<pre class="brush:cpp">// Include GLEW. Always include it before gl.h and glfw.h, since it's a bit magic.<br />
#include <GL/glew.h></pre><br />
We decided to let GLFW handle the window and the keyboard, so let's include it too :</p>
<pre class="brush: cpp">// Include GLFW<br />
#include <GL/glfw3.h></pre><br />
We don't actually need this one right now, but this is a library for 3D mathematics. It will prove very useful soon. There is no magic in GLM, you can write your own if you want; it's just handy. The "using namespace" is there to avoid typing "glm::vec3", but "vec3" instead.</p>
<pre class="brush: cpp">// Include GLM<br />
#include <glm/glm.hpp><br />
using namespace glm;</pre><br />
If you cut'n paste all these #include's in playground.cpp, the compiler will complain that there is no main() function. So let's create one :</p>
<pre class="brush: cpp">int main(){</pre><br />
First thing to do it to initialize GLFW :</p>
<pre class="brush: cpp">// Initialise GLFW<br />
if( !glfwInit() )<br />
{<br />
    fprintf( stderr, "Failed to initialize GLFW\n" );<br />
    return -1;<br />
}</pre><br />
We can now create our first OpenGL window !</p>
<p>&nbsp;</p>
<pre class="brush: cpp">glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing<br />
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3<br />
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);<br />
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed<br />
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL </p>
<p>// Open a window and create its OpenGL context<br />
GLFWwindow* window; // (In the accompanying source code, this variable is global)<br />
window = glfwCreateWindow( 1024, 768, "Tutorial 01", NULL, NULL);<br />
if( window == NULL ){<br />
    fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );<br />
    glfwTerminate();<br />
    return -1;<br />
}<br />
glfwMakeContextCurrent(window); // Initialize GLEW<br />
glewExperimental=true; // Needed in core profile<br />
if (glewInit() != GLEW_OK) {<br />
    fprintf(stderr, "Failed to initialize GLEW\n");<br />
    return -1;<br />
}</pre><br />
Build this and run. A window should appear, and be closed right away. Of course ! We need to wait until the user hits the Escape key :</p>
<pre class="brush: cpp">// Ensure we can capture the escape key being pressed below<br />
glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);</p>
<p>do{<br />
    // Draw nothing, see you in tutorial 2 !</p>
<p>    // Swap buffers<br />
    glfwSwapBuffers(window);<br />
    glfwPollEvents();</p>
<p>} // Check if the ESC key was pressed or the window was closed<br />
while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &amp;&amp;<br />
glfwWindowShouldClose(window) == 0 );</pre><br />
And this concludes our first tutorial ! In Tutorial 2, you will learn how to actually draw a triangle.<br />
<script>// <![CDATA[<br />
SyntaxHighlighter.all()<br />
// ]]></script></p>
