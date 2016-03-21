---
layout: page
status: publish
published: true
title: Un compteur de FPS
date: '2015-11-21 17:14:22 +0100'
categories: []
order: 40
tags: []
language: fr
---

Dans le monde des graphismes en temps réel, il est important de garder un œil sur les performances. Une bonne pratique est de déterminer un nombre de FPS comme objectif (habituellement 60 ou 30) et faire tout son possible pour s'y tenir.

Un compteur de FPS ressemble à cela :

{% highlight text linenos %}
 double lastTime = glfwGetTime();
 int nbFrames = 0;

 do{

     // Measure speed
     double currentTime = glfwGetTime();
     nbFrames++;
     if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1 sec ago
         // printf and reset timer
         printf("%f ms/frame\n", 1000.0/double(nbFrames));
         nbFrames = 0;
         lastTime += 1.0;
     }

     ... rest of the main loop
```

Il y a une chose étrange dans ce code. Il affiche le temps, en millisecondes, nécessaire pour afficher une image (la moyenne sur une seconde) au lieu du nombre d'images dessinées durant la dernière seconde.

En fait, c'est généralement **beaucoup mieux**. Ne fais **pas** confiance aux FPS. FramePerSecond = 1/SecondPerFrame, ce qui est une proportionnelle inverse et les humains sont nuls pour comprendre ce genre de proportionnelle. Prend un exemple : tu écris une superbe fonction de rendu qui fonctionne à 1000 FPS (1ms/image), mais tu oublies un petit calcul dans le shader, qui ajoute un coût de 0,1 ms. Et bam, 1/0.0011 = 900, tu viens de perdre 100 FPS. Moralité : **n'utilise jamais les FPS pour des analyses de performances**.

Si tu prévois de faire un jeu fonctionnant à 60 FPS, ton objectif sera 16,6666 ms ; si tu prévois de faire un jeu fonctionnant à 30 FPS, votre objectif sera 33,3333 ms. C'est tout ce que tu dois savoir.

Ce code est utilisé dans tous les tutoriels à partir du neuvième : [indexation VBO]({{site.baseurl}}/fr/intermediate-tutorials/tutorial-9-vbo-indexing/) ; regardez le fichier [tutorial09_vbo_indexing/tutorial09.cpp](https://github.com/opengl-tutorials/ogl/blob/master/tutorial09_vbo_indexing/tutorial09.cpp#L142). D'autres outils pour les performances sont disponibles dans la page [Outils - débogueurs]({{site.baseurl}}/miscellaneous/useful-tools-links/#debugging-tools).
