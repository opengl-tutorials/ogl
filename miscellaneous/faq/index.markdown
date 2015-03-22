---
layout: page
status: publish
published: true
title: FAQ
author:
  display_name: Calvin1602
  login: Calvin1602
  email: arnaud1602@gmail.com
  url: ''
author_login: Calvin1602
author_email: arnaud1602@gmail.com
wordpress_id: 526
wordpress_url: http://www.opengl-tutorial.org/?page_id=526
date: '2012-04-29 13:22:31 +0200'
date_gmt: '2012-04-29 13:22:31 +0200'
categories: []
tags: []
---
<h1>About sending e-mails...</h1><br />
Sending an e-mail to contact@opengl-tutorial.org is the most effective way to get support. However, if you have a problem, please include as much information as you can. This means at least :</p>
<ul>
<li>OS : Gentoo ? Windows XP ? ... (remember : use the 2.1 port if you have a mac !)</li>
<li>32 bits or 64 bits ?</li>
<li>Graphic card : NVIDIA ? AMD ? Intel ? S3 ? Matrox ? (remember : use the 2.1 port if you have an integrated GPU !)</li><br />
</ul><br />
... and optionally any other information you can find useful. This may include :</p>
<ul>
<li>GPU Driver version</li>
<li>Call stack</li>
<li>screenshots</li>
<li>console output</li>
<li>minidump...</li><br />
</ul><br />
And of course, read this FAQ first. It's called FAQ for a reason =)</p>
<h1>I can't compile the tutorials</h1></p>
<ul>
<li>Make sure you read Tutorial 1. PLEASE use CMake instead of re-creating the project. Or at least, make sure you read&nbsp;<a title="Building your own C application" href="http://www.opengl-tutorial.org/miscellaneous/building-your-own-c-application/">Building your own C application</a>.</li>
<li>If you have an error related to the AssImp library, it'll be fixed soon; in the meantime, it only affects ONE tutorial, all the others will build fine.</li>
<li>If you have an error related to the AntTweakBar library, it only affects ONE tutorial, all the others will build fine.</li>
<li>If there is really a problem, don't hesitate to send us an e-mail.</li><br />
</ul></p>
<h1>I have compiled the tutorials, but it fails at startup. What's going on ?</h1><br />
Several possible reasons :</p>
<h2>Incompatible GPU/OS</h2><br />
Please check if you have an Intel card. You can do so using glewinfo, GPU Caps Viewer, or any other tool.</p>
<p>Intel cards, except recent HD4000, don't support OpenGL 3.3. As a matter of fact, most only support OpenGL 2.1. You have to download the 2.1 version from the Downloads page instead.</p>
<p>The other possible reason is that you're on a Mac, with a pre-Lion version. Same stuff applies...</p>
<h2>Wrong working directory</h2><br />
Chances are that you don't run them from the right directory. Try double-clicking on the .exe from the explorer.</p>
<p>See Tutorial 1 for configuring the IDE so that you can debug the executable.</p>
<h2>No VAO</h2><br />
If you created a program from scratch, make sure you created a VAO :</p>
<pre>GLuint VertexArrayID;<br />
 glGenVertexArrays(1, &amp;VertexArrayID);<br />
 glBindVertexArray(VertexArrayID);</pre></p>
