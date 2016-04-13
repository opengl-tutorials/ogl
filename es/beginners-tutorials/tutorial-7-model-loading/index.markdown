---
layout: page
status: publish
published: true
title: 'Tutorial 7 : Cargando un modelo'
date: '2011-05-08 17:48:12 +0200'
date_gmt: '2011-05-08 17:48:12 +0200'
categories: [tuto]
order: 70
tags: []
language: es
---

Hasta ahora, hemos escrito directamente nuestro cubo en el código fuente. Y podemos estar de acuerdo en que ésta es una forma muy engorrosa y poco práctica de hacerlo.

En este tutorial, aprenderemos como cargar mallas 3D desde archivo. Lo haremos de la misma manera en que lo hicimos para las texturas: escribiremos una pequeña y muy limitada función para cargar las mallas y luego le daremos un vistazo a las librerías que pueden hacer esto mucho mejor que nosotros.

Para mantener este tutorial lo más simple que sea posible, usaremos el formato OBJ, que resulta ser bastante simple y común. Y una vez más, para mantener las cosas simples, sólo trataremos con archivos OBJ con una coordenada UV y una normal por vértice (Y no necesitamos preocuparnos por lo que es una normal justo ahora).

# Cargando el OBJ

Nuestra función, ubicada en common/objloader.cpp y declarada en common/objloader.hpp tendrá la siguiente declaración:
 :

``` cpp
bool loadOBJ(
    const char * path,
    std::vector < glm::vec3 > & out_vertices,
    std::vector < glm::vec2 > & out_uvs,
    std::vector < glm::vec3 > & out_normals
)
```

Queremos que loadObj lea el archivo en "path", escriba la información en out_vertices/out_uvs/out_normals, y devuelva falso si algo sale mal. std::vector es la manera que tiene C++ para declarar un arreglo de tipo glm::vec3 cuyo tamaño puede ser modificado a voluntad: No tiene nada que ver con un vector en el sentido matemático. Es sólo un arreglo, de verdad. Finalmente, el símbolo & significa que la función será capaz de modificar los std::vectors.

## Archivo OBJ de ejemplo

Un archivo OBJ se ve más o menos así :
```

# Blender3D v249 OBJ File: untitled.blend
# www.blender3d.org
mtllib cube.mtl
v 1.000000 -1.000000 -1.000000
v 1.000000 -1.000000 1.000000
v -1.000000 -1.000000 1.000000
v -1.000000 -1.000000 -1.000000
v 1.000000 1.000000 -1.000000
v 0.999999 1.000000 1.000001
v -1.000000 1.000000 1.000000
v -1.000000 1.000000 -1.000000
vt 0.748573 0.750412
vt 0.749279 0.501284
vt 0.999110 0.501077
vt 0.999455 0.750380
vt 0.250471 0.500702
vt 0.249682 0.749677
vt 0.001085 0.750380
vt 0.001517 0.499994
vt 0.499422 0.500239
vt 0.500149 0.750166
vt 0.748355 0.998230
vt 0.500193 0.998728
vt 0.498993 0.250415
vt 0.748953 0.250920
vn 0.000000 0.000000 -1.000000
vn -1.000000 -0.000000 -0.000000
vn -0.000000 -0.000000 1.000000
vn -0.000001 0.000000 1.000000
vn 1.000000 -0.000000 0.000000
vn 1.000000 0.000000 0.000001
vn 0.000000 1.000000 -0.000000
vn -0.000000 -1.000000 0.000000
usemtl Material_ray.png
s off
f 5/1/1 1/2/1 4/3/1
f 5/1/1 4/3/1 8/4/1
f 3/5/2 7/6/2 8/7/2
f 3/5/2 8/7/2 4/8/2
f 2/9/3 6/10/3 3/5/3
f 6/10/4 7/6/4 3/5/4
f 1/2/5 5/1/5 2/9/5
f 5/1/6 6/10/6 2/9/6
f 5/1/7 8/11/7 6/10/7
f 8/11/7 7/12/7 6/10/7
f 1/2/8 2/9/8 3/13/8
f 1/2/8 3/13/8 4/14/8
```

