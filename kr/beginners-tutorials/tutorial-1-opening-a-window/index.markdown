---
layout: page
status: publish
published: true
title: 'Tutorial 1 : 윈도우 열기'
date: '2011-04-07 17:54:16 +0200'
date_gmt: '2011-04-07 17:54:16 +0200'
categories: [tuto]
order: 10
tags: []
---

# 소개

첫 튜토리얼에 환영합니다 !

Before jumping into OpenGL, you will first learn how to build the code that goes with each tutorial, how to run it, and most importantly, how to play with the code yourself.
OpenGL 을 시작하기 전에, 먼저 각각의 튜토리얼의 코드를 어떻게 빌드하고 실행할수 있는지, 거기에 가장 중요한, 코드를 스스로 다루는 법을 배워야합니다.

# 준비물

이 튜토리얼들을 따라오는데 특별한 준비물은 필요 없습니다. 어떠한 언어 ( C, Java, Lisp, Javascript, 무엇이든) 라도 경험해보았다면 코드를 더 쉽게 이해하는데 도움이 되겠으나, 필수는 아닙니다 ; 다만 두가지를 동시에 배우는게 조금 어려울 뿐입니다.

모든 튜토리얼은 "쉬운 C++" 로 작성되었습니다 : 가능한 코드를 간단하게 만드려고 많은 노력이 들어갔습니다. 템플릿도, 클래스도, 포인터도 사용하지 않습니다. 그렇기에 당신은 Java 외엔 아는게 없어도 모든걸 이해할 수 있습니다.

# 다 잊어버리세요

You don't have to know anything, but you have to forget everything you know about OpenGL.
If you know about something that looks like glBegin(), forget it. Here you will learn modern OpenGL (OpenGL 3 and 4) , and most online tutorials teach "old" OpenGL (OpenGL 1 and 2). So forget everything you might know before your brain melts from the mix.

아는게 아무것도 없어도 됩니다. 하지만 OpenGL 에 대해 이미 알고 있는 것들은 모두 잊어버려야만 합니다.
glBegin() 처럼 생긴 무언가를 기억하고 있다면, 잊어버리세요. 여기서는 최신 OpenGL (OpenGL 3 과 4) 을 배우지만, 대부분의 OpenGL 온라인 강의들은 "낡은" OpenGL (OpenGL 1 과 2) 를 가르치죠. 그러니 혼동으로 인해 뇌가 녹아버리기 전에 이미 알고 있던 것들은 전부 잊어버리세요.

# 튜토리얼을 빌드하기

All tutorials can be built on Windows, Linux and Mac. For all these platforms, the procedure is roughly the same :
모든 튜토리얼은 윈도우, 리눅스와 맥에서 빌드 가능합니다. 모든 플랫폼에서, 빌드 과정은 대략적으로 모두 똑같습니다 :

* **드라이버를 업데이트하세요** !! 바아아안드시 하십쇼. 미리 경고했어요.
* 아직 없다면, 컴파일러를 하나 다운로드 하세요.
* CMake 를 설치하기
* 튜토리얼들 에서 소스 코드를 다운로드
* CMake 로 프로젝트를 생성하기
* 프로젝트 빌드하기
* 샘플로 놀아보자!

자세한 과정은 아래에 각 플랫폼에 대해 서술되어 있습니다. 경우에 따라 자신의 환경에 맞춰 수정이 필요할 수도 있습니다. 잘 모르겠다면, 윈도우를 위한 절차를 먼저 읽은 다음, 적용해보세요.

## 윈도우에서 빌드


