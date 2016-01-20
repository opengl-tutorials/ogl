---
layout: page
status: publish
published: true
title: 'Tutorial 3 : Matrices'
date: '2011-04-09 20:59:15 +0200'
date_gmt: '2011-04-09 20:59:15 +0200'
categories: [tuto]
order: 30
tags: []
language: es
---
{:TOC}

> _Los motores no mueven la nave. La nave permanece en su lugar y el universo se mueve alrededor de ella._
> 
> Futurama

**Este es el tutorial mas importante de los tutoriales de principiante. Leelo almenos 8 veces.**

#Coordenadas homogeneas

Hasta ahora, consideramos las coordenadas 3D como triplas (x,y,z). Vamos a introducir a 'w'. Ahora tendremos vectores (x,y,z,w).

Sera mas sencillo despues, por ahora solo recuerda que:

- Si w==1 el vector es una posicion en el espacio.
- Si w==0 el vector e suna direccion.

(Recuerdelo para siempre)

Que diferencia hace? Bueno, para una rotacion no hace la diferencia. Cuando usted rota un punto o una direccion, obtiene el mismo resultado. Sinembargo para una traslacion (mover un punto en una direccion), las cosas son diferentes. Que podria significar "traslacion de una direccion"? Nada.

Las coordenadas homogeneas usan una unica formula matematica para lidiar con estos dos casos cases.

# Transformacion de matrices


## Introduction a las matrices

En terminos simples, una matriz es un arreglo de numeros con un numero predefinido de filas y columnas. Por ejemplo, una matrix de 2x3 se ve asi

![]({{site.baseurl}}/assets/images/tuto-3-matrix/2X3.png)

En computacion grafica se usan matrices de 4x4. Estas mastrices nos permitiran transformar nuestros vertices (x,y,z,w). 

Esto se hace multiplicando el vertice con la matriz :

**Matrix x Vertex (in this order !!) = TransformedVertex**

![]({{site.baseurl}}/assets/images/tuto-3-matrix/MatrixXVect.gif)

No es tan terrible como se ve. Pon tu dedo izquierdo sobre la a y tu dedo derecho sobre la x. Esto es ax_. Mueve tu dedo izquierdo al siguiente numero (b), y tu dedo derecho a (y). ahora tienes _by_. Una vez mas, _cz_. Una vez mas : _dw_. ax + by + cz + dw. Tienes tu nueva x ! haz lo mismo para cada lina y obtendras tu vector (x,y,z,w).

Esto es aburrido de calcular, y lo haremos frecuentemente, asi que mejor digamosle al computador que lo haga en nuestro lugar.

**En C++, con GLM:**
{% highlight cpp linenos %}
glm::mat4 myMatrix;
glm::vec4 myVector;
// Llene  myMatrix y myVector de alguna forma
glm::vec4 transformedVector = myMatrix * myVector; // En este orden, es importante.
{% endhighlight %}

**En GLSL :**
{% highlight glsl linenos %}
mat4 myMatrix;
vec4 myVector;
// Llene  myMatrix y myVector de alguna forma
vec4 transformedVector = myMatrix * myVector; // Si basicamente es lo mismo que GLM
{% endhighlight %}

( Ya copiaste y pegaste el codigo? intentalo )

##Matrices de translacion\

Estas son las matrices mas faciles de entender. Una matriz de translacion se ve asi :

![]({{site.baseurl}}/assets/images/tuto-3-matrix/translationMatrix.png)

Donde X,Y,Z son los valores de tu posicion.

Asi que si queremos transladar el vector (10,10,10,1) 10 unidades en la direccion X, obtendremos :

![]({{site.baseurl}}/assets/images/tuto-3-matrix/translationExamplePosition1.png)

(Intentalo! Inteeeeentalo)

... obtendremos un vector homogeneo (20,10,10,1) ! Recuerda el 1 significa que es una posicion no una direccion. La transformacion no ha cambiado eso, lo cual es bueno.

Ahora veremos lo que le pasa a un vector direccion en direccion -z : (0,0,-1,0)

![]({{site.baseurl}}/assets/images/tuto-3-matrix/translationExampleDirection1.png)

... es decir nuestra direccion original (0,0,-1,0), lo cual es genial por que como te dije antes, mover una direccion no tiene sentido.

