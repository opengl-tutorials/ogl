---
layout: page
status: publish
published: true
title: 'Tutorial 5 : Un cubo con textura'
date: '2011-04-26 07:55:58 +0200'
date_gmt: '2011-04-26 07:55:58 +0200'
categories: [tuto]
order: 50
tags: []
language: es
---

En este tutorial aprenderás :

* Qué son las coordenadas UV
* Cómo cargar texturas
* Cómo usarlas en OpenGL
* Qué es filtradro y qué son los mapas MIP y cómo se utilizan
* Cómo cargar texturas de manera más robusta usando GLFW
* Qué es el canal Alfa


# Acerca de las coordenadas UV

Cuando se le añade una textura a una malla, necesitas una manera de decirle a OpenGl qué parte de la imagen tiene que ser usada para cada triángulo y es para esto que se emplean las coordenadas UV.

Cada vértice puede tener, además de su posición, una pareja de números de punto flotante, U y V. Estas coordenadas son usadas para acceder a la tectura de la siguiente manera:

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/UVintro.png)

Nota como la textura se distorsiona en el triángulo.
 

# Cargando imágenes BMP por ti mismo

Conocer el formato BMP no es crucial : Hay muchas librerías que pueden cargar archivos BMP por ti. Sin embargo, el formato es bastante simple y conocerlo podría ayudarte a entender como funcionan las cosas por debajo. Así que escribermos un cargador de archivos BMP desde cero, para que puedas entender como funciona y luego<span style="text-decoration: underline;">no vuelvas a usarlo nunca más</span>.

Aquí se declara la función para cargar la imagen :

``` cpp
GLuint loadBMP_custom(const char * imagepath);
```

y se utiliza así :

``` cpp
GLuint image = loadBMP_custom("./my_texture.bmp");
```

Veamos ahora como leer un archivo en formato BMP.

Primero, necesitaremos alguna información. Estas variables serán asignadas cuando leamos el archivo

``` cpp
// Lectura de información del encabezado del archivo
unsigned char header[54]; // Each BMP file begins by a 54-bytes header
unsigned int dataPos;     // Position in the file where the actual data begins
unsigned int width, height;
unsigned int imageSize;   // = width*height*3
// Información RGB
unsigned char * data;
```

We now have to actually open the file

``` cpp
// Apertura del archivo
FILE * file = fopen(imagepath,"rb");
if (!file){printf("Image could not be opened\n"); return 0;}
```

The first thing in the file is a 54-bytes header. It contains information such as "Is this file really a BMP file?", the size of the image, the number of bits per pixel, etc. So let's read this header :

``` cpp
if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
    printf("Not a correct BMP file\n");
    return false;
}
```

El encabezado siempre comienza con BM. De hecho, esto es lo que obtienes cuando abres un archivo de extensión .BMP en un editor hexadecimal:

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/hexbmp.png)

Es por esto que tenemos que verificar que los dos primeros bytes son realmente las letras 'B' y 'M' :

``` cpp
if ( header[0]!='B' || header[1]!='M' ){
    printf("Not a correct BMP file\n");
    return 0;
}
```

Ahora podemos leer el tamaño de la imagen, la ubicación de la información en el archivo, etc :

``` cpp
// Lectura de los enteros desde el arreglo de bytes
dataPos    = *(int*)&(header[0x0A]);
imageSize  = *(int*)&(header[0x22]);
width      = *(int*)&(header[0x12]);
height     = *(int*)&(header[0x16]);
```

Tenemos que rellenar algunas piezas de información en caso de que estén ausentes :

``` cpp
// Algunos archivos BMP tienen un mal formato, así que adivinamos la información faltante
if (imageSize==0)    imageSize=width*height*3; // 3 : un byte por cada componente Rojo (Red), Verde (Green) y Azul(Blue)
if (dataPos==0)      dataPos=54; // El encabezado del BMP está hecho de ésta manera
```

Ahora que sabemos el tamaño de la imagen, podemos reservar algo de memoria para la imagen que vamos a leer :

``` cpp
// Se crea un buffer
data = new unsigned char [imageSize];

// Leemos la información del archivo y la ponemos en el buffer
fread(data,1,imageSize,file);

//Todo está en memoria ahora, así que podemos cerrar el archivo
fclose(file);
```

Llegamos ahora entonces a la verdadera parte del OpenGL. Crear texturas es muy similar a crear buffers de vértices: Se crea una textura, se ata, se rellena y se configura.

En glTexImage2D, La opción GL_RGB indica que estamos hablando de un color en 3 componentes, y GL_BGR señala cómo éste es representado exactamente en la memoria RAM. En realidad, BMP no almacena los colores de la forma Rojo->Verde->Azul sino de la forma Azul->Verde->Rojo, así que se lo tenemos que decir explícitamente a OpenGL.

