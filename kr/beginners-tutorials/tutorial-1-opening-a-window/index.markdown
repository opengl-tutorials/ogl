---
layout: tutorial
status: publish
published: true
title: 'Tutorial 1 : 윈도우 열기'
date: '2016-11-19 17:54:16 +0200'
date_gmt: '2016-11-19 17:54:16 +0200'
categories: [tuto]
language: kr
order: 10
tags: []
---

# 소개

첫 튜토리얼을 환영합니다 !


OpenGL을 시작하기 전에, 먼저 각 자습서와 함께 제공되는 코드 빌드 방법, 실행 방법 및 (가장 중요한) 코드 작성 방법을 배워야합니다.

# 준비물

이 튜토리얼들을 따라 진행하는데 특별한 준비물은 필요 없습니다. 어떠한 프로그래밍 언어 ( C, Java, Lisp, Javascript, 등) 라도 경험해보았다면 코드를 더 쉽게 이해하는데 도움이 되겠으나 필수는 아닙니다. 다만 두가지를 동시에 배우는게 조금 어려울 뿐입니다.

모든 튜토리얼은 "쉬운 C++" 로 작성되었습니다. 가능하면 코드를 간단하게 만들기 위해 많은 노력이 있었습니다. 템플릿, 클래스, 포인터를 사용하지 않습니다. 이렇게하 Java만 알더라도 모든걸 이해할 수 있습니다.

# 다 잊어버리세요

아무것도 알 필요는 없지만, OpenGL에 대해 알고 있는 것들은 모두 잊어버려야 합니다.
glBegin()처럼 생긴 무언가를 기억하고 있다면 잊어버리세요. 여기서는 최신 OpenGL (OpenGL 3 과 4)을 배우지만, 대부분의 OpenGL 온라인 강의들은 "예전" OpenGL (OpenGL 1 과 2)를 가르치죠. 그러니 혼동으로 인해 뇌가 녹아버리기 전에 이미 알고 있던 것들은 전부 잊어버리세요.

# 튜토리얼 빌드하기

모든 튜토리얼은 윈도우, 리눅스 및 맥에서 빌드 가능합니다. 모든 플랫폼에서, 빌드 과정은 대략적으로 모두 동일합니다.

* **드라이버를 업데이트하세요** !! 바아아안드시 하십쇼. 미리 경고했어요.
* 아직 없다면, 컴파일러를 하나 다운로드 하세요.
* CMake 설치하기
* 튜토리얼 소스 코드 다운로드
* CMake로 프로젝트 생성하기
* 프로젝트 빌드하기
* 샘플로 놀아보자!

이제 각 플랫폼에 대한 자세한 과정이 서술됩니다. 경우에 따라 자신의 환경에 맞게 수정을 해야할 수도 있습니다. 잘 모르겠다면 윈도우용 설명을 먼저 읽은 다음 적용해보세요.

## 윈도우에서 빌드하기


