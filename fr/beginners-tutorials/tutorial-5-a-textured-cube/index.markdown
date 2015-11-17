---
layout: page
status: publish
published: true
title: 'Tutoriel 5 : un cube texturé'
date: '2011-04-26 07:55:58 +0200'
date_gmt: '2011-04-26 07:55:58 +0200'
categories: [tuto]
order: 50
tags: []
language: fr
---

Dans ce tutoriel, tu vas apprendre :

* Ce que sont les coordonnées UV
* Comment charger une texture par toi-même
* Comment les utiliser dans OpenGL
* Ce que sont le filtrage et les MIP maps et comment les utiliser
* comment charger une texture plus facilement avec GLFW.
* La signification du "channel alpha"


#À propos des coordonnées UV

Lorsque l'on applique une texture sur un modèle 3D, on a besoin d'une méthode pour indiquer à OpenGL quelle partie de l'image doit être utilisée pour chaque triangle. Cela se fait grâce aux coordonnées UV.

Chaque sommet possède, en plus de sa position, une paire de floats, U et V. Ces coordonnées sont utilisées pour accéder à la texture de la manière suivante :

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/UVintro.png)

Remarque comment la texture est déformée sur le triangle.

#Charger des images .BMP à la main

Connaître le format de fichier BMP n'est pas important : nombreuses sont les bibliothèques pouvant le faire pour toi. Mais il est très simple et il peut t'aider à comprendre comment les choses fonctionnent en interne. Donc, on va écrire un chargeur de fichier BMP à partir de rien, afin que tu saches comment ça fonctionne, et ensuite on l'utilisera *plus jamais* !

Voici la déclaration de la fonction de chargement :
{% highlight cpp linenos %}
GLuint loadBMP_custom(const char * imagepath);
{% endhighlight %}
Et elle s'utilise comme ça :
{% highlight cpp linenos %}
GLuint image = loadBMP_custom("./my_texture.bmp");
{% endhighlight %}
Maintenant, comment lire un fichier BMP ?

Premièrement, on a besoin de quelques données. Ces variables seront définies lors de la lecture du fichier.
{% highlight cpp linenos %}
// Data read from the header of the BMP file
unsigned char header[54]; // Each BMP file begins by a 54-bytes header
unsigned int dataPos;     // Position in the file where the actual data begins
unsigned int width, height;
unsigned int imageSize;   // = width*height*3
// Actual RGB data
unsigned char * data;
{% endhighlight %}
On doit maintenant ouvrir le fichier :
{% highlight cpp linenos %}
// Open the file
FILE * file = fopen(imagepath,"rb");
if (!file){printf("Image could not be opened\n"); return 0;}
{% endhighlight %}
La première chose dans le fichier est un en-tête de 54 octets. Il contient les informations telles que « est-ce vraiment un fichier BMP ? », la taille de l'image, le nombre de bits par pixel, etc. Donc, on lit l'en-tête :
{% highlight cpp linenos %}
if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
    printf("Not a correct BMP file\n");
    return false;
}
{% endhighlight %}
L'en-tête démarre toujours avec BM. En fait, voici ce que tu obtiens lorsque tu ouvres un fichier .BMP dans un éditeur hexadécimal :

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/hexbmp.png)

Donc, on vérifier si les deux premiers octets valent vraiment 'B' et 'M' :
{% highlight cpp linenos %}
if ( header[0]!='B' || header[1]!='M' ){
    printf("Not a correct BMP file\n");
    return 0;
}
{% endhighlight %}
Maintenant, on peut lire la taille de l'image, l'emplacement des données dans le fichier, etc :
{% highlight cpp linenos %}
// Read ints from the byte array
dataPos    = *(int*)&(header[0x0A]);
imageSize  = *(int*)&(header[0x22]);
width      = *(int*)&(header[0x12]);
height     = *(int*)&(header[0x16]);
{% endhighlight %}
On doit compléter les informations pour les cas où elles sont manquantes :
{% highlight cpp linenos %}
// Some BMP files are misformatted, guess missing information
if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
if (dataPos==0)      dataPos=54; // The BMP header is done that way
{% endhighlight %}
Maintenant que la taille de l'image est connue, on peut allouer de la mémoire pour la remplir avec l'image lue :
{% highlight cpp linenos %}
// Create a buffer
data = new unsigned char [imageSize];