Entonces:

* `#` señala la ubicación de un comentario, así como lo hacen los // en C++
* usemtl y mtllib describen la apariencia del modelo. No lo usaremos en este tutorial.
* v es un vértice
* vt es la coordenada de textura de un vértice
* vn es la normal de un vértice
* f es una cara

v, vt y vn son simples de entender. f es algo más complicado. Así, para f 8/11/7 7/12/7 6/10/7 :

* 8/11/7 describe el primer vértice del triángulo
* 7/12/7 describe el segundo vértice del triángulo 
* 6/10/7 describe el tercer vértice del  triángulo (duh)
* Para el primer vértice, el 8 indica qué vértice utilizar. Así que en este caso, -1.000000 1.000000 -1.000000 (los índices comienzan con 1, y no con 0 como en C++)
* 11 dice que coordenada de textura utilizar. En este caso, 0.748355 0.998230
* 7 dice que normal utilizar. En este caso, 0.000000 1.000000 -0.000000

Estos números son llamados índices. Esto es útil dado que si varios vértices comparten la misma posición, sólo tiene que escribir una vez un "v" en el archivo y usarlo varias veces, ahorrando espacio en memoria.

La mala noticia es que no es posible decirle a OpenGL que use un índice para la posición, otro para la tectura y otro para la normal. Así que para este tutorial hice una malla estándar, sin indexación y más adelante me ocupo del indexamiento en el Tutorial 9, que explica cómo esquivar esto.
## Crear un archivo OBJ en Blender

Dado que nuestra pequeña función de carga es bastante limitada, tenemos que ser extremadamente cuidadosos para activar las opciones adecuadas cuando exportemos el archivo. Así es como debería verse en Blender:

![]({{site.baseurl}}/assets/images/tuto-7-model-loading/Blender.png)


## Leyendo el archivo

Bien, ahora vamos al código en cuestión. Necesitamos algunas variables temporales en las que almacenaremos los contenidos del .obj :

``` cpp
std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
std::vector< glm::vec3 > temp_vertices;
std::vector< glm::vec2 > temp_uvs;
std::vector< glm::vec3 > temp_normals;
```

Desde el Tutorial 5 : Un cubo con texturas, sabemos como abrir un archivo :

``` cpp
FILE * file = fopen(path, "r");
if( file == NULL ){
    printf("Impossible to open the file !\n");
    return false;
}
```

Leamos este archivo hasta el final:

``` cpp
while( 1 ){

    char lineHeader[128];
    // Lee la primera palabra de la línea
    int res = fscanf(file, "%s", lineHeader);
    if (res == EOF)
        break; // EOF = End Of File, es decir, el final del archivo. Se finaliza el ciclo.

    // else : analizar el lineHeader
```

(Es importante notar que asumimos que la primera palabra de la línea no tendrá más de 128 caracteres, lo cual es un supuesto algo ridículo. Pero para una función de carga de juguete como la nuestra, está bien.)

Tratemos los vértices primero :

``` cpp
if ( strcmp( lineHeader, "v" ) == 0 ){
    glm::vec3 vertex;
    fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
    temp_vertices.push_back(vertex);
```

i.e : Si la primera palabra de la línea es "v", entonces el resto tiene que tener 3 flotantes, así que creamos un glm::vec3 a partir de estos y lo añadimos al vector.

``` cpp
}else if ( strcmp( lineHeader, "vt" ) == 0 ){
    glm::vec2 uv;
    fscanf(file, "%f %f\n", &uv.x, &uv.y );
    temp_uvs.push_back(uv);
```

i.e si no es "v" sino "vt", entonces el resto tiene que tener dos flotantes, así que creamos un glm::vec2 y lo añadimos al vector.

