---
layout: page
status: publish
published: true
title: 'Tutorial 9 : Indexado VBO'
date: '2011-05-12 19:21:49 +0200'
date_gmt: '2011-05-12 19:21:49 +0200'
categories: [tuto]
order: 10
tags: []
language: es
---

* TOC
{:toc}

# El principío del indexado

Hasta ahora, al construir un VBO, siempre duplicamos nuestros vértices cada vez que dos triángulos compartían un borde.

En este tutorial, presentamos la indexación, que permite reutilizar el mismo vértice una y otra vez. Esto se hace con un * index buffer *.

![]({{site.baseurl}}/assets/images/tuto-9-vbo-indexing/indexing1.png)


El índice del búfer contiene números enteros, tres para cada triángulo en la malla, que hacen referencia a los diversos * búferes de atributos * (posición, color, coordenadas UV, otras coordenadas UV, normal, ...). Es un poco como en el formato de archivo OBJ, con una gran diferencia: solo hay UN búfer de índice. Esto significa que para que un vértice se comparta entre dos triángulos, todos los atributos deben ser iguales.

# Compartido vs separado

Tomemos el ejemplo de las normales. En esta figura, el artista que creó estos dos triángulos probablemente quería que representaran una superficie lisa. Así podemos mezclar las normales de los dos triángulos en un solo vértice normal. Para fines de visualización, agregué una línea roja que representa el aspecto de la superficie lisa.

![]({{site.baseurl}}/assets/images/tuto-9-vbo-indexing/goodsmooth.png)


En esta segunda figura, sin embargo, el artista quería visiblemente una "costura", un borde áspero. Pero si fusionamos las normales, esto significa que el sombreador se interpolará suavemente como de costumbre y creará un aspecto suave como antes:

![]({{site.baseurl}}/assets/images/tuto-9-vbo-indexing/badmooth.png)


Entonces, en este caso, en realidad es mejor tener dos normales diferentes, una para cada vértice. La única forma de hacer esto en OpenGL es duplicar todo el vértice, con todo su conjunto de atributos.

![]({{site.baseurl}}/assets/images/tuto-9-vbo-indexing/spiky.png)


# VBO indexado en OpenGL

Usar indexación es muy simple. Primero, debe crear un búfer adicional, que debe completar con los índices correctos. El código es el mismo que antes, pero ahora es un ELEMENT_ARRAY_BUFFER, no un ARRAY_BUFFER.

``` cpp
std::vector<unsigned int> indices;

// llenar los "índices" según sea necesario

// Generar un buffer para los índices.
 GLuint elementbuffer;
 glGenBuffers(1, &elementbuffer);
 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
 glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
```

y para dibujar la malla, simplemente reemplace glDrawArrays por esto:

``` cpp
// Indice del buffer
 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

 // Dibujar los triangulos !
 glDrawElements(
     GL_TRIANGLES,      // modo
     indices.size(),    // conteo
     GL_UNSIGNED_INT,   // tipo
     (void*)0           // offset de elementos arreglo del buffer
 );
```

(nota rápida: es mejor usar "unsigned short" que "unsigned int", porque requiere menos memoria, lo que también lo hace más rápido)

# Llenar el búfer de índices

Ahora tenemos un problema. Como dije antes, OpenGL solo puede usar un búfer de índices, mientras que OBJ (y algunos otros formatos 3D populares como Collada) usan un búfer de índices * por atributo *. Lo que significa que de alguna manera tenemos que convertir de N buffers de índice a 1 buffer de índice.

El algoritmo para hacer esto es el siguiente:
```

Por cada vértice de entrada
    Tratar de buscar un similar ( = el mismo por todos los atributos ) vértice entre todos aquellos que ya sacamos
    Si encuentra :
        Un vértice similar ya está en el VBO, ¡úsalo ese!
    Si no lo encuentra :
        No se encontró un vértice similar, agréguelo a la VBO
```

El código real de C ++ se puede encontrar en common/vboindexer.cpp. Está muy comentado, por lo que si comprende el algoritmo anterior, debería estar bien.

El criterio de similitud es que la posición de los vértices, los rayos UV y las normales deben ser ** iguales. Tendras que adaptar esto si deseas agregar más atributos.

La búsqueda de un vértice similar se realiza con una simple búsqueda lineal para simplificar. Un std::map sería más apropiado para un uso real.

# Extra : el contador de FPS

No está directamente relacionado con la indexación, pero es un buen momento para echar un vistazo [el contador de FPS](http://www.opengl-tutorial.org/miscellaneous/an-fps-counter/) porque eventualmente podemos ver la mejora de la velocidad de indexación. Otras herramientas de rendimiento están disponibles en [Tools - Debuggers](http://www.opengl-tutorial.org/miscellaneous/useful-tools-links/#header-4).