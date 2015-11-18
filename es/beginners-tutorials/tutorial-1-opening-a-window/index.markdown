---
layout: page
status: publish
published: true
title: 'Tutorial 1 : Opening a window'
date: '2011-04-07 17:54:16 +0200'
date_gmt: '2011-04-07 17:54:16 +0200'
categories: [tuto]
order: 10
tags: []
language: es
---

#Introducción

Bienvenido al primer tutorial !

Antes de saltar a OpenGL, primero es importante aprender a compilar el código que viene con cada tutorial, como correrlo y lo mas importante, como modificar el código usted mismo.

#Prerrequisitos

No hay prerrequisitos para seguir este tutorial. Si tiene experiencia con cualquier lenguaje de programación ( C, Java, Lisp, Javascript, otros ) le servirá para entender completamente el código pero no es necesario. Śería como aprender dos cosas al mismo tiempo.

Todos los tutoriales estan escritos en C++ "fácil". Hemos hecho un gran esfuerzo para hacer l código lo mas sencillo posible. No hay templates, no hay clases, no hay apuntadores. De esta forma usted entenderá todo, aun si solo sabe programar en Java.

#Olvide todo lo anterior

Usted no tiene que saberlas todas, pero aquí debe olvidar todo lo que sabe de OpenGL. Si usted sabe algo acerca de algo que se parece a glBegin(), olvidelo. Aquí usted va aprender el OpenGl moderno (OpenGL 3 y 4), y la mayoría de tutoriales enseñan el OpenGl "viejo" (OpenGL 1 and 2). así que olvide todo lo que sabe antes de que su cerebro se derrita con la mezcla.

#Compilando los tutoriales

Todos los tutoriales pueden ser compilados en Windows, Linux y Mac. Para todas las plataformas el proceso es prácticamente el mismo :

* **Actualice sus controlares** !! Hagalo ! Soldado advertido no muere en guerra ...
* Descargue un compilador, si no tiene uno aun. 
* Instale CMake
* Descargue el código fuente de los tutoriales
* Genere un proyecto usando CMake
* Compile el proyecyo
* Juegue con los ejemplos !

Ahora en detalle para cada plataforma. Es posible que se necesite adaptar el proceso. Si no esta seguro, siga las instrucciones para Windows y trate de adaptarlas.

##Building on Windows