Como se traduce esto a codigo?


**En C++, con GLM:**
{% highlight cpp linenos %}
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>
 
glm::mat4 myMatrix = glm::translate(10.0f, 0.0f, 0.0f);
glm::vec4 myVector(10.0f, 10.0f, 10.0f, 0.0f);
glm::vec4 transformedVector = myMatrix * myVector; // guess the result
{% endhighlight%}

**En GLSL :**
{% highlight glsl linenos %}
vec4 transformedVector = myMatrix * myVector;
{% endhighlight%}

De hecho casi nunca se hace esto en GLSL. La mayoría de las veces se usa glm::translate() en C++ para calcular la matriz, enviarla a GLSL y solo hacer la multiplicación.

## La matriz identidad

Esta es especial. No hace nada. Pero la menciono por que es importante sabe que al multiplicar A por 1.0 te da 1.

![]({{site.baseurl}}/assets/images/tuto-3-matrix/identityExample.png)

**En C++ :**
{% highlight cpp linenos %}
glm::mat4 myIdentityMatrix = glm::mat4(1.0f);
{% endhighlight%}

## Escalando matrices

Escalar es muy facil tambien :

![]({{site.baseurl}}/assets/images/tuto-3-matrix/scalingMatrix.png)

Asi que si quieres escalar un vector (posición o dirección, no importa) por 2.0 en todas las direcciones :

![]({{site.baseurl}}/assets/images/tuto-3-matrix/scalingExample.png)

Y la w no cambia. Te preguntaras cual es el significado de "escalar una dirección"? Pues, con frecuencia no significa mucho, pero aveces resulta útil.

(Nota que la matriz identidad es solo un caso especial de escalamiento de matrices con (X,Y,Z) = (1,1,1). También es un caso especial, la translación con una matriz (X,Y,Z)=(0,0,0) )

**En C++ :**
{% highlight cpp linenos %}
// Use #include <glm/gtc/matrix_transform.hpp> and #include <glm/gtx/transform.hpp>
glm::mat4 myScalingMatrix = glm::scale(2.0f, 2.0f ,2.0f);
{% endhighlight%}

## Rotación de matrices

