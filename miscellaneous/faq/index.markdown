---
layout: page
status: publish
published: true
title: FAQ
date: '2012-04-29 13:22:31 +0200'
date_gmt: '2012-04-29 13:22:31 +0200'
categories: []
order: 10
tags: []
---

# About sending e-mails...

Sending an e-mail to contact@opengl-tutorial.org is the most effective way to get support. However, if you have a problem, please include as much information as you can. This means at least :

* OS : Gentoo ? Windows XP ? ... (remember : use the 2.1 port if you have a mac !)
* 32 bits or 64 bits ?
* Graphic card : NVIDIA ? AMD ? Intel ? S3 ? Matrox ? (remember : use the 2.1 port if you have an integrated GPU !)

... and optionally any other information you can find useful. This may include :

* GPU Driver version
* Call stack
* screenshots
* console output
* minidump...

And of course, read this FAQ first. It's called FAQ for a reason =)

# I can't compile the tutorials


* Make sure you read Tutorial 1. PLEASE use CMake instead of re-creating the project. Or at least, make sure you read [Building your own C application](http://www.opengl-tutorial.org/miscellaneous/building-your-own-c-application/).
* If you have an error related to the AssImp library, it'll be fixed soon; in the meantime, it only affects ONE tutorial, all the others will build fine.
* If you have an error related to the AntTweakBar library, it only affects ONE tutorial, all the others will build fine.
* If there is really a problem, don't hesitate to send us an e-mail.


# I have compiled the tutorials, but it fails at startup. What's going on ?

Several possible reasons :

## Incompatible GPU/OS

Please check if you have an Intel card. You can do so using glewinfo, GPU Caps Viewer, or any other tool.

Intel cards, except recent HD4000, don't support OpenGL 3.3. As a matter of fact, most only support OpenGL 2.1. You have to download the 2.1 version from the Downloads page instead.

The other possible reason is that you're on a Mac, with a pre-Lion version. Same stuff applies...

## Wrong working directory

Chances are that you don't run them from the right directory. Try double-clicking on the .exe from the explorer.

See Tutorial 1 for configuring the IDE so that you can debug the executable.

Please note that the .exe is compiled in the *build* directory, but automatically copied to the *source* directory, so that it can find the needed resources (images, 3D models, shaders).

## No VAO

If you created a program from scratch, make sure you created a VAO :

```
GLuint VertexArrayID;
 glGenVertexArrays(1, &VertexArrayID);
 glBindVertexArray(VertexArrayID);
```

## GLEW bug

GLEW has a bug which make it impossible to use a core context (except when you use the source code from the tutorials, which has been fixed). 3 solutions:

* Ask GLFW for a Compatibility Profile instead:

```

glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
```

* Use glewExperimental; this is the recommended way:

```

glewExperimental = true;
```

* Actually fix glew... See [this patch](http://code.google.com/p/opengl-tutorial-org/source/browse/external/glew-1.5.8.patch?name=0009_33).


## CMake

You did read Tutorial 1, right ? You didn't try to write your own makefile and build everything yourself, RIGHT ?

# Why should I use OpenGL 3.3 if Intel and Mac can't run it ?!

... also known as :

# Which version of OpenGL should I use ?

As a matter of fact, I don't recommend using OpenGL 3 or above for an application. I use it in the tutorials because it's the **clean** way to learn OpenGL, without all the deprecated stuff, and because once you know 3.3, using 2.1 is straighforward.

What I recommend is :

* Learn in OpenGL 3.3 so that you know the "right way"
* Set a target hardware for your application. For instance, *require *FBOs and GLSL.
* Use GLEW to load all the extensions. At startup, refuse all hardware which hasn't the required functionality level.
* From now on, you can code almost like if you were on 3.3, with only a few changes.
* If you really want to deal with older/cheaper hardware , you can still deal with them by disabling effects which require FBOs, for instance.

<div><span style="font-size: medium;"><span style="line-height: 24px;">There's one big situation where you might want to use a very recent version, say 4.2 : you're a graduate student doing high-end research, you really need a recent feature, and you don't care about compatibility because your software will never be ran outside your lab. In this case, don't waste time and go straight to the highest OpenGL version your hardware supports.</span></span></div>


# Where do I download OpenGL 3 ?

You don't.

On Windows, for instance, you only have opengl32.dll, which is only OpenGL 1.1. BUT there is this function, wglGetProcAddress(), which makes is possible to get functions that are not implemented directly in opengl32.dll, but which are available in the driver.

GLEW calls wglGetProcAdress on all needed symbols, and make them available to you. (you can do it yourself but it's horribly boring). It also declares new constants which did not exist 10 years ago, like, for instance, GL_VERTEX_ATTRIB_ARRAY_DIVISOR_ARB.

So, just make sure your GPU driver supports the needed version, use GLEW, and you're good to go.



# Why do you create a VAO in each tutorial, but you never use it ?


Wrong. It's bound, so in fact, it's used during the whole execution.

VAOs are wrappers around VBOs. They remember which buffer is bound to which attribute and various other things. This reduces the number of OpenGL calls before glDrawArrays/Elements(). Since OpenGL 3 Core, they are compulsory, but you may use only one and modify it permanently (which is what is done in the tutorial).

VAOs may be confusing for this beginner's tutorial, and there is no equivalent in OpenGL 2 (which I recommend for production, see related FAQ), and the performance benefits are not clear. If you're interested in VAOs, please have a look at OpenGL's wiki. It *may* slightly simplify your application and *may* increase the performance a tiny bit, but not always.
<div><span style="font-size: medium;"><span style="line-height: 24px;">
</span></span></div>

# I've got error "Unable to start program ALL_BUILD"

ALL_BUILD is just a helper project generated by CMake; it's not a real program.

As stated in Tutorial 1, you have to select the project you want to run by right-clicking on a project (from inside Visual) and select "Set up as startup project", like this :

![]({{site.baseurl}}/assets/images/faq/StartupProject.png)


 

# I've got a message about the working directory, and the program crashes.

You have to start the program from tutorial01_first_window/, tutorial02_red_triangle/, etc. If you start the program from your IDE, you have to configure it from him to do so.

Please read Tutorial 1 for details.
