---
layout: page
status: publish
published: true
title: 'Tutorial 4 : Un cubo con color'
date: '2011-04-26 07:55:37 +0200'
date_gmt: '2011-04-26 07:55:37 +0200'
categories: [tuto]
order: 40
tags: []
language: es
---
Bienvenido al cuarto tutorial ! Aquí vas a aprender a :

* Dibujar un cubo en vez de un triángulo aburrido
* Añadir colores geniales
* Apreder qué cosa es un z-buffer

# Dibujar un cubo

Un cubo tiene seis caras cuadradas. Dado que OpenGl solo sabe de triángulos, tendrémos que dibujar 12 triángulos : dos por cada cara. Definimos los vértices de la misma forma que lo hicimos para los triángulos.

``` cpp
// Nuestros vértices. Tres flotantes consecutivos hacen un vértice 3D; tres vértices consecutivos hacen un triángulo.
// Un cubo tiene 6 caras con 2 triángulos cada una, esto significa 6*2=12 triángulos, y 12*3 vértices
static const GLfloat g_vertex_buffer_data[] = {
    -1.0f,-1.0f,-1.0f, // triángulo 1 : comienza
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triángulo 1 : termina
    1.0f, 1.0f,-1.0f, // triángulo 2 : comienza
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triángulo 2 : termina
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
};
```

El buffer OpenGl es creado, asociado, llenado y configurado con las funciones estándar (glGenBuffers, glBindBuffer, glBufferData, glVertexAttribPointer) ; Mira el tutorial 2 para repasar. La función para pintar tampoco cambia, solo se le debe indicar el número adecuado de vértices a dibujar :

``` cpp
// Dibujar el triángulo !
glDrawArrays(GL_TRIANGLES, 0, 12*3); // 12*3 los índices comienzan en 0 -> 12 triángulos -> 6 cuadrados
```

Unos apuntes sobre este código :

* Por ahora, nuestro modelo 3D es fijo : para cambiarlo, se debe modificar el código, recompilar la aplicación y esperar lo mejor. Vamos a aprender a cargar modelos de forma dinámica en el tutorial 7
* Cada vértice está siendo escrito al menos 3 veces (busca "-1.0f,-1.0f,-1.0f" en el código arriba). Es un espacio terrible en memoria y vamos a lidiar con esto en el tutorial 9.

Ahora que tenemos las piezas para dibujar el cubo en blanco, vamos a hacer funcionar los shaders ! Vamos, por lo menos intenta :)

# Añadiendo colores


Conceptualmente, un color es lo mismo que una posición : solo son datos. En términos de OpenGL son “atributos”. De hecho, ya usamos esto en las funciones glEnableVertexAttribArray() y glVertexAttribPointer(). Vamos a añadir otro atributo. El código va a ser muy parecido 

Primero, declara tus colores : una tripla RGB por vértice. Aquí generé unos al azar, así que el resultado no se va a ver muy bien. Se puede hacer algo mejor, copiar la posición del vértice en el color.

``` cpp
// Un color por vértice. Fueron generados al azar.
static const GLfloat g_color_buffer_data[] = {
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
};
```

El buffer es creado, asociado y llenado en la misma forma que el anterior :

``` cpp
GLuint colorbuffer;
glGenBuffers(1, &colorbuffer);
glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
```

La configuración también es idéntica :

``` cpp
// 2do atributo del buffer : colores
glEnableVertexAttribArray(1);
glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
glVertexAttribPointer(
    1,                                // Atributo. No hay razón especial para el 1, pero debe corresponder al número en el shader.
    3,                                // tamaño
    GL_FLOAT,                         // tipo
    GL_FALSE,                         // normalizado?
    0,                                // corrimiento
    (void*)0                          // corrimiento de buffer
);
```

Ahora en el vertex shader, tenemos que acceder a este buffer adicional :

``` glsl
// Nota que “1” aquí es igual al “1” en glVertexAttribPointer
layout(location = 1) in vec3 vertexColor;
```
{: .highlightglslvs }

En nuestro caso, no hacemos nada extraño con el en el vertex shader, simplemente se lo mandamos al fragment shader :