Estas son un poco mas complicadas. Omitiré detalles por simplicidad. Para mas información mira [Matrices and Quaternions FAQ](http://www.cs.princeton.edu/~gewang/projects/darth/stuff/quat_faq.html) (recurso popular en varios idiomas). Y puedes mirar también los [Rotations tutorials]({{site.baseurl }}{{intermediate-tutorials/tutorial-17-quaternions}}) 

**En C++ :**
{% highlight cpp linenos %}
// Use #include <glm/gtc/matrix_transform.hpp> and #include <glm/gtx/transform.hpp>
glm::vec3 myRotationAxis( ??, ??, ??);
glm::rotate( angle_in_degrees, myRotationAxis );
{% endhighlight %}

## Acumulando transformaciones

Ya sabemos rotar , transladar y escalar nuestros vectores. Seria genial combinar todas estas transformaciones. Esto se hace multiplicando las matrices, por ejemplo :

{% highlight cpp linenos %}
TransformedVector = TranslationMatrix * RotationMatrix * ScaleMatrix * OriginalVector;
{% endhighlight %}


**!!! ATENCIÓN !!!** Estas lineas primero hacen el ESCALAMIENTO, luego la ROTACIÓN y luego la TRANSLACIÓN. Asi es como funciona la multiplicación.

Escribir las operaciones en otro orden no produce el mismo resultado. Intentalo tu mismo :

- Da un paso adelante (cuidado con tu computador) y voltea a la derecha.

- Voltea a la derecha y da un paso al frente.

De hecho, el orden de arriba es el que usualmente necesitaras para personajes de un juego y otros items : Escala primero si es necesario, luego escoge una direccion y luego transladalo. Eliminemos rotación por simplicidad. Por ejemplo, dado un modelo de un barco  :

* La forma incorrect :
	- Transladar el barco en (10,0,0). Su centro esta ahora a 10 unidades del origen.
	- Escalar el barco por 2\. Cada coordenada es multiplicada por 2 _con relación al origen_, que ya esta lejos de aqui.. Asi que vas a terminar con un barco grande pero centrado en 2*10 = 20. Y no quieres eso.

* La forma correcta :
	- Escalar tu barco por 2\. Tienes un gran barco centrado en el origen.
	- Transladas tu barco. Tendra el tamaño y la posición adecuada.

La multiplicación matriz-matriz es muy similar a la multiplicación matriz-vector, asiq ue vamos a saltarnos esa parte y si tienes dudas consulta las preguntas frecuentes de Matrices y cuaterniones. Por ahora le diremos al computador que lo haga por nosotros :

**En C++, con GLM :**
{% highlight cpp linenos %}
glm::mat4 myModelMatrix = myTranslationMatrix * myRotationMatrix * myScaleMatrix;
glm::vec4 myTransformedVector = myModelMatrix * myOriginalVector;
{% endhighlight%}
**En GLSL :**
{% highlight glsl linenos %}
mat4 transform = mat2 * mat1;
vec4 out_vec = transform * in_vec;
{% endhighlight%}

# Matrices modelo, vista y proyección

_Para el resto del tutorial, vamos a suponer que todos conocen el famosisimo mono de Blender : El mono Suzanne._

Las matrices modelo, vista y proyección, son muy utiles para hacer las transformaciones limpiamente. Pueda que nunca uses esto (ya lo hicimos en los tutoriales 1 y 2). Pero deberías. Es como todos lo hacen, por que es la forma más fácil.

## La matriz modelo 

Este modelo, como nuestro triangulo querido, esta definido por un set de vertices. Las coordenadas (x,y,z) de estos vertices, son definidas relativamente a un centro : un lugar llamado (0,0,0), es el centro del objeto.

![]({{site.baseurl}}/assets/images/tuto-3-matrix/model.png)

Queremos poder mover este objeto, por ejemplo controlandolo con el teclado o el mouse. Ya sabes hacerlo, es facil : `translacion*rotacion*escala` y listo. Aplicas esta matriz a todos tus vertices en cada cuadro (en GLSL, no en C++!) y todo se mueve. Algo que no se mueve esta en el _centro del mundo_.

![]({{site.baseurl}}/assets/images/tuto-3-matrix/world.png)

Al hacer esto tus vertices estan en el _espacio de mundo_. Este es el significado de la flecha negra de la imagen abajo : _Fuimos del espacio del model (todos los vertices estan definidos con respecto centro del modelo) al espacio del mundo (all vertices defined relatively to the center of the world)._

![]({{site.baseurl}}/assets/images/tuto-3-matrix/model_to_world.png)

We can sum this up with the following diagram :

![]({{site.baseurl}}/assets/images/tuto-3-matrix/M.png)

## The View matrix

Let's quote Futurama again :

> _The engines don't move the ship at all. The ship stays where it is and the engines move the universe around it._

![]({{site.baseurl}}/assets/images/tuto-3-matrix/camera.png)

When you think about it, the same applies to cameras. It you want to view a moutain from another angle, you can either move the camera... or move the mountain. While not practical in real life, this is really simple and handy in Computer Graphics.

So initially your camera is at the origin of the World Space. In order to move the world, you simply introduce another matrix. Let's say you want to move your camera of 3 units to the right (+X). This is equivalent to moving your whole world (meshes included) 3 units to the LEFT ! (-X). While you brain melts, let's do it :

Again, the image below illustrates this : _We went from World Space (all vertices defined relatively to the center of the world, as we made so in the previous section) to Camera Space (all vertices defined relatively to the camera)._

![]({{site.baseurl}}/assets/images/tuto-3-matrix/model_to_world_to_camera.png)

Before you head explodes from this, enjoy GLM's great glm::lookAt function:

{% highlight cpp linenos %}
glm::mat4 CameraMatrix = glm::lookAt(
    cameraPosition, // the position of your camera, in world space
    cameraTarget,   // where you want to look at, in world space
    upVector        // probably glm::vec3(0,1,0), but (0,-1,0) would make you looking upside-down, which can be great too
);
{% endhighlight %}

Here's the compulsory diagram :

![]({{site.baseurl}}/assets/images/tuto-3-matrix/MV.png)

This is not over yet, though.

## The Projection matrix

We're now in Camera Space. This means that after all theses transformations, a vertex that happens to have x==0 and y==0 should be rendered at the center of the screen. But we can't use only the x and y coordinates to determine where an object should be put on the screen : its distance to the camera (z) counts, too ! For two vertices with similar x and y coordinates, the vertex with the biggest z coordinate will be more on the center of the screen than the other.

This is called a perspective projection :

![]({{site.baseurl}}/assets/images/tuto-3-matrix/model_to_world_to_camera_to_homogeneous.png)

And luckily for us, a 4x4 matrix can represent this projection[^projection] :

{% highlight cpp linenos %}
// Generates a really hard-to-read matrix, but a normal, standard 4x4 matrix nonetheless
glm::mat4 projectionMatrix = glm::perspective(
    FoV,         // The horizontal Field of View, in degrees : the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
    4.0f / 3.0f, // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
    0.1f,        // Near clipping plane. Keep as big as possible, or you'll get precision issues.
    100.0f       // Far clipping plane. Keep as little as possible.
);
{% endhighlight %}

One last time :

_We went from Camera Space (all vertices defined relatively to the camera) to Homogeneous Space (all vertices defined in a small cube. Everything inside the cube is onscreen)._

And the final diagram :

![]({{site.baseurl}}/assets/images/tuto-3-matrix/MVP.png)

Here's another diagram so that you understand better what happens with this Projection stuff. Before projection, we've got our blue objects, in Camera Space, and the red shape represents the frustum of the camera : the part of the scene that the camera is actually able to see.

![]({{site.baseurl}}/assets/images/tuto-3-matrix/nondeforme.png)

Multiplying everything by the Projection Matrix has the following effect :

![]({{site.baseurl}}/assets/images/tuto-3-matrix/homogeneous.png)

In this image, the frustum is now a perfect cube (between -1 and 1 on all axes, it's a little bit hard to see it), and all blue objects have been deformed in the same way. Thus, the objects that are near the camera ( = near the face of the cube that we can't see) are big, the others are smaller. Seems like real life !

Let's see what it looks like from the "behind" the frustum :

![]({{site.baseurl}}/assets/images/tuto-3-matrix/projected1.png)

Here you get your image ! It's just a little bit too square, so another mathematical transformation is applied (this one is automatic, you don't have to do it yourself in the shader) to fit this to the actual window size :