// Read the actual data from the file into the buffer
fread(data,1,imageSize,file);

//Everything is in memory now, the file can be closed
fclose(file);
{% endhighlight %}
On arrive à la vrai section OpenGL. La création de textures est très similaire à la création de tampons : créer une texture, la lier, la remplir et la configurer.

Dans glTexImage2D, GL_RGB indique que l'on utilise une couleur ayant trois composantes et GL_BGR indique comment les données sont réellement disposées en mémoire. En fait, le fichier BMP ne stocke pas les pixels en Rouge->Vert->Bleu mais Bleu->Vert->Rouge, donc on doit en informer OpenGL.

{% highlight cpp linenos %}
// Create one OpenGL texture
GLuint textureID;
glGenTextures(1, &textureID);

// "Bind" the newly created texture : all future texture functions will modify this texture
glBindTexture(GL_TEXTURE_2D, textureID);

// Give the image to OpenGL
glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
{% endhighlight %}
On va expliquer les deux dernières lignes plus tard. Dorénavant, du côté C++, vous pouvez utiliser la nouvelle fonction pour charger une texture :
{% highlight cpp linenos %}
GLuint Texture = loadBMP_custom("uvtemplate.bmp");
{% endhighlight %}

>Il est important d'utiliser des textures ayant des **tailles en puissances de deux** :
>* correct : 128*128, 256*256, 1024*1024, 2*2 ...
>* mauvais : 127*128, 3*5 ...
>* correct mais étrange : 128*256, 1024*128, ...

#Utiliser une texture dans OpenGL

On commence par le fragment shader. Il est globalement simple :
{% highlight glsl linenos cssclass=highlightglslfs %}
#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;

void main(){

    // Output color = color of the texture at the specified UV
    color = texture( myTextureSampler, UV ).rgb;
}
{% endhighlight %}
Trois choses :
* Le fragment shader a besoin des coordonnées UV. Cela semble logique
* Il a aussi besoin d'un « sampler2D » pour savoir à quelle texture accéder (vous pouvez accéder à plusieurs textures dans le même shader) ;
* Finalement, l'accès à la texture est effectué avec texture(), renvoyant un vec4 contenant (R,G,B,A). On va voir ce qu'est le A, prochainement.

Le vertex shader est simple aussi, vous devez juste passer les coordonnées UV au fragment shader :
{% highlight glsl linenos cssclass=highlightglslvs %}
#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;

void main(){

    // Output position of the vertex, in clip space : MVP * position
    gl_Position =  MVP * vec4(vertexPosition_modelspace,1);

    // UV of the vertex. No special space for this one.
    UV = vertexUV;
}
{% endhighlight %}
Te souviens-tu du « layout(location = 1) in vec2 vertexUV » du [quatrième tutoriel]({{site.baseurl}}}/fr/beginners-tutorials/tutorial-4-a-colored-cube/) ? Eh bien, on doit faire exactement la même chose ici, mais au lieu de donner un tampon de triplets (R,G,B), on va donner une paire (U,V).
{% highlight cpp linenos %}
// Two UV coordinatesfor each vertex. They were created with Blender. You'll learn shortly how to do this yourself.
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
{% endhighlight %}
Les coordonnées UV ci-dessus correspondent à ce modèle :

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/uv_mapping_blender.png)

Le reste est évident. Générer le tampon, le lier, le remplir, le configurer et dessiner le tampon de sommet comme d'habitude. Fait attention et utilise 2 comme second paramètre (la taille) de la fonction glVertexAttribPointer au lieu de 3, car on a que 2 coordonées par sommet (U et V).

Voici le résultat :

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/nearfiltering.png)

et en zoomant un peu :

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/nearfiltering_zoom.png)

#Que sont le filtrage et les MIP maps et comment les utiliser

Comme tu peux le voir dans la capture ci-dessus, la qualité de la texture n'est pas superbe. C'est dû à ce que l'on a écrit dans la fonction loadBMP_custom :
{% highlight cpp linenos %}
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
{% endhighlight %}
Ça signifie que dans le fragment shader, la fonction texture() prend le texel qui est aux coordonnées (U, V) et continue joyeusement avec :

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/nearest.png)

