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

##Generando en Windows

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

En el menu *Build*, haga clic en *Build All*. Cada tutorial y dependencia será generado. Cada ejecutable también será copiado en  C:\Users\XYZ\Projects\OpenGLTutorials\ . Con suerte, no habrá errores.
![]({{site.baseurl}}/assets/images/tuto-1-window/visual_2010.png)

* Abra C:\Users\XYZ\Projects\OpenGLTutorials\playground, y ejecute playground.exe. Debe aparecer una pantalla negra.
![]({{site.baseurl}}/assets/images/tuto-1-window/empty_window.png)

Usted puede ejecutar los tutoriales desde Visual Studio. Clic derecho en el proyecto Playground y "Escoger como proyecto principal". Puede depurar presionando F5.

![]({{site.baseurl}}/assets/images/tuto-1-window/StartupProject.png)

##Generando en Linux

Hay tantas variantes de Linux en el mundo que es imposible listar para cada plataforma posible. Adapte estas instrucciones si y de ser necesario consulte la documentación de su distribución.

* Instale los controladores mas recientes. Recomendamos los controladores binarios de codigo cerrado. No serán GNU pero de seguro si funcionan. Si su distribución no provee los controladores automáticamente, intente con [la guía de Ubuntu](http://help.ubuntu.com/community/BinaryDriverHowto).
* Instale los compiladores necesarios, herramientas y librerías. La lista completa es : *cmake make g++ libx11-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxext-dev libxi-dev* . Use `sudo apt-get install *****` o `su && yum install ******`.
* [Descargue el código fuente](http://www.opengl-tutorial.org/download/) y descomprimalo, por ejemplo en ~/Projects/OpenGLTutorials/
* cd ~/Projects/OpenGLTutorials/ e ingrese los siguientes comandos :

 * mkdir build
 * cd build
 * cmake ..

* Un archivo makefile se habrá creado en el directorio build/ .
* Escriba "make all". Cada tutorial y dependencia será compilado. Cada ejecutable será copiado en ~/Projects/OpenGLTutorials/ . Con suerte, no habrá errores.
* Abra ~/Projects/kOpenGLTutorials/playground, y ejecute ./playground. Debe aparecer una ventana negra.

Nota: Es recomendable usar un IDE como [Qt Creator](http://qt-project.org/). En particular este tiene soporte integrado para CMake, de manera que le proveerá una agradable experiencia para depurar. Estas son las instrucciones en QtCreator :

* En QtCreator, vaya a Archivo->Herramientas->Opciones->Compilar&ejecutar->CMake
* Esriba la ruta de CMake. Probablemente sea /usr/bin/cmake
* Archivo->Abrir proyecto; Seleccione, tutorials/CMakeLists.txt
* Seleccione un directorio para construir, preferiblemente fuera del directorio de los tutoriales.
* Opcionalmente puede usar -DCMAKE_BUILD_TYPE=Debug en los parámetros. Valide.
* Para ejecutar los tutoriales desde QtCreator, haga clic en Proyectos->Parámetros de ejecución->Directorio actual, y seleccione el directorio donde estan los shaders, texturas y modelos. Ejemplo para tutorial 2 : ~/opengl-tutorial/tutorial02_red_triangle/
* Haga clic en el martillo de abajo. Estos tutoriales pueden ser ejecutados desde el directorio tutorials/.


##Generandi en Mac

El procedimiento es muy similar a Windows (También se puede usar Makefiles pero no los vamos a explicar aquí) :

* Instale XCode desde la App Store
* [Descargue CMake](http://www.cmake.org/cmake/resources/software.html), e instale el .dmg . No necesita instalar las herramientas de linea de comando.
* [Descargue el código fuente](http://www.opengl-tutorial.org/download/) y descomprimalo, por ejemplo en ~/Projects/OpenGLTutorials/ .
* Ejecute CMake (Applications->CMake). En la primera linea, navegue hasta el directorio descomprimido. Si no esta seguro, busque el directorio que contiene el archivo CMakeLists.txt. En la segunda línea, escriba dónde se generarán todos los archivos para la compilación. Por ejemplo ~/Projects/OpenGLTutorials_bin_XCode/. Note que puede ser en cualquier parte, no necesariamente en el mismo directorio.
* Haga clic en el botón configurar. Dado que es la primera vez que configura un proyecto, CMake le preguntará qué copilador desea usar. Escoja XCode.
* Clic en Configurar hasta que desaparezcan las lineas rojas. Clic en Generar. Su proyecto XCode ha sido creado. Ahora puede olvidarse de CMake.
* Abra ~/Projects/OpenGLTutorials_bin_XCode/ . Verá un archivo Tutorials.xcodeproj : abralo.
* Seleccione el tutorial que desea ejecutar en el panel de XCode y luego use el botón de Ejecutar para compilar y ejecutar.

![]({{site.baseurl}}/assets/images/tuto-1-window/Xcode-projectselection.png)


##Nota para Code::Blocks

Por culpa de 2 bugs (uno en C::B y otro en CMake), usted debe editar la linea de comando en Proyecto->Opciones de construcción->Comandos Make, así :

![]({{site.baseurl}}/assets/images/tuto-1-window/CodeBlocksFix.png)

También debe seleccionar el directorio de trabajo usted mismo : Proyecto->Propiedades -> Proyecto a construir -> tutorial N -> directorio de trabajo ( que es : src_dir/tutorial_N/ ).

#Ejecutando los tutoriales

Usted debe ejecutar los tutoriales directamente de los directorios, simplemente haga doble clic en el ejecutable. Si prefier usar la linea de comandos asegurese de hacer cd al directorio correcto.

Si quiere ejecutar los tutoriales desde el IDE, no olvide leer las instrucciones de arriba para seleccionar el directorio correcto.

#Cómo seguir estos tutoriales

Cada tutorial consiste en su código y sus datos, cada uno se puede encontrar en tutorialXX/. Sinembargo, nunca debe modificar estos proyectos : solo son para referencia. Abra playground/playground.cpp, y modifique este archivo en su lugar. Torturelo como le plazca. Si se pierde, simplemente copie otro tutorial dentro de playground/playground.cpp, todo deberá haber vuelto a la normalidad.

Nosotros le proveemos pedacitos de código a lo largo del tutorial. No dude en copiar y pegarlos directamente en el playground mientras va avanzando : Experimentar es bueno ! Evite leer todo el código finalizado, no va a aprender mucho de esta manera. Aun si solo copia y pega los pedazos aprenderá mas y podrá solucionar problemas.

#Abriendo una ventana

Código ! Porfin !
Bueno, en realidad no. Todos los tutoriales le muestran el "nivel bajo" de hacer las cosas, de manera que usted pueda ver qué no es nada mágico, es parte de un largo y tedioso proceso, así que vamos a usar GLFW, una librería externa para que haga la parte aburrida por nosotros. Si usted realmente quisiera, podría usar el API de Win32 en windows, el API X11 en Linux o el API Cocoa en Mac. Podría usar otras librerías como SFML, FreeGLUT, SDL, ... Vea los [vinculos de herramientas útiles aquí](http://www.opengl-tutorial.org/miscellaneous/useful-tools-links/) 

Bueno, ahora si. Listos? Primero, debemos lidiar con las dependencias : necesitamos lo básico para mostrar mensajes en consola :
{% highlight cpp linenos %}
// Incluir los cabeceros estándar
#include <stdio.h>
#include <stdlib.h>
{% endhighlight %}
Primero GLEW. Esto de hecho es un poco de mágia, pero luego lo explicamos.
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



