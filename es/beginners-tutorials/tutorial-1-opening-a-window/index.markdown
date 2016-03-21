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

Antes de saltar a OpenGL, primero es importante aprender a compilar el código que viene con cada tutorial, como correrlo y lo mas importante, como modificar el código tu mismo.

#Prerrequisitos

No hay prerrequisitos para seguir este tutorial. Si tienes experiencia con cualquier lenguaje de programación ( C, Java, Lisp, Javascript, otros ) te servirá para entender completamente el código pero no es necesario. Śería como aprender dos cosas al mismo tiempo.

Todos los tutoriales estan escritos en C++ "fácil". Hemos hecho un gran esfuerzo para hacer el código lo mas sencillo posible. No hay templates, no hay clases, no hay apuntadores. De esta forma usted entenderá todo, aun si solo sabe programar en Java.

#Olvide todo lo anterior

No tienes que saberlas todas, pero aquí debes olvidar todo lo que sabes de OpenGL. Si sabes algo acerca de una cosa que se parece a glBegin(), olvidalo. Aquí vas a aprender el OpenGl moderno (OpenGL 3 y 4), y la mayoría de tutoriales enseñan el OpenGl "viejo" (OpenGL 1 and 2). así que olvida todo lo que sabes antes de que tu cerebro se derrita con la mezcla.

#Compilando los tutoriales

Todos los tutoriales pueden ser compilados en Windows, Linux y Mac. Para todas las plataformas el proceso es prácticamente el mismo :

* **Actualiza los controlares** !! Hazlo ! Soldado advertido no muere en guerra ...
* Descarga un compilador, si no tienes uno aun. 
* Instala CMake
* Descarga el código fuente de los tutoriales
* Genera un proyecto usando CMake
* Compila el proyecyo
* Juega con los ejemplos !

Ahora en detalle para cada plataforma. Es posible que se necesite adaptar el proceso. Si no estas seguro, sigue las instrucciones para Windows y trate de adaptarlas.

## Generando en Windows

