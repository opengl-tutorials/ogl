---
layout: page
status: publish
published: true
title: Math Cheatsheet
date: '2015-11-22 11:38:28 +0200'
categories: []
order: 20
tags: []
language: fr
---

# Trigonométrie

## Pi

const float pi = 3.14159265f; // avec une infinité de nombre après

## Cosinus & Sinus

![](http://upload.wikimedia.org/wikipedia/commons/thumb/7/71/Sine_cosine_one_period.svg/600px-Sine_cosine_one_period.svg.png")
*(Provient de [http://commons.wikimedia.org/wiki/User:Geek3](http://commons.wikimedia.org/wiki/User:Geek3) , sous la licence GNU Free Documentation)*

## Cercle unitaire

![]({{site.baseurl}}/assets/images/math-cheatsheet/UnitCircle.png)

*( Modifié depuis [http://en.wikipedia.org/wiki/User:Gustavb](http://en.wikipedia.org/wiki/User:Gustavb), licence: Creative Commons 3.0 )*t est un angle en radian.

0 radians = 0 degrés

180 degrés = Pi radians

360 degrés (cercle complêt) = 2*Pi radians

90 degrés = Pi/2 radians

# Vecteurs

Fais TOUJOURS attention au repère dans lesquels tes vecteurs sont. Regarde la section 3 pour plus de détails.

## Coordonées homogène 

Un vecteur 3D est représenté par : (x, y, z), mais un vecteur 3D en coordonnées homogènes est représenté par : (x, y, z, w) :

* w=0 : Le vecteur représente une direction
* w=1 : Le vecteur représente une position
* w=qqch d'autre : C'est peut être encore correct, mais t'as plutôt intérêt de savoir ce que tu fais.

On ne peut multiplier une matrice 4*4 qu'avec un vecteur homogène.

## Longueur

Comme pour une distance cartésienne : racine carrée(x&sup2; + y&sup2; + z&sup2;). w n'est pas pris en compte.

## Produit en croix

![]({{site.baseurl}}/assets/images/math-cheatsheet/Right_hand_rule_cross_product.png)

*( Modifié depuis [http://en.wikipedia.org/wiki/User:Acdx](http://en.wikipedia.org/wiki/User:Acdx) , image sous la license: Creative Commons 3.0 )*Le X est la notation du produit en croix. longueur( a x b ) == longueur(a) * longueur(b) * sin(&theta;), donc tu voudras peut être normaliser le résultat

## Produit scalaire (Dot product en anglais)

##![]({{site.baseurl}}/assets/images/math-cheatsheet/DotProduct.png)


*( Depuis [http://en.wikipedia.org/wiki/File:Dot_Product.svg](http://en.wikipedia.org/wiki/File:Dot_Product.svg) )*A.B = longueur(A)*cos(&theta;) , mais on peut le calculer comme ça: A.x*B.x +A.y*B.y +A.z*B.z

## Addition et soustraction

Pour chaque composante (x, y, ...) :
```

res.x = A.x + B.x
res.y = A.y + B.y
...
```

## Multiplication

Pour chaque composante (x, y, ...) :
```

res.x = A.x * B.x
res.y = A.y * B.y
...
```

## Normalisation

On divise le vecteur par sa longueur
```

normalizedVector = vec * ( 1.0f / vec.length() )
```

# Matrices

## Multiplication Matrice à Matrices

Exemple pour une matrice de translation :

![]({{site.baseurl}}/assets/images/math-cheatsheet/translationExamplePosition1.png)

## Multiplication matrice à vecteur

![]({{site.baseurl}}/assets/images/math-cheatsheet/MatrixXVect.gif)

# Transformations habituelles

![]({{site.baseurl}}/assets/images/math-cheatsheet/MVP.png)

... mais dans tes shaders, tu peux aussi représenter tes vecteurs dans le repère tangent. Et aussi dans le repère image quand tu fais des effets après rendu.

res.x = A.x + B.x
