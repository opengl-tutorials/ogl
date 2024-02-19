---
layout: page
status: publish
published: true
title: Гарні інструменти та посилання
date: '2011-05-11 20:31:21 +0200'
date_gmt: '2011-05-11 20:31:21 +0200'
categories: []
order: 30
tags: []
language: uk
---

# Документація



## Посилання OpenGL


* [OpenGL Quick Reference PDF](http://www.opengl.org/sdk/docs/reference_card/opengl45-reference-card.pdf)
* [OpenGL 4.5 Reference Pages](http://www.opengl.org/sdk/docs/man4/)
* [Специфікація OpenGL 4.5 (Core Profile)](https://www.khronos.org/registry/OpenGL/specs/gl/glspec45.core.pdf). Важке для читання.
* [Специфікація GLSL](https://www.khronos.org/registry/OpenGL/specs/gl/GLSLangSpec.4.50.pdf)
* [Список всіх розширень та актуальні характеристики](http://www.opengl.org/registry/) Якщо Ваша відеокарта відносно нова, більшість з цього доступно через GLEW.


## Інші туторіали


* [ogldev](http://ogldev.atspace.co.uk/index.html) Гарний і ретельний туторіал
* [NeHe ](http://nehe.gamedev.net/) Детальний туторіал та ресурси по OpenGL 1.1. В основному все застаріло, але можна знайти цікаві речі.


## Книги


* [Real-time Rendering 3](http://www.realtimerendering.com/). Фантастична книга для вивчення високорівневих концепцій.
* [GPU Pro book series](http://gpupro.blogspot.fr/). Детальні пояснення певних алгоритмів.

## Інше


* [A trip trough the graphic pipeline](http://fgiesen.wordpress.com/2011/07/09/a-trip-through-the-graphics-pipeline-2011-index/) : Детальна інформація про те, як працює драйвер та відеокарта насправді. Фантастичне джерело інформації. Рекомендовано.
* [Unity stats](https://hwstats.unity3d.com/)
* [Extensions stats](http://gpuinfo.org/)


# Інструменти для налагодження


* [NVidia Parallel NSight](http://developer.nvidia.com/nvidia-parallel-nsight) Дивовижний інструмент, який дає доступ до дуже детальних даних для профайлера. Рекомендується. Тільки для Visual Studio + Nvidia. Це те, що я використовую найбільше.
* [GLIntercept ](http://glintercept.nutty.org/) Генерує вебсторінку з списком OpenGL команд, кодом шейдерів, вмістом зображень, фреймбуферів. Трохи заскладний для освоєння, та дуже точний і корисний.
* [gdebugger](http://www.gremedy.com/) профайлер


# Бібліотеки


## Вікна та різноманітне

* [GLFW ](http://www.glfw.org/), ми це використовуємо
* GLUT, найстаріше, не підтримується, жахлива ліцензія, не рекомендується.
* [FreeGlut](http://freeglut.sourceforge.net/), те саме API, але з відкритим кодом.
* [SDL](http://www.libsdl.org/) Я думаю, що тут трішки все дико, та деякі люди це люблять.
* [SFML](http://www.sfml-dev.org/index-fr.php). Включає кавоварку, пральну машину і мобільний телефон.

## Завантаження розширень

Обережно, більшість бібліотек для завантаження розширень погано працюють з OpenGL 3+ Core. Насправді, я зміг заставити лише GLEW працювати, дещо змінивши код.

Якщо не впевнені, використовуйте GLEW, яка є в коді на сайті.

* [GLEW ](http://glew.sourceforge.net/), це ми використовуємо
* [GLEE ](http://elf-stone.com/glee.php) Я чув, що ця непогана
* [gl3w ](https://github.com/skaslev/gl3w/wiki). Скрипт на Python, що генерує C++ файл.

## Математичні бібліотеки

* [GLM](http://glm.g-truc.net/), цю ми використовуємо. Добре зроблена. Пряма сумісність з OpenGl та CUDA.
* [Bullet's Vectormath](http://bulletphysics.com/Bullet/BulletFull/) Ніколи не використовував, та здається, вона використовує SIMD (а це значить швидше, навіть якщо Ви не часто робите великі обчислення на CPU)
* [Boost.ublas ](http://www.boost.org/). Дуже важка. Я не рекомендую її для OpenGL.
* [MathFu](https://google.github.io/mathfu/) математична бібліотека від Google з SIMD оптимізаціями.

## Завантаження зображень

* [stbimage](http://nothings.org/) Один сі файл до Вашого проекту і можна завантажувати jpeg, bmp та png файли !!!
* [SOIL ](http://www.lonesock.net/soil.html) Я рекомендую цю бібліотеку. Основана на stbimage, надає зручні функції для використання з OpenGL та DDS.
* [DevIL](http://openil.sourceforge.net/) Бібліотека для завантаження зображень все в одному.
* [FreeImage](http://freeimage.sourceforge.net/) ... іще одна
* [Boost.GIL](http://www.boost.org/) Велика і громіздка, не вміє jpg.
* libjpg Типова бібліотека для завантаження jpg. Дещо складна для використання, та в інтернеті є достатньо прикладів.
* libpng те саме для png.

## Завантаження статичних об'єктів

* [ASSIMP ](http://assimp.sourceforge.net/)

## Завантаження об'єктів поділених на частини (з'єданних)

* [Cal3D](http://gna.org/projects/cal3d/) Завантажувач об'єктів Quake III чи Quake IV


## Фізика


* [Bullet](http://bulletphysics.org/wordpress/) З відкритим кодом, використовується багатьма іграми і навіть фільмами.
* [Newton](http://newtondynamics.com/forum/newton.php) Безкоштовне, також дуже хороше.
* [ODE](http://www.ode.org/). Старе та нестабільне, уникайте.
* PhysX
* Havok (дорого)

