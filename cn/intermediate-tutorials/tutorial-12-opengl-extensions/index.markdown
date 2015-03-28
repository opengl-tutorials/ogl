---
layout: page
status: publish
published: true
title: "第十二课：OpenGL扩展"
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 817
wordpress_url: http://www.opengl-tutorial.org/?page_id=817
date: '2013-01-27 04:04:46 +0100'
date_gmt: '2013-01-27 04:04:46 +0100'
categories: []
tags: []
---
<h1>扩展<&#47;h1><br />
GPU的性能随着更新换代一直在提高，支持渲染更多的三角形和像素点。然而，原始性能不是我们唯一关心的。NVIDIA, AMD和Intel也通过增加功能来改善他们的显卡。来看一些例子。</p>
<h2>ARB_fragment_program<&#47;h2><br />
回溯到2002年，GPU都没有顶点着色器或片断着色器：所有的一切都硬编码在芯片中。这被称为固定功能流水线（Fixed-Function Pipeline (FFP)）。同样地，当时最新的OpenGL 1.3中也没有接口可以创建、操作和使用所谓的&ldquo;着色器&rdquo;，因为它根本不存在。接着NVIDIA决定用实际代码描述渲染过程，来取代数以百计的标记和状态量。这就是ARB_fragment_program的由来。当时还没有GLSL，但你可以写这样的程序：</p>
<pre>!!ARBfp1.0 MOV result.color, fragment.color; END<&#47;pre><br />
但若要显式地令OpenGL使用这些代码，你需要一些还不在OpenGL里的特殊函数。在进行解释前，再举个例子。</p>
<h2>ARB_debug_output<&#47;h2><br />
好，你说『ARB_fragment_program太老了，所以我不需要扩展这东西』？其实有不少新的扩展非常方便。其中一个便是ARB_debug_output，它提供了一个不存在于OpenGL 3.3中的，但你可以&#47;应该用到的功能。它定义了像GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB或GL_DEBUG_SEVERITY_MEDIUM_ARB之类的字符串，和DebugMessageCallbackARB这样的函数。这个扩展的伟大之处在于，当你写了一些不正确的代码，例如：</p>
<pre>glEnable(GL_TEXTURE); &#47;&#47; Incorrect ! You probably meant GL_TEXTURE_2D !<&#47;pre><br />
你能得到错误消息和错误的精确位置。总结：</p>
<ul>
<li>即便在现在的OpenGL 3.3中，扩展仍旧十分有用。<&#47;li>
<li>请使用ARB_debug_output ！下文有链接。<&#47;li><br />
<&#47;ul><br />
<a href="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2012&#47;02&#47;breakpoint.png"><img class="alignnone size-large wp-image-622" src="http:&#47;&#47;www.opengl-tutorial.org&#47;wp-content&#47;uploads&#47;2012&#47;02&#47;breakpoint-1024x678.png" alt="" width="640" height="423" &#47;><&#47;a></p>
<h2>获取扩展 - 复杂的方式 <&#47;h2><br />
『手动』查找一个扩展的方法是使用以下代码片断 (转自<a href="http:&#47;&#47;www.opengl.org&#47;wiki&#47;GlGetString">OpenGL.org wiki<&#47;a>)：</p>
<pre>int NumberOfExtensions;<br />
glGetIntegerv(GL_NUM_EXTENSIONS, &amp;NumberOfExtensions);<br />
for(i=0; i<NumberOfExtensions; i++) {<br />
  const GLubyte *ccc=glGetStringi(GL_EXTENSIONS, i);<br />
  if ( strcmp(ccc, (const GLubyte *)"GL_ARB_debug_output") == 0 ){<br />
    &#47;&#47; The extension is supported by our hardware and driver<br />
    &#47;&#47; Try to get the "glDebugMessageCallbackARB" function :<br />
    glDebugMessageCallbackARB  = (PFNGLDEBUGMESSAGECALLBACKARBPROC) wglGetProcAddress("glDebugMessageCallbackARB");<br />
  }<br />
}<&#47;pre></p>
<h2>获得所有的扩展 - 简单的方式<&#47;h2><br />
上面的方式太复杂。若用GLEW, GLee, gl3w这些库，就简单多了。例如，有了GLEW，你只需要在创建窗口后调用glewInit()，不少方便的变量就创建好了：  </p>
<pre>if (GLEW_ARB_debug_output){ &#47;&#47; Ta-Dah ! }<&#47;pre><br />
(小心：debug_output是特殊的，因为你需要在上下文创建的时候启用它。在GLFW中，这通过glfwOpenWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1)完成。)</p>
<h2>ARB vs EXT vs ...<&#47;h2><br />
扩展的名字暗示了它的适用范围：</p>
<p>GL_:所有平台；<br />
GLX_:只有Linux和Mac下可使用（X11）；<br />
WGL_:只有Windows下可使用。</p>
<p>EXT:通用的扩展。<br />
ARB:已经被OpenGL架构评审委员会的所有成员接受（EXT扩展没多久后就经常被提升为ARB）的扩展。<br />
NV&#47;AMD&#47;INTEL:顾名思义 =)</p>
<h1>设计与扩展<&#47;h1></p>
<h2>问题<&#47;h2><br />
比方说，你的OpenGL 3.3应用程序需要渲染一些大型线条。你能够写一个复杂的顶点着色器来完成，或者简单地用<a href="http:&#47;&#47;www.opengl.org&#47;registry&#47;specs&#47;NV&#47;path_rendering.txt">GL_NV_path_rendering<&#47;a>，它能帮你处理所有复杂的事。</p>
<p>因此你可以这样写代码：</p>
<pre>if ( GLEW_NV_path_rendering ){<br />
    glPathStringNV( ... ); &#47;&#47; Draw the shape. Easy !<br />
}else{<br />
    &#47;&#47; Else what ? You still have to draw the lines<br />
    &#47;&#47; on older NVIDIA hardware, on AMD and on INTEL !<br />
    &#47;&#47; So you have to implement it yourself anyway !<br />
}<&#47;pre></p>
<h2>均衡考量<&#47;h2><br />
当使用扩展的益处（如渲染质量、性能），超过维护两种不同方法（如上面的代码，一种靠你自己实现，一种使用扩展）的代价时，通常就选择用扩展。</p>
<p>例如，在时空幻境（Braid, 一个时空穿越的二维游戏）中，当你干扰时间时，就会有各种各样的图像变形效果，而这种效果在旧硬件上没法渲染。</p>
<p>而在OpenGL 3.3及更高版本中，包含了99%的你可能会用到的工具。一些扩展很有用，比如GL_AMD_pinned_memory,虽然它通常没法像几年前使用GL_ARB_framebuffer_object(用于纹理渲染)那样让你的游戏看起来变好10倍。</p>
<p>如果你不得不兼容老硬件，那么就不能用OpenGL 3+，你需要用OpenGL 2+来代替。你将不再能使用各种神奇的扩展了，你需自行处理那些问题。</p>
<p>更多的细节可以参考例子<a href="http:&#47;&#47;code.google.com&#47;p&#47;opengl-tutorial-org&#47;source&#47;browse&#47;tutorial14_render_to_texture&#47;tutorial14.cpp?name=2.1%20branch#152">OpenGL 2.1版本的第14课 - 纹理渲染，第152行<&#47;a>，需手动检查GL_ARB_framebuffer_object是否存在。常见问题可见<a href="&#47;?page_id=526">FAQ<&#47;a>。</p>
<h1>结论Conclusion<&#47;h1><br />
OpenGL扩展提供了一个很好的方式来增强OpenGL的功能，它依赖于你用户的GPU。 </p>
<p>虽然现在扩展属于高级用法（因为大部分功能在核心中已经有了），了解扩展如何运作和怎么用它提高软件性能（付出更高的维护代价）还是很重要的。</p>
<h1>深度阅读<&#47;h1></p>
<ul>
<li><a href="http:&#47;&#47;sites.google.com&#47;site&#47;opengltutorialsbyaks&#47;introduction-to-opengl-4-1---tutorial-05">debug_output tutorial by Aks<&#47;a> 因为有GLEW，你可以跳过第一步。<&#47;li>
<li><a href="http:&#47;&#47;www.opengl.org&#47;registry&#47;">The OpenGL extension registry<&#47;a> 所有扩展的规格说明。圣经。<&#47;li>
<li><a href="http:&#47;&#47;glew.sourceforge.net&#47;">GLEW<&#47;a> OpenGL标准扩展库<&#47;li>
<li><a href="https:&#47;&#47;github.com&#47;skaslev&#47;gl3w">gl3w<&#47;a> 简单的OpenGL 3&#47;4核心配置加载 <&#47;li><br />
<&#47;ul></p>