* 드라이버를 업데이트하는 방법은 쉽죠. NVIDIA 나 AMD 의 웹사이트에 가서 드라이버를 다운로드 하세요. GPU 모델을 잘 모르겠다면 : 제어판 -> 시스템과 보안 -> 시스템 -> 장치 관리자 -> 디스플레이. 만약 Intel 내장 GPU 를 사용한다면, 주로 OEM 에서 (Dell, HP, ...) 드라이버를 제공합니다.
* 데스크탑용 Visual Studio 2015 Express 을 컴파일러로 추천합니다. 무료로 [여기서](https://www.visualstudio.com/en-US/products/visual-studio-express-vs) 다운로드 할 수 있습니다. MinGW 를 선호한다면, [Qt Creator](http://qt-project.org/) 를 추천합니다. 사용하고 싶은 것을 설치하면 됩니다. 아래 과정은 Visual Studio 기준으로 설명되었으나, 다른 IDE 에서의 과정도 비슷합니다.
* [CMake ](http://www.cmake.org/cmake/resources/software.html) 를 다운로드 하고 설치하세요.
* [소스코드를 다운로드 받아](http://www.opengl-tutorial.org/download/) 압축을 해제하세요. 경로의 예시는 C:\Users\XYZ\Projects\OpenGLTutorials\ .
* CMake 를 실행하세요. 첫번 째 줄에서는, 압축해제한 폴더를 지정하세요. 잘 모르겠다면, CMakeLists.txt 파일을 포함하고 있는 폴더를 지정하세요. 두번째 줄에는, 컴파일러가 다룰 모든 것들을 저장해두고 싶은 장소를 선택하세요. 예를 들어, C:\Users\XYZ\Projects\OpenGLTutorials-build-Visual2015-64bits\, 나 C:\Users\XYZ\Projects\OpenGLTutorials\build\Visual2015-36bits\ 같은 경로가 될수 있죠. 참고로 아무곳이나 지정해도 된다는 걸 알아두세요. 그러니 같은 폴더일 필요도 없습니다. ![]({{site.baseurl}}/assets/images/tuto-1-window/CMake.png)


* Configure 버튼을 클릭하세요. 처음 프로젝트를 설정해보는 것이기 때문에, CMake는 어떤 컴파일러를 사용할지 물어볼 것 입니다. 처음 과정에 따라 알맞은 것을 선택하세요. 첫 번째 과정에서 맞춰 현명하게 선택하세요. 64bit 윈도우라면 64 bits 컴파일러들을 선택해도 됩니다; 잘 모르겠다면, 32 bits 를 선택하면 됩니다.
* Configure 버튼을 모든 붉은 라인이 사라질 때 까지 클릭하세요. 그 후 Generate 를 클릭합니다. 이제 Visual Studio 프로젝트가 생성되었습니다. 이제 CMake 에 대해서는 잊어버려도 됩니다.
* C:\Users\XYZ\Projects\OpenGLTutorials-build-Visual2010-32bits\ 를 엽니다. Tutorials.sln 파일이 보입니다 : Visual Studio 로 여세요.
![]({{site.baseurl}}/assets/images/tuto-1-window/directories.png)

*Build(빌드)* 메뉴에서, *Build All(모두 빌드)* 를 클릭하세요. 모든 튜토리얼과 의존성(dependency) 들이 컴파일 될겁니다. 그리고 각각의 실행파일들은 C:\Users\XYZ\Projects\OpenGLTutorials\ 로 다행이도 아무 에러 없이 복사되어 들어갈거에요.
![]({{site.baseurl}}/assets/images/tuto-1-window/visual_2010.png)

* C:\Users\XYZ\Projects\OpenGLTutorials\playground 를 열고, playground.exe 를 실행하세요. 검은 윈도우가 나타날겁니다.
![]({{site.baseurl}}/assets/images/tuto-1-window/empty_window.png)


물론 Visual Studio 내부에서 원하는 어떤 튜토리얼이라도 모두 실행할 수 있습니다. Playground 를 마우스 오른쪽 클릭한다음, "Choose as startup project(startup 프로젝트로 지정)" 을 누루세요. F5 를 누르면 이제 코드를 디버그 할 수 있습니다.

![]({{site.baseurl}}/assets/images/tuto-1-window/StartupProject.png)











## Linux 에서 빌드하기

너무 많은 종류의 Linux 배포판이 있어, 모든 플랫폼을 일일이 명시하는건 불가능합니다. 필요시 적절히 바꿔 적용하세요. 그리고 사용하는 배포판의 문서를 읽는 것을 망설이지 마세요.

 

* 최신 드라이버를 설치하세요. 우리는 비공개소스 바이너리 드라이버들을 강력하게 추천합니다. GNU 같은 오픈소스 기반은 아닌 대신에 제대로 동작합니다. 만약 당신의 배포판이 자동 설치를 지원하지 않으면, [우분투 가이드](http://help.ubuntu.com/community/BinaryDriverHowto) 를 시도해 보세요.
* 필요한 컴파일러와 도구, 라이브러리를 설치하세요. 준비물 리스트는 : *cmake make g++ libx11-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxext-dev libxi-dev* . `sudo apt-get install *****` 나 `su && yum install ******` 를 사용하세요.
* [소스코드를 다운로드](http://www.opengl-tutorial.org/download/) 하고 압축을 푸세요. 예를 들어 ~/Projects/OpenGLTutorials/
* cd in ~/Projects/OpenGLTutorials/ 를 타이핑하고 아래 명령어를 입력하세요 :

 * mkdir build
 * cd build
 * cmake ..


* build/ 폴더에 makefile 이 생성될겁니다.
* "make all" 을 입력하세요. 그러면 모든 튜토리얼과 의존성들이 컴파일 될겁니다. 그리고 각각의 실행파일들 또한 ~/Projects/OpenGLTutorials/ 로 복사되어 들어갑니다. 다행이도 아무런 에러도 일어나지 않습니다.
* ~/Projects/OpenGLTutorials/playground 를 열고, ./playground 를 실행하세요. 검은 윈도우가 나타나야 합니다.

참고로, [Qt Creator](http://qt-project.org/) 같은 IDE 를 사용하는게 정말 좋을겁니다. 특히, 이 친구는 CMake 를 빌트인으로 지원하고, 디버깅할때 매우 나은 경험을 제공합니다. QtCreator 를 위한 절차가 아래에 있습니다:

* QtCreator 에서, File->Tools->Options->Compile&Execute->CMake 로 가세요
* CMake 로의 path를 설정하세요. 보통 /usr/bin/cmake 에 있을겁니다.
* File->Open Project; 다음에 tutorials/CMakeLists.tx 를 선택
* 빌드 폴더를 지정하세요. 튜토리얼 폴더 밖을 추천합니다.
* 옵션을 위한 파라미터 박스에서 -DCMAKE_BUILD_TYPE=Debug 로 지정후. Validate 하세요.
* 바닥 쪽에 망치를 클릭하세여. 이제 tutorials/ 폴더의 튜토리얼들이 실행 가능합니다.
* QtCreator 에서 튜토리얼들을 실행하기 위해, Projects->Execution parameters->Working Directory 을 클릭하고, 쉐이더와, 텍스쳐 & 모델 들이 있는 디렉토리를 지정하세요. 예를 들어 튜토리얼 2의 경우 ~/opengl-tutorial/tutorial02_red_triangle/


## Mac 에서 빌딩하기

윈도우와 절차가 비슷합니다. (Makefile 또한 지원되나, 여기서 설명하지는 않습니다) :

* XCode 를 맥 앱스토어 에서 설치합니다
* [CMake 를 다운로드](http://www.cmake.org/cmake/resources/software.html) 하고 .dmg 파일을 설치합니다. 커맨드 라인 도구를 설치할 필요는 없습니다.
* [소스코드를 다운로드](http://www.opengl-tutorials.org/download/) 하고 압축을 푸세요. 예시 경로는 ~/Projects/OpenGLTutorials/  입니다.
* (Application->CMake) CMake 를 실행합니다. 첫줄에는, 압축을 해제했던 폴더를 지정합니다. 확실치 않다면, CMakeList.txt 파일을 포함하는 폴더를 선택하세요. 두번째 줄에는, 컴파일러가 다룰 물건들이 죄다 들어갈 곳을 지정해주세요. 예를 들어, ~/Projects/OpenGLTutorials_bin_XCode/ 를 선택할 수 있습니다. 참고로 어떤 경로를 선택해도 상관없습니다. 같은 폴더일 필요도 없습니다. 
* Configure 버튼을 클릭합니다. 프로젝트를 최초로 설정하기 때문에, CMake 가 사용하고 싶은 컴파일로를 물어볼겁니다. Xcode를 선택하세요.
* 모든 붉은 줄이 사라질때 까지 Configure 버튼을 클릭합니다. 그리고 Generate 버튼을 클릭합니다. Xcode 프로젝트가 생성되었습니다. 이제 CMake에 대해서는 잊어버려도 되요.
* ~/Projects/OpenGLTutorials_bin_XCode/ 로 갑니다. Tutorials.xcodeproj 파일이 보일겁니다 : 실행하세요.
* Xcode의 Scheme 패널에서 실행하고 싶은 튜토리얼을 선택합니다. 그리고 Run 버튼을 사용하여 컴파일 & 실행을 해보세요 :

![]({{site.baseurl}}/assets/images/tuto-1-window/Xcode-projectselection.png)


## 코드 메모::블록들

두 개의 버그 때문에 (하나는 C::B, 하나는 CMake), Project->Build Options->Make 에서의 커맨드라인의 커맨드들을 아래와 같이 편집해야 합니다:

![]({{site.baseurl}}/assets/images/tuto-1-window/CodeBlocksFix.png)


또한 현재 작업중인 폴더를 스스로 지정해줘야 합니다 : Project->Properties -> Build targets -> tutorial N -> 작업중인 디렉토리 실행 ( src_dir/tutorial_N/ 에 있습니다 ).

# 튜토리얼들 실행하기

올바른 디렉토리에서 곧바로 튜토리얼들을 실행시켜야 합니다 : 간단하게 실행파일을 더블 클릭합니다. 커맨드 라인을 좋아한다면, 올바른 폴더로 cd 하세요.

IDE 에서 튜토리얼을 실행하고자 한다면, 위의 설명을 잊지 말고 읽어서 올바른 작업 디렉토리를 지정해주세요.

# 튜토리얼들을 따라하는 방법

Each tutorial comes with its source code and data, which can be found in tutorialXX/. However, you will never modify these projects : they are for reference only. Open playground/playground.cpp, and tweak this file instead. Torture it in any way you like. If you are lost, simply cut'n paste any tutorial in it, and everything should be back to normal.
각각의 튜토리얼은 소스 코드와 데이타와 함게 옵니다.

We will provide snippets of code all along the tutorials. Don't hesitate to cut'n paste them directly in the playground while you're reading : experimentation is good. Avoid simply reading the finished code, you won't learn a lot this way. Even with simple cut'n pasting, you'll get your boatload of problems.

# Opening a window

Finally ! OpenGL code !
Well, not really. All tutorials show you the "low level" way to do things, so that you can see that no magic happens. But this part is actually very boring and useless, so we will use GLFW, an external library, to do this for us instead. If you really wanted to, you could use the Win32 API on Windows, the X11 API on Linux, and the Cocoa API on Mac; or use another high-level library like SFML, FreeGLUT, SDL, ... see the [Links](http://www.opengl-tutorial.org/miscellaneous/useful-tools-links/) page.

Ok, let's go. First, we'll have to deal with dependencies : we need some basic stuff to display messages in the console :

``` cpp
// Include standard headers
#include <stdio.h>
#include <stdlib.h>
```

First, GLEW. This one actually is a little bit magic, but let's leave this for later.

``` cpp
// Include GLEW. Always include it before gl.h and glfw.h, since it's a bit magic.
#include <GL/glew.h>
```

We decided to let GLFW handle the window and the keyboard, so let's include it too :

``` cpp
// Include GLFW
#include <GL/glfw3.h>
```

We don't actually need this one right now, but this is a library for 3D mathematics. It will prove very useful soon. There is no magic in GLM, you can write your own if you want; it's just handy. The "using namespace" is there to avoid typing "glm::vec3", but "vec3" instead.

``` cpp
// Include GLM
#include <glm/glm.hpp>
using namespace glm;
```

If you cut'n paste all these #include's in playground.cpp, the compiler will complain that there is no main() function. So let's create one :

``` cpp
int main(){
```

First thing to do it to initialize GLFW :

``` cpp
// Initialise GLFW
if( !glfwInit() )
{
    fprintf( stderr, "Failed to initialize GLFW\n" );
    return -1;
}
```

We can now create our first OpenGL window !

 

``` cpp
glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

// Open a window and create its OpenGL context
GLFWwindow* window; // (In the accompanying source code, this variable is global)
window = glfwCreateWindow( 1024, 768, "Tutorial 01", NULL, NULL);
if( window == NULL ){
    fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
    glfwTerminate();
    return -1;
}
glfwMakeContextCurrent(window); // Initialize GLEW
glewExperimental=true; // Needed in core profile
if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    return -1;
}
```

Build this and run. A window should appear, and be closed right away. Of course ! We need to wait until the user hits the Escape key :

``` cpp
// Ensure we can capture the escape key being pressed below
glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

do{
    // Draw nothing, see you in tutorial 2 !

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

} // Check if the ESC key was pressed or the window was closed
while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
glfwWindowShouldClose(window) == 0 );
```

And this concludes our first tutorial ! In Tutorial 2, you will learn how to actually draw a triangle.



