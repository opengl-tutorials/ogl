---
layout: page
status: publish
published: true
title: 'Tutoriel 11 : texte 2D'
date: '2015-11-19 21:26:33 +0200'
categories: [tuto]
order: 30
tags: []
language: fr
---

Dans ce tutoriel, on va apprendre à afficher un texte en 2D par-dessus le contenu 3D. Ici, ce sera un simple chronomètre :

![]({{site.baseurl}}/assets/images/tuto-11-2d-text/clock.png)

# L'API

On va implémenter cette simple interface (dans *common/text2D.h*) :

``` cpp
void initText2D(const char * texturePath);
void printText2D(const char * text, int x, int y, int size);
void cleanupText2D();
```

Afin que le code fonctionne, que ce soit en 640 x 480 ou 1080p, x et y seront des coordonnées dans l'espace [0-800][0-600]. Le vertex shader adaptera les coordonnées pour correspondre à la taille de l'écran.

Regarde *common/text2D.cpp* pour voir l'implémentation complète.

# La texture

*initText2D* lit simplement une texture et un couple de shaders. Il n'y a rien de spécial là-dedans, mais regarde à quoi ressemble la texture :

![]({{site.baseurl}}/assets/images/tuto-11-2d-text/fontalpha.png)

Cette texture a été générée avec [CBFG](http://www.codehead.co.uk/cbfg/), un des nombreux outils pouvant générer une texture à partir d'une police de caractères. Puis la texture a été importée dans Paint.NET où j'ai ajouté un fond rouge (seulement pour des raisons de visualisation : là où c'est rouge, cela devrait être transparent).

Le but de *printText2D* sera donc de générer des rectangles avec les positions écran appropriées et les coordonnées de texture qui vont bien.

# L'affichage

On doit remplir ces tampons :

``` cpp
std::vector<glm::vec2> vertices;
std::vector<glm::vec2> UVs;
```

Pour chaque caractère, on calcule les coordonnées des quatre sommets définissant le rectangle puis on ajoute les deux triangles qui le compose :

``` cpp
for ( unsigned int i=0 ; i<length ; i++ ){

    glm::vec2 vertex_up_left    = glm::vec2( x+i*size     , y+size );
    glm::vec2 vertex_up_right   = glm::vec2( x+i*size+size, y+size );
    glm::vec2 vertex_down_right = glm::vec2( x+i*size+size, y      );
    glm::vec2 vertex_down_left  = glm::vec2( x+i*size     , y      );

    vertices.push_back(vertex_up_left   );
    vertices.push_back(vertex_down_left );
    vertices.push_back(vertex_up_right  );

    vertices.push_back(vertex_down_right);
    vertices.push_back(vertex_up_right);
    vertices.push_back(vertex_down_left);
```

Maintenant les coordonnées UV. La coordonnée du coin supérieur gauche est calculée comme suit :

``` cpp
    char character = text[i];
    float uv_x = (character%16)/16.0f;
    float uv_y = (character/16)/16.0f;
```

Cela fonctionne (en quelque sorte - voyez ci-dessous) car le [code ASCII](http://www.asciitable.com/) pour A est 65.

65 % 16 = 1, donc A est sur la colonne numéro 1 (on commence à 0 !).

65 / 16 = 4, donc A est sur la ligne numéro 4 (c'est une division entière, donc ce n'est pas 4.0625 comme cela devrait l'être).

Les deux sont divisés par 16.0 pour rentrer dans l'échelle [0.0 - 1.0] nécessaire aux textures OpenGL.

Et maintenant, on doit faire une chose très proche de ce que nous faisions pour les sommets, mais pour les coordonnées de texture :

``` cpp
    glm::vec2 uv_up_left    = glm::vec2( uv_x           , 1.0f - uv_y );
    glm::vec2 uv_up_right   = glm::vec2( uv_x+1.0f/16.0f, 1.0f - uv_y );
    glm::vec2 uv_down_right = glm::vec2( uv_x+1.0f/16.0f, 1.0f - (uv_y + 1.0f/16.0f) );
    glm::vec2 uv_down_left  = glm::vec2( uv_x           , 1.0f - (uv_y + 1.0f/16.0f) );

    UVs.push_back(uv_up_left   );
    UVs.push_back(uv_down_left );
    UVs.push_back(uv_up_right  );

    UVs.push_back(uv_down_right);
    UVs.push_back(uv_up_right);
    UVs.push_back(uv_down_left);
 }
```

Le reste est habituel : lier les buffers (tampons), les remplir, sélectionner le bon shader, lier la texture, activer/lier/configurer les attributs de sommets, activer le mélange (pour la transparence) et appeller la fonction glDrawArrays. Hourra ! Tu as fini.

> Très important ! Les coordonnées sont générées sur l'échelle [0-800][0-600]. En d'autres mots, il n'y a PAS BESOIN de matrices ici. Le vertex shader doit juste les passer à l'échelle [-1,1][-1,1] avec une simple opération mathématique (cela aurait aussi pu être fait en C++).

``` glsl
void main(){

    // Output position of the vertex, in clip space
    // map [0..800][0..600] to [-1..1][-1..1]
    vec2 vertexPosition_homoneneousspace = vertexPosition_screenspace - vec2(400,300); // [0..800][0..600] -> [-400..400][-300..300]
    vertexPosition_homoneneousspace /= vec2(400,300);
    gl_Position =  vec4(vertexPosition_homoneneousspace,0,1);

    // UV of the vertex. No special space for this one.
    UV = vertexUV;
}
```
{: .highlightglslvs }

Le fragment shader ne fait que très peu de choses aussi :

``` glsl
void main(){
    color = texture( myTextureSampler, UV );
}
```
{: .highlightglslfs }

D'ailleurs, n'utilise pas ce code en production, car il ne gère que l'alphabet latin. Ou alors ne vend rien en Inde, Chine, Japon (ou même Allemagne, car il n'y a pas de ß dans cette image). Cette texture marchera principalement en France (remarque la présence des é, à, ç, etc.) car elle a été générée avec ma locale. Et fait attention lors de l'adaptation du code d'autres tutoriels provenant d'autres sites, ou encore lorsque tu as recours à des bibliothèques, la plupart d'entre eux/elles utilisent OpenGL 2, qui n'est pas compatible avec l'UTF8. Malheureusement, je ne connais pas de bibliothèque qui gère UTF-8.

À propos de cela, **tu dois lire** [The Absolute Minimum Every Software Developer Absolutely, Positively Must Know About Unicode and Character Sets (No Excuses!)](http://www.joelonsoftware.com/articles/Unicode.html) (le minimum absolu que chaque développeur de logiciels devrait absolument connaître sur l'Unicode et les ensembles de caractères (pas d'excuse !) de Joel Spolsky.

Regarde aussi cet [article de Valve](http://www.valvesoftware.com/publications/2007/SIGGRAPH2007_AlphaTestedMagnification.pdf) si tu as besoin de grand texte.
