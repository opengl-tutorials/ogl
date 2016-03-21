---
layout: page
status: publish
published: true
title: 'Billboards'
date: '2015-11-21 14:51:16 +0200'
categories: []
order: 110
tags: []
language: fr
---

#Introduction

Les billboards sont des éléments 2D incrustés dans un monde 3D. Ce n'est pas un menu 2D au-dessus de tout le reste, ni un plan 3D autour duquel tu peux tourner, mais quelque chose entre les deux, comme les barres de vies dans beaucoup de jeux.

Ce qui diffère avec les billboards est qu'ils sont positionnés à un endroit spécifique, mais que leur orientation est automatiquement calculée afin qu'ils soient toujours face à la caméra.

#Solution n°1 : la méthode 2D

Cette méthode est super simple.

Calcule simplement où ton point est à l'écran et affiche un texte 2D (voir le [onzième tutoriel]({{site.baseurl}}/fr/intermediate-tutorials/tutorial-11-2d-text/)) à cette position.

``` cpp
// Everything here is explained in Tutorial 3 ! There's nothing new.
glm::vec4 BillboardPos_worldspace(x,y,z, 1.0f);
glm::vec4 BillboardPos_screenspace = ProjectionMatrix * ViewMatrix * BillboardPos_worldspace;
BillboardPos_screenspace /= BillboardPos_screenspace.w;

if (BillboardPos_screenspace.z < 0.0f){
    // Object is behind the camera, don't display it.
}
```

Voilà !

En plus d'être super facile à implémenter, le billboard aura la même taille, peu importe sa distance avec la caméra. Mais le texte 2D est toujours affiché au-dessus de tout le reste et cela peut désorganiser le rendu et s'afficher au-dessus d'autres objets.

#Solution n°2 : la méthode 3D

Celle-ci est habituellement mieux et pas trop compliquée.

Le but est de garder le modèle aligné avec la caméra, même si la caméra se déplace :

![]({{site.baseurl}}/assets/images/tuto-billboard/2a.gif)

Tu peux voir ce problème comme étant un souci de génération de matrice de modèle, même si ce n'est pas aussi simple que cela.

L'idée est que chaque coin du billboard est à la position centrale, déplacé par les vecteurs haut et droit de la caméra ;

![]({{site.baseurl}}/assets/images/tuto-billboard/principle.png)

Bien sûr, on ne connaît que le centre du billboard dans le repère du monde, donc on a aussi besoin des vecteurs haut/droit de la caméra dans le repère du monde.

Dans l'espace caméra, le vecteur haut de celle-ci est (0, 1, 0). Pour l'obtenir dans l'espace monde, on le multiplie par la matrice qui transforme du repère de la caméra vers le repère du monde, qui est, bien sûr, l'inverse de la matrice de vue.

Une façon plus simple de l'exprimer en mathématique est :

```
CameraRight_worldspace = {ViewMatrix[0][0], ViewMatrix[1][0], ViewMatrix[2][0]}
CameraUp_worldspace = {ViewMatrix[0][1], ViewMatrix[1][1], ViewMatrix[2][1]}
```
 
Une fois que l'on a ça, il est très simple de calculer la position finale du sommet :

``` glsl vs
vec3 vertexPosition_worldspace =
    particleCenter_wordspace
    + CameraRight_worldspace * squareVertices.x * BillboardSize.x
    + CameraUp_worldspace * squareVertices.y * BillboardSize.y;
```

* *particleCenter_worldspace* est, comme son nom l'indique, la position du centre du billboard : elle est déterminée en utilisant une variable uniforme vec3
* *squareVertices* est le modèle original. SquareVertices.x est -0.5 pour les sommets de gauche, qui sont donc déplacé vers la gauche de la caméra (à cause du *CameraRight_worldsspace)
* *BillboardSize* est la taille du billboard, en unités monde, envoyée avec une autre variable uniforme.

Et presto, voici le résultat. C'était facile, non ?

![]({{site.baseurl}}/assets/images/tuto-billboard/2.gif)

Pour information, voici comment squareVertices est définie :

``` cpp
// The VBO containing the 4 vertices of the particles.
 static const GLfloat g_vertex_buffer_data[] = {
 -0.5f, -0.5f, 0.0f,
 0.5f, -0.5f, 0.0f,
 -0.5f, 0.5f, 0.0f,
 0.5f, 0.5f, 0.0f,
 };
```
 
#Solution n°3 : la méthode 3D avec taille fixe

Comme tu peux le voir ci-dessus, la taille du billboard change suivant la distance de la caméra. Dans certains cas, cela est le résultat attendu, mais dans d'autres, tel que les barres de vies, tu veux probablement une taille fixe à la place.

Comme le déplacement entre le centre et un coin doit être fixe dans l'espace écran, c'est exactement ce que l'on va faire : calculer la position du centre dans l'espace écran et la décaler pour avoir la position des coins.

``` cpp
vertexPosition_worldspace = particleCenter_wordspace;
// Get the screen-space position of the particle's center
gl_Position = VP * vec4(vertexPosition_worldspace, 1.0f);
// Here we have to do the perspective division ourselves.
gl_Position /= gl_Position.w;

// Move the vertex in directly screen space. No need for CameraUp/Right_worlspace here.
gl_Position.xy += squareVertices.xy * vec2(0.2, 0.05);
```

Souvient-toi qu'à cet endroit du pipeline de rendu, tu es en Normalized Device Coordinates (coordonnées normalisées du périphérique), donc entre -1 et 1 sur les deux axes : ce n'est pas en pixels.

Si tu veux une taille en pixels, c'est facile : utilise simplement (ScreenSizeInPixels / BillboardSizeInPixels) au lieu de BillboardSizeInScreenPercentage.

![]({{site.baseurl}}/assets/images/tuto-billboard/3.gif)

#Solution n°4 : rotation verticale seule

Quelques technique de rendue représentent les arbres lointains et les lampes avec des billboards. Mais tu ne souhaites vraiment, vraiment pas, que votre arbre soit incliné : il DOIT être vertical. Donc tu as besoin d'un système hybride qui tourne seulement autour d'un axe.

Eh bien ... ce cas-là est laissé comme exercice pour le lecteur !
