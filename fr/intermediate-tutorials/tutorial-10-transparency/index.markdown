---
layout: page
status: publish
published: true
title: 'Tutoriel 10 : la transparence'
date: '2015-11-19 20:56:26 +0200'
categories: [tuto]
order: 20
tags: []
language: fr
---

# La canal alpha

Le concept du canal alpha est très simple. À la place d'écrire un résultat en RGB, on écris un résultat en RGBA :

``` glsl
// Données de sorties : c'est maintenant un vec4 
out vec4 color;
```
{: .highlightglslfs }

Les trois premières composantes sont toujours accessibles avec *.xyz* (ou *.rgb*), tandis que la dernière est accessible avec *.a* :

``` glsl
color.a = 0.3;
```
{: .highlightglslfs }

Contre toute logique, alpha = opacité, donc alpha = 1 signifie complètement opaque alors que alpha = 0 signifie complètement transparent.

Ici, on a simplement codé en dur le canal alpha à 0.3, mais tu préféreras sûrement utiliser une variable uniforme ou la lire à partir d'une texture RGBA (le format DDS supporte le canal alpha).

Voici le résultat. Assures-toi de désactiver le « backface culling » (suppression des faces arrières) (glDisable(GL_CULL_FACE)) car comme on peut voir à travers le modèle, on pourrait voir si on ne dessine pas la face « arrière ».

![]({{site.baseurl}}/assets/images/tuto-10-transparency/transparencyok.png)

# L'ordre est important

La capture d'écran précédente paraît correcte, mais c'est uniquement car on est chanceux.

## Le problème

Ici, j'ai dessiné deux carrés ayant 50 % d'alpha, un vert et un rouge. Tu peux voir que l'ordre est important, la couleur finale donne une importante piste visuelle sur la perception de la profondeur.

![]({{site.baseurl}}/assets/images/tuto-10-transparency/transparencyorder.png)

Ce phénomène se produit aussi sur la scène. Si tu change un peu ton point de vue :

![]({{site.baseurl}}/assets/images/tuto-10-transparency/transparencybad.png)

On voit tout de suite le problème apparaitre.
En fait, c'est un problème très complexe. Tu ne vois jamais énormément de transparence dans les jeux vidéo, n'est-ce pas ?

## Solution classique

La solution classique est de trier tous les triangles transparents. Oui, TOUS les triangles transparents.

* Dessine la partie du monde opaque afin que le tampon de profondeur puisse déjà rejeter les triangles transparents cachés
* Trie les triangles transparents, du plus loin aux plus proches
* Dessine les triangles transparents

Tu peux trier ce que tu veux avec qsort (en C) ou std::sort (en C++). Je n'entrerai pas dans les détails, car...

## Mise en garde

Faire comme cela fonctionne (plus de détails dans la section suivante), mais :

* Tu vas être limité par la bande passante. En effet, chaque fragment sera écrit 10, 20 fois ou même plus. Cela est beaucoup trop pour le pauvre bus mémoire. Habituellement, le tampon de profondeur permet de rejeter assez de fragments « lointains », mais là, tu les tries explicitement, faisant que le tampon de profondeur devient totalement inutile
* Tu vas faire cela quatre fois par pixel (on utilise le 4xMSAA), sauf si tu utilises une optimisation plus intelligente
* Le tri des triangles prend du temps
* Si tu dois changer de texture, ou pire, de shader, de triangle en triangle, tu vas avoir de sérieux problèmes de performance. Ne le fait juste pas.

Une solution assez bonne est souvent de :

* Limiter à un maximum le nombre de polygones transparents
* Utiliser le même shader et la même texture pour tous les polygones transparents
* S'ils sont sensés être très différents, utilise ta texture (atlas) !
* Si tu peux éviter le tri et que ça ne soit pas trop moche, tu peux t'estimer chanceux :)

## Transparence indépendante de l'ordre

De nombreuses autres techniques sont intéressantes si ton moteur a vraiment, vraiment besoin de l'état de l'art de la transparence :

* [Le papier original 2001 Depth Peeling](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.18.9286&rep=rep1&type=pdf) : résultats parfait au pixel près, pas très rapide
* [Dual Depth Peeling](http://developer.download.nvidia.com/SDK/10/opengl/src/dual_depth_peeling/doc/DualDepthPeeling.pdf) : une petite amélioration
* De nombreux papiers sur le bucket sort utilisent un tableau de fragments ; et les tris par profondeur dans le shader
* [Démonstration d'ATI Mecha](http://fr.slideshare.net/hgruen/oit-and-indirect-illumination-using-dx11-linked-lists) : bon et rapide, mais compliqué à implémenter. Utilise une liste chaînées de fragments
* [Variation de la technique d'ATI par Cyril Crassin](http://blog.icare3d.org/2010/07/opengl-40-abuffer-v20-linked-lists-of.html) : implémentation encore plus compliquée.

> Même un jeu récent comme Little Big Planet, s'exécutant sur une console puissante, utilise **une seul** couche de transparence.

# La fonction de mélange

Afin que le code précédent fonctionne, on doit initialiser la fonction de mélange :

``` cpp
// Enable blending
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
```

Ce qui signifie :

```

nouvelle couleur dans le buffer d'écran = 
    alpha actuel dans le buffer d'écran * couleur actuelle dans le buffer d'écran + 
    (1 - alpha actuel dans le tampon d'écran) * la couleur de sortie du shader
```

Exemple de l'image ci-dessus, avec le rouge au-dessus :

``` cpp
new color = 0.5*(0,1,0) + (1-0.5)*(1,0.5,0.5); // (the red was already blended with the white background)
new color = (1, 0.75, 0.25) = the same orange
```

 