* 드라이버를 업데이트하는 방법은 쉽죠. NVIDIA나 AMD의 웹사이트에 가서 드라이버를 다운로드 하세요. GPU 모델을 잘 모르겠다면, 제어판 -> 시스템과 보안 -> 시스템 -> 장치 관리자 -> 디스플레이로 가세요. 만약 Intel 내장 GPU를 사용한다면, 주로 OEM (Dell, HP, ...)에서 드라이버를 제공합니다.
* 데스크탑용 Visual Studio 2015 Express 을 컴파일러로 추천합니다. 무료로 [여기서](https://www.visualstudio.com/en-US/products/visual-studio-express-vs) 다운로드 할 수 있습니다. MinGW 를 선호한다면, [Qt Creator](http://qt-project.org/)를 추천합니다. 사용하고 싶은 것을 설치하면 됩니다. 아래 과정은 Visual Studio 기준으로 설명되었으나, 다른 IDE 에서의 과정도 비슷합니다.
* [CMake](http://www.cmake.org/cmake/resources/software.html)를 다운로드 하고 설치하세요.
* [소스코드를 다운로드 받아](http://www.opengl-tutorial.org/download/) 압축을 해제하세요. 예를들어 C:\Users\XYZ\Projects\OpenGLTutorials\ 같은 곳에 하면 됩니다.
* CMake를 실행하세요. 첫 번째 줄은 압축을 해제한 폴더로 지정하세요. 잘 모르겠다면, CMakeLists.txt 파일을 포함하고 있는 폴더를 지정하세요. 두 번째 줄은 컴파일러가 다룰 것들을 저장해두고 싶은 장소를 선택하세요. 예를 들어, C:\Users\XYZ\Projects\OpenGLTutorials-build-Visual2015-64bits\, 나 C:\Users\XYZ\Projects\OpenGLTutorials\build\Visual2015-36bits\ 같은 경로가 될수 있죠. 참고로 아무곳이나 지정해도 됩니다. 그러니 같은 폴더일 필요가 없습니다. ![]({{site.baseurl}}/assets/images/tuto-1-window/CMake.png)


* Configure(구성) 버튼을 클릭하세요. 처음 프로젝트를 설정해보는 것이기 때문에, CMake는 어떤 컴파일러를 사용할지 물어볼 것 입니다. 처음 과정에 따라 알맞은 것을 선택하세요. 첫 번째 과정에 맞춰 현명하게 선택하세요. 64bit 윈도우라면 64bits 컴파일러들을 선택해도 됩니다. 잘 모르겠다면 32bits를 선택하면 됩니다.
* 모든 붉은 라인이 사라질 때까지 Configure(구성) 버튼을 클릭하세요. 그 후 Generate(생성) 버튼을 클릭합니다. 이제 Visual Studio 프로젝트가 생성되었습니다. 이제 CMake에 대해서는 잊어버려도 됩니다.
* C:\Users\XYZ\Projects\OpenGLTutorials-build-Visual2010-32bits\ 를 엽니다. Tutorials.sln 파일이 보입니다 : Visual Studio로 여세요.
![]({{site.baseurl}}/assets/images/tuto-1-window/directories.png)

*Build(빌드)* 메뉴에서, *Build All(모두 빌드)* 를 클릭하세요. 모든 튜토리얼과 의존성(dependency)들이 컴파일 될 겁니다. 그리고 각각의 실행파일들은 C:\Users\XYZ\Projects\OpenGLTutorials\ 로 아무 에러 없이 복사되어 들어갈거에요.
![]({{site.baseurl}}/assets/images/tuto-1-window/visual_2010.png)

* C:\Users\XYZ\Projects\OpenGLTutorials\playground 를 열고, playground.exe 를 실행하세요. 검은 윈도우가 나타날 겁니다.
![]({{site.baseurl}}/assets/images/tuto-1-window/empty_window.png)


Visual Studio 내에서 다른 튜토리얼을 실행할 수 있습니다. Playground에서 마우스 오른쪽 버튼을 클릭하고 "Choose as startup project(시작 프로젝트로 지정)"을 클릭하세요. 이제 F5를 눌러 코드를 디버그 할 수 있습니다.

![]({{site.baseurl}}/assets/images/tuto-1-window/StartupProject.png)











## Linux에서 빌드하기

너무 많은 종류의 Linux 배포판이 있어서 모든 플랫폼을 일일이 명시하는건 불가능합니다. 필요하면 적절히 바꿔 적용하고, 사용하는 배포판의 문서를 읽는 것을 망설이지 마세요.



* 최신 드라이버를 설치하세요. 비공개 소스 바이너리 드라이버들을 강력하게 추천합니다. GNU든 아니든 제대로 동작합니다. 만약 배포판이 자동 설치를 지원하지 않으면, [우분투 가이드](http://help.ubuntu.com/community/BinaryDriverHowto)를 시도해 보세요.
* 필요한 컴파일러와 도구, 라이브러리를 설치하세요. 준비물 리스트는 : *cmake make g++ libx11-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxext-dev libxi-dev* . `sudo apt-get install *****` 나 `su && yum install ******` 를 사용하세요.
* [소스코드를 다운로드](http://www.opengl-tutorial.org/download/)하고 압축을 푸세요. ~/Projects/OpenGLTutorials/ 같은 경로에 풀면 됩니다.
* cd in ~/Projects/OpenGLTutorials/ 를 입력하고 아래 명령어를 입력하세요.

 * mkdir build
 * cd build
 * cmake ..


* build/ 폴더에 makefile이 생성됩니다.
* "make all"을 입력하면 모든 튜토리얼과 의존성들이 컴파일 됩니다. 그리고 각각의 실행파일도 ~/Projects/OpenGLTutorials/ 로 복사되어 들어갑니다. 아무런 에러도 일어나지 않을 겁니다.
* ~/Projects/OpenGLTutorials/playground 를 열고, ./playground 를 실행하세요. 검은 윈도우가 나타나야 합니다.

참고로, [Qt Creator](http://qt-project.org/) 같은 IDE를 사용하면 좋습니다. 특히 이 툴은 CMake를 내부적으로 지원하고, 디버깅할때 훨씬 좋은 경험을 제공합니다. QtCreator 를 위한 절차가 아래에 있습니다.

* QtCreator 에서, File->Tools->Options->Compile&Execute->CMake로 가세요.
* CMake 경로를 설정하세요. 보통 /usr/bin/cmake 에 있을 겁니다.
* File->Open Project로 가서 tutorials/CMakeLists.txt 를 선택
* 빌드 폴더를 지정하세요. 튜토리얼 폴더 바깥에 지정하는 것을 추천합니다.
* 필요하면 매개변수 상자에서 -DCMAKE_BUILD_TYPE=Debug 로 설정 후. Validate 하세요.
* 하단의 망치를 클릭하세요. 이제 tutorials/ 폴더에서 튜토리얼을 실행할 수 있습니다.
* QtCreator에서 튜토리얼을 실행하기 위해, Projects->Execution parameters->Working Directory를 클릭하고, 쉐이더, 텍스쳐 및 모델이 있는 디렉토리를 지정하세요. 예를 들어 튜토리얼 2의 경우 ~/opengl-tutorial/tutorial02_red_triangle/를 지정하면 됩니다.


## Mac에서 빌드하기

윈도우와 절차가 비슷합니다 (Makefile 도 지원되지만 여기서는 설명하지 않습니다).

* XCode를 맥 앱스토어에서 설치합니다.
* [CMake 를 다운로드](http://www.cmake.org/cmake/resources/software.html)하고 .dmg 파일을 설치합니다. 커맨드 라인 도구는 설치하지 않아도 됩니다.
* [소스코드를 다운로드](http://www.opengl-tutorials.org/download/) 하고 압축을 푸세요. ~/Projects/OpenGLTutorials/ 같은 경로에 풀면 됩니다.
* (Application->CMake) CMake를 실행합니다. 첫 번째 줄에는 압축을 해제했던 폴더를 지정합니다. 확실하지 않으면 CMakeList.txt 파일을 포함하는 폴더를 선택하세요. 두 번째 줄에는 컴파일러가 다룰 파일들이 저장될 곳을 지정해주세요. 예를 들어, ~/Projects/OpenGLTutorials_bin_XCode/ 를 선택할 수 있습니다. 참고로 어떤 경로를 선택해도 상관없습니다. 같은 폴더일 필요도 없습니다.
* Configure(구성) 버튼을 클릭합니다. 프로젝트를 최초로 설정하기 때문에, CMake가 사용하고 싶은 컴파일러를 물어볼겁니다. Xcode를 선택하세요.
* 붉은 줄이 전부 사라질 때까지 Configure(구성) 버튼을 클릭합니다. 그리고 Generate(생성) 버튼을 클릭합니다. Xcode 프로젝트가 생성되었습니다. 이제 CMake에 대해서는 잊어버려도 됩니다.
* ~/Projects/OpenGLTutorials_bin_XCode/ 로 갑니다. Tutorials.xcodeproj 파일이 보일겁니다. 실행하세요.
* XCode의 Scheme 패널에서 실행하고 싶은 튜토리얼을 선택합니다. 그리고 Run 버튼을 클릭하여 컴파일, 실행을 해보세요.

![]({{site.baseurl}}/assets/images/tuto-1-window/Xcode-projectselection.png)


## Code::Blocks에 대한 참고 사항

두 개의 버그 때문에 (하나는 C::B, 하나는 CMake), Project->Build Options->Make 에서 커맨드라인의 커맨드들을 아래와 같이 편집해야 합니다:

![]({{site.baseurl}}/assets/images/tuto-1-window/CodeBlocksFix.png)


그리고 현재 작업중인 폴더를 직접 지정해줘야 합니다. Project -> Properties -> Build targets -> tutorial N -> 작업중인 디렉토리 실행 ( src_dir/tutorial_N/ 에 있습니다 ).

# 튜토리얼 실행하기

올바른 디렉토리에서 직접 튜토리얼들을 실행시켜야 합니다. 간단하게 실행파일을 더블 클릭합니다. 커맨드 라인을 좋아한다면, 해당 폴더로 cd 하세요.

IDE에서 튜토리얼을 실행하려면, 위의 설명을 읽고 올바른 작업 디렉토리를 지정해주세요.

# 튜토리얼들을 따라하는 방법

각각의 튜토리얼은 소스 코드와 데이터를 제공합니다. 이들은 tutorialXX/ 에서 찾을 수 있습니다. 이 프로젝트들을 절대 수정하지 마세요. 이들은 참고용으로만 써야 합니다.  playground/playground.cpp 파일을 대신 수정하세요. 원하는대로 마음껏 수정해도 됩니다. 어떻게 할지 모를때는 튜토리얼에 있는 코드를 복사 붙여넣기 하세요. 그러면 다시 정상으로 돌아갈 겁니다.

튜토리얼 페이지를 따라 코드 조각들을 제공할겁니다. 그러니 공부하는 동안 playground에 그것들을 가져다 붙이는걸 주저하지 마세요. 실험정신은 좋은 것입니다. 이미 완성된 코드를 읽기만 하는 것은 피하세요. 그렇게 하면 많은 것을 배울 수 없어요. 간단한 잘라 붙여넣기만으로도, 여러 과제를 한가득 얻어가게 될겁니다.

# 윈도우 엽시다

드디어 ! OpenGL 코드로 !

사실, 조금 더 알아둬야 할게 있습니다. 모든 튜토리얼은 어떤 일을 하는 방법을 "저수준" 에서 알려줄겁니다. 여기엔 어떠한 마법도 일어나지 않습니다. 하지만 이 부분은 확실이 지루하고 불필요하기때문에, 우리대신 이 부분을 수행 해줄 외부 라이브러리인 GLFW를 사용할겁니다. 만약 원한다면, 윈도우즈의 Win32 API나 리눅스의 X11, 혹은 맥의 Cocoa API를 사용할 수 있습니다. 아니면 SFML, FreeGLUT, SDL, ... 등의 다른 고수준 라이브러리들을 사용할 수도 있겠죠. 여기에 관해선 [링크](http://www.opengl-tutorial.org/miscellaneous/useful-tools-links/) 페이지를 참고하세요.

좋아요, 이제 시작해봅시다. 먼저, 우리는 의존성들을 다뤄야 합니다. 콘솔에 메세지를 띄우기 위한 몇 가지 기초적인 것들이 필요합니다.

``` cpp
// 표준 헤더 포함
#include <stdio.h>
#include <stdlib.h>
```

먼저, GLEW. 이 녀석은 사실 작은 마법을 부리지만, 여기에 관해선 나중에 설명하죠.

``` cpp
// GLEW 포함. gl.h 나 glfw.h 를 포함하기 전에 먼저 포함하세요. 그래서 마법을 좀 부릴 수 있게요.
#include <GL/glew.h>
```

우리는 GLFW가 윈도우와 키보드를 다루도록 결정했습니다. 그러니 이 친구도 포함하도록 하죠.

``` cpp
// GLFW 도 포함
#include <GL/glfw3.h>
```

사실 지금은 이게 필요하지 않지만, 이것은 3D 계산을 위한 라이브러리입니다. 그리고 곧 도움이 될겁니다. GLM에서는 마법이란 없어서, 원한다면 스스로 작성할 수 있습니다. 다만 이런식으로 하는게 더 편하죠. 여기 "using namespace" 는 "glm::vec3" 대신 "vec3" 을 입력하는 것을 피하기 위한 것입니다.

``` cpp
// GLM 포함
#include <glm/glm.hpp>
using namespace glm;
```

만약 playground.cpp 에 #include 할 것들을 모두 잘라 붙여넣었다면, 컴파일러가 main() 함수가 없다고 불평할 겁니다. 그러니 하나 만들죠.

``` cpp
int main(){
```

GLFW를 초기화 해주기 위해 먼저 해야 합니다.

``` cpp
// GLFW 초기화
if( !glfwInit() )
{
    fprintf( stderr, "GLFW 초기화 실패\n" );
    return -1;
}
```

이제 우리의 첫번째 OpenGL 윈도우를 생성할 수 있습니다!



``` cpp
glfwWindowHint(GLFW_SAMPLES, 4); // 4x 안티에일리어싱
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3 을 쓸 겁니다
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS 가 기분 좋아짐; 꼭 필요한 부분은 아님
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //옛날 OpenGL은 원하지 않아요

// 새창을 열고, OpenGL 컨텍스트를 생성
GLFWwindow* window; // (후술되는 코드를 보면, 이 변수는 전역(Global)입니다.)
window = glfwCreateWindow( 1024, 768, "Tutorial 01", NULL, NULL);
if( window == NULL ){
    fprintf( stderr, "GLFW 윈도우를 여는데 실패했습니다. Intel GPU 를 사용한다면, 3.3 지원을 하지 않습니다. 2.1 버전용 튜토리얼을 시도하세요.\n" );
    glfwTerminate();
    return -1;
}
glfwMakeContextCurrent(window); // GLEW 초기화
glewExperimental=true; // 코어 프로파일을 위해 필요함
if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    return -1;
}
```

이것을 빌드하고 실행하세요. 새 창이 나타날겁니다. 그리고 바로 닫힙니다. 당연한거죠! 우리는 사용자가 Escape 키를 누를때 까지 기다리도록 해야 합니다.

``` cpp
// 밑에서 Escape 키가 눌러지는 것을 감지할 수 있도록 할 것
glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

do{
    // 아무것도 그리지 않습니다. 두번째 튜토리얼에서 만나도록 하죠!

    // 버퍼들을 교체
    glfwSwapBuffers(window);
    glfwPollEvents();

} // 만약 ESC 키가 눌러졌는지 혹은 창이 닫혔는지 체크 체크
while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
glfwWindowShouldClose(window) == 0 );
```

이걸로 첫번째 튜토리얼이 끝났습니다. 튜토리얼 2 에서는, 실제로 삼각형을 어떻게 그리는지 배우겠습니다.
