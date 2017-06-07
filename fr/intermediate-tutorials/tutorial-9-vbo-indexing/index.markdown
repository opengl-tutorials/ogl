---
layout: tutorial
status: publish
published: true
title: 'Tutoriel 9 : indexation de VBO'
date: '2015-11-19 20:31:48 +0200'
categories: [tuto]
order: 490
tags: []
language: fr
---

* TOC
{:toc}

# Le principe de l'indexation

Jusqu'à présent, lors de la construction du VBO, on avait dupliqué les sommets à chaque fois que deux triangles partageaient un côté.

Dans ce tutoriel, on va s'initier à l'indexation, qui permet de réutiliser le même sommet encore et encore. Cela est possible grâce au buffer (tampon) d'indices.

![]({{site.baseurl}}/assets/images/tuto-9-vbo-indexing/indexing1.png)

Le tampon d'indices contient des entiers, trois pour chaque triangle dans le modèle, faisant référence aux différents tampons d'attributs (position, couleur, coordonnées UV, autres coordonnées UV, normales…). C'est un peu comme dans le fichier .OBJ, avec une grande différence : il n'y a qu'un SEUL tampon d'indices. Cela signifie que pour qu'un sommet soit partagé entre deux triangles, tous les attributs doivent être les mêmes.

# Partagé ou séparé ?

On va prendre en exemple les normales. Dans ce schéma, l'artiste qui a créé ces deux triangles voulait certainement qu'ils représentent une surface lisse. On peut donc fusionner les normales des deux triangles en une normale d'un seul sommet. Pour des soucis de visualisation, j'ai ajouté une ligne rouge qui représente l'aspect de la surface lisse.

![]({{site.baseurl}}/assets/images/tuto-9-vbo-indexing/goodsmooth.png)

Dans le second schéma, par contre, l'artiste a visiblement voulu une « couture », un côté pointu. Mais si on fusionne les normales, cela signifie que le shader va effectuer un adoucissement, comme d'habitude, et créer un aspect plus doux, comme dans le cas précédent :

![]({{site.baseurl}}/assets/images/tuto-9-vbo-indexing/badmooth.png)

Donc, dans ce cas il est préférable d'avoir deux normales distinctes, une pour chaque sommet. La seule façon de faire cela en OpenGL est de dupliquer entièrement le sommet, avec son ensemble d'attributs :

![]({{site.baseurl}}/assets/images/tuto-9-vbo-indexing/spiky.png)

# VBO indexé en OpenGL

C'est très simple d'utiliser l'indexation. Premièrement, tu vas créer un tampon supplémentaire, que tu vas remplir avec les bons indices. Le code est le même qu'avant, mais maintenant c'est un ELEMENT_ARRAY_BUFFER, et non un ARRAY_BUFFER.

``` cpp
std::vector<unsigned int> indices;

// fill "indices" as needed

// Generate a buffer for the indices
 GLuint elementbuffer;
 glGenBuffers(1, &elementbuffer);
 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
 glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
```

Et pour dessiner le modèle, remplaces simplement glDrawArrays par :

``` cpp
// Index buffer
 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

 // Draw the triangles !
 glDrawElements(
     GL_TRIANGLES,      // mode
     indices.size(),    // count
     GL_UNSIGNED_INT,   // type
     (void*)0           // element array buffer offset
 );
```

>Il est préférable d'utiliser des « unsigned short » que des « unsigned int », car cela utilise moins de mémoire et du coup accélère le programme.

# Remplir le buffer (tampon) d'indices

On a maintenant un problème. Comme je l'ai dit avant, OpenGL ne peut utiliser qu'un seul tampon d'indices, alors que le format OBJ (ainsi que d'autres formats de fichier 3D populaires comme Collada) utilise un tampon d'indices par attribut. Cela signifie que d'une façon ou d'une autre, on doit convertir N tampons d'indices en un.

L'algorithme pour ce faire est le suivant :

```

Pour chaque sommet en entrée
    Essayer de trouver un sommet similaire ( = identique pour tous les attributs) parmi ceux déjà en sortie
    Si trouvé : 
        Un sommet similaire est déjà dans le VBO, on l'utilise !
    Si non trouvé : 
        Aucun sommet similaire trouvé, ajouter le au VBO
```

Le code C++ peut être trouvé dans le fichier common/vboindexer.cpp. Il est intensément commenté, donc si tu comprends l'algorithme ci-dessus, ça devrait aller.

Le critère pour la similarité des sommets est que la position, la normale et les coordonnées UV doivent êtres identiques. Tu devras l'adapter si tu ajoutes plus d'attributs.

La recherche d'un sommet similaire est effectuée d'une manière linéaire pour garder l'algorithme simple. Une std::map serait plus appropriée.

# Extra : le compteur de FPS

Ce n'est pas directement lié à l'indexation, mais c'est une bonne occasion de jeter un œil au compteur de FPS car on peut possiblement voir une amélioration de la vitesse grâce à l'indexation. D'autres outils pour les performances sont disponibles dans la page [Outils - débogueurs]({{site.baseurl}}/miscellaneous/useful-tools-links/#debugging-tools).
