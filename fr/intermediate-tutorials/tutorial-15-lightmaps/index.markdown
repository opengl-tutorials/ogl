---
layout: page
status: publish
published: true
title: 'Tutoriel 15 : Lightmaps'
date: '2015-11-21 09:13:32 +0200'
categories: [tuto]
order: 70
tags: []
language: fr
---

#Introduction

J'aurais bien traduit *lightmap* mais en programmation graphique tout le monde utilise ce terme. On pourrait peut être dire *Cartes de lumière* mais ca serait une traduction artificielle.

Ce tutoriel est un tutoriel vidéo seulement. Il n'introduit aucune nouvelle technique/syntaxe spécifique à OpenGL, mais te présente comment utiliser les techniques que tu connais déjà pour créer des ombres de grande qualité.

Tu vas voir comment créer un monde simple dans Blender et préparer des textures de lumière afin que tu puisses les utiliser dans ton application.

![]({{site.baseurl}}/assets/images/tuto-15-lightmaps/lighmappedroom.png)

Aucune connaissance de Blender n'est nécessaire. Je vais expliquer tous les raccourcis clavier et tout ce que je fais.

#Une note sur les textures de lumière

Les lightmaps sont précalculées. Elles sont gravées dans le marbre. Cela signifie qu'elles sont complètement statiques, tu ne peux pas décider de déplacer une lumière durant l'exécution. Même pas de la supprimer.

Mais cela peut toujours être utile pour la lumière du soleil, ou encore, dans les scènes d'intérieur où on ne peut pas casser d'ampoules. Mirror Edge, publiée en 2009, les utilisent intensivement, que ce soit en extérieur ou en intérieur.

De plus, c'est très simple à mettre en place et tu ne peux rien faire de moins couteux.

#La vidéo

C'est une vidéo en 1024 x 768p, utilise le mode HD ...

<iframe src="http://player.vimeo.com/video/24359223?title=0&byline=0&portrait=0" frameborder="0" width="800" height="450"></iframe>

#Appendice

Lors du rendu en OpenGL, tu peux remarquer quelques corruptions (ici exagérées) :

![]({{site.baseurl}}/assets/images/tuto-15-lightmaps/positivebias.png)

Cela est dû aux MIP maps, qui mélangent les texels ensemble lorsqu'ils sont visualisés de loin. Les pixels noirs provenant du fond de la texture sont mélangés avec les bonnes parties de la texture de lumière. Pour éviter cela, il y a quelques petits ajustements que tu peux faire :

* Tu peux demander à Blender de générer une marge autour des limites des coordonnées UV. Cela est accessible à travers le paramètre « margin » dans le panneau « bake ». Pour de bons résultats, tu peux aller jusqu'à une marge de 20 pixels ;
* Tu peux utiliser un biais dans accèder à la texture :
  {% highlight glsl linenos cssclass=highlightglslfs %}
  color = texture( myTextureSampler, UV, -2.0 ).rgb;
  {% endhighlight %}
  -2 est LE biais. Tu peux expérimenter avec cette valeur. La capture d'écran ci-dessus a été effectuée avec un biais de +2, ce qui signifie que OpenGL va sélectionner deux MIP maps au-dessus de celle qu'il aurait choisi (donc 16 fois plus petites, provoquant les corruptions)
* Tu peux remplir le fond noir dans une étape de post-process. Je vais poster plus tard plus d'information là-dessus.