``` cpp
// Se Crea una textura OpenGL
GLuint textureID;
glGenTextures(1, &textureID);

// Se "Ata" la nueva textura : Todas las futuras funciones de texturas van a modificar esta textura
glBindTexture(GL_TEXTURE_2D, textureID);

// Se le pasa la imagen a OpenGL
glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
```

Explicaremos estas dos líneas más adelante. Mientras tanto, en el lado C++, puedes usar tu nueva función para cargar una textura :

``` cpp
GLuint Texture = loadBMP_custom("uvtemplate.bmp");
```

Otro punto muy importante :** Usar texturas en potencias de dos !**

* Bien : 128x128, 256x256, 1024x1024, 2x2...
* Mal : 127x128, 3x5, ...
* Aceptable (aunque raro) : 128*256


# Usando la textura en OpenGL

Le daremos un vistazo primero al fragment shader. La mayor parte es bastante simple :

``` glsl
#version 330 core

// Valores interpolados de los vertex shaders
in vec2 UV;

// Valores de salida
out vec3 color;

// Valores que permanecen constantes para toda la malla.
uniform sampler2D myTextureSampler;

void main(){

    // Color de Salida = color de la textura en las coordenadas UV específicadas
    color = texture( myTextureSampler, UV ).rgb;
}
```
{: .highlightglslfs }

Tres cosas :

* El fragment shader necesita coordenadas UV. Lo cual parece justo.
* También necesita un  "sampler2D" para saber qué textura debe acceder (puedes acceder varias texturas en el mismo shader).
* Finalmente, el acceso a una textura se realiza con la función texture() que retorna un vec4 de la forma (R,G,B,A) vec4. Más adelante hablaremos de lo que significa esa última A.

El vertex shader es simple también. Sólo tienes que pasar coordenadas UV al fragment shader :

``` glsl
#version 330 core

// Información de entrada de los vértices. Es diferente para cada una de las ejecuciones de este shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

// Valores de salida ; serán interpolados para cada fragmento.
out vec2 UV;

// Valores que permanecen constantes para toda la malla. .
uniform mat4 MVP;

void main(){

    // Posición de salida del vértice. En el espacio clip: MVP * position
    gl_Position =  MVP * vec4(vertexPosition_modelspace,1);

    // UV de los vértices. No se necesita un espacio especial para esta línea.
    UV = vertexUV;
}
```
{: .highlightglslvs }

¿Recuerdas la línea "layout(location = 1) in vec2 vertexUV" del Tutorial 4 ? Bien, tendremos que hacer exactamente lo mismo aquí, pero en lugar de darle un buffer de tripletas (R,G,B), le daremos un buffer de parejas (U,V).

``` cpp
// Dos coordenadas UV para cada vértice. Éstas fueron creadas con Blender. Aprenderás en breve como hacer esto tu mismo.
static const GLfloat g_uv_buffer_data[] = {
    0.000059f, 1.0f-0.000004f,
    0.000103f, 1.0f-0.336048f,
    0.335973f, 1.0f-0.335903f,
    1.000023f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.336024f, 1.0f-0.671877f,
    0.667969f, 1.0f-0.671889f,
    1.000023f, 1.0f-0.000013f,
    0.668104f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.000059f, 1.0f-0.000004f,
    0.335973f, 1.0f-0.335903f,
    0.336098f, 1.0f-0.000071f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.336024f, 1.0f-0.671877f,
    1.000004f, 1.0f-0.671847f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.668104f, 1.0f-0.000013f,
    0.335973f, 1.0f-0.335903f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.668104f, 1.0f-0.000013f,
    0.336098f, 1.0f-0.000071f,
    0.000103f, 1.0f-0.336048f,
    0.000004f, 1.0f-0.671870f,
    0.336024f, 1.0f-0.671877f,
    0.000103f, 1.0f-0.336048f,
    0.336024f, 1.0f-0.671877f,
    0.335973f, 1.0f-0.335903f,
    0.667969f, 1.0f-0.671889f,
    1.000004f, 1.0f-0.671847f,
    0.667979f, 1.0f-0.335851f
};
```

Las coordenadas UV arriba corresponden al siguiente modelo :

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/uv_mapping_blender.png)

El resto es obvio. Genera el buffer, atalo, llénalo, configúralo y dibuja el Vertex Buffer de la manera habitual. Solo ten cuidado y usa 2 como el segundo parámetro (el tamaño) del glVertexAttribPointer en lugar de 3.

Este es el resultado :

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/nearfiltering.png)

Y esta es la versión aumentada :

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/nearfiltering_zoom.png)

# ¿Qué son el filtrado, los mapas MIP y cómo se usan?