![]({{site.baseurl}}/assets/images/tuto-3-matrix/final1.png)

And this is the image that is actually rendered !

## Cumulating transformations : the ModelViewProjection matrix

... Just a standard matrix multiplication as you already love them !

{% highlight cpp linenos %}
// C++ : compute the matrix
glm::mat4 MVPmatrix = projection * view * model; // Remember : inverted !
{% endhighlight %}

{% highlight glsl linenos cssclass=highlightglslfs %}
// GLSL : apply it
transformed_vertex = MVP * in_vertex;
{% endhighlight %}


# Putting it all together

*  First step : generating our MVP matrix. This must be done for each model you render.
*  Second step : give it to GLSL
* Third step : use it in GLSL to transform our vertices
* Done ! Here is the same triangle as in tutorial 2, still at the origin (0,0,0), but viewed in perspective from point (4,3,3), heads up (0,1,0), with a 45° field of view.

![]({{site.baseurl}}/assets/images/tuto-3-matrix/perspective_red_triangle.png)

In tutorial 6 you'll learn how to modify these values dynamically using the keyboard and the mouse to create a game-like camera, but first, we'll learn how to give our 3D models some colour (tutorial 4) and textures (tutorial 5).

# Exercises

*   Try changing the glm::perspective
*   Instead of using a perspective projection, use an orthographic projection (glm::ortho)
*   Modify ModelMatrix to translate, rotate, then scale the triangle
*   Do the same thing, but in different orders. What do you notice ? What is the "best" order that you would want to use for a character ?

_Addendum_


[^projection]: [...]luckily for us, a 4x4 matrix can represent this projection : Actually, this is not correct. A perspective transformation is not affine, and as such, can't be represented entirely by a matrix. After beeing multiplied by the ProjectionMatrix, homogeneous coordinates are divided by their own W component. This W component happens to be -Z (because the projection matrix has been crafted this way). This way, points that are far away from the origin are divided by a big Z; their X and Y coordinates become smaller; points become more close to each other, objects seem smaller; and this is what gives the perspective. This transformation is done in hardware, and is not visible in the shader.