* Actualizar tus controladores debe ser fácil. Solo ve a los sitios de NVIDIA o AMD y descarga los controladores. Si no sabes tu modelo de GPU usa : Panel de Control -> Sistema y Seguridad -> Sistema -> Administrador de Dispositivos -> Adaptadores de antalla. Si tienes una tarjeta gráfica integrada, los controladores usualmente han sido ya instalados por el fabricante del equipo (Dell, HP, ...).
* Sugerimos que uses Visual Studio 2015 Express de escritorio como compilador. Puedes descargarlo grátis [aquí](https://www.visualstudio.com/en-US/products/visual-studio-express-vs). Si prefieres puedes usar MinGW, en ese caso te recomendamos usar [Qt Creator](http://qt-project.org/). Instala cualquiera que desees. Los pasos a continuación son para Visual Studio, pero son los mismo para cualquier IDE.
* Descarga [CMake](http://www.cmake.org/cmake/resources/software.html) de aquí e instalelo
* [Descargue el código fuente](http://www.opengl-tutorial.org/download/) descomprímelo en una ubicación que recuerdes, por ejemplo,  C:\Users\XYZ\Projects\OpenGLTutorials\ .
* Abre CMake. En la primera línea navega hasta la carpeta descomprimida. Si no estas seguro, escoge la carpeta que contiene el archivo CMakeLists.txt . En la segunda línea  escribe la ruta del lugar donde será compilado y estarán todos los archivos. Por ejemplo puede escoger C:\Users\XYZ\Projects\OpenGLTutorials-build-Visual2015-64bits\, o C:\Users\XYZ\Projects\OpenGLTutorials\build\Visual2015-36bits\ . Nota que puede ser quen cualquier lugar, no necesariamente en la misma carpeta .
![]({{site.baseurl}}/assets/images/tuto-1-window/CMake.png)

* Haz clic en el botón Configurar. Dado que es la primera vez que configuras un proyecto, CMake le preguntará el compilador que desea usar. Escoge bien dependiendo del paso 1. Si tienes windows de 64 bits, puede seleccionar 64 bits, si no lo sabes escoge 32 bits.
* Haz clic en configurar hasta que todas las lineas rojas desaparezcan. Haz clic en generar. Tu proyecto de Visual Studio project ha sido creado. En este momento puede olvidarse de CMake.
* Abre C:\Users\XYZ\Projects\OpenGLTutorials-build-Visual2010-32bits\. Verás un archivo Tutorials.sln : abralo con Visual Studio.
![]({{site.baseurl}}/assets/images/tuto-1-window/directories.png)

En el menu *Build*, haz clic en *Build All*. Cada tutorial y dependencia será generado. Cada ejecutable también será copiado en  C:\Users\XYZ\Projects\OpenGLTutorials\ . Con suerte, no habrá errores.
![]({{site.baseurl}}/assets/images/tuto-1-window/visual_2010.png)

* Abre C:\Users\XYZ\Projects\OpenGLTutorials\playground, y ejecuta playground.exe. Debe aparecer una pantalla negra.
![]({{site.baseurl}}/assets/images/tuto-1-window/empty_window.png)

Puedes ejecutar los tutoriales desde Visual Studio. Clic derecho en el proyecto Playground y "Escoger como proyecto principal". Puede depurar presionando F5.

![]({{site.baseurl}}/assets/images/tuto-1-window/StartupProject.png)

## Generando en Linux

Hay tantas variantes de Linux en el mundo que es imposible listar para cada plataforma posible. Adapte estas instrucciones si y de ser necesario consulta la documentación de tu distribución.

* Instala los controladores mas recientes. Recomendamos los controladores binarios de codigo cerrado. No serán GNU pero de seguro si funcionan. Si tu distribución no provee los controladores automáticamente, intente con [la guía de Ubuntu](http://help.ubuntu.com/community/BinaryDriverHowto).
* Instala los compiladores necesarios, herramientas y librerías. La lista completa es : *cmake make g++ libx11-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxext-dev libxi-dev* . Use `sudo apt-get install *****` o `su && yum install ******`.
* [Descarga el código fuente](http://www.opengl-tutorial.org/download/) y descomprimalo, por ejemplo en ~/Projects/OpenGLTutorials/
* cd ~/Projects/OpenGLTutorials/ e ingrese los siguientes comandos :

 * mkdir build
 * cd build
 * cmake ..

* Un archivo makefile se habrá creado en el directorio build/ .
* Escribe "make all". Cada tutorial y dependencia será compilado. Cada ejecutable será copiado en ~/Projects/OpenGLTutorials/ . Con suerte, no habrá errores.
* Abra ~/Projects/kOpenGLTutorials/playground, y ejecute ./playground. Debe aparecer una ventana negra.

Nota: Es recomendable usar un IDE como [Qt Creator](http://qt-project.org/). En particular este tiene soporte integrado para CMake, de manera que le proveerá una agradable experiencia para depurar. Estas son las instrucciones en QtCreator :

* En QtCreator, ve a Archivo->Herramientas->Opciones->Compilar&ejecutar->CMake
* Esribe la ruta de CMake. Probablemente sea /usr/bin/cmake
* Archivo->Abrir proyecto; Selecciona, tutorials/CMakeLists.txt
* Selecciona un directorio para construir, preferiblemente fuera del directorio de los tutoriales.
* Opcionalmente puedes usar -DCMAKE_BUILD_TYPE=Debug en los parámetros. Valide.
* Para ejecutar los tutoriales desde QtCreator, haz clic en Proyectos->Parámetros de ejecución->Directorio actual, y seleccione el directorio donde estan los shaders, texturas y modelos. Ejemplo para tutorial 2 : ~/opengl-tutorial/tutorial02_red_triangle/
* haz clic en el martillo de abajo. Estos tutoriales pueden ser ejecutados desde el directorio tutorials/.


## Generando en Mac

El procedimiento es muy similar a Windows (También se puede usar Makefiles pero no los vamos a explicar aquí) :

* Instale XCode desde la App Store
* [Descargue CMake](http://www.cmake.org/cmake/resources/software.html), e instale el .dmg . No necesita instalar las herramientas de linea de comando.
* [Descargue el código fuente](http://www.opengl-tutorial.org/download/) y descomprimalo, por ejemplo en ~/Projects/OpenGLTutorials/ .
* Ejecute CMake (Applications->CMake). En la primera linea, navegue hasta el directorio descomprimido. Si no esta seguro, busque el directorio que contiene el archivo CMakeLists.txt. En la segunda línea, escriba dónde se generarán todos los archivos para la compilación. Por ejemplo ~/Projects/OpenGLTutorials_bin_XCode/. Note que puede ser en cualquier parte, no necesariamente en el mismo directorio.
* Haz clic en el botón configurar. Dado que es la primera vez que configuras un proyecto, CMake te preguntará qué copilador desea usar. Escoja XCode.
* Clic en Configurar hasta que desaparezcan las lineas rojas. Clic en Generar. tu proyecto XCode ha sido creado. Ahora puedes olvidarse de CMake.
* Abre ~/Projects/OpenGLTutorials_bin_XCode/ . Verás un archivo Tutorials.xcodeproj : abrelo.
* Selecciona el tutorial que deseas ejecutar en el panel de XCode y luego usa el botón de Ejecutar para compilar y ejecutar.

![]({{site.baseurl}}/assets/images/tuto-1-window/Xcode-projectselection.png)


## Nota para Code::Blocks

Por culpa de 2 bugs (uno en C::B y otro en CMake), debes editar la linea de comando en Proyecto->Opciones de construcción->Comandos Make, así :

![]({{site.baseurl}}/assets/images/tuto-1-window/CodeBlocksFix.png)

También debes seleccionar el directorio de trabajo tu mismo : Proyecto->Propiedades -> Proyecto a construir -> tutorial N -> directorio de trabajo ( que es : src_dir/tutorial_N/ ).

#Ejecutando los tutoriales

Debes ejecutar los tutoriales directamente de los directorios, simplemente haz doble clic en el ejecutable. Si prefieres usar la linea de comandos asegurate de hacer cd al directorio correcto.

Si quieres ejecutar los tutoriales desde el IDE, no olvides leer las instrucciones de arriba para seleccionar el directorio correcto.

#Cómo seguir estos tutoriales

Cada tutorial consiste en su código y sus datos, cada uno se puede encontrar en tutorialXX/. Sinembargo, nunca debes modificar estos proyectos : solo son para referencia. Abre playground/playground.cpp, y modifica este archivo en su lugar. Torturela como te plazca. Si se pierde, simplemente copia otro tutorial dentro de playground/playground.cpp, todo deberá haber vuelto a la normalidad.

Nosotros te proveemos pedacitos de código a lo largo del tutorial. No dudes en copiar y pegarlos directamente en el playground mientras va avanzando : Experimentar es bueno ! Evita leer todo el código finalizado, no vas a aprender mucho de esta manera. Aun si solo copias y pegas los pedazos aprenderás mas y podrás solucionar problemas.

#Abriendo una ventana

Código ! Porfin !
Bueno, en realidad no. Todos los tutoriales te muestran el "nivel bajo" de hacer las cosas, de manera que puedas ver qué no es nada mágico, es parte de un largo y tedioso proceso, así que vamos a usar GLFW, una librería externa para que haz la parte aburrida por nosotros. Si realmente quisieras, podrías usar el API de Win32 en windows, el API X11 en Linux o el API Cocoa en Mac. Podría usar otras librerías como SFML, FreeGLUT, SDL, ... Ve los [vinculos de herramientas útiles aquí](http://www.opengl-tutorial.org/miscellaneous/useful-tools-links/) 

Bueno, ahora si. Listos? Primero, debemos lidiar con las dependencias : necesitamos lo básico para mostrar mensajes en consola :

``` cpp
// Incluir los cabeceros estándar
#include <stdio.h>
#include <stdlib.h>
```

Primero GLEW. Esto de hecho es un poco de mágia, pero luego lo explicamos.

``` cpp
// Incluya GLEW. Siempre incluyalo antes de gl.h y glfw.h, un poco de magia.
#include <GL/glew.h>
```

Decidimos dejar que GLFW maneje la ventana y el teclado, asi que lo incluimos :

``` cpp
// Incluir GLFW
#include <GL/glfw3.h>

```

En realidad no necesitamos esta en este momento, pero una librería para matemáticas 3D. Nos será muy util pronto. No hay magia en GLM, ustes puede escribir la suya propia si desea. Simplemente esta es útil. El "using namespace" esta allí para evitar que debamos escribir "glm::vec3", y escribamos "vec3" en su lugar.

``` cpp
// Incluir GLM
#include <glm/glm.hpp>
using namespace glm;
```

Si no puede copiar el código, todo esto está incluído en playground.cpp. 
El compilador se va a quejar por que no hay una función main(). Creamos una :

``` cpp
int main(){
```

Lo primero que haremos es inicializar GLFW :

``` cpp
// Inicializar GLFW
if( !glfwInit() )
{
    fprintf( stderr, "Error al inicializar GLFW\n" );
    return -1;
}
```

Ahora podemos crear nuestra primera ventana OpenGL !

 

``` cpp
glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Queremos OpenGL 3.3
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Para hacer feliz a MacOS ; Aunque no debería necesitarse
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //No queremos el viejo OpenGL 

//Crear una ventana y su contexto OpenGL
GLFWwindow* window; // (En el código que viene aqui, esta variable es global)
window = glfwCreateWindow( 1024, 768, "Tutorial 01", NULL, NULL);
if( window == NULL ){
    fprintf( stderr, "Falla al abrir una ventana GLFW. Si usted tiene una GPU Intel, esta no es compatible con 3.3. Intente con la versón 2.1 de los tutoriales.\n" );
    glfwTerminate();
    return -1;
}
glfwMakeContextCurrent(window); // Inicializar GLEW
glewExperimental=true; // Se necesita en el perfil de base.
if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Falló al inicializar GLEW\n");
    return -1;
}
```

Construya este y ejecutelo. Una ventana debe aparecer y se cerrará de inmediato. Debemos hacer que espere hasta que alguien oprima la tecla ESC :

``` cpp
// Capturar la tecla ESC cuando sea presionada
glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

do{
    // No vamos a pintar nada, nos vemos en el tutorial 2 !

    // Intercambiar buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

} // Revisar que la teclar ESC fue presionada y cerrar la ventana
while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
glfwWindowShouldClose(window) == 0 );
```

Y así termina el primer tutorial ! En el tutorial 2 aprenderás a dibujar un triangulo.



