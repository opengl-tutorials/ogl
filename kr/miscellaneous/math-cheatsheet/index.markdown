---
layout: page
status: publish
published: true
title: Math Cheatsheet
date: '2011-05-11 20:04:48 +0200'
date_gmt: '2011-05-11 20:04:48 +0200'
categories: []
order: 20
tags: []
---

# Trigonometry


## Pi

const float pi = 3.14159265f; // but an infinity of digits in reality

## Cosinus & Sinus

<img class="alignnone" title="Sine_cosine_one_period" src="http://upload.wikimedia.org/wikipedia/commons/thumb/7/71/Sine_cosine_one_period.svg/600px-Sine_cosine_one_period.svg.png" alt="" width="600" height="240" />
*(From http://commons.wikimedia.org/wiki/User:Geek3 , under GNU Free Documentation License )*

## Unit circle

![]({{site.baseurl}}/assets/images/math-cheatsheet/UnitCircle.png)

*( Modified from http://en.wikipedia.org/wiki/User:Gustavb under Crative Commons 3.0 )*t is an angle in radians.

0 radians = 0 degrees

180 degrees = Pi radians

360 degrees ( full circle ) = 2*Pi radians

90 degrees = Pi/2 radians

# Vectors

ALWAYS know in which coordinates your vector is. See section 3 for details.

## Homogeneous coordinates

A 3D vector is (x,y,z), but a homogeneous 3D vector is (x,y,z,w).

* w=0 : it's a direction
* w=1 : it's a position
* else : it may still be correct, but you'd better know what you're doing.

You can only multiply a 4x4 matrix with a homogeneous vector.

## Length

Just like cartesian distance : sqrt( x&sup2; + y&sup2; + z&sup2; ). w doesn't count.

## Cross product

![]({{site.baseurl}}/assets/images/math-cheatsheet/Right_hand_rule_cross_product.png)

*( Modified from http://en.wikipedia.org/wiki/User:Acdx , former image under Creative Commons 3.0 )*The X is the notation for the cross product. length( a x b ) == length(a) * length(b) * sin(&theta;), so you may want to normalize() the result.

## Dot product


##![]({{site.baseurl}}/assets/images/math-cheatsheet/DotProduct.png)


*( from http://en.wikipedia.org/wiki/File:Dot_Product.svg )*A.B = length(A)*cos(Theta) , but most likely computed as A.x*B.x +A.y*B.y +A.z*B.z

## Addition and substraction

compontent-wise :

``` cpp
res.x = A.x + B.x
res.y = A.y + B.y
...
```

## Multiplication

compontent-wise :

``` cpp
res.x = A.x * B.x
res.y = A.y * B.y
...
```

## Normalization

Divide the vector by its length :

``` cpp
normalizedVector = vec * ( 1.0f / vec.length() )
```

# Matrices


## Matrix-Matrix multiplication

example for a translation matrix :

![]({{site.baseurl}}/assets/images/math-cheatsheet/translationExamplePosition1.png)


 

## Matrix-Vector multiplication

![]({{site.baseurl}}/assets/images/math-cheatsheet/MatrixXVect.gif)


# Usual Transformations

![]({{site.baseurl}}/assets/images/math-cheatsheet/MVP.png)


... but in your shaders, you can also represent your vectors in tangent space. And in image-space when you do post-effects.

res.x = A.x + B.x
