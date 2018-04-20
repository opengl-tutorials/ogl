---
layout: page
status: publish
published: true
title: Математическая шпаргалка
date: '2011-05-11 20:04:48 +0200'
date_gmt: '2011-05-11 20:04:48 +0200'
categories: []
order: 20
tags: []
language: ru
---

# Тригонометрия


## Пи

const float pi = 3.14159265f; // на самом деле бесконечное число цифр

## Косинус и синус

<img class="alignnone" title="Sine_cosine_one_period" src="http://upload.wikimedia.org/wikipedia/commons/thumb/7/71/Sine_cosine_one_period.svg/600px-Sine_cosine_one_period.svg.png" alt="" width="600" height="240" />
*(Источник: http://commons.wikimedia.org/wiki/User:Geek3 , под лицензией GNU Free Documentation License )*

## Единичная окружность

![]({{site.baseurl}}/assets/images/math-cheatsheet/UnitCircle.png)

*( Изменено на основе http://en.wikipedia.org/wiki/User:Gustavb под лицензией Crative Commons 3.0 )*
t - угол в радианах.

0 радиан = 0 градусов

180 градусов = Pi радиан

360 градусов ( полный круг ) = 2*Pi радиан

90 градусов = Pi/2 радиан

# Вектора

ВСЕГДА необходимо знать в каких координатах ваш вектор. Подробнее смотрите в разделе 3.

## Однородные координаты

Трёхмерный вектор представляется как (x,y,z), но однородный трёхмерный вектор - (x,y,z,w).

* w=0 : это направление
* w=1 : это позиция
* иначе : все еще может быть допустимым, но вам лучше знать, что вы делаете.

Вы можете только перемножать матрицу 4x4 с однородным вектором.

## Длина

Как и декартово растояние: sqrt( x&sup2; + y&sup2; + z&sup2; ). w не учитывается.

## Векторное произведение

![]({{site.baseurl}}/assets/images/math-cheatsheet/Right_hand_rule_cross_product.png)

*( Изменено на основе http://en.wikipedia.org/wiki/User:Acdx , прежнее изображение под лицензией Creative Commons 3.0 )*

X обозначет вектороное произведение. длина( a x b ) == длина(a) * длина(b) * sin(&theta;), поэтому вы можете нормализовать (normalize()) результат.

## Скалярное произведение


##![]({{site.baseurl}}/assets/images/math-cheatsheet/DotProduct.png)


*( Источник: http://en.wikipedia.org/wiki/File:Dot_Product.svg )*
A.B = длина(A)*cos(Theta) , но, скорее всего, вычисляется как A.x*B.x +A.y*B.y +A.z*B.z

## Сложение и вычитание

покомпонентно :

``` cpp
res.x = A.x + B.x
res.y = A.y + B.y
...
```

## Multiplication

покомпонентно :

``` cpp
res.x = A.x * B.x
res.y = A.y * B.y
...
```

## Нормализация

Разделите вектор на его длину:

``` cpp
normalizedVector = vec * ( 1.0f / vec.length() )
```

# Матрицы


## Умножение Матрица-Матрица

пример для матрицы переноса:

![]({{site.baseurl}}/assets/images/math-cheatsheet/translationExamplePosition1.png)


 

## Умножение Матрица-Вектор

![]({{site.baseurl}}/assets/images/math-cheatsheet/MatrixXVect.gif)


# Обычные преобразования

![]({{site.baseurl}}/assets/images/math-cheatsheet/MVP.png)


... но в ваших шейдерах вы также можете представлять свои векторы в касательном пространстве. И в пространстве изображений, когда вы делаете пост-эффекты.

res.x = A.x + B.x