Cómo puedes ver en la captura de pantalla de arriba, la calidad de la textura no es la mejor. Esto es porque en nuestra función loadBMP_custom escribimos lo siguiente :

``` cpp
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
```

Esto significa que en nuestro fragment shader, texture() toma the texel que está en la coordenada (U,V) y continúa campante

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/nearest.png)

Hay varias maneras en las que podemos mejorar esto.

## Filtrado Lineal

Con el filtrado lineal, texture() también mira los otros texeles alrededor y mezcla los colores de acuerdo con su distancia al centro. Esto nos permite evitar los bordes duros que vemos en el ejemplo.

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/linear1.png)

Así está mucho mejor. Esta es una solución muy utilizada, pero si quieres una mejor calidad, puedes emplear un filtrado anisotrópico, que es algo más lento.

## Filtrado Anisotrópico

Este aproxima la parte de la imagen que está siendo vista realmente a través del fragmento. Por ejemplo, si la siguiente textura está siendo vista de lado y de forma un poco rotada, el filtrado anisotrópico calculará el color contenido en el rectángulo azul tomando un número fijo de muestras (el "nivel anisotrópico") en esa dirección.

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/aniso.png)

## Mapas MIP

El filtrado lineal y el filtrado anisotrópico tienen un problema. Si la textura es vista desde una distancia muy lejana, mezclar solamente 4 texeles no será suficiente. De hecho, si tu modelo 3D está ubicado suficientemente lejos, sólo requerirá un fragmento en la pantalla. TODOS los texeles de la imagen deberían ser entonces promediados para producir el color final. Esto no se hace por razones obvias, pero en su lugar, presentamos los mapas MIP :

