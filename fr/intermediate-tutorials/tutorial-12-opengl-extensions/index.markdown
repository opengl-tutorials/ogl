---
layout: page
status: publish
published: true
title: 'Tutoriel 12 : extensions OpenGL'
date: '2015-11-19 21:43:00 +0100'
categories: [tuto]
order: 40
tags: []
language: fr
---

# Extensions

Avec chaque nouvelle génération, les performances des GPU augmentent, permettant ainsi d'afficher plus de triangles et plus de pixels. Néanmoins, la performance brute n'est pas le seul intérêt. NVIDIA, AMD et Intel améliorent aussi leurs cartes graphiques en y ajoutant des nouvelles fonctionnalités. En voici quelques exemples.

## ARB_fragment_program

En 2002, les GPU n'avaient pas de vertex shader ni de fragment shader : tout était codé en dur dans la puce. C'était ce que l'on appelait le pipeline à fonctionnalités fixes (Fixed-Function Pipeline (FFP)). La plus récente version de l'API l'OpenGL, qui était alors OpenGL 1.3, ne proposait aucun moyen de créer, manipuler et utiliser les « shaders », car ils n'existaient même pas. Mais NVIDIA a décidé que cela pourrait être pratique de décrire le processus de rendu avec du code, à la place de la centaine d'indicateurs et de variables d'états. C'est ainsi qu'a été créé ARB_fragment_program : il n'y avait pas de GLSL, mais à la place, vous pouviez écrire des trucs comme :

```

!!ARBfp1.0 MOV result.color, fragment.color; END
```

Évidemment, pour indiquer à OpenGL d'utiliser un tel code, on avait besoin de fonctions spéciales, qui n'étaient pas encore dans OpenGL. Avant de plonger dans les explications, un autre exemple.

## ARB_debug_output

Ok, tu te dis que ce ARB_fragment_program est trop vieux, ou que je suis un dinosaure, et que tu n'as certainement plus besoin de ce truc ? En fait, il y a de *nouvelles* extensions qui sont très pratiques. L'une d'entre elles est ARB_debug_output, qui expose une fonctionnalité qui n'existait pas dans OpenGL 3.3 mais que tu peux/dois tout de même utiliser. Elle définit des symboles comme GL_DEBUG_SYNCHRONOUS_ARB ou GL_DEBUG_SEVERITY_MEDIUM_ARB et des fonctions comme DebugMessageCallbackARB. Le bon point de cette extension est qu'à chaque fois que tu écris un code incorrect, comme :

``` cpp
glEnable(GL_TEXTURE); // Incorrect ! You probably meant GL_TEXTURE_2D !
```

Tu peux avoir une erreur et l'emplacement exact du problème.
Tu viens donc d'apprendre que :

* Les extensions c'est très utiles, même en OpenGL 3.3 moderne
* Tu dois utiliser ARB_debug_output ! Voir les liens ci-dessous.

![]({{site.baseurl}}/assets/images/tuto-12-ogl-ext/breakpoint.png)

## Récupérer une extension - la méthode difficile

La méthode « manuelle » pour vérifier si une extension est disponible est d'utiliser ce morceau de code (provenant du [wiki OpenGL.org](http://www.opengl.org/wiki/GlGetString)) :

``` cpp
int NumberOfExtensions;
glGetIntegerv(GL_NUM_EXTENSIONS, &NumberOfExtensions);
for(i=0; i<NumberOfExtensions; i++) {
  const GLubyte *ccc=glGetStringi(GL_EXTENSIONS, i);
  if ( strcmp(ccc, (const GLubyte *)"GL_ARB_debug_output") == 0 ){
    // The extension is supported by our hardware and driver
    // Try to get the "glDebugMessageCallbackARB" function :
    glDebugMessageCallbackARB  = (PFNGLDEBUGMESSAGECALLBACKARBPROC) wglGetProcAddress("glDebugMessageCallbackARB");
  }
}
```

## Récupérer toutes les extension - la méthode facile

Somme toute, c'est très compliqué. Les bibliothèques comme GLEW, Glee, gl3w, etc. rendent cela plus facile. Par exemple, avec GLEW, tu n'as qu'à appeler glewInit() après avoir créé la fenêtre, et hop ! Tu as des variables pratiques qui sont créées pour toi comme :