Il y a de plusieurs choses que l'on peut faire pour améliorer cela.

##Filtrage linéaire

Avec le filtrage linéaire, la fonction texture() regarde aussi les texels autour et mélange les couleurs suivant la distance de chaque centre. Cela évite les bordures nettes vues précédemment.

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/linear1.png)

C'est beaucoup mieux et c'est beaucoup utilisé, mais si tu veux une meilleure qualité, tu peux aussi utiliser le filtrage anisotrope, qui est un peu plus lent mais plus joli.

##Filtrage anisotrope

Celui-ci se rapproche de la partie de l'image qui est réellement vue dans le fragment. Par exemple, si la texture suivante est vue sur le côté et légèrement tournée, le filtrage anisotrope calculera la couleur contenue dans le rectangle bleu en prenant un nombre fixe d'échantillons (le niveau d'anisotropie) suivant sa direction principale :

![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/aniso.png)

##Mipmaps

Les filtrages linéaire et anisotrope ont tous les deux un souci. Si la texture est vue de très loin, le mélange de quatre texels ne suffira pas. En fait, si votre modèle 3D est très loin et qu'il ne prend qu'un fragment sur l'écran, TOUS les texels de l'image vont être pris en compte pour calculer la moyenne afin de produire la couleur finale. Évidemment, cela n'est pas fait pour préserver les performances. À la place, on introduit les MIP maps :

![](http://upload.wikimedia.org/wikipedia/commons/5/5c/MipMap_Example_STS101.jpg)

* Au moment de l'initialisation, on divise les dimensions de notre image d'un facteur 2, successivement, jusqu'à atteindre une image 1 x 1 (qui correspond à la moyenne de tous les texels de l'image)
* Lorsque l'on dessine un modèle, on sélectionnez la mipmap la plus appropriée à utiliser suivant la taille à laquelle devrait être le texel
* On échantillonnez cette MIP map avec l'un des filtrages vus précédemment (anisantropique ou linéaire)
* Pour une qualité supérieure, on peut aussi échantillonner deux niveau de mipmaps et mélanger le résultat.

Heureusement, tout cela est très simple à faire, OpenGL sait le faire pour toi si tu lui demandez gentiment :
{% highlight cpp linenos %}
// When MAGnifying the image (no bigger mipmap available), use LINEAR filtering
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// When MINifying the image, use a LINEAR blend of two mipmaps, each filtered LINEARLY too
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
// Generate mipmaps, by the way.
glGenerateMipmap(GL_TEXTURE_2D);
{% endhighlight %}

#Charger les images avec GLFW

La fonction loadBMP_custom est bien, car on l'a faite à partir de rien. Mais l'utilisation d'une bibliothèque dédiée est conseillé. GLFW peut aussi faire cela (mais uniquement pour les fichiers TGA).

>*Le chargement des fichiers TGA dans GLFW est dépréciée depuis la version 3.*

{% highlight cpp linenos %}
GLuint loadTGA_glfw(const char * imagepath){

    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Read the file, call glTexImage2D with the right parameters
    glfwLoadTexture2D(imagepath, 0);

    // Nice trilinear filtering.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Return the ID of the texture we just created
    return textureID;
}
{% endhighlight %}

#Les textures compressées

À ce point, tu te demande probablement comment charger les fichiers JPEG à la place des TGA.

Réponse courte : ne le fait pas. Ta carte graphique (GPU) ne sais pas ce qu'est un JPEG ou un PNG.
Tu devras décompresser ton image en JPEG et la donner à ta carte graphique: Tu va perdre du temps a la décompresser, tu va perdre en qualité, et aussi en performance car tu vas transmettre à ta carte graphique une texture décompressée.

Il y a une meilleures options : les textures compressées.

##Créer une texture compressée

* Télécharge l'outil d'ATI : [Le Compressonator](http://developer.amd.com/Resources/archive/ArchivedTools/gpu/compressonator/Pages/default.aspx)
* Charge une texture en puissance de deux avec.
* Compresse-la en DXT1, DXT3 ou DXT5 (plus d'informations sur les différences des formats sur [Wikipedia](https://en.wikipedia.org/wiki/S3_Texture_Compression))
![]({{site.baseurl}}/assets/images/tuto-5-textured-cube/TheCompressonator.png)
* Génére les MIP maps afin de ne pas avoir à le faire à l'exécution
* Exporte le résultat dans un fichier .DDS

À ce moment, ton image est compressée dans un format qui est directement compatible avec le GPU. Pour n'importe quel appel à texture() dans un shader, le GPU décompressera la texture à la volée. Cela peut sembler lent, mais comme cela prend TELLEMENT moins de mémoire, moins de données ont besoin d'être transférées, sachant que les transferts mémoire sont lents, et que la décompression de texture est gratuite (il y a des puces dédiées à cela). Généralement, l'utilisation de la compression de texture augmente les performances de 20 %.

##Utiliser la texture compressée

Voici comment charger l'image. C'est très proche du code pour le BMP, sauf que l'en-tête est organisé différemment :
{% highlight cpp linenos %}
GLuint loadDDS(const char * imagepath){

    unsigned char header[124];

    FILE *fp;

    /* try to open the file */
    fp = fopen(imagepath, "rb");
    if (fp == NULL)
        return 0;

    /* verify the type of file */
    char filecode[4];
    fread(filecode, 1, 4, fp);
    if (strncmp(filecode, "DDS ", 4) != 0) {
        fclose(fp);
        return 0;
    }

    /* get the surface desc */
    fread(&header, 124, 1, fp); 

    unsigned int height      = *(unsigned int*)&(header[8 ]);
    unsigned int width         = *(unsigned int*)&(header[12]);
    unsigned int linearSize     = *(unsigned int*)&(header[16]);
    unsigned int mipMapCount = *(unsigned int*)&(header[24]);
    unsigned int fourCC      = *(unsigned int*)&(header[80]);
{% endhighlight %}
Les données de l'image se trouvent après l'en-tête : tous les niveaux de MIP maps, les uns après les autres. On peut les lire en une fois :
 
{% highlight cpp linenos %}
    unsigned char * buffer;
    unsigned int bufsize;
    /* how big is it going to be including all mipmaps? */
    bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
    fread(buffer, 1, bufsize, fp);
    /* close the file pointer */
    fclose(fp);
{% endhighlight %}
Ici, on doit gérer trois formats différents : DXT1, DXT3 et DXT5. On doit convertir l'indicateur « fourCC » en une valeur que comprend OpenGL.
{% highlight cpp linenos %}
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
{% endhighlight %}
La création de texture est effectuée comme d'habitude :
{% highlight cpp linenos %}
    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);
{% endhighlight %}
Et maintenant, on peut remplir chaque MIP map l'une après l'autre :
{% highlight cpp linenos %}
    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;

    /* load the mipmaps */
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
{% endhighlight %}

##Inversing the UVs

La compression DXT vient du monde DirectX, où les coordonnées de texture UV sont inversées par rapport à OpenGL. Donc, si tu utilises les textures compressées, tu dois utiliser (coord.u, 1.0-coord.v) pour récupérer le texel adéquat. Tu peux le faire quand tu le souhaite : dans ton script d'exportation, dans ton chargeur, dans ton shader ...

#Conclusion

Tu viens d'apprendre à créer, charger et utiliser les textures avec OpenGL.

En général, tu dois utiliser uniquement les textures compressées, car elles sont plus petites à stocker, chargées presque instantanément et sont plus rapides à utiliser ; le principal inconvénient est que tu dois convertir tes images avec le Compressonator ou un outils similaire.

#Exercices

* Le chargeur DDS est implémenté dans le code source, mais pas la modification des coordonnées de texture. Change le code à l'emplacement adéquat pour afficher le cube correctement.
* Expérimente avec les différents formats DDS. Est-ce qu'ils donnent le même résultat ? Des ratios de compression différents ?
* Essaye de ne pas générer les MIP maps avec The Compressonator. Quel est le résultat ? Donne trois méthodes différentes pour corriger cela.

#Références

* [Using texture compression in OpenGL](http://www.oldunreal.com/editing/s3tc/ARB_texture_compression.pdf) , Sébastien Domine, NVIDIA

