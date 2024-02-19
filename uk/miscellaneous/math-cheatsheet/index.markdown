---
layout: page
status: publish
published: true
title: Шпаргалка з математики
date: '2011-05-11 20:04:48 +0200'
date_gmt: '2011-05-11 20:04:48 +0200'
categories: []
order: 20
tags: []
print: true
language: uk
---

# Тригонометрія


## Pi

const float pi = 3.14159265f; // але в реальності тут безкінечна послідовність

## Косинус та синус

<img class="alignnone" title="Sine_cosine_one_period" src="http://upload.wikimedia.org/wikipedia/commons/thumb/7/71/Sine_cosine_one_period.svg/600px-Sine_cosine_one_period.svg.png" alt="" width="600" height="240" />
*(З http://commons.wikimedia.org/wiki/User:Geek3 , ліцензія GNU Free Documentation)*

## Одиничне коло

![]({{site.baseurl}}/assets/images/math-cheatsheet/UnitCircle.png)

*( Це модифіковане зображення http://en.wikipedia.org/wiki/User:Gustavb оригінальне зображення під ліцензією  Crative Commons 3.0 )*

t це кут в радіанах.

0 радіан = 0 градусів

180 градусів = Pi радіан

360 градусів ( повне коло ) = 2*Pi радіан

90 градусів = Pi/2 радіан

# Вектора

Завжди знайте в яких координатах ваш вектор. Дивіться секцію 3 для деталей.

## Однорідні координати

3D вектор - це (x,y,z), але 3D вектор з однорідними координатами - це (x,y,z,w).

* w=0 : це напрямок
* w=1 : це позиція 
* щось інше : може бути коректним, але ви знаєте краще, що ви робите

Ви можете множити матрицю 4х4 тільки з вектором з однорідними координатами.

## Довжина

Просто як декартова відстань : sqrt( x&sup2; + y&sup2; + z&sup2; ). w не рахується.

## Векторний добуток (Cross product)

![]({{site.baseurl}}/assets/images/math-cheatsheet/Right_hand_rule_cross_product.png)

*( Це модифіковане зображення http://en.wikipedia.org/wiki/User:Acdx , оригінальне зображення під ліцензією Creative Commons 3.0 )*

Символ Х використовується для позначення векторного добутку. `length( a x b ) == length(a) * length(b) * sin(&theta;)`, тому можливо ви захочете викликати normalize() для результату.

## Скалярний добуток (Dot product)


##![]({{site.baseurl}}/assets/images/math-cheatsheet/DotProduct.png)


*( З http://en.wikipedia.org/wiki/File:Dot_Product.svg )*

`A.B = length(A)*cos(Theta)` , але зазвичай розраховується за формулою `A.x*B.x +A.y*B.y +A.z*B.z`

## Додавання та віднімання

кодом :

``` cpp
res.x = A.x + B.x
res.y = A.y + B.y
...
```

## Множення

кодом :

``` cpp
res.x = A.x * B.x
res.y = A.y * B.y
...
```

## Нормалізація

Потрібно розділити вектор на його довжину :

``` cpp
normalizedVector = vec * ( 1.0f / vec.length() )
```

# Матриця


## Множення матриці на матрицю

Приклад переміщення (зсуву) матриці:

![]({{site.baseurl}}/assets/images/math-cheatsheet/translationExamplePosition1.png)


 

## Множення матриці на вектор

![]({{site.baseurl}}/assets/images/math-cheatsheet/MatrixXVect.gif)


# Звичайні трансформації

![]({{site.baseurl}}/assets/images/math-cheatsheet/MVP.png)


... але в шейдерах, ви можете використовувати вектори в дотичному просторі. А для обробки зображень - в просторі зображення.
'res.x = A.x + B.x'
