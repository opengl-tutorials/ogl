---
layout: page
status: publish
published: true
title: Billboards
date: '2013-10-15 17:15:15 +0200'
date_gmt: '2013-10-15 17:15:15 +0200'
categories: []
order: 110
tags: []
language: es
---

* TOC
{:toc}

Los billboard son elementos 2D incrustados en un mundo 3D. No es un menú 2D encima de todo lo demás; no es un plano 3D alrededor del cual puedes girar; pero algo intermedio, como las barras de salud en muchos juegos.

Lo que es diferente con los billboard es que se colocan en una ubicación específica, pero su orientación se calcula automáticamente para que siempre esté frente a la cámara.

 

# Solucion #1 : El camino 2D

Esta es superfacil.

Simplemente calcule la ubicacion de un punto en la pantalla y muestre un texto 2D (consulte el Tutorial 11) en esta posición.

``` cpp
// Todo esto ya fue explicado en el Tutorial 3! No hay nada nuevo.
glm::vec4 BillboardPos_worldspace(x,y,z, 1.0f);
glm::vec4 BillboardPos_screenspace = ProjectionMatrix * ViewMatrix * BillboardPos_worldspace;
BillboardPos_screenspace /= BillboardPos_screenspace.w;

if (BillboardPos_screenspace.z < 0.0f){
    // Los objetos detras de camara no se visualizan.
}
```

Ta-dah !

En el lado positivo, este método es realmente fácil, y el billboard tendrá el mismo tamaño independientemente de su distancia a la cámara. Pero el texto 2D siempre se muestra encima de todo lo demás, y esto puede/arruinar el renderizado y se mostrará sobre otros objetos.

# Solucion #2 : El camino 3D

Este suele ser mejor y no es muy complejo.

El objetivo es mantener la malla alineada con la cámara, incluso cuando la cámara se mueve :

![]({{site.baseurl}}/assets/images/tuto-billboard/2a.gif)


Puede ver este problema como la generación de una matriz Modelo adecuada, aunque es mucho más simple que eso.

La idea es que cada esquina del billboard esté en la posición central, desplazada por los vectores hacia arriba y hacia la derecha de la cámara:

 

![]({{site.baseurl}}/assets/images/tuto-billboard/principle.png)


 

Por supuesto, solo conocemos la posición central de la cartelera en el espacio global, por lo que también necesitamos los vectores arriba / derecha de la cámara en el espacio global.

En el espacio de la cámara, el vector hacia arriba de la cámara es (0,1,0). Para obtenerlo en el espacio global, simplemente multiplique esto por la matriz que va del espacio de la camara al espacio global, que es, por supuesto, la inversa de la matriz de visualización.


Una forma más fácil de expresar lo mismo de forma matemática es:
```

CameraRight_worldspace = {ViewMatrix[0][0], ViewMatrix[1][0], ViewMatrix[2][0]}
CameraUp_worldspace = {ViewMatrix[0][1], ViewMatrix[1][1], ViewMatrix[2][1]}
```

Una vez que tenemos esto, es muy fácil calcular la posición final del vértice:

``` glsl
vec3 vertexPosition_worldspace =
    particleCenter_wordspace
    + CameraRight_worldspace * squareVertices.x * BillboardSize.x
    + CameraUp_worldspace * squareVertices.y * BillboardSize.y;
```
{: .highlightglslvs }

* ParticleCenter_worldspace es, como su nombre lo indica, la posición central de la cartelera. Se especifica con un vec3 uniforme.
* squareVertices es la malla original. squareVertices.x es -0.5 para los vértices izquierdos, que se mueven hacia la izquierda de la cámara (debido al *CameraRight_worldspace)
* BillboardSize es el tamaño, en unidades globales, del billboard, enviada como otro uniforme.

<div><span style="font-size: medium;"><span style="line-height: 24px;">And presto, here's the result. Wasn't this easy ? </span></span><span style="font-size: 16px;"> </span></div>
![]({{site.baseurl}}/assets/images/tuto-billboard/2.gif)


 

Para el registro, así es como se hacen squareVertices:

``` cpp
// The VBO containing the 4 vertices of the particles.
 static const GLfloat g_vertex_buffer_data[] = {
 -0.5f, -0.5f, 0.0f,
 0.5f, -0.5f, 0.0f,
 -0.5f, 0.5f, 0.0f,
 0.5f, 0.5f, 0.0f,
 };
```

# Solucion #3 : El Camino del 3D Ajustado

Como puede ver arriba, el tamaño del billboard cambia con respecto a la distancia de la cámara. Este es el resultado esperado en algunos casos, pero en otros, como las barras de salud, es probable que desee un tamaño fijo.

Dado que el desplazamiento entre el centro y una esquina debe fijarse en el espacio de la pantalla, eso es exactamente lo que vamos a hacer: calcular la posición del centro en el espacio de la pantalla y compensarlo.

``` cpp
vertexPosition_worldspace = particleCenter_wordspace;
// Obtener la posición del espacio de la pantalla del centro de la partícula
gl_Position = VP * vec4(vertexPosition_worldspace, 1.0f);
// Aquí tenemos que hacer la división de perspectiva nosotros mismos.
gl_Position /= gl_Position.w;
// Mueva el vértice directamente en el espacio de la pantalla. No hay necesidad de CameraUp/Right_worlspace derecho aquí.
gl_Position.xy += squareVertices.xy * vec2(0.2, 0.05);
```

Recuerde que en esta etapa de la canalización de representación, está en coordenadas normalizadas, por lo tanto, entre -1 y 1 en ambos ejes: no está en píxeles.

Si quieres un tamaño en píxeles, fácil, facil : Solo usa (ScreenSizeInPixels / BillboardSizeInPixels) en vez de BillboardSizeInScreenPercentage.

 

![]({{site.baseurl}}/assets/images/tuto-billboard/3.gif)


 

# Solucion #4 : Solo rotacion vertical

Algunos sistemas modelan árboles y lámparas lejanos como billboards. Pero realmente no quieres que tu árbol se doble: DEBE ser vertical. Por lo tanto, necesitas un sistema híbrido que rote solo alrededor de un eje.

Bueno, ¡esto se deja como ejercicio para el lector!

 

 