<h2>GLEW bug</h2><br />
GLEW has a bug which make it impossible to use a core context (except when you use the source code from the tutorials, which has been fixed). 3 solutions:</p>
<ul>
<li>Ask GLFW for a Compatibility Profile instead:</li><br />
</ul></p>
<pre>glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);</pre></p>
<ul>
<li>Use glewExperimental; this is the recommended way:</li><br />
</ul></p>
<pre>glewExperimental = true;</pre></p>
<ul>
<li>Actually fix glew... See <a href="http://code.google.com/p/opengl-tutorial-org/source/browse/external/glew-1.5.8.patch?name=0009_33">this patch</a>.</li><br />
</ul></p>
<h2>CMake</h2><br />
You did read Tutorial 1, right ? You didn't try to write your own makefile and build everything yourself, RIGHT ?</p>
<h1>Why should I use OpenGL 3.3 if Intel and Mac can't run it ?!</h1><br />
... also known as :</p>
<h1>Which version of OpenGL should I use ?</h1><br />
As a matter of fact, I don't recommend using OpenGL 3 or above for an application. I use it in the tutorials because it's the <strong>clean</strong> way to learn OpenGL, without all the deprecated stuff, and because once you know 3.3, using 2.1 is straighforward.</p>
<p>What I recommend is :</p>
<ul>
<li>Learn in OpenGL 3.3 so that you know the "right way"</li>
<li>Set a target hardware for your application. For instance, <em>require </em>FBOs and GLSL.</li>
<li>Use GLEW to load all the extensions. At startup, refuse all hardware which hasn't the required functionality level.</li>
<li>From now on, you can code almost like if you were on 3.3, with only a few changes.</li>
<li>If you really want to deal with older/cheaper hardware , you can still deal with them by disabling effects which require FBOs, for instance.</li><br />
</ul></p>
<div><span style="font-size: medium;"><span style="line-height: 24px;">There's one big situation where you might want to use a very recent version, say 4.2 : you're a graduate student doing high-end research, you really need a recent feature, and you don't care about compatibility because your software will never be ran outside your lab. In this case, don't waste time and go straight to the highest OpenGL version your hardware supports.</span></span></div></p>
<div></div></p>
<h1>Where do I download OpenGL 3 ?</h1><br />
You don't.</p>
<p>On Windows, for instance, you only have opengl32.dll, which is only OpenGL 1.1. BUT there is this function,&nbsp;wglGetProcAddress(), which makes is possible to get functions that are not implemented directly in opengl32.dll, but which are available in the driver.</p>
<p>GLEW calls wglGetProcAdress on all needed symbols, and make them available to you. (you can do it yourself but it's horribly boring). It also declares new constants which did not exist 10 years ago, like, for instance, GL_VERTEX_ATTRIB_ARRAY_DIVISOR_ARB.</p>
<p>So, just make sure your GPU driver supports the needed version, use GLEW, and you're good to go.</p>
<div></div></p>
<div></div></p>
<h1>Why do you create a VAO in each tutorial, but you never use it ?</h1></p>
<div></div><br />
Wrong. It's bound, so in fact, it's used during the whole execution.</p>
<p>VAOs are wrappers around VBOs. They remember which buffer is bound to which attribute and various other things. This reduces the number of OpenGL calls before glDrawArrays/Elements(). Since OpenGL 3 Core, they are compulsory, but you may use only one and modify it permanently (which is what is done in the tutorial).</p>
<p>VAOs may be confusing for this beginner's tutorial, and there is no equivalent in OpenGL 2 (which I recommend for production, see related FAQ), and the performance benefits are not clear. If you're interested in VAOs, please have a look at OpenGL's wiki. It <em>may</em>&nbsp;slightly simplify your application and <em>may</em> increase the performance a tiny bit, but not always.</p>
<div><span style="font-size: medium;"><span style="line-height: 24px;"><br />
</span></span></div></p>
<h1>&nbsp;I've got error "Unable to start program ALL_BUILD"</h1><br />
ALL_BUILD is just a helper project generated by CMake; it's not a real program.</p>
<p>As stated in Tutorial 1, you have to select the project you want to run by right-clicking on a project (from inside Visual) and select "Set up as startup project", like this :</p>
<p><a href="http://www.opengl-tutorial.org/wp-content/uploads/2012/04/StartupProject.png"><img class="alignnone size-medium wp-image-544" title="StartupProject" src="http://www.opengl-tutorial.org/wp-content/uploads/2012/04/StartupProject-185x300.png" alt="" width="185" height="300" /></a></p>
<p>&nbsp;</p>
<h1>I've got a message about the working directory, and the program crashes.</h1><br />
You have to start the program from tutorial01_first_window/, tutorial02_red_triangle/, etc. If you start the program from your IDE, you have to configure it from him to do so.</p>
<p>Please read Tutorial 1 for details.</p>
<h1></h1></p>
