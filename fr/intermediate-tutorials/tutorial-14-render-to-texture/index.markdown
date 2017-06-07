---
layout: tutorial
status: publish
published: true
title: 'Tutoriel 14 : rendu dans une texture'
date: '2015-11-21 08:00:40 +0200'
categories: [tuto]
order: 540
tags: []
language: fr
---

* TOC
{:toc}

Le rendu dans une texture (render to texture) est une méthode pratique pour créer une multitude d'effets. L'idée de base est de dessiner une scène, tout comme vous le faites habituellement, mais cette fois, dans une texture que tu peux réutiliser plus tard.

Les applications de cette technique incluent les caméras dans les jeux, le post-processing et autant d'effets graphiques que tu le souhaites.

# Rendu dans une texture

On a trois tâches : créer une texture dans laquelle on va faire le rendu, faire le rendu dans celle-ci et utiliser la texture générée.

## Créer la render target

La chose dans laquelle on va dessiner s'appelle un Framebuffer (tampon d'image). C'est un conteneur pour les textures et optionnellement un Z buffer (tampon de profondeur). Il est créé exactement comme n'importe quel un autre objet OpenGL :

``` cpp
// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
GLuint FramebufferName = 0;
glGenFramebuffers(1, &FramebufferName);
glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
```

Maintenant on doit créer la texture qui va contenir la sortie RGB du shader. Ce code est très classique :

``` cpp
// The texture we're going to render to
GLuint renderedTexture;
glGenTextures(1, &renderedTexture);

// "Bind" the newly created texture : all future texture functions will modify this texture
glBindTexture(GL_TEXTURE_2D, renderedTexture);

// Give an empty image to OpenGL ( the last "0" )
glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, 1024, 768, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

// Poor filtering. Needed !
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
```

On a aussi besoin d'un tampon de profondeur. C'est optionnel et dépend de ce que tu veux afficher dans ta texture ; mais comme on va afficher Suzanne, on a besoin du test de profondeur.

``` cpp
// The depth buffer
GLuint depthrenderbuffer;
glGenRenderbuffers(1, &depthrenderbuffer);
glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 768);
glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);
```

Finalement, on configure le framebuffer :

``` cpp
// Set "renderedTexture" as our colour attachement #0
glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

// Set the list of draw buffers.
GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers
```

Quelque chose a pu mal se passer durant ce processus, suivant les capacités du GPU. On vérifie les erreurs comme ça :

``` cpp
// Always check that our framebuffer is ok
if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
return false;
```

## Dessiner dans la texture

Le rendu dans la texture est direct. On lie simplement le framebuffer et on dessine notre scène comme d'hab. Facile !

``` cpp
// Render to our framebuffer
glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
glViewport(0,0,1024,768); // Render on the whole framebuffer, complete from the lower left corner to the upper right
```

Le fragment shader nécessite une adaptation mineure :

``` cpp
layout(location = 0) out vec3 color;
```

Cela signifie que lors de l'écriture dans la variable « color », on va écrire dans la cible de rendu 0, qui correspond à la texture, car DrawBuffers[0] est GL_COLOR_ATTACHMENT*i*, qui est dans notre cas, renderedTexture.

Pour récapituler :

* *color* sera écrit dans le premier tampon à cause du layout(location=0)
* Le premier buffer est *GL_COLOR_ATTACHMENT0* car *DrawBuffers[1] = {GL_COLOR_ATTACHMENT0}*
* *renderedTexture* est attaché à *GL_COLOR_ATTACHMENT0*, donc c'est la que la couleur sera écrite
* En d'autres mots, tu peux remplacer GL_COLOR_ATTACHMENT0 par GL_COLOR_ATTACHMENT2 et ça fonctionnera toujours.

> Il n'y a pas de layout(location=i) dans OpenGL < 3.3, mais tu peux utiliser glFragData[i] = myvalue à la place.

## Utiliser la texture générée

On va dessiner un simple rectangle pour remplir l'écran. On doit utiliser les tampons habituels, shaders, identifiants ...

``` cpp
// The fullscreen quad's FBO
GLuint quad_VertexArrayID;
glGenVertexArrays(1, &quad_VertexArrayID);
glBindVertexArray(quad_VertexArrayID);

static const GLfloat g_quad_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    1.0f,  1.0f, 0.0f,
};

GLuint quad_vertexbuffer;
glGenBuffers(1, &quad_vertexbuffer);
glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);

// Create and compile our GLSL program from the shaders
GLuint quad_programID = LoadShaders( "Passthrough.vertexshader", "SimpleTexture.fragmentshader" );
GLuint texID = glGetUniformLocation(quad_programID, "renderedTexture");
GLuint timeID = glGetUniformLocation(quad_programID, "time");
```