lo mismo para las normales :

``` cpp
}else if ( strcmp( lineHeader, "vn" ) == 0 ){
    glm::vec3 normal;
    fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
    temp_normals.push_back(normal);
```

Y ahora la "f", lo cual es más difícil :

``` cpp
}else if ( strcmp( lineHeader, "f" ) == 0 ){
    std::string vertex1, vertex2, vertex3;
    unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
    int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
    if (matches != 9){
        printf("File can't be read by our simple parser : ( Try exporting with other options\n");
        return false;
    }
    vertexIndices.push_back(vertexIndex[0]);
    vertexIndices.push_back(vertexIndex[1]);
    vertexIndices.push_back(vertexIndex[2]);
    uvIndices    .push_back(uvIndex[0]);
    uvIndices    .push_back(uvIndex[1]);
    uvIndices    .push_back(uvIndex[2]);
    normalIndices.push_back(normalIndex[0]);
    normalIndices.push_back(normalIndex[1]);
    normalIndices.push_back(normalIndex[2]);
```

Este código es bastante similar al anterior, excepto que hay más información para leer.

## Procesando la información

Lo que hicimos fue, simplemente, cambiar la forma general de la información. Teníamos un string y ahora tenemos un conjunto de std::vectors. No obstante, esto no es suficiente, y tenemos que organizarla de tal manera que a OpenGl le guste. Es decir, removeremos los índices y tendremos objetos glm::vec3 simplemente. Esta operación es lo que se denomina "indexar".

Vamos a través de cada vértice ( cada v/vt/vn ) de cada triángulo ( cada línea marcada con una "f" ) :

``` cpp
    // Para cada vértice de cada triángulo
    for( unsigned int i=0; i<vertexIndices.size(); i++ ){

```

El índice a la posición del vértice es vertexIndices[i] :

``` cpp
unsigned int vertexIndex = vertexIndices[i];
```

así que la posición es temp_vertices[ vertexIndex-1 ] (aquí tenemos que poner el -1 porque en C++ el indexamiento comienza en 0 y para los OBJ comienza en 1, como lo mencioné anteriormente) :

``` cpp
glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
```

Y con esto tenemos la posición de nuestro nuevo vértice

``` cpp
out_vertices.push_back(vertex);
```

Aplicamos lo mismo para las coordenadas UV y las normales y hemos finalizado!

# Usando la información cargada

Una vez tenemos esto, casi nada cambia. En lugar de declarar nuestro usual static const GLfloat g_vertex_buffer_data[] = {...}, declararemos en su lugar un std::vector vértices (y lo mismo haremos para las coordenadas UV y las normales). Llamamos a la función loadOBJ con los parámetros necesarios :

``` cpp
// Read our .obj file
std::vector< glm::vec3 > vértices;
std::vector< glm::vec2 > uvs;
std::vector< glm::vec3 > normals; // No las usaremos por ahora
bool res = loadOBJ("cube.obj", vértices, uvs, normals);
```

Y le daremos nuestros vectores a OpenGL en lugar de nuestros arreglos :

``` cpp
glBufferData(GL_ARRAY_BUFFER, vértices.size() * sizeof(glm::vec3), &vértices[0], GL_STATIC_DRAW);
```

Y eso es todo !

# Resultados

Me disculpo por la textura sosa, no soy un buen artista. Sin embargo, cualquier contribución será más que bienvenida.

![]({{site.baseurl}}/assets/images/tuto-7-model-loading/ModelLoading.png)


# Otros formatos/funciones de carga

Esta pequeña función de carga es suficiente para comenzar, pero en realidad no es lo que querríamos utilizar en la vida real. Aquí hay algunos links a [herramientas útiles](http://www.opengl-tutorial.org/miscellaneous/useful-tools-links/) con herramientas que podemos usar. Sin embargo, lo mejor sería esperar hasta el tutorial 9 para que las usemos de verdad.


