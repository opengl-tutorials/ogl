---
layout: page
status: publish
published: true
title: "第一课：新建一个窗口"
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 687
wordpress_url: http://www.opengl-tutorial.org/?page_id=687
date: '2012-11-15 01:37:45 +0100'
date_gmt: '2012-11-15 01:37:45 +0100'
categories: []
tags: []
---
<p><!-- Include required JS files --><br />
<!-- At least one brush, here we choose JS. You need to include a brush for every     language you want to highlight --></p>
<h1>简介<&#47;h1><br />
欢迎来到第一课！</p>
<p>在学习OpenGL之前，我们将先学习如何生成，运行，和玩转（最重要的一点）课程中的代码。</p>
<h1>预备知识<&#47;h1><br />
不需要特别的预备知识。如果你有编程语言（C、Java、Lisp、Javascript等）的经验，理解课程代码会更快；但这不是必需的；如果没有，仅仅是同时学两样东西（编程语言+OpenGL）会稍微复杂点而已。</p>
<p>课程全部用&ldquo;傻瓜式C++&rdquo;编写：我费了很大劲尽量让代码简单些。代码里没有模板（template）、类或指针。就是说，即使只懂Java，也能理解所有内容。</p>
<h1>忘记一切<&#47;h1><br />
如前面所说，我们不需要预备知识；但请暂时把『老式OpenGL』先忘了吧（例如glBegin()这类东西）。<br />
在这里，你将学习新式OpenGL（OpenGL 3和4），而多数网上教程还在讲『老式OpenGL』（OpenGL 1和2）。所以，在你的脑袋乱成一锅粥之前，把它们都搁在一边吧。</p>
<h1>生成课程中的代码<&#47;h1><br />
所有课程代码都能在Windows、Linux、和Mac上生成，而且过程大体相同：</p>
<ol>
<li><strong>更新驱动<&#47;strong> ！！赶快更新吧。我可是提醒过你哟。<&#47;li>
<li>下载C++编译器。<&#47;li>
<li>安装CMake<&#47;li>
<li>下载全部课程代码<&#47;li>
<li>用CMake创建工程<&#47;li>
<li>编译工程<&#47;li>
<li>试试这些例子！<&#47;li><br />
<&#47;ol><br />
各平台的详细过程如下。可能需要一些改动。若不确定，看看Windows平台说明，按需改动一下。</p>
<h2>在Windows上生成<&#47;h2></p>
<ol>
<li>更新驱动应该很轻松。直接去NVIDIA或者AMD的官网下载。若不清楚GPU的型号:控制面板->系统和安全->系统->设备管理器->显示适配器。如果是Intel集成显卡，一般由电脑厂商（Dell、HP等）提供驱动。<&#47;li>
<li>建议用Visual Studio 2010 Express来编译。 <a href="http:&#47;&#47;www.microsoft.com&#47;express&#47;Downloads&#47;#2010-Visual-CPP" target="_blank">这里<&#47;a>可以免费下载。 若喜欢用MinGW，推荐<a href="http:&#47;&#47;qt-project.org&#47;">Qt Creator<&#47;a>。安装哪个都行。下列步骤是用Visual Studio讲解的，其他IDE也差不多。<&#47;li>
<li>从这里下载安装 <a href="http:&#47;&#47;www.cmake.org&#47;cmake&#47;resources&#47;software.html" target="_blank">CMake <&#47;a>。<&#47;li>
<li><a title="Download" href="&#47;?page_id=200" target="_blank">下载课程源码<&#47;a> ，解压到例如C:&#47;Users&#47;XYZ&#47;Projects&#47;OpenGLTutorials .<&#47;li>
<li>启动CMake。让第一栏路径指向刚才解压缩的文件夹；若不确定，就选包含CMakeLists.txt的文件夹。第二栏，填CMake输出路径 （译者注：这里CMake输出一个可以在Visual Studio中打开和编译的工程）。例如C:&#47;Users&#47;XYZ&#47;Projects&#47;OpenGLTutorials-build-Visual2010-32bits，或者C:&#47;Users&#47;XYZ&#47;Projects&#47;OpenGLTutorials&#47;build&#47;Visual2010-32bits。注意，此处可随便填，不一定要和源码在同一文件夹。<br />
<a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;CMake.png"><img class="alignnone size-medium wp-image-8" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;CMake.png" alt="" width="846" height="392" &#47;><&#47;a><&#47;li></p>
<li>点击Configure。由于是首次configure工程，CMake会让你选择编译器。根据步骤1选择。如果你的Windows是64位的，选64位。不清楚就选32位。<&#47;li>
<li>再点Configure直至红色行全部消失。点Generate。Visual Studio工程创建完毕。不再需要CMake了，可以卸载掉。<&#47;li>
<li>打开 C:&#47;Users&#47;XYZ&#47;Projects&#47;OpenGL&#47;Tutorials-build-Visual2010-32bits会看到Tutorials.sln文件（译者注：这就是CMake生成的VS项目文件），用Visual Studio打开它。<br />
<a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;directories.png"><img class="alignnone size-medium wp-image-9" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;directories.png" alt="" width="560" height="302" &#47;><&#47;a><br />
在 <em>Build<&#47;em> 菜单中，点<em>Build All<&#47;em>。每个课程代码和依赖项都会被编译。生成的可执行文件会出现在 C:&#47;Users&#47;XYZ&#47;Projects&#47;OpenGLTutorials。但愿不会报错。<br />
<a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;visual_2010.png"><img class="alignnone size-medium wp-image-11" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;visual_2010-300x212.png" alt="" width="300" height="212" &#47;><&#47;a><&#47;li></p>
<li>打开C:&#47;Users&#47;XYZ&#47;Projects&#47;OpenGLTutorials&#47;playground，运行playground.exe，会弹出一个黑色窗口。<br />
<a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;empty_window.png"><img class="alignnone size-medium wp-image-10" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;empty_window-300x231.png" alt="" width="300" height="231" &#47;><&#47;a><&#47;li><br />
<&#47;ol><br />
也可以在Visual Studio中运行任意一课的代码，但得先设置工作目录：右键点击Playground，选择Debugging、Working Directory、Browse，设置路径为C:&#47;Users&#47;XYZ&#47;Projects&#47;OpenGLTutorials&#47;playground。验证一下。再次右键点击Playground，&ldquo;Choose as startup project&rdquo;。按F5就可以调试了。</p>
<p><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2012&#47;04&#47;StartupProject.png"><img class="size-medium wp-image-544 alignnone" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2012&#47;04&#47;StartupProject-185x300.png" alt="" width="185" height="300" &#47;><&#47;a><a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;WorkingDir.png"><img class="alignright size-medium wp-image-546" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;WorkingDir-300x211.png" alt="" width="300" height="211" &#47;><&#47;a></p>
<h2>在Linux上生成<&#47;h2><br />
Linux版本众多，这里不可能列出所有的平台。按需变通一下吧，也不妨看一下发行版文档。</p>
<ol>
<li>安装最新驱动。强烈推荐闭源的二进制驱动；它们不开源，但好用。如果发行版不提供自动安装，试试<a href="http:&#47;&#47;help.ubuntu.com&#47;community&#47;BinaryDriverHowto" target="_blank">Ubuntu指南<&#47;a>.<&#47;li>
<li>安装全部需要的编译器、工具和库。完整清单如下：<em>cmake make g++ libx11-dev libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxext-dev<&#47;em> 。 用 sudo apt-get install ***** 或者 su &amp;&amp; yum install ******。<&#47;li>
<li><a title="Download" href="&#47;?page_id=200" target="_blank">下载课程源码<&#47;a> 并解压到如 ~&#47;Projects&#47;OpenGLTutorials&#47;<&#47;li>
<li>接着输入如下命令 :
<ul>
<li>cd ~&#47;Projects&#47;OpenGLTutorials&#47;<&#47;li>
<li>mkdir build<&#47;li>
<li>cd build<&#47;li>
<li>cmake ..<&#47;li><br />
<&#47;ul><br />
<&#47;li></p>
<li>build&#47;目录会创建一个makefile文件。<&#47;li>
<li>键入&ldquo;make all&rdquo;。每个课程代码和依赖项都会被编译。生成的可执行文件在~&#47;Projects&#47;OpenGLTutorials&#47;。但愿不会报错。<&#47;li>
<li>打开~&#47;Projects&#47;OpenGLTutorials&#47;playground，运行.&#47;playground会弹出一个黑色窗口。<&#47;li><br />
<&#47;ol><br />
提示：推荐使用<a href="http:&#47;&#47;qt-project.org&#47;">Qt Creator<&#47;a>作为IDE。值得一提的是，Qt Creator内置支持CMake，调试起来也顺手。如下是QtCreator使用说明：</p>
<ol>
<li>在QtCreator中打开Tools->Options->Compile-&amp;Execute->CMake<&#47;li>
<li>设置CMake路径。很可能像这样&#47;usr&#47;bin&#47;cmake<&#47;li>
<li>File->Open Project；选择 tutorials&#47;CMakeLists.txt<&#47;li>
<li>选择生成目录，最好选择tutorials文件夹外面<&#47;li>
<li>还可以在参数栏中设置-DCMAKE_BUILD_TYPE=Debug。验证一下。<&#47;li>
<li>点击下面的锤子图标。现在教程可以从tutorials&#47;文件夹启动了。<&#47;li>
<li>要想在QtCreator中运行教程源码，点击Projects->Execution parameters->Working Directory，选择着色器、纹理和模型所在目录。以第二课为例：~&#47;opengl-tutorial&#47;tutorial02_red_triangle&#47;<&#47;li><br />
<&#47;ol></p>
<h2>在Mac上生成<&#47;h2><br />
Mac OS不支持OpenGL 3.3。最近，搭载MacOS 10.7 Lion和兼容型GPU的Mac电脑可以跑OpenGL 3.2了，但3.3还不行；所以我们用2.1移植版的课程代码。除此外，其他步骤和Windows类似（也支持Makefiles，此处不赘述）：</p>
<ol>
<li>从Mac App Store安装XCode<&#47;li>
<li><a href="http:&#47;&#47;www.cmake.org&#47;cmake&#47;resources&#47;software.html">下载CMake<&#47;a>，安装.dmg。无需安装命令行工具。<&#47;li>
<li><a title="Download" href="&#47;?page_id=200" target="_blank">下载课程源码<&#47;a> （2.1版！！）解压到如~&#47;Projects&#47;OpenGLTutorials&#47; .<&#47;li>
<li>启动CMake （Applications->CMake）。让第一栏路径指向刚才解压缩的文件夹，不确定就选包含CMakeLists.txt的文件夹。第二栏，填CMake输出路径。例如~&#47;Projects&#47;OpenGLTutorials_bin_XCode&#47;。注意，这里可以随便填，不一定要和源码在同一文件夹。<&#47;li>
<li>点击Configure。由于是首次configure工程，CMake会让你选择编译器。选择Xcode。<&#47;li>
<li>再点Configure直至红色行全部消失。点Generate。Xcode项目创建完毕。不再需要CMake了，可以卸载掉。<&#47;li>
<li>打开~&#47;Projects&#47;OpenGLTutorials_bin_XCode&#47;会看到Tutorials.xcodeproj文件：打开它。<&#47;li>
<li>选择一个教程，在Xcode的Scheme面板上运行，点击Run按钮编译和运行：<&#47;li><br />
<&#47;ol><br />
<a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;Xcode-projectselection.png"><img class="alignnone size-full wp-image-643" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;Xcode-projectselection.png" alt="" width="826" height="330" &#47;><&#47;a></p>
<p><span style="color: #ff0000;">在第二课及后续课程中，Run按钮就失效了。下一版本会解决这个bug。目前，请用Cmd-B键运行（双击源码文件夹&#47;tutorialX&#47;tutorialX，或者通过终端）。<&#47;span></p>
<h1>关于Code::Blocks的说明<&#47;h1><br />
由于C::B和CMake中各有一个bug，你得在Project->Build->Options->Make commands中手动设置编译命令，如下图所示：<br />
<a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;CodeBlocksFix.png"><img class="alignnone size-full wp-image-712" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2011&#47;04&#47;CodeBlocksFix.png" alt="" width="746" height="340" &#47;><&#47;a><br />
同时你还得手动设置工作目录：Project->Properties->Build targets->tutorial N->execution working dir（即src_dir&#47;tutorial_N&#47;）。</p>
<h1>运行课程例子<&#47;h1><br />
一定要在正确的目录下运行课程例子：你可以双击可执行文件；如果爱用命令行，请用cd命令切换到正确的目录。</p>
<p>若想从IDE中运行程序，别忘了看看上面的说明&mdash;&mdash;先正确设置工作目录。</p>
<h1>如何学习本课程<&#47;h1><br />
每课都附有源码和数据，可在tutorialXX&#47;找到。不过，建议您不改动这些工程，将它们作为参考；推荐在playground&#47;playground.cpp中做试验，怎么折腾都行。要是弄乱了，就去粘一段课程代码，一切就会恢复正常。</p>
<p>我们会在整个教程中提供代码片段。不妨在看教程时，直接把它们复制到playground里跑跑看。动手实验才是王道。单纯看别人写好的代码学不了多少。即使仅仅粘贴一下代码，也会碰到不少问题。</p>
<h1>新建一个窗口<&#47;h1><br />
终于！写OpenGL代码的时刻来了！<br />
呃，其实还早着呢。有的教程都会教你以&ldquo;底层&rdquo;的方式做事，好让你清楚每一步的原理。但这往往很无聊也无用。所以，我们用一个外部的库&mdash;&mdash;GLFW来帮我们处理窗口、键盘消息等细节。你也可以使用Windows的Win32 API、Linux的X11 API，或Mac的Cocoa API；或者用别的库，比如SFML、FreeGLUT、SDL等，请参见<a title="Useful Tools &amp; Links" href="&#47;?page_id=210" target="_blank">链接<&#47;a>页。</p>
<p>我们开始吧。从处理依赖库开始：我们要用一些基本库，在控制台显示消息：</p>
<pre>&#47;&#47; Include standard headers<br />
#include <stdio.h><br />
#include <stdlib.h><&#47;pre><br />
然后是GLEW库。这东西的原理，我们以后再说。</p>
<pre>&#47;&#47; Include GLEW. Always include it before gl.h and glfw.h, since it's a bit magic.<br />
#include <GL&#47;glew.h><&#47;pre><br />
我们使用GLFW库处理窗口和键盘消息，把它也包含进来：</p>
<pre>&#47;&#47; Include GLFW<br />
#include <GL&#47;glfw.h><&#47;pre><br />
下面的GLM是个很有用的三维数学库，我们暂时没用到，但很快就会用上。GLM库很好用，但没有什么神奇的，你自己也可以写一个。添加&ldquo;using namespace&rdquo;是为了不用写&ldquo;glm::vec3&rdquo;，直接写&ldquo;vec3&rdquo;。</p>
<pre>&#47;&#47; Include GLM<br />
#include <glm&#47;glm.hpp><br />
using namespace glm;<&#47;pre><br />
如果把这些#include都粘贴到playground.cpp，编译器会报错，说缺少main函数。所以我们创建一个 ：</p>
<pre>int main(){<&#47;pre><br />
首先初始化GLFW ：</p>
<pre>&#47;&#47; Initialise GLFW<br />
if( !glfwInit() )<br />
{<br />
    fprintf( stderr, "Failed to initialize GLFWn" );<br />
    return -1;<br />
}<&#47;pre><br />
可以创建我们的第一个OpenGL窗口啦！</p>
<pre>glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4); &#47;&#47; 4x antialiasing<br />
glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3); &#47;&#47; We want OpenGL 3.3<br />
glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);<br />
glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); &#47;&#47;We don't want the old OpenGL</p>
<p>&#47;&#47; Open a window and create its OpenGL context<br />
if( !glfwOpenWindow( 1024, 768, 0,0,0,0, 32,0, GLFW_WINDOW ) )<br />
{<br />
    fprintf( stderr, "Failed to open GLFW windown" );<br />
    glfwTerminate();<br />
    return -1;<br />
}</p>
<p>&#47;&#47; Initialize GLEW<br />
if (glewInit() != GLEW_OK) {<br />
    fprintf(stderr, "Failed to initialize GLEWn");<br />
    return -1;<br />
}</p>
<p>glfwSetWindowTitle( "Tutorial 01" );<&#47;pre><br />
编译并运行。一个窗口弹出后立即关闭了。可不是嘛！还没设置等待用户Esc按键再关闭呢：</p>
<pre>&#47;&#47; Ensure we can capture the escape key being pressed below<br />
glfwEnable( GLFW_STICKY_KEYS );</p>
<p>do{<br />
    &#47;&#47; Draw nothing, see you in tutorial 2 !</p>
<p>    &#47;&#47; Swap buffers<br />
    glfwSwapBuffers();</p>
<p>} &#47;&#47; Check if the ESC key was pressed or the window was closed<br />
while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &amp;&amp;<br />
glfwGetWindowParam( GLFW_OPENED ) );<&#47;pre><br />
第一课就到这啦！第二课会教大家画三角形。</p>