Maintenant tu veux dessiner sur l'écran. Cela se fait en utilisant 0 comme second paramètre de glBindFramebuffer.

``` cpp
// Render to the screen
glBindFramebuffer(GL_FRAMEBUFFER, 0);
glViewport(0,0,1024,768); // Render on the whole framebuffer, complete from the lower left corner to the upper right
```

On peut dessiner le rectangle plein écran avec un tel shader :

``` glsl
#version 330 core

in vec2 UV;

out vec3 color;

uniform sampler2D renderedTexture;
uniform float time;

void main(){
    color = texture( renderedTexture, UV + 0.005*vec2( sin(time+1024.0*UV.x),cos(time+768.0*UV.y)) ).xyz;
}
```
{: .highlightglslfs }

Ce code échantillonne simplement la texture, mais ajoute un léger décalage dépendant du temps.

# Results

![]({{site.baseurl}}/assets/images/tuto-14-render-to-texture/wavvy.png)


# Aller plus loin

## Utiliser la profondeur

Dans quelques cas tu peux avoir besoin de la profondeur lors de l'utilisation de la texture générée. Dans ce cas, dessine simplement la texture comme suit :

``` cpp
glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT24, 1024, 768, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
```

> « 24 » est la précision, en bits. Tu peux choisir entre 16, 24 et 32, suivant tes besoins. Habituellement 24 suffit.

Cela devrait être assez pour pouvoir démarrer.

Remarque que cela devrait être quelque peu plus lent, car le pilote ne sera pas capable d'utiliser quelques optimisations comme [Hi-Z](http://fr.slideshare.net/pjcozzi/z-buffer-optimizations).

Dans cette capture d'écran, les niveaux de profondeur sont rendu artificiellement « plus beaux ». Habituellement, c'est beaucoup plus difficile de voir quelque chose sur une texture de profondeur. Proche = Z tendant vers 0 = noir, Lointain = Z tendant vers 1 = blanc.

![]({{site.baseurl}}/assets/images/tuto-14-render-to-texture/wavvydepth.png)

## Multi-échantillonnage

Tu peux écrire dans des textures utilisant le multi-échantillonnage au lieu d'utiliser les textures de « base » : tu dois simplement remplacer glTexImage2D par [glTexImage2DMultisample](http://www.opengl.org/sdk/docs/man3/xhtml/glTexImage2DMultisample.xml) dans le code C++ et sampler2D/texture par sampler2DMS/texelFetch dans le fragment shader.

Par contre, il y a un énorme inconvénient : texelFetch a besoin d'un argument supplémentaire, correspondant au numéro de l'échantillon à récupérer. En d'autres mots, il n'y a pas de méthode automatique de « filtrage » (le terme correct, lorsque l'on parle de multi-échantillonnage, est « résolution »).

Donc, vous devras peut être résoudre la texture utilisant le multi-échantillonnage toi-même, dans une autre texture *sans* multi-échantillonnage, grâce à un autre shader.

Rien de difficile, mais c'est simplement pénible.

## Cible de rendu multiples

Tu peux écrire dans plusieurs textures en même temps.

Crée simplement plusieurs textures (toutes avec la même et correcte taille !), appele glFramebufferTexture avec une couleur d'attache différente pour chaque, appele glDrawBuffers avec des paramètres mis à jour (quelque chose comme (2, {GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1})) et ajoutez une autre variable de sortie dans votre fragment shader :

``` glsl
layout(location = 1) out vec3 normal_tangentspace; // or whatever
```
{: .highlightglslfs }

> Si tu as besoin d'écrire un vecteur dans une texture, les textures à virgule flottante existe, avec une précision de 16 ou 32 bits au lieu de 8 ... voir la documentation de [glTexImage2D](http://www.opengl.org/sdk/docs/man/xhtml/glTexImage2D.xml) (ctrl+f GL_FLOAT).

> Dans les versions précédentes d'OpenGL, utilise glFragData[1] = myvalue à la place.

# Exercices

* Essaye d'utiliser glViewport(0,0,512,768); à la place de glViewport(0,0,1024,768); (essaye avec le framebuffer et l'écran)
* Expérimente avec d'autres coordonnées UV dans le dernier fragment shader.
* Transforme le rectangle avec une vraie matrice de transformation. Code-la en dur puis essaye d'utiliser les fonctions de controls.hpp ; que remarque-vous ?
