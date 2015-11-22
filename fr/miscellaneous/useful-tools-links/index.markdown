---
layout: page
status: publish
published: true
title: Useful Tools & Links
date: '2015-11-22 12:05:23 +0200'
categories: []
order: 30
tags: []
language: fr
---

#Documentation

##OpenGL references

* [OpenGL 3.2 Références rapides](http://www.khronos.org/files/opengl-quick-reference-card.pdf)
* [OpenGL 4.1 Références rapides](http://www.opengl.org/sdk/docs/man4/)
* [OpenGL 4.0 Spécification](http://www.opengl.org/registry/doc/glspec40.core.20100311.pdf). Pas facile à lire !
* [GLSL Spécifications](http://www.opengl.org/registry/doc/GLSLangSpec.4.10.6.clean.pdf)
* [Liste de toutes les extensions](http://www.opengl.org/registry/) Si ton GPU est assez récent, la pluspart seront disponible via GLEW

##Autre tutoriels

* [http://arcsynthesis.org/gltut/](http://arcsynthesis.org/gltut/) Un tutoriel complêt ; Courbe d'apprentissage élevée
* [ogldev](http://ogldev.atspace.co.uk/index.html) Notre principale compétiteur :)
* [http://openglbook.com/](http://openglbook.com/) Quelques autres tutoriels pour débutant
* [NeHe](http://nehe.gamedev.net/) Plein de tutoriel 1.1, avec quelques points intéressant, mais pour la pluspart déprécié

##Livres

* [Real-time Rendering 3](http://www.realtimerendering.com/)
* [OpenGL SuperBible](http://www.openglsuperbible.com/)
* [More Opengl Programming](http://glbook.gamedev.net/GLBOOK/glbook.gamedev.net/moglgp/index.html)

##Autres

* [Un voyage à travers le pipeline graphique](http://fgiesen.wordpress.com/2011/07/09/a-trip-through-the-graphics-pipeline-2011-index/) : Des informations en profondeur à propos des drivers et des cartes graphiques. et comment ils fonctionnent réellement. C'est vraiment une très bonne source d'info. Très recommandé !
* [Statistiques d'Unity](http://stats.unity3d.com/web/gpu.html) : Des statistiques sur les cartes graphiques actuellement dans le marché.
* [Plus de statistiques](http://feedback.wildfiregames.com/report/opengl/) : Plus précises, mais avec des infos plus vieilles.

#Outils de débogage

* [glslDevil](http://cumbia.informatik.uni-stuttgart.de/glsldevil/) : un fantastique débogueur GLSL - lorsqu'il fonctionne. Même si le site Web est souvent hors ligne.
* [GLIntercept](http://glintercept.nutty.org/) : génère une page Web avec la liste des commandes OpenGL exécutées. Affiche le code des shaders, le contenu des images, le contenu des buffers d'image, etc.
* [gdebugger](http://www.gremedy.com/) : un profileur.
* [NVidia Parallel NSight](http://developer.nvidia.com/nvidia-parallel-nsight) : un outil merveilleux qui donne accès à des informations très précises sur les performances. Hautement recommandé. Visual Studio + Nvidia seulement.

#Bibliothèques

##Fenêtrage et divers

* [GLFW ](http://www.glfw.org/), celui que l'on utilise.
* GLUT, le plus vieux. Pas maintenu, licence horrible. Non recommandé.
* [FreeGlut](http://freeglut.sourceforge.net/), même bibliothèque, mais Open Source.
* [SDL](http://www.libsdl.org/), je pense que celle-là est étrange mais certains l'aiment.
* [SFML](http://www.sfml-dev.org/index-fr.php), inclut une machine à café, une machine à laver et un téléphone portable.

##Chargement des extensions

* [GLEW](http://glew.sourceforge.net/), celle que l'on utilise.
* [GLEE](http://elf-stone.com/glee.php), j'ai entendu dire qu'elle n'était pas mauvaise non plus.
* [gl3w](https://github.com/skaslev/gl3w/wiki), un script Python qui génère un fichier C++.

##Bibliothèques mathématiques

* [GLM](http://glm.g-truc.net/), celle que l'on utilise. Très complète. Directement compatible avec OpenGL et CUDA.
* [Vectormath de Bullet](http://bulletphysics.com/Bullet/BulletFull/), jamais utilisé mais elle semble être SIMD (= plus rapide, même si tu n'effectue que rarement de grands calculs sur le CPU).
* [Boost.ublas ](http://www.boost.org/), c'est très gros. Je ne la recommande pas pour OpenGL.
* [MathFu](https://google.github.io/mathfu/) Google a fait sa bibliothèque de math optimisé SIMD.

##Chargement d'images

* [stbimage](http://nothings.org/) Un simple fichier .c à inclure dans ton projet et tu peux charger les fichiers .jpeg, .bmp et .png !!!
* [SOIL](http://www.lonesock.net/soil.html)Je recommande celle-ci. Basée sur stbimage, elle fournit des fonctions pratiques pour l'utiliser avec OpenGL, ainsi qu'un chargeur de fichiers DDS.
* [DevIL](http://openil.sourceforge.net/) Une bibliothèque de chargement d'image tout en un.
* [FreeImage](http://freeimage.sourceforge.net/) ... et encore une autre.
* [Boost.GIL](http://www.boost.org/) Grosse et encombrante, ne charge pas les .jpg.
* libjpg La bibliothèque classique pour charger les .jpg. Assez difficile à utiliser, mais de nombreux exemples sur le net.
* libpng Pareil.

##Chargement d'objets statiques

* [ASSIMP ](http://assimp.sourceforge.net/)

##Chargement d'objets articulés et autres

* N'importe quel chargeur de fichier Quake III et Quake IV.
* [Cal3D](http://gna.org/projects/cal3d/)

##Physique

* [Bullet](http://bulletphysics.org/wordpress/) Open Source, utilisée dans beaucoup de jeux et même des films.
* [Newton](http://newtondynamics.com/forum/newton.php) Gratuite et aussi très bonne.
* [ODE](http://www.ode.org/). Vieille et instable. À éviter.
* [PhysX](http://www.geforce.co.uk/hardware/technology/physx)
* [Havok](http://www.havok.com/physics/) (chère)