``` cpp
if (GLEW_ARB_debug_output){ // Ta-Dah ! }
```

> debug_output est un peu spéciale, car tu dois l'activer à la création du contexte. Dans GLFW, cela est fait avec glfwOpenWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);

## ARB vs EXT vs ...

Le nom de chaque extension contient des informations sur sa disponibilité :

* GL_ : toutes les plates-formes
* GLX_ : Linux et Mac seulement (X11)
* WGL_ : Windows seulement

* EXT : une extension générique

* ARB : l'extension a été acceptée par tous les membres du OpenGL Architecture Review Board (les extensions EXT sont souvent promues ARB au bout d'un moment)

* NV/AMD/INTEL : assez évident =)

# Concevoir avec les extensions

## Le problème

Disons que ton application OpenGL 3.3 a besoin d'afficher quelques lignes larges. Tu peux écrire un vertex shader compliqué pour ce faire, ou simplement t'appuyer sur [GL_NV_path_rendering](http://www.opengl.org/registry/specs/NV/path_rendering.txt), qui gère tous les problèmes pour toi.

Tu auras donc un code qui ressemble à ceci :

``` cpp
if ( GLEW_NV_path_rendering ){ 
    glPathStringNV( ... ); // Affiche la forme. Facile !
}else{ 
    // Sinon quoi ? Tu as toujours besoin d'afficher des lignes
    // sur les machines NVIDIA plus vieilles, sur les machines AMD, sur les machines INTEL !
    // Donc, tu dois tout de même l'implémenter toi-même ! 
}
```

## Choisir la limite

Une possibilité est de choisir d'utiliser une extension lorsque le gain dans la qualité du rendu ou la performance dépasse les souffrances de la maintenance de deux codes.

Par exemple, Braid (le jeu 2D où vous voyagez dans le temps) possède plein d'effets de déformation d'images, lorsque vous jouez avec le temps, qui ne sont simplement pas affichés avec du matériel plus ancien.

Avec OpenGL 3.3 et supérieur, tu as déjà 99 % des outils dont tu vas avoir besoin. Quelques extensions peuvent être utiles, comme GL_AMD_pinned_memory, mais c'est différent d'il y a quelques années, lorsqu'avoir GL_ARB_framebuffer_object (utilisé pour le rendu sur texture), pouvait rendre le jeu dix fois plus beau.

Si tu dois gérer du matériel de dinosaure, alors OpenGL 3.3 ne sera pas disponible et tu vas avoir à utiliser OpenGL 2+ à la place. Tu ne pourras pas supposer que tu as toutes ces extensions fantaisistes et tu vas devoir te débrouiller sans.

Pour plus de détails, regardes par exemple la [version OpenGL 2.1 du quatorzième tutoriel - rendu sur texture ligne 167](https://github.com/opengl-tutorials/ogl/blob/2.1_branch/tutorial14_render_to_texture/tutorial14.cpp#L167) où je dois vérifier la présence de GL_ARB_framebuffer_object à la main.

# Conclusion

Les extensions OpenGL fournissent une méthode efficace pour étendre les capacités d'OpenGL, suivant le GPU de l'utilisateur.

Bien que les extensions soient principalement utilisées pour les usages avancés depuis que la plupart des fonctionnalités sont déjà présentes dans le noyau de l'API OpenGL, il reste important de connaître comment elles fonctionnent et comment tu peux les utiliser pour améliorer ton logiciel - pour un coût de maintenance plus chère.

# Pour continuer

* [Tutoriel debug_output par Aks](http://sites.google.com/site/opengltutorialsbyaks/introduction-to-opengl-4-1---tutorial-05), vous pouvez passer la première étape grâce à GLFW
* [Le registre des extensions OpenGL](http://www.opengl.org/registry/), toutes les spécifications des extensions. La bible
* [GLEW](http://glew.sourceforge.net/), le OpenGL Extension Wrangler Library
* [gl3w](https://github.com/skaslev/gl3w), Chargement simple du profil OpenGL 3/4 core