* Actualizar sus controladores debe ser fácil. Solo vaya a los sitios de NVIDIA's o AMD's y descargue los controladores. Si no sabe su modelo de GPU use : Panel de Control -> Sistema y Seguridad -> Sistema -> Administrador de Dispositivos -> Adaptadores de antalla. Si usted tiene una tarjeta gráfica integrada, los controladores usualmente han sido ya instalados por el fabricante del equipo (Dell, HP, ...).
* Sugerimos que use Visual Studio 2015 Express de escritorio como compilador. Puede descargarlo grátis [aquí](https://www.visualstudio.com/en-US/products/visual-studio-express-vs). Si prefiere puede usar MinGW, en ese casi le recomendamos usar [Qt Creator](http://qt-project.org/). Instale cualquier que desee. Los pasos a continuación son para Visual Studio, pero son los mismo para cualquier IDE.
* Descargue [CMake ](http://www.cmake.org/cmake/resources/software.html) de aquí e instalelo
* [Descargue el código fuente](http://www.opengl-tutorial.org/download/) descomprimalo en una ubicación que usted recuerde, por ejemplo,  C:\Users\XYZ\Projects\OpenGLTutorials\ .
* Abra CMake. En la primera línea navegue hasta la carpeta descomprimida. Si no esta seguro, escoja la carpeta que contiene el archivo CMakeLists.txt . En la segunda línea  escriba la ruta del lugar donde será compilado y estarán todos los archivos. Por ejemplo puede escoger C:\Users\XYZ\Projects\OpenGLTutorials-build-Visual2015-64bits\, o C:\Users\XYZ\Projects\OpenGLTutorials\build\Visual2015-36bits\ . Note que puede ser quen cualquier lugar, no necesariamente en la misma carpeta .
![]({{site.baseurl}}/assets/images/tuto-1-window/CMake.png)

* Haga clic en el botón Configurar. Dado que es la primera vez que usted configura un proyecto, CMake le preguntará el compilador que desea usar. Escoja bien dependiendo del paso 1. Si usted tiene windows de 64 bits, puede seleccionar 64 bits, si no lo sabe escoja 32 bits.
* Hagala cloc en configurar hasta que todas las lineas rojas desaparezcan. Haga clic en generar. Su proyecto de Visual Studio project ha sido creado. En este momento puede olvidarse de CMake.
* Abra C:\Users\XYZ\Projects\OpenGLTutorials-build-Visual2010-32bits\. Verá un archivo Tutorials.sln : abralo con Visual Studio.
![]({{site.baseurl}}/assets/images/tuto-1-window/directories.png)

En el menu *Build*, haga clic en *Build All*. Cada tutorial y dependencia será compilado. Cada ejecutable también será copiado en  C:\Users\XYZ\Projects\OpenGLTutorials\ . Hopefuly no error occurs.
![]({{site.baseurl}}/assets/images/tuto-1-window/visual_2010.png)

* Open C:\Users\XYZ\Projects\OpenGLTutorials\playground, and launch playground.exe. A black window should appear.
![]({{site.baseurl}}/assets/images/tuto-1-window/empty_window.png)


You can also launch any tutorial from inside Visual Studio. Right-click on Playground once, "Choose as startup project". You can now debug the code by pressing F5.

![]({{site.baseurl}}/assets/images/tuto-1-window/StartupProject.png)











##Building on Linux

They are so many Linux variants out there that it's impossible to list every possible platform. Adapt if required, and don't hesitate to read your distribution's documentation.

 

* Install the latest drivers. We highly recommend the closed-source binary drivers. It's not GNU or whatever, but they work. If your distribution doesn't provide an automatic install, try [Ubuntu's guide](http://help.ubuntu.com/community/BinaryDriverHowto).
* Install all needed compilers, tools & libs. Complete list is : *cmake make g++ libx11-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxext-dev libxi-dev* . Use `sudo apt-get install *****` or `su && yum install ******`.
* [Download the source code](http://www.opengl-tutorial.org/download/) and unzip it, for instance in ~/Projects/OpenGLTutorials/
* cd in ~/Projects/OpenGLTutorials/ and enter the following commands :

 * mkdir build
 * cd build
 * cmake ..


* A makefile has been created in the build/ directory.
* type "make all". Every tutorial and dependency will be compiled. Each executable will also be copied back into ~/Projects/OpenGLTutorials/ . Hopefuly no error occurs.
* Open ~/Projects/OpenGLTutorials/playground, and launch ./playground. A black window should appear.

Note that you really should use an IDE like [Qt Creator](http://qt-project.org/). In particular, this one has built-in support for CMake, and it will provide a much nicer experience when debugging. Here are the instructions for QtCreator :

* In QtCreator, go to File->Tools->Options->Compile&Execute->CMake
* Set the path to CMake. This is most probably /usr/bin/cmake
* File->Open Project; Select tutorials/CMakeLists.txt
* Select a build directory, preferably outside the tutorials folder
* Optionally set -DCMAKE_BUILD_TYPE=Debug in the parameters box. Validate.
* Click on the hammer on the bottom. The tutorials can now be launched from the tutorials/ folder.
* To run the tutorials from QtCreator, click on Projects->Execution parameters->Working Directory, and select the directory where the shaders, textures & models live. Example for tutorial 2 : ~/opengl-tutorial/tutorial02_red_triangle/


##Building on Mac

The procedure is very similar to Windows' (Makefiles are also supported, but won't be explained here) :

* Install XCode from the Mac App Store
* [Download CMake](http://www.cmake.org/cmake/resources/software.html), and install the .dmg . You don't need to install the command-line tools.
* [Download the source code](http://www.opengl-tutorial.org/download/) and unzip it, for instance in ~/Projects/OpenGLTutorials/ .
* Launch CMake (Applications->CMake). In the first line, navigate to the unzipped folder. If unsure, choose the folder that contains the CMakeLists.txt file. In the second line, enter where you want all the compiler's stuff to live. For instance, you can choose ~/Projects/OpenGLTutorials_bin_XCode/. Notice that it can be anywhere, not necessarily in the same folder.
* Click on the Configure button. Since this is the first time you configure the project, CMake will ask you which compiler you would like to use. Choose Xcode.
* Click on Configure until all red lines disappear. Click on Generate. Your Xcode project is now created. You can forget about CMake.
* Open ~/Projects/OpenGLTutorials_bin_XCode/ . You will see a Tutorials.xcodeproj file : open it.
* Select the desired tutorial to run in Xcode's Scheme panel, and use the Run button to compile & run :

![]({{site.baseurl}}/assets/images/tuto-1-window/Xcode-projectselection.png)


##Note for Code::Blocks

Due to 2 bugs (one in C::B, one in CMake), you have to edit the command-line in Project->Build Options->Make commands, as follows :

![]({{site.baseurl}}/assets/images/tuto-1-window/CodeBlocksFix.png)


You also have to setup the working directory yourself : Project->Properties -> Build targets -> tutorial N -> execution working dir ( it's src_dir/tutorial_N/ ).

#Running the tutorials

You should run the tutorials directly from the right directory : simply double-click on the executable. If you like command line best, cd to the right directory.

If you want to run the tutorials from the IDE, don't forget to read the instructions above to set the correct working directory.

#How to follow these tutorials

Each tutorial comes with its source code and data, which can be found in tutorialXX/. However, you will never modify these projects : they are for reference only. Open playground/playground.cpp, and tweak this file instead. Torture it in any way you like. If you are lost, simply cut'n paste any tutorial in it, and everything should be back to normal.

We will provide snippets of code all along the tutorials. Don't hesitate to cut'n paste them directly in the playground while you're reading : experimentation is good. Avoid simply reading the finished code, you won't learn a lot this way. Even with simple cut'n pasting, you'll get your boatload of problems.

#Opening a window

Finally ! OpenGL code !
Well, not really. All tutorials show you the "low level" way to do things, so that you can see that no magic happens. But this part is actually very boring and useless, so we will use GLFW, an external library, to do this for us instead. If you really wanted to, you could use the Win32 API on Windows, the X11 API on Linux, and the Cocoa API on Mac; or use another high-level library like SFML, FreeGLUT, SDL, ... see the [Links](http://www.opengl-tutorial.org/miscellaneous/useful-tools-links/) page.

Ok, let's go. First, we'll have to deal with dependencies : we need some basic stuff to display messages in the console :
{% highlight cpp linenos %}
// Include standard headers
#include <stdio.h>
#include <stdlib.h>
{% endhighlight %}
First, GLEW. This one actually is a little bit magic, but let's leave this for later.
{% highlight cpp linenos %}
// Include GLEW. Always include it before gl.h and glfw.h, since it's a bit magic.
#include <GL/glew.h>
{% endhighlight %}
We decided to let GLFW handle the window and the keyboard, so let's include it too :
{% highlight cpp linenos %}
// Include GLFW
#include <GL/glfw3.h>
{% endhighlight %}
We don't actually need this one right now, but this is a library for 3D mathematics. It will prove very useful soon. There is no magic in GLM, you can write your own if you want; it's just handy. The "using namespace" is there to avoid typing "glm::vec3", but "vec3" instead.
{% highlight cpp linenos %}
// Include GLM
#include <glm/glm.hpp>
using namespace glm;
{% endhighlight %}
If you cut'n paste all these #include's in playground.cpp, the compiler will complain that there is no main() function. So let's create one :
{% highlight cpp linenos %}
int main(){
{% endhighlight %}
First thing to do it to initialize GLFW :
{% highlight cpp linenos %}
// Initialise GLFW
if( !glfwInit() )
{
    fprintf( stderr, "Failed to initialize GLFW\n" );
    return -1;
}
{% endhighlight %}
We can now create our first OpenGL window !

 
{% highlight cpp linenos %}
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
{% endhighlight %}
Build this and run. A window should appear, and be closed right away. Of course ! We need to wait until the user hits the Escape key :
{% highlight cpp linenos %}
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
{% endhighlight %}
And this concludes our first tutorial ! In Tutorial 2, you will learn how to actually draw a triangle.