![](http://upload.wikimedia.org/wikipedia/commons/5/5c/MipMap_Example_STS101.jpg)

* En el cuadro de inicialización, reduces la escala de tu imagen en 2 sucesivamente hasta que tengas una imagen de 1x1 image (la cuál es efectivamente el promedio de todos los texeles presentes en la imagen original)
* Cuando dibujas una malla, selecciona qué mapa MIP es el más apropiado para usar en razón de qué tan grande debería ser el texel.
* Muestrea este mapa MIP con el filtrado lineal o anisotrópico.
* Para calidad adicional, puedes muestrear dos mapas MIP y mezclar los resultados.

Por suerte, todo esto es bastante simple de hacer. OpenGL es capaz de realizar todo esto por nosotros si se lo pedimos amablemente :

``` cpp
// Cuando se MAGnifique la imagen (no hay un mapa MIP disponible), se usa filtrado Lineal
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// Cuando se MINimice la imagen, se usa una combinación LINEAL de dos mapas MIP, cada uno filtrado LINEALMENTE también. 
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
// Generamos los mapas MIP, claro está.
glGenerateMipmap(GL_TEXTURE_2D);
```

# Cómo cargar una textura con GLFW

Nuestra función loadBMP_custom es genial porque la hicimos nosotros mismos, pero usar una librería dedicada es aún mejor. GLFW2 puede hacer esto también (pero solo para archivos TGA y está característica ha sido removida de GLFW3 que es que usaremos) :

``` cpp
GLuint loadTGA_glfw(const char * imagepath){

    // Creamos una textura OpenGL
    GLuint textureID;
    glGenTextures(1, &textureID);

    // Se "Ata" la nueva textura : Todas las futuras funciones de texturas van a modificar está textura
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Se lee el archivo. Se hace el llamado a glTexImage2D con los parámetros correctos
    glfwLoadTexture2D(imagepath, 0);

    // Un bonito filtrado trilineal
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Retornamos la ID de la textura que acabamos de crear
    return textureID;
}
```

# Texturas Comprimidas

En este punto, te estarás preguntando cómo cargar archivos JPEG en lugar de TGA.

La respuesta corta a esta pregunta es : No lo hagas. Las GPUs no entienden JPEG, así que vas a comprimir tu imagen original en JPEG y luego a descomprimirla para que la GPU pueda entenderla. Así que al final, terminas trabajando con las mismas imágenes en bruto pero habiendo perdido calidad al haberla comprimido a JPEG.

Hay una mejor opción

## Creación de Texturas Comprimidas


* Descarga [The Compressonator](http://developer.amd.com/Resources/archive/ArchivedTools/gpu/compressonator/Pages/default.aspx), una herramienta de AMD
* Carga texturas de potencias de dos en él.
* Genera mapas MIP para que no tengas que hacerlo en tiempo de ejecución.
* Comprímelas en DXT1, DXT3 o en DXT5 (puedes encontrar más información sobre las diferencias entre estos formatos en [Wikipedia](http://en.wikipedia.org/wiki/S3_Texture_Compression)) :

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/TheCompressonator.png)

* Expórtala como un archivo .DDS.

En este mundo, tu imagen está comprimida en un formato que es directamente compatible con la GPU. Cuando llames la función texture() en un shader, éste la descomprimirá por el camino. Esto puede parecer lento, pero dado que consume MUCHO menos memoria, habrá menos datos que necesiten ser transferidos. Las transferencias de memoria son costosas, pero la descompresión de texturas no tiene costo (hay hardware dedicado para ello). Típicamente, usar compresión de texturas aumenta el desempeño en un 20%. Así que mejoras rendimiento y disminuyes el uso de memoria a cambio de reducir un poco la calidad de tu textura.

## Usando la Textura Comprimida

Veamos ahora cómo cargar la imagen. El código es muy similar al código de BMP, excepto que el encabezado está organizado de manera diferente :

``` cpp
GLuint loadDDS(const char * imagepath){

    unsigned char header[124];

    FILE *fp;

    /* Tratando de abrir el archivo */
    fp = fopen(imagepath, "rb");
    if (fp == NULL)
        return 0;

    /* Verificando el tipo de archivo */
    char filecode[4];
    fread(filecode, 1, 4, fp);
    if (strncmp(filecode, "DDS ", 4) != 0) {
        fclose(fp);
        return 0;
    }

    /* Obtenemos la descripción de la superficie */
    fread(&header, 124, 1, fp); 

    unsigned int height      = *(unsigned int*)&(header[8 ]);
    unsigned int width         = *(unsigned int*)&(header[12]);
    unsigned int linearSize     = *(unsigned int*)&(header[16]);
    unsigned int mipMapCount = *(unsigned int*)&(header[24]);
    unsigned int fourCC      = *(unsigned int*)&(header[80]);
```

Después del encabezado está la verdadera información: Todos los niveles de los mapas MIP uno después del otro. Podemos leerlos todos en una sola pasada :

 

``` cpp
    unsigned char * buffer;
    unsigned int bufsize;
    /* ¿qué tan grande será si incluimos todos los mapas MIP? */
    bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
    fread(buffer, 1, bufsize, fp);
    /* cerramos el puntero al archivo */
    fclose(fp);
```

Aquí tratamos con tres formatos diferentes: DXT1, DXT3 y DXT5. Necesitamos convertir el flag "fourCC" en un valor que OpenGL pueda entender

``` cpp
    unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4;
    unsigned int format;
    switch(fourCC)
    {
    case FOURCC_DXT1:
        format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
        break;
    case FOURCC_DXT3:
        format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
        break;
    case FOURCC_DXT5:
        format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
        break;
    default:
        free(buffer);
        return 0;
    }
```

La creación de la textura se hace de la forma habitual :

``` cpp
    // Se crea una textura OpenGL
    GLuint textureID;
    glGenTextures(1, &textureID);

    //  Se "Ata" la nueva textura : Todas las futuras funciones de texturas van a modificar está textura
    glBindTexture(GL_TEXTURE_2D, textureID);
```

Y ahora rellenamos cada mapa MIP uno después del otro :

``` cpp
    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;

    /* se cargan los mapas MIP*/
    for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
    {
        unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 
            0, size, buffer + offset);

        offset += size;
        width  /= 2;
        height /= 2;
    }
    free(buffer); 

    return textureID;
```

## Invirtiendo las coordenadas UV

La compresión DXT  viene del mundo DirectX, en dónde las la coordenada Vde la textura es invertida en comparación a OpenGL. Así que si usas texturas comprimidas, tendrás que usar ( coord.u, 1.0-coord.v) para localizar el texel correcto. Puedes hacer esto en dónde desees: En el script que importa la textura, en el método de carga, en el shader...

# Conclusión

Acabas de aprender a crear, cargar y usar texturas en OpenGL.

En general, deberías usar sólo texturas comprimidas, dado que ocupan menos espacio de almacenamiento, se cargan de forma casi instantánea y son muy rápidas de usar. La única desventaja es que tienes que utilizar The Compressonator (o cualquier herramienta similar) con todas las imágenes que pretendas utilizar.

# Ejercicios


* El cargador DDS está implementado en el código fuente; no así la modificación de las coordenadas de la textura. Cambia el código en el lugar apropiada para que el cubo se muestre de manera correcta.
* Experimenta con varios formatos DDS. ¿Dan diferentes resultados? ¿Diferentes niveles de compresión?
* Trata de no generar mapas MIP en The Compressonator. ¿Cuál es el resultado?. Encuentra 3 maneras diferentes de solucionar esto.


# Referencias


* [Using texture compression in OpenGL](http://www.oldunreal.com/editing/s3tc/ARB_texture_compression.pdf) , S&eacute;bastien Domine, NVIDIA


