---
layout: page
status: publish
published: true
title: "第一课：打开一个窗口"
date: '2012-11-15 01:37:45 +0100'
date_gmt: '2012-11-15 01:37:45 +0100'
categories: []
tags: []
order: 10
language: cn
---
第一课：打开一个窗口
===

#导语
欢迎来到第一课 ！

在学习OpenGL之前，我们将先学习如何生成，运行，和玩转课程中的代码。

#预备知识
本课程不需要特别的预备知识。如果您学过编程语言（C、Java、Lisp、Javascript等），理解起课程代码来会快一些；但这并非必需的；如果没有编程经验，那也不要紧，只不过是同时学习两样东西（编程语言+OpenGL）而已。

为了让代码尽量简单，我特意用“傻瓜式C++”编写了所有课程代码。代码中没有模板（template）、类或指针。也就是说，即使您只懂Java也能理解所有内容。

#忘记一切
像前面讲的那样，本课程无需预备知识；不过，请您先把glBegin()这类“旧版OpenGL”的东西忘掉吧。
多数网上教程还在讲“旧版OpenGL”（OpenGL 1、2）。但在这里，您将学到新版OpenGL（OpenGL 3、4）。所以，为了不让您的脑袋乱成一锅粥，请先把过时的知识清空吧。

#生成课程中的代码
所有课程代码都能在Windows、Linux、和Mac上生成，过程大体相同：

1. **更新驱动** ！！赶快更新吧。别怪我没提醒您哟。
2. 下载C++编译器
3. 安装CMake
4. 下载全部课程代码
5. 用CMake创建工程
6. 编译工程
7. 试试这些例子！

各平台的详细过程如下。您可能要根据实际情况做些调整。若不确定，请按照Windows平台说明操作。

##在Windows上生成

