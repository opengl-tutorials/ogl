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

Podemos verlo todo en el siguiente diagrama :

![]({{site.baseurl}}/assets/images/tuto-3-matrix/M.png)

## La matriz vista

Vamos a citar a "Futurama" otra vez:

> _El motor no mueve la nave. La nave se queda donde esta y los motores mueven el universo a su alrededor._

![]({{site.baseurl}}/assets/images/tuto-3-matrix/camera.png)

Cuando lo piensas, esto se aplica a las camaras. Si quieres ver una montaña desde otro angulo, puedes mover la camara... o mover la montaña. No es práctico en la vida real, es solo que asi es mas facil en computación gráfica.

Inicialmente, la camara esta en el origen del espacio mundo. Para mover el mundo, simplemente se introduce otra matriz. Digamos que quieres mover tu camara 3 unidades a la derecha (+X). Esto es equivalente a mover todo el mundo (y lo que contenga) 3 unidades a la izquierda !. Mientras tu cerebro se derrite, vamos a hacerlo :

Una vez mas, la imagen abajo ilustra esto : _Fuimos del espacio mundo (todos los vertices estan definidos relativamente al centro del mundo) al espacio camara (todos los vertices se definen relativamente a la camara)._

![]({{site.baseurl}}/assets/images/tuto-3-matrix/model_to_world_to_camera.png)

Antes que tu cabeza explote con todo esto, disfruta la gran función de GLM : glm::lookAt :

{% highlight cpp linenos %}
glm::mat4 CameraMatrix = glm::lookAt(
    cameraPosition, // La posición de tu camara en el espaio mundo
    cameraTarget,   // Hacia donde quieres mirar, en el espacio mundo
    upVector        // Probablemente glm::vec3(0,1,0), porque (0,-1,0) te haría mirar cabeza abajo, aunque puede ser divertido.
);
{% endhighlight %}

Aquí esta el diagrama obligatorio :

![]({{site.baseurl}}/assets/images/tuto-3-matrix/MV.png)

Pero aun no hemos acabado.

## La matriz proyección

Ahora estamos en el espacio camara. Esto significa que despues de todas las transformaciones, un vertice que tenga coordenadas x==0 y y==0 debe pintarse en el centro de la pantalla. Pero no solo usamos las coordenadas x y y para determinar la posicion de un objeto en la pantalla : su distancia a la camara (z) también cuenta ! Para dos vertices con las mismas coordenadas x y y, el vertice con mayor (z) estará mas en el centro de la pantalla que el otro.

Esto es lo que se llama una perspectiva de proyección :

![]({{site.baseurl}}/assets/images/tuto-3-matrix/model_to_world_to_camera_to_homogeneous.png)

Y por suerte para nosotros, una matriz 4x4 puede representar esta proyección [^projection] :

{% highlight cpp linenos %}
// Genera una matriz dificil de leer pero almenos es 4x4
glm::mat4 projectionMatrix = glm::perspective(
    FoV,         // El campo de visión horizontal, en grados : la cantidad de "zoom". Piensa en el lente de la camara. Usualmente esta entre 90° (extra ancho) y 30° (zoom aumentado)
    4.0f / 3.0f, // Proporción. Depende del tamaño de tu ventana 4/3 == 800/600 == 1280/960, Parece familiar?
    0.1f,        // Plano de corte cercano. Tan grande como sea posible o tendrás problemas de precisión.
    100.0f       // Plano de corte lejano. Tan pequeño como se pueda.
);
{% endhighlight %}

Una ultima vez :


_Fuimos del espacio de la camara (todos los vertices definidos relativamente a la camara) al espacio homogeneo (todos los vertices definidos en un pequeño cubo. Todo aquello que esta dentro del cubo esta dentro de la pantalla)._

Y el diagrama final :

![]({{site.baseurl}}/assets/images/tuto-3-matrix/MVP.png)

Aquí hay otro diagrama para que entiendas mejor lo que pasa con todo esto de la proyección. Antes de la proyección, tenemos nuestros objetos azules, en el espacio de la camara, y la forma roja representa la pirmide de la camara : la parte de la escena que la camara ve en efecto. 

![]({{site.baseurl}}/assets/images/tuto-3-matrix/nondeforme.png)

Multiplicar todo por la matriz de proyección tiene el siguiente efecto :

![]({{site.baseurl}}/assets/images/tuto-3-matrix/homogeneous.png)

En esta imagen el cono es ahora un cubo perfecto (entre -1 y 1 en todos los ejes, es un poco dificil de entender), y todos los objetos azules ahora parecen deformados de algun modo. Los objetos cercanos a la camara (cerca de la cara del cubo de -1 a 1) son mas grandes, los otros son mas pequeños. Tal como en la vida real.

Veamos ahora como se ve por "detras" de la piramide :

![]({{site.baseurl}}/assets/images/tuto-3-matrix/projected1.png)

He aquí tu imagen ! Es un poco cuadrada, así que otra transformación matemática es aplicada (es automatica, no tienes que hacerla en el shader) para quedar del tamaño de la pantalla correctamente.

![]({{site.baseurl}}/assets/images/tuto-3-matrix/final1.png)

Y esta imagen de hecho es el render !

## Acumulando transformaciones : La matriz ModeloVistaProyección

... Solo una multiplicación estándar, así como te gustan !

{% highlight cpp linenos %}
// C++ : calcular la matriz
glm::mat4 MVPmatrix = projection * view * model; // Recurda : invertida !
{% endhighlight %}

{% highlight glsl linenos cssclass=highlightglslfs %}
// GLSL : aplicala
transformed_vertex = MVP * in_vertex;
{% endhighlight %}


# Uniendo todo

*  Primer paso : generar la matriz MVP. Esto se hace para cada modelo que se renderice.
*  Segundo paso : entregarle todo a GLSL.
*  Tercer paso : usar GLSL para transformar nuestros vertices.
*  Listo ! He aquí el mismo triangulo del tutorial 2, aún en el origen (0,0,0), pero visto desde la perspectiva del punto (4,3,3), cabeza arriba (0,1,0), con un campo de visión de 45°.

![]({{site.baseurl}}/assets/images/tuto-3-matrix/perspective_red_triangle.png)


En el tutorial 6 aprenderás a modificar estos valores de forma dinámica usando el teclado y el mouse para crear una camara como de los juegos. Pero primero, vamos a aprender a darle un colo a nuestros modelos 3D (tutorial 4) y usar texturas (tutorial 5).

# Ejercicios

*   Intenta cambiar la glm::perspective.
*   En  lugar de usar una perspectiva de proyección, usa una proyección ortográfica (glm::ortho).
*   Modifica la matriz de modelo para transladar, rotar y luego escalar el triangulo.
*   Haz lo mismo en diferentes ordenes. Qué notas? cual es el "mejor" orden que se debe usar para un personaje?

_Addendum_


[^proyección]: [...]por suerte para nosotros, una matriz 4x4 puede representar esta proyección : De hecho esto no es correcto. Una transformación de perspectiva no es una transformación afín, y como tal, no puede ser representada en su totalidad por una matriz. Luego de ser multiplicadas por una matriz de proyección, las coordenadas homogeneas deben ser divididas por su propio componente w. Esta componente W suele se -Z. De esta forma, los puntos que estan lejos del origen se dividen por una gran Z; sus componentes X y Y se vuelven mas pequeñas y los puntos se acercan entre ellos, los objetos se vuelven mas pequeños y eso es lo que produce la perspectiva. Esta transformación se hace en hardware y no se nota en el shader.