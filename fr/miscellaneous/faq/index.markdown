---
layout: page
status: publish
published: true
title: FAQ
date: '2015-11-21 21:54:32 +0200'
categories: []
order: 10
tags: []
language: fr
---

# Envoyer des e-mails ...

Le meilleur moyen d'avoir du support est d'envoyer des courriels à [contact@opengl-tutorial.org](mailto:contact@opengl-tutorial.org). Toutefois, si tu as un problème, essaye d'inclure autant d'informations que tu peux. Au minimum :

* Ton système d'exploitation : Gentoo, Windows XP, 7, 10, Mac OS (Lion, Yosemite, El Capitan ?) ...
* 32 bits or 64 bits ?
* Ta carte graphique : NVIDIA, AMD, Intel, S3, Matrox ? (Souviens-toi : utilise le portage OpenGL 2.1 si tu as un GPU intégré !).

... Et aussi n'importe quelle autre information que tu penses utile, par exemple:

* La version de ton pilote de carte graphique
* La call stack (pile d'appel) de ton crash
* Un (des?) capture(s) d'écran
* Les log de la console
* Un minidump ...

Et bien sûr, lis la FAQ en premier. Ça s'appelle FAQ (*Questions fréquentes* en anglais) pour une certaine raison =).

# Je n'arrives pas à compiler les tutoriels

* Assures-toi d'avoir lu le [premier tutoriel]({{site.baseurl}}/fr/beginners-tutorials/tutorial-1-opening-a-window/). **S'IL TE PLAIT**, utilise CMake au lieu de recréer le projet, ou, au moins, assure-toi d'avoir lu [Compiler votre propre application C]({{site.baseurl}}/fr/miscellaneous/building-your-own-c-application/).
* Si tu as une erreur liée à la bibliothèque Assimp, cela sera corrigé prochainement ; toutefois, cela n'affecte qu'un SEUL tutoriel, tous les autres pourront être compilés correctement.
* Si tu as une erreur liée à la bibliothèque AntTweakBar, cela n'affecte qu'un SEUL tutoriel, tous les autres pourront être compilés correctement.
* S'il y a un autre souci, n'hésite pas à poster à nous envoyer un courriel.

# J'ai compilé les tutoriels, mais cela plante au démarrage. Que se passe-t-il ?

Plusieurs raisons possibles :

## GPU/Système d'exploitation incompatible

Vérifie STP si tu avez une carte Intel. Tu peux le faire en utilisant glewinfo, [GPU Caps Viewer](http://www.ozone3d.net/gpu_caps_viewer/) ou n'importe quel autre outil.

Les cartes graphiques Intel, sauf les récentes HD4000, ne supporte pas OpenGL 3.3. Cela veut dire que la plupart supporte seulement OpenGL 2.1. Tu dois télécharger la version OpenGL 2.1 sur la [page des téléchargements]({{site.baseurl}}/fr/download/), à la place.

L'autre raison possible est que tu utilises un Mac, avec une version avant Lion. Dans ce cas télécharge aussi la version 2.1 sur la [page des téléchargements]({{site.baseurl}}/fr/download/).

## Mauvais répertoire de travail

Il se peut que tu n'exécutes pas les tutoriels à partir du bon répertoire. Essaye en double-cliquant sur le .exe à partir de l'explorateur de fichiers.

Lis le [premier tutoriel]({{site.baseurl}}/fr/beginners-tutorials/tutorial-1-opening-a-window/) pour configurer ton IDE afin que tu puisses déboguer l'exécutable.

> Les .exe sont compilés dans le répertoire *build*, mais ensuite automatiquement copiés dans le répertoire *source*, pour qu'il puisse trouver les ressources nécessaire (images, modèle 3D, shaders)

## Pas de VAO

Si tu as créé un programme à partir de rien, assure-toi d'avoir créé un VAO au moment de l'initialisation :

```
GLuint VertexArrayID;
 glGenVertexArrays(1, &VertexArrayID);
 glBindVertexArray(VertexArrayID);
```

## Bogue de GLEW

GLEW possède un bogue qui rend impossible l'utilisation d'un contexte core (sauf lorsque tu utilises le code source des tutoriels, qui a été corrigé). Trois solutions :

* Demande à GLFW de fournir un profil de compatibilité à la place :

  ```
  glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
  ```

* Utilise glewExperimental ; voici la méthode recommandée :
  
  ```
  glewExperimental = true;
  ```

* Corrige GLEW ... [Voir ce patch](http://code.google.com/p/opengl-tutorial-org/source/browse/external/glew-1.5.8.patch?name=0009_33).

## CMake

T'as pas lu le premier tutoriel, pas vrai ? T'as pas essayé d'écrire ton propre Makefile et de tout compiler toi-même, N'EST-CE PAS ?

# Pourquoi devrais-je utiliser OpenGL 3.3 si Intel et Mac ne peuvent pas l'exécuter ?!

... Aussi connu comme :

# Quelle version d'OpenGL dois-je utiliser ?

En fait, je ne recommande pas d'utiliser OpenGL 3 ou supérieur pour une application. Je l'utilise dans les tutoriels, car c'est la méthode propre pour apprendre OpenGL, sans tous les trucs dépréciés et, car une fois que vous connaissez OpenGL 3.3, l'utilisation d'OpenGL 2.1 est immédiate.

Ce que je recommande :

* Apprend OpenGL 3.3 afin de connaître la « bonne façon »
* Définis un matériel cible pour ton application. Par exemple, elle nécessite les FBO et le GLSL
* Utilise GLEW pour charger les extensions. Au démarrage, refuse tous les matériels qui n'ont pas le niveau de fonctionnalité requis.
* A partir de maintenant, tu peux coder presque comme si tu étais avec OpenGL 3.3, avec juste quelques changements mineurs.
* Si tu veux vraiment gérer les matériels plus anciens/moins chers, tu peux toujours les gérer en désactivant les effets qui nécessite les FBO, par exemple.

Il y a une vrai situation où tu peux utiliser une version très récente, disons OpenGL 4.2 : tu es un étudiant diplômé faisant de la recherche, tu as vraiment besoin d'une fonctionnalité récente et tu ne te soucies pas de la compatibilité, car ton logiciel ne sera jamais exécuté en dehors de ton laboratoire. Dans ce cas, ne perd pas de temps et utilise directement la version la plus récente d'OpenGL que ton matériel supporte.

# Où télécharger OpenGL 3 ?

Tu ne le télécharges pas.

Sur Windows, par exemple, tu as seulement opengl32.dll, qui est seulement OpenGL 1.1. MAIS il y a une fonction, *wglGetProcAddress()*, qui permet de récupérer les fonctions qui ne sont pas implémentées directement dans opengl32.dll, mais qui sont disponibles dans le pilote.

GLEW appelle *wglGetProcAddress* sur tous les symboles nécessaires et les rend disponibles. (tu peux le faire toi-même, mais c'est extrêmement ennuyeux). GLEW déclare aussi des constantes qui n'existait pas dix ans auparavant, comme, GL_VERTEX_ATTRIB_ARRAY_DIVISOR_ARB.

Donc, assure-toi que ton GPU supporte la dernière version nécessaire, utilise GLEW et tu es prêt.

# Pourquoi crée-t-on un VAO dans chaque tutoriel, mais on ne l'utilise jamais ?

Faux. Il est lié, donc en réalité, il est utilisé durant toute l'exécution.

Les VAO sont des abstractions de VBO. Ils se souviennent quel tampon est lié à quel attribut et une multitude d'autres choses. Ils réduisent le nombre d'appels OpenGL avant glDrawArrays/Elements(). Depuis OpenGL 3 Core, ils sont obligatoires, mais tu peux en utiliser seulement un seul et le modifier une fois pour toute (c'est ce qui est fait dans ce tutoriel).

Les VAO peuvent être source de confusion pour ces tutoriels pour débutant et il n'y a pas d'équivalant en OpenGL 2. De plus le gain de performance n'est pas très visible. Si tu es intéressés dans les VAO, jete un œil au wiki d'OpenGL. Cela peut légèrement simplifier ton application et améliorer légèrement les performances, mais ce n'est pas toujours le cas.

# J'ai une erreur « Impossible de démarrer le programme ALL_BUILD »

ALL_BUILD n'est qu'un projet générés par CMake pour compiler tout les autres projets ; ce n'est pas un vrai programme.

Comme indiqué dans le premier tutoriel, tu dois sélectionner le projet que tu souhaites exécuter en effectuant un clic droit sur un projet (à partir de Visual Studio) et sélectionner « Définir comme projet de démarrage », comme ceci :

![]({{site.baseurl}}/assets/images/faq/StartupProject.png)

# J'obtiens un message à propos du répertoire de travail et le programme plante.

Tu dois démarrer le programme à partir des dossiers tutorial01_first_window/, tutorial02_red_triangle/, etc. Si tu démarres le programme à partir de l'IDE, tu dois le configurer pour qu'il fasse ainsi.

Lis le premier tutoriel pour avoir plus de détails.