``` glsl
// Datos de salida, serán interpolados para cada fragmento.
out vec3 fragmentColor;

void main(){
    [...]

    // El color de cada vértice será interpolado
    // para producir el color de cada fragmento
    fragmentColor = vertexColor;
}
```
{: .highlightglslvs }

En el fragment shader, se declara fragmentColor de nuevo:

``` glsl
// Valores interpolados de los vertex shaders
in vec3 fragmentColor;
```
{: .highlightglslfs }

... y es copiado en el color final

``` glsl
// datos de salida
out vec3 color;

void main(){
    // Color de salida = color especificado en el vertex shader,
    // Interpolado entre los 3 vértices alrededor
    color = fragmentColor;
}
```
{: .highlightglslfs }

Y esto es lo que obtenemos :

![]({{site.baseurl}}/assets/images/tuto-4-colored-cube/missing_z_buffer.png)


Urgh. Qué feo. Para entender lo que pasa, vamos a ver como se ve un triángulo “lejano” y uno “cercano” : 

![]({{site.baseurl}}/assets/images/tuto-4-colored-cube/FarNear.png)
 
Parece bien. Ahora  pinta el triángulo “lejano” de último :

![]({{site.baseurl}}/assets/images/tuto-4-colored-cube/NearFar.png)

El lejano se está pintando sobre el “cercano” aun cuando se supone que debería estár atrás ! Esto es lo que pasa con nuestro cubo : algunas caras se supone están escondidas, pero como se dibujan al final, se ven encima. ¿ Ahora, quién podrá defendernos ? El Z-Buffer al rescate !

* Nota 1: Si no ves cual es el problema, cambia la posición de la cámara a (4,3,-3)

* Nota 2* : Si color, como la posición, es un atributo, ¿por qué necesitamos declarar out vec3 fragmentColor e in vec3 fragmentColor para el color y no para la posición? Porque la posición es especial : Es la única cosa obligatoria en OpenGL (de lo contrario no sabría dónde pintar el triángulo). Así que en el vertex shader la variable gl_Position es una variable incorporada, viene declarada dentro de OpenGL.

# El Z-Buffer


La solución a este problema es guardar el componente “Z” o profundidad para cada fragmento en un buffer, y cada vez que se quiere escribir un fragmento, primero se debe revisar si se debe pintar o estaba detrás y no debe ser pintado.

Tu puedes hacer esto por ti mismo, pero es mucho más fácil pedirle al hardware que lo haga por ti :

``` cpp
// Habilidad el test de profundidad
glEnable(GL_DEPTH_TEST);
// Aceptar el fragmento si está más cerca de la cámara que el fragmento anterior
glDepthFunc(GL_LESS);
```

También necesitas tanto la profundidad como el color de cada fragmento :

``` cpp
// Limpiar la ventana
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
```

Y esto es suficiente para resolver todos los problemas. 

![]({{site.baseurl}}/assets/images/tuto-4-colored-cube/one_color_per_vertex.png)


# Ejercicios

* Dibujar el cubo Y el triángulo en diferentes ubicaciones. Necesitarás generar 2 matrices MVP para hacer 2 llamadas en el bucle principal, pero solo se necesita un shader.

* Genera los valores de colores tu mismo. Algunas ideas : al azar para que veas los colores cambiar en cada ejecución del programa. Dependiendo de la posición del vértice. Combinando los dos. Cualquier otra idea creativa :) Si sabes C, aquí está la sintaxis :

``` cpp
static GLfloat g_color_buffer_data[12*3*3];
for (int v = 0; v < 12*3 ; v++){
    g_color_buffer_data[3*v+0] = tu color rojo aquí;
    g_color_buffer_data[3*v+1] = tu color verde aquí;
    g_color_buffer_data[3*v+2] = tu color azul aquí;
}
```

* Una vez hayas hecho eso, haz que los colores cambien en cada cuadro. Tendrás que llamar a call glBufferData en cada cuadro. Asegurate de que el buffer esté correctamente asociado (usando glBindBuffer) con anterioridad !