1. 更新驱动。请直接去NVIDIA或者AMD的官网下载。若不清楚GPU的型号，请在：控制面板->系统和安全->系统->设备管理器->显示适配器 查看。如果是Intel集成显卡，一般由OEM（Dell、HP…）提供驱动。
2. 建议用Visual Studio 2010 Express来编译。[这里](http://www.microsoft.com/express/Downloads/#2010-Visual-CPP)可以免费下载。若您偏爱MinGW，推荐使用[Qt Creator](http://qt-project.org/)。IDE可根据个人喜好选择。下列步骤是按Visual Studio讲解的，其他IDE差别不大。
3. 从[这里](http://www.cmake.org/cmake/resources/software.html)下载安装CMake
4. [下载课程源码](http://www.opengl-tutorial.org/download/)，解压到`C:\Users\XYZ\Projects\OpenGLTutorials\`
5. 启动CMake。将第一栏路径指向刚才解压缩的文件夹；不确定就选包含CMakeLists.txt的文件夹。第二栏填CMake输出路径。例如`C:\Users\XYZ\Projects\OpenGLTutorials-build-Visual2010-32bits\`，或者`C:\Users\XYZ\Projects\OpenGLTutorials\build\Visual2010-32bits\`。注意，此处可随意填写，不一定要和源码在同一文件夹。

![CMake]({{site.baseurl}}/assets/images/tuto-1-window/CMake.png)

6. 点击Configure。由于是首次configure工程，CMake会让您选择编译器。根据步骤1选择。如果您的系统是Windows 64 bit的，选64 bit。不清楚就选32 bit。
7. 再点Configure直至红色警告全部消失。点Generate。Visual Studio工程创建完毕。到这里就不再需要CMake了，可以卸载掉。
8. 打开`C:\Users\XYZ\Projects\OpenGLTutorials-build-Visual2010-32bits\`会看到Tutorials.sln文件，用Visual Studio打开它。

![directories]({{site.baseurl}}/assets/images/tuto-1-window/directories.png)

在*Build*菜单中，点*Build All*。每个课程代码和依赖项都将编译。生成的可执行文件会出现在 `C:\Users\XYZ\Projects\OpenGLTutorials\`。这一步一般没什么问题。

![visual_2010]({{site.baseurl}}/assets/images/tuto-1-window/visual_2010.png)

9. 打开`C:\Users\XYZ\Projects\OpenGLTutorials\playground`，运行playground.exe，会弹出一个黑色窗口。

![empty_window]({{site.baseurl}}/assets/images/tuto-1-window/empty_window.png)

也可以在Visual Studio中运行任意一课的代码，但必须先设置工作目录：右键点击Playground，选择Debugging、Working Directory、Browse，设置路径为`C:\Users\XYZ\Projects\OpenGLTutorials\playground\`。验证一下。再次右键点击Playground，“Set as startup project”。按F5就可以调试了。

![StartupProject]({{site.baseurl}}/assets/images/tuto-1-window/StartupProject.png)

###在Linux上生成###

Linux版本众多，这里不可能列出所有的平台。可根据实际情况自行调整，也不妨看一下发行版文档。

1. 安装最新驱动。强烈推荐闭源的二进制驱动；不开源但是好用。如果发行版不提供自动安装，试试[Ubuntu指南](http://help.ubuntu.com/community/BinaryDriverHowto)。
2. 安装必需的编译器、工具和库。完整清单如下： *`cmake make g++ libx11-dev libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxext-dev`*。命令行是`sudo apt-get install` 或者 `su && yum install`。
3. [下载课程源码](http://www.opengl-tutorial.org/download/)并解压到 `~/Projects/OpenGLTutorials/`
4. 输入如下命令 :
- `cd ~/Projects/OpenGLTutorials/`
- `mkdir build`
- `cd build`
- `cmake ..`
5. build目录下多了一个刚刚创建的makefile文件
6. 键入“make all”。每个课程代码和依赖项都会被编译。生成的可执行文件在 `~/Projects/OpenGLTutorials/`。应该不会出什么错误。
7. 打开`~/Projects/OpenGLTutorials/playground`，运行./playground会弹出一个黑色窗口。

> **提示**：推荐使用[Qt Creator](http://qt-project.org/)作为IDE。值得一提的是，Qt Creator原生支持CMake，调试很方便。如下是QtCreator使用说明：

1. 在QtCreator中打开Tools->Options->Compile->Execute->CMake
2. 设置CMake路径。比如 `/usr/bin/cmake`
3. File->Open Project；选择 tutorials/CMakeLists.txt
4. 选择生成目录，最好选择tutorials文件夹外面
5. 还可以在参数栏中设置 `-DCMAKE_BUILD_TYPE=Debug`。验证一下。
6. 点击下面的锤子图标。现在教程可以从`tutorials/`文件夹启动了。
7. 要想在QtCreator中运行教程源码，点击Projects->Execution parameters->Working Directory，选择着色器、纹理和模型所在目录。以第二课为例：`~/opengl-tutorial/tutorial02_red_triangle/`

##在Mac上生成
Mac OS不支持OpenGL 3.3。最近，搭载MacOS 10.7 Lion和兼容型GPU的Mac机可以跑OpenGL 3.2了，但3.3还不行；所以我们用2.1移植版的课程代码。除此外，其他步骤和Windows类似（也支持Makefiles，此处不赘述）：

1. 从Mac App Store安装XCode
2. [下载 CMake](http://www.cmake.org/cmake/resources/software.html)，安装.dmg。无需安装命令行工具。
3. [下载课程源码](http://www.opengl-tutorial.org/download/)（2.1版！！）解压到如`~/Projects/OpenGLTutorials/`
4. 启动CMake （Applications->CMake）。将第一栏路径指向刚才解压缩的文件夹，不确定就选包含CMakeLists.txt的文件夹。第二栏填CMake输出路径。例如`~/Projects/OpenGLTutorials_bin_XCode/`。注意，这里可以随便填，不一定要和源码在同一文件夹。
5. 点击Configure。由于是首次configure工程，CMake会让您选择编译器。选择Xcode。
6. 再点Configure直至红色警告全部消失。点Generate。Xcode项目创建完毕。到这里就不再需要CMake了，可以卸载掉。
7. 打开`~/Projects/OpenGLTutorials_bin_XCode/`会看到Tutorials.xcodeproj文件：打开它。
8. 选择一课，在Xcode的Scheme面板上点击Run按钮编译和运行：

![Xcode-projectselection]({{site.baseurl}}/assets/images/tuto-1-window/Xcode-projectselection.png)

##关于Code::Blocks的说明
由于C::B和CMake中各有一个bug，您必须在Project->Build->Options->Make commands中手动设置编译命令，如下图所示：

![CodeBlocksFix]({{site.baseurl}}/assets/images/tuto-1-window/CodeBlocksFix.png)

同时您还得手动设置工作目录：Project->Properties->Build targets->tutorial N->execution working dir（即`src_dir/tutorial_N/`）。

#运行课程例子
一定要在正确的目录下运行课程例子：您可以双击可执行文件；如果想用命令行，请用cd命令切换到正确的目录。

若想从IDE中运行程序，别忘了看看上面的说明——先正确设置工作目录。

#如何学习本课程
每课都附有源码和数据，可在`tutorialXX/`找到。不过，建议您先不要改动这些工程，而是将它们作为参考；推荐您在`playground/playground.cpp`中做试验，怎么折腾都行。要是弄乱了就去粘一段课程代码，一切就会恢复正常。

我们会在整个教程中提供代码片段。不妨一边看教程，一边把代码复制到playground里调试。动手实验才是王道。单纯看别人写好的代码学不了多少东西。即便只是粘贴一下代码，也会碰到不少问题。

#打开一个窗口
终于到了写OpenGL代码的时刻！
呵呵，其实还没到真正写OpenGL代码的时刻。有些教程喜欢讲一些“底层”的细节，好让您清楚每一步的原理。这些内容往往索然无味，而且用处也不大。因此，我们直接把窗口、键盘消息等细节交给第三方库GLFW来处理。您也可以使用Windows的Win32 API、Linux的X11 API，或Mac的Cocoa API；或者SFML、FreeGLUT、SDL等库，请参见[链接页](http://www.opengl-tutorial.org/miscellaneous/useful-tools-links/)。

开工啦。从处理依赖库开始：我们要用一些基本库在控制台显示消息：

```

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
```

然后是GLEW库。其原理我们以后再说。

```

// Include GLEW. Always include it before gl.h and glfw.h, since it's a bit magic.
#include <GL/glew.h>
```

我们使用GLFW库处理窗口和键盘消息，把它也包含进来：

```

// Include GLFW
#include <GL/glfw3.h>
```

下文中的GLM是个很有用3D数学库，我们暂时用不到，但很快就会派上用场。GLM库很好用，但也没什么神奇的，您不妨自己试着写一个。添加“using namespace”，这样就可以不用写“glm::vec3”，直接写“vec3”。

```

// Include GLM
#include <glm/glm.hpp>
using namespace glm;
```

把这些#include都粘贴到playground.cpp。编译时编译器报错，说缺少main函数，那就创建一个呗：

```

int main(){
```

首先初始化GLFW ：

```

// Initialise GLFW
if( !glfwInit() )
{
    fprintf( stderr, "Failed to initialize GLFW\n" );
    return -1;
}
```

终于可以创建我们的第一个OpenGL窗口啦！

```

glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
glfwWindowHint(GLFW_CONTEXT_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL

// Open a window and create its OpenGL context
GLFWwindow* window;
window = glfwCreateWindow(1024, 768, "Totorial 01", NULL, NULL);

if (window == NULL)
{
    fprintf( stderr, "Failed to open GLFW window\n" );
    glfwTerminate();
    return -1;
}

// Initialize GLEW
glfwMakeContextCurrent(window);
glewExperimental=true; // Needed in core profile
if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    return -1;
}
```

生成并运行。一个窗口弹出后立即关闭了。可不是嘛，还没设置等待用户按Esc键再关闭呢：

```

// Ensure we can capture the escape key being pressed below
glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

do{
    // Draw nothing, see you in tutorial 2 !

    // Swap buffers
    glfwSwapBuffers(window);

} // Check if the ESC key was pressed or the window was closed
while( glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
glfwWindowShouldClose(window) == 0);
```

第一课就到这啦！第二课会教大家绘制三角形。